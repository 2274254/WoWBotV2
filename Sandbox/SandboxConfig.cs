using System;
using System.Collections.Generic;
using System.Security;
using System.Security.Permissions;
using Agony.Sandbox.Shared;

namespace Agony.Sandbox
{
    /// <summary>
    ///     Sandbox Configuration Placeholder.
    /// </summary>
    public class SandboxConfig
    {
        /// <summary>
        ///     Data Directory, normally the full path towards the installation.
        /// </summary>
        public static string DataDirectory;

        /// <summary>
        ///     Libraries Directory, full path towards the libraries directory.
        /// </summary>
        public static string LibrariesDirectory;

        /// <summary>
        ///     A full path towards the Agony.Wrapper.dll
        /// </summary>
        public static string WrapperDllPath;

        /// <summary>
        ///     Permissions for the secure application domain.
        /// </summary>
        public static PermissionSet Permissions;

        /// <summary>
        ///     Buddy.
        /// </summary>
        public static bool IsVip;

        public static Dictionary<string, string> PluginConfigs { get; set; }

        public static string CurrentProfile { get; set; }

        static SandboxConfig()
        {
            Reload();
        }

        [PermissionSet(SecurityAction.Assert, Unrestricted = true)]
        public static void Reload()
        {
            Configuration config = null;
            try
            {
                config = ServiceFactory.CreateProxy<ILoaderService>().GetConfiguration(Sandbox.Pid);
            }
            catch (Exception e)
            {
                Logs.Log("Sandbox: Reload, getting configuration failed");
                Logs.Log(e.ToString());
            }

            if (config != null)
            {
                DataDirectory = config.DataDirectory;
                WrapperDllPath = config.WrapperDllPath;
                LibrariesDirectory = config.LibrariesDirectory;
                Permissions = config.Permissions;
                IsVip = config.IsVip;
                PluginConfigs = config.PluginConfigs;
                CurrentProfile = config.CurrentProfile;
            }
            else
            {
                Logs.Log("Sandbox: Reload, config is null");
            }
        }
    }
}