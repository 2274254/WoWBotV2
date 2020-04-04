﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Security;
using System.Security.Permissions;
using System.Security.Policy;
using System.Text.RegularExpressions;
using System.Xml;
using Agony.Sandbox.AgonyAddon;
using Agony.SDK.CommonBot;
using AgonyLauncher;
using AgonyLauncher.Data;
using AgonyLauncher.Logger;
using AgonyLauncher.Utils;

namespace Agony.Sandbox
{
    internal class PluginDomain : MarshalByRefObject
    {
        internal static readonly Dictionary<string, Assembly> LoadedLibraries = new Dictionary<string, Assembly>();
        internal static readonly List<string> LoadedAddons = new List<string>();

        static PluginDomain()
        {
            // Listen to requried events
            AppDomain.CurrentDomain.AssemblyResolve += DomainOnAssemblyResolve;
        }

        [PermissionSet(SecurityAction.Assert, Unrestricted = true)]
        internal static PluginDomain CreateDomain(string domainName)
        {
            PluginDomain domain = null;
            try
            {
                if (string.IsNullOrEmpty(domainName))
                {
                    domainName = "Sandbox" + Guid.NewGuid().ToString("N") + "Domain";
                }

                // Initialize app AppDomainSetup
                var appDomainSetup = new AppDomainSetup
                {
                    ApplicationName = domainName,
                    ApplicationBase = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\"
                };

                // Initialize all permissions
                var permissionSet = new PermissionSet(PermissionState.None);
                permissionSet.AddPermission(new EnvironmentPermission(EnvironmentPermissionAccess.Read, "USERNAME"));
                permissionSet.AddPermission(new FileIOPermission(FileIOPermissionAccess.AllAccess, Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)));
                permissionSet.AddPermission(new FileIOPermission(FileIOPermissionAccess.AllAccess, Settings.Instance.Directories.AppDataDirectory));
                permissionSet.AddPermission(new FileIOPermission(FileIOPermissionAccess.AllAccess, Settings.Instance.Directories.LibrariesDirectory));
                permissionSet.AddPermission(new FileIOPermission(FileIOPermissionAccess.AllAccess, PathRandomizer.WrapperDllPath));
                permissionSet.AddPermission(new FileIOPermission(FileIOPermissionAccess.PathDiscovery, Path.GetFullPath(Path.Combine(Directory.GetCurrentDirectory(), "..\\..\\..\\..\\..\\..\\"))));
                permissionSet.AddPermission(new FileIOPermission(FileIOPermissionAccess.Read, Path.GetFullPath(Path.Combine(Directory.GetCurrentDirectory(), "..\\..\\..\\..\\..\\..\\"))));
                permissionSet.AddPermission(new ReflectionPermission(PermissionState.Unrestricted));
                permissionSet.AddPermission(new SecurityPermission(SecurityPermissionFlag.Execution));
                permissionSet.AddPermission(new SecurityPermission(SecurityPermissionFlag.Infrastructure));
                permissionSet.AddPermission(new SecurityPermission(SecurityPermissionFlag.RemotingConfiguration));
                permissionSet.AddPermission(new SecurityPermission(SecurityPermissionFlag.SerializationFormatter));
                permissionSet.AddPermission(new SecurityPermission(SecurityPermissionFlag.UnmanagedCode));
                permissionSet.AddPermission(new UIPermission(PermissionState.Unrestricted));
                /*permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/(\\w+)\\.lolnexus\\.com\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/(\\w+)\\.riotgames\\.com\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/(www\\.)?champion\\.gg\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/(www\\.)?Agony\\.net\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/edge\\.Agony\\.net\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/(www\\.)?leaguecraft\\.com\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/(www\\.)?lolbuilder\\.net\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/(www\\.|raw.)?github(usercontent)?\\.com\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/(www|oce|las|ru|br|lan|tr|euw|na|eune|sk2)\\.op\\.gg\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/ddragon\\.leagueoflegends\\.com\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("http?:\\/\\/strefainformatyka\\.hekko24\\.pl\\/.*")));
                permissionSet.AddPermission(new WebPermission(NetworkAccess.Connect, new Regex("https?:\\/\\/strefainformatyka\\.hekko24\\.pl\\/.*")));*/

                /*
                #if DEBUG
                // TODO: Remove once protected domain works
                var appDomain = AppDomain.CreateDomain(domainName);
                #else
                // Create the AppDomain
                var appDomain = AppDomain.CreateDomain(domainName, null, appDomainSetup, permissionSet,
                    PublicKeys.AllKeys.Concat(new[] { Assembly.GetExecutingAssembly().Evidence.GetHostEvidence<StrongName>() }).ToArray());
                #endif
                */
                var appDomain = AppDomain.CreateDomain(domainName);

                // Create a new Domain instance
                domain = (PluginDomain)Activator.CreateInstanceFrom(appDomain, Assembly.GetExecutingAssembly().Location, typeof(PluginDomain).FullName).Unwrap();
                if (domain != null)
                {
                    domain.DomainHandle = appDomain;
                    domain.Initialize();
                }
            }
            catch (Exception e)
            {
                Log.Instance.DoLog("An exception occurred creating the AppDomain!", Log.LogType.Error);
                Log.Instance.DoLog(e.ToString(), Log.LogType.Error);
            }

            return domain;
        }

        [PermissionSet(SecurityAction.Assert, Unrestricted = true)]
        internal static bool FindAddon(AssemblyName assemblyName, out string resolvedPath)
        {
            resolvedPath = "";

            foreach (var candidate in new[] { SandboxConfig.LibrariesDirectory, Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) }
                .Where(directory => directory != null && Directory.Exists(directory)).SelectMany(Directory.EnumerateFiles))
            {
                try
                {
                    if (AssemblyName.GetAssemblyName(candidate).Name.Equals(assemblyName.Name))
                    {
                        resolvedPath = candidate;
                        return true;
                    }
                }
                catch (Exception)
                {
                    // ignored
                }
            }

            Log.Instance.DoLog(string.Format("Sandbox: Could not find addon '{0}'", assemblyName.Name), Log.LogType.Error);
            return false;
        }

        internal static bool IsSystemAssembly(string path)
        {
            return path.EndsWith(".dll") || Path.GetDirectoryName(path).EndsWith("Libraries");
        }

        internal static Assembly AddonLoadFrom(string path)
        {
            if (IsSystemAssembly(path))
            {
                return Assembly.LoadFrom(path);
            }
            var buffer = File.ReadAllBytes(path);
            if (!buffer.IsDosExecutable())
            {
                try
                {
                    buffer = SignedAddon.VerifyAndDecrypt(buffer);
                }
                catch (Exception e)
                {
                    Log.Instance.DoLog(string.Format("Unexpected exception when loading signed addon: {0}, Exception:", path), Log.LogType.Error);
                    Log.Instance.DoLog(e.ToString(), Log.LogType.Error);
                }
            }
            return buffer == null ? null : Assembly.Load(buffer);
        }

        [PermissionSet(SecurityAction.Assert, Unrestricted = true)]
        internal static void UnloadDomain(PluginDomain domain)
        {
            AppDomain.Unload(domain.DomainHandle);
        }

        [PermissionSet(SecurityAction.Assert, Unrestricted = true)]
        internal static Assembly DomainOnAssemblyResolve(object sender, ResolveEventArgs args)
        {
#if DEBUG
            //Logs.Log("Sandbox: Resolving '{0}'", args.Name);
#endif
            Assembly resolvedAssembly = null;

            try
            {
                // Don't handle resources
                if (args.Name.Contains(".resources"))
                {
                    return null;
                }

                // Get AssemblyName and special token
                var assemblyName = new AssemblyName(args.Name);
                var assemblyToken = assemblyName.GenerateToken();

                if (Assembly.GetExecutingAssembly().FullName.Equals(args.Name))
                {
                    // Executing assembly
                    resolvedAssembly = Assembly.GetExecutingAssembly();
                }
                //else if (Sandbox.EqualsPublicToken(assemblyName, "7339047cb10f6e86"))
                else if (assemblyName.Name == "Agony")
                {
                    Console.WriteLine("Agony Token: " + assemblyName.GetPublicKeyToken().Select(o => o.ToString("x2")).Concat(new[] { string.Empty }).Aggregate(string.Concat));
                    // Agony.dll
                    resolvedAssembly = Assembly.LoadFrom(SandboxConfig.WrapperDllPath);
                }
                else
                {
                    string resolvedPath;
                    if (FindAddon(assemblyName, out resolvedPath))
                    {
#if DEBUG
                        //Logs.Log("Sandbox: Successfully resolved '{0}'", assemblyName.Name);
#endif
                        if (LoadedLibraries.ContainsKey(assemblyToken))
                        {
                            resolvedAssembly = LoadedLibraries[assemblyToken];
                        }
                        else
                        {
#if DEBUG
                            //Logs.Log("Sandbox: Creating new instance '{0}'", assemblyName.Name);
#endif
                            // Load the addon into the app domain
                            //resolvedAssembly = Assembly.LoadFrom(resolvedPath); //AddonLoadFrom(resolvedPath);
                            resolvedAssembly = AddonLoadFrom(resolvedPath);

                            // Add the addon to the loaded addons dictionary
                            LoadedLibraries.Add(assemblyToken, resolvedAssembly);
                        }
                    }
                }
            }
            catch (Exception e)
            {
                //Logs.Log("Sandbox: Failed to resolve addon:");
                Log.Instance.DoLog(e.ToString(), Log.LogType.Error);
            }

            if (resolvedAssembly != null && resolvedAssembly.IsFullyTrusted)
            {
#if DEBUG
                //Logs.Log("Sandbox: Resolved assembly '{0}' is fully trusted!", resolvedAssembly.GetName().Name);
#endif
            }

            return resolvedAssembly;
        }

        [PermissionSet(SecurityAction.Assert, Unrestricted = true)]
        private static void OnUnhandledException(object sender, UnhandledExceptionEventArgs unhandledExceptionEventArgs)
        {
            /*Logs.Log("Sandbox: Unhandled addon exception:");
#if DEBUG
            var securityException = unhandledExceptionEventArgs.ExceptionObject as SecurityException;
            if (securityException != null)
            {
                Logs.Log(unhandledExceptionEventArgs.ExceptionObject.ToString());
            }
#endif
            Logs.PrintException(unhandledExceptionEventArgs.ExceptionObject);*/
        }

        // ==========================================================================================================
        // PluginDomain Instance
        // ==========================================================================================================

        internal static PluginDomain Instance { get; set; }

        internal AppDomain DomainHandle { get; private set; }

        internal void Initialize()
        {
            // Listen to unhandled exceptions
            DomainHandle.UnhandledException += OnUnhandledException;
        }

        internal bool LoadAddon(string path, string[] args)
        {
            AssemblyName assemblyName = null;
            try
            {
                if (File.Exists(path))
                {
                    // Get the AssemblyName of the addon by the path
                    assemblyName = AssemblyName.GetAssemblyName(path);
                    // Try to execute the addon
                    DomainHandle.ExecuteAssemblyByName(assemblyName, args);
                    if (!LoadedAddons.Contains(assemblyName.Name))
                    {
                        LoadedAddons.Add(assemblyName.Name);
                    }
                    return true;
                }
                else
                {
                    Log.Instance.DoLog("Failed to load addon: File does not exists (" + path + ")", Log.LogType.Error);
                }
            }
            catch (MissingMethodException)
            {
                // The addon is a dll
                if (assemblyName != null && !LoadedLibraries.ContainsKey(assemblyName.GenerateToken()))
                {
                    try
                    {
                        // Load the DLL
                        var assembly = DomainHandle.Load(assemblyName);
                        Console.WriteLine("Loaded " + assembly.FullName);
                        // Store the DLL into loaded addons
                        LoadedLibraries[assemblyName.GenerateToken()] = assembly;
                        return true;
                    }
                    catch (Exception e)
                    {
                        Log.Instance.DoLog("Failed to call Bootstrap for Agony.SDK", Log.LogType.Error);
                        Log.Instance.DoLog(e.ToString(), Log.LogType.Error);
                    }
                }
            }
            catch (Exception e)
            {
                Log.Instance.DoLog("Failed to load plugin", Log.LogType.Error);
                Log.Instance.DoLog(e.ToString(), Log.LogType.Error);
            }
            return false;
        }

        internal Assembly LoadFrom(string path)
        {
            if (IsSystemAssembly(path) || path.EndsWith(".exe"))
            {
                return Assembly.LoadFrom(path);
            }
            var buffer = File.ReadAllBytes(path);
            if (!buffer.IsDosExecutable())
            {
                try
                {
                    buffer = SignedAddon.VerifyAndDecrypt(buffer);
                }
                catch (Exception e)
                {
                    Log.Instance.DoLog(string.Format("Unexpected exception when loading signed addon: {0}, Exception:", path), Log.LogType.Error);
                    Log.Instance.DoLog(e.ToString(), Log.LogType.Error);
                }
            }

            

            return buffer == null ? null : Assembly.Load(buffer);
        }

        internal string ShowPluginConfigs(string assemblyPath)
        {
            foreach(var assembly in AppDomain.CurrentDomain.GetAssemblies())
            {
                if(assembly.Location == assemblyPath)
                {
                    IEnumerable<Type> currentAssemblytypes = assembly.GetTypes().Where(y => typeof(PluginBase).IsAssignableFrom(y) && !y.IsAbstract && !y.IsInterface);
                    if (currentAssemblytypes.Any())
                    {
                        var CurrentBot = (PluginBase)Activator.CreateInstance(currentAssemblytypes.First());
                        if (CurrentBot != null)
                        {
                            return CurrentBot.ShowConfigs(null);
                        }
                    }
                }
            }
            return null;
        }

        [PermissionSet(SecurityAction.Assert, Unrestricted = true)]
        public override object InitializeLifetimeService()
        {
            return null;
        }
    }
}
