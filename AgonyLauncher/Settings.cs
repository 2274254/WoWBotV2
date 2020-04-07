using AgonyLauncher.Data;
using AgonyLauncher.Logger;
using AgonyLauncher.Types;
using AgonyLauncher.Utils;
using AgonyLauncher.Windows;
using NLog;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Timers;
using System.Xml.Linq;

namespace AgonyLauncher
{
    [Serializable]
    public class Settings
    {
        public SettingsDirectories Directories = new SettingsDirectories();
        public InstalledPluginList InstalledPlugins { get; private set; }
        public bool DeveloperMode = false;

        static Settings()
        {
            SaveTimer = new Timer(60000);
            SaveTimer.Elapsed += OnSaveTimerElapsed;
            SaveTimer.Start();
        }

        private static Timer SaveTimer { get; set; }

        private static void OnSaveTimerElapsed(object sender, ElapsedEventArgs elapsedEventArgs)
        {
            Save();
        }

        private static Settings _instance;

        public static Settings Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new Settings();
                }

                return _instance;
            }
        }

        public static string LastSave { get; private set; }

        public static bool SaveRequired()
        {
            try
            {
                return LastSave != Convert.ToBase64String(Serialization.Serialize(Instance));
            }
            catch (Exception)
            {
                return true;
            }
        }

        public static void Save()
        {
            if (!SaveRequired())
            {
                return;
            }
            Log.Instance.DoLog("Serializing settings.");
            var bytes = Serialization.Serialize(Instance);
            if (bytes != null)
            {
                try
                {
                    File.WriteAllBytes(Instance.Directories.SettingsFilePath, bytes);
                    LastSave = Convert.ToBase64String(bytes);
                }
                catch (Exception ex)
                {
                    Log.Instance.DoLog(
                        string.Format("Failed to save settings.\r\nSettingsFilePath: {0}\r\nException: {1}\r\n",
                            Instance.Directories.SettingsFilePath, ex), Log.LogType.Error);
                }
            }
            else
            {
                Log.Instance.DoLog(
                    string.Format("Failed to serialize settings. SettingsFilePath: \"{0}\".",
                        Instance.Directories.SettingsFilePath), Log.LogType.Error);
            }
        }

        public static void Load()
        {
            if (File.Exists(Instance.Directories.SettingsFilePath))
            {
                Log.Instance.DoLog("Deserializing settings.");

                try
                {
                    var savedSettings = (Settings)Serialization.Deserialize(File.ReadAllBytes(Instance.Directories.SettingsFilePath));

                    if (savedSettings != null)
                    {
                        savedSettings.Directories.Verify();
                        _instance = savedSettings;
                        if (_instance.InstalledPlugins == null) _instance.InstalledPlugins = new InstalledPluginList();
                    }
                    else
                    {
                        Log.Instance.DoLog(
                            string.Format("Failed to deserialize settings. SettingsFilePath: \"{0}\".",
                                Instance.Directories.SettingsFilePath), Log.LogType.Error);

                        try
                        {
                            Log.Instance.DoLog(string.Format("Deleting settings file: \"{0}\".",
                                Instance.Directories.SettingsFilePath));

                            File.Delete(Instance.Directories.SettingsFilePath);
                        }
                        catch (Exception ex)
                        {
                            Log.Instance.DoLog(
                                string.Format("Failed to delete settings file: \"{0}\"\r\nException: {1}\r\n",
                                    Instance.Directories.SettingsFilePath, ex), Log.LogType.Error);
                        }
                    }
                }
                catch (Exception ex)
                {
                    Log.Instance.DoLog(string.Format("Failed to load settings.\r\nSettingsFilePath: {0}\r\nException: {1}\r\n", Instance.Directories.SettingsFilePath, ex), Log.LogType.Error);
                }
            }
        }

        private Settings()
        {
            Directories = new SettingsDirectories();
            InstalledPlugins = new InstalledPluginList();
            Directories.Verify();
        }
    }

    [Serializable]
    public class InstalledPluginList : List<AgonyPlugin>
    {
        private static readonly NLog.Logger NLog = LogManager.GetCurrentClassLogger();

        public void RemoveInvalidPlugins()
        {
            var invalidPlugins = this.Where(a => !a.IsValid()).ToArray();
            foreach (var plugin in invalidPlugins)
            {
                UninstallPlugin(plugin);
            }
        }

        private static BackgroundWorker _uninstallBackgroundWorker;

        public InstalledPluginList()
        {
            _uninstallBackgroundWorker = new BackgroundWorker()
            {
                WorkerSupportsCancellation = false,
                WorkerReportsProgress = false
            };
        }

        public bool IsPluginInstalled(AgonyPlugin plugin)
        {
            return this.Any(a => a.Equals(plugin));
        }

        public bool IsPluginInstalled(string url, string projectFile)
        {
            return this.Any(a => a.Equals(new AgonyPlugin(url, projectFile)));
        }

        public void UninstallPlugin(AgonyPlugin plugin)
        {
            Remove(plugin);
            if (PluginsWindow.Instance != null)
            {
                PluginsWindow.Instance.RemovePlugin(plugin);
            }
            _uninstallBackgroundWorker.DoWork += delegate
            {
                if (File.Exists(plugin.GetOutputFilePath()))
                {
                    try
                    {
                        File.Delete(plugin.GetOutputFilePath());
                    }
                    catch (Exception)
                    {
                        // ignored
                    }
                }
                var directory = plugin.GetRemotePluginRepositoryDirectory();
                if (this.Count(a => a.GetRemotePluginRepositoryDirectory() == directory) == 0)
                {
                    try
                    {
                        DirectoryHelper.DeleteDirectory(directory);
                    }
                    catch (Exception)
                    {
                        // ignored
                    }
                }
            };
            if (!_uninstallBackgroundWorker.IsBusy)
            {
                _uninstallBackgroundWorker.RunWorkerAsync();
            }
        }

        public void UninstallPlugin(int index)
        {
            UninstallPlugin(this[index]);
        }

        public bool InstallPlugin(AgonyPlugin plugin)
        {
            Log.Instance.DoLog(string.Format("Installing plugin: \"{0}\".", plugin));

            if (this.Any(a => a.Equals(plugin)))
            {
                Log.Instance.DoLog(
                    string.Format("Failed to install plugin: \"{0}\", this plugin is already installed!", plugin));

                return false;
            }
            plugin.Compile();
            if (plugin.State == PluginState.Ready)
            {
                Add(plugin);
                if (PluginsWindow.Instance != null)
                {
                    PluginsWindow.Instance.AddLastPlugin();
                }
                Log.Instance.DoLog(string.Format("Successfully installed plugin: \"{0}\"", plugin));
                Settings.Save();
                return true;
            }

            Log.Instance.DoLog(string.Format(
                    "Failed to install plugin: \"{0}\". Plugin state: \"{1}\". The plugin either did not update or did not compile!",
                    plugin, plugin.State), Log.LogType.Error);

            return false;
        }

        public bool InstallPlugin(string url, string projectFile)
        {
            return InstallPlugin(new AgonyPlugin(url, projectFile));
        }

        public void RecompileSelectedPlugins()
        {
            foreach (var plugin in this.Where(a => a.Enabled).OrderByDescending(a => (int)a.Type).Reverse())
            {
                plugin.Compile();
            }
            NLog.Info("Recompile selected Plugins");
        }
    }

    [Serializable]
    public class SettingsDirectories
    {
        public string AppDataDirectory { get; private set; } // agony appdata directory

        public string LoaderFilePath // loader current path
        {
            get { return Process.GetCurrentProcess().MainModule.FileName; }
        }

        public string CurrentDirectory // current directory (loader directory)
        {
            get { return AppDomain.CurrentDomain.BaseDirectory; }
        }

        public string DependenciesDirectory // dependencies directory
        {
            get { return Path.Combine(CurrentDirectory, "Dependencies") + "\\"; }
        }

        public string SettingsDirectory // settings directory
        {
            get { return Path.Combine(CurrentDirectory, "Settings") + "\\"; }
        }

        public string LanguagesDirectory // languages directory
        {
            get { return Path.Combine(SettingsDirectory, "Languages") + "\\"; }
        }

        public string SettingsFilePath // settings file path
        {
            get { return Path.Combine(SettingsDirectory, "settings.data"); }
        }

        public string LogsDirectory // log direcotry
        {
            get { return Path.Combine(CurrentDirectory, "Logs") + "\\"; }
        }

        public string SystemDirectory // system directory
        {
            get { return Path.Combine(CurrentDirectory, "System") + "\\"; }
        }

        public string CoreDllPath // core dll path (system folder)
        {
            get { return Path.Combine(SystemDirectory, "Agony.Core.dll"); }
        }

        public string WrapperDllPath // wrapper dll path (system folder)
        {
            get { return Path.Combine(SystemDirectory, "Agony.Wrapper.dll"); }
        }

        public string SandboxDllPath // sandbox dll path (system folder)
        {
            get { return Path.Combine(SystemDirectory, "Agony.Sandbox.dll"); }
        }

        public string SdkDllPath // sdk dll path (system folder)
        {
            get { return Path.Combine(SystemDirectory, "Agony.SDK.dll"); }
        }

        public string UnmanagedDllPath // unmanaged dll path (system folder)
        {
            get { return Path.Combine(SystemDirectory, "libinj.dll"); }
        }

        public string RepositoryDirectory // repository directory, all remote installed plugins are saved here
        {
            get { return Path.Combine(AppDataDirectory, "Repositories") + "\\"; }
        }

        public string TempDirectory // temp directory in appdata, used for storing temporary files
        {
            get { return Path.Combine(AppDataDirectory, "Temp") + "\\"; }
        }

        public string AssembliesDirectory { get; set; } // compiled plugins are placed here

        public string LibrariesDirectory // all dlls from system folder are placed here
        {
            get { return Path.Combine(AssembliesDirectory, "Libraries") + "\\"; }
        }

        public string TempCoreDirectory { get; set; } // temp directory for injection
        public string TempCoreDllPath { get; set; } // temp core dll path
        public string TempSandboxDllPath { get; set; } // temp sandbox dll path
        public string TempWrapperDllPath { get; set; } // temp wrapper dll path
        public string TempUnmanagedDllPath { get; set; } // temp unmanaged dll path

        internal SettingsDirectories()
        {
            AppDataDirectory = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "Agony\\");
            AssembliesDirectory = Path.Combine(AppDataDirectory, "Plugins") + "\\";
            CreateDirectories();
        }

        internal void Verify()
        {
            var newInstance = new SettingsDirectories();
            foreach (var property in GetType().GetProperties())
            {
                var propertyValue = property.GetValue(this);

                if (propertyValue == null && property.GetSetMethod() != null)
                {
                    property.SetValue(this, property.GetValue(newInstance));
                }
            }
            CreateDirectories();
        }

        private void CreateDirectories()
        {
            foreach (var property in GetType().GetProperties())
            {
                var propertyName = property.Name;
                var propertyValue = property.GetValue(this) as string;
                if (propertyName.ToLower().Contains("directory") && propertyValue != null)
                {
                    if (!Directory.Exists(propertyValue))
                        Directory.CreateDirectory(propertyValue);
                }
            }
        }
    }

    public enum Language
    {
        Default = 0,
        English = 100,
        Arabic = 200,
        German = 300,
        Spanish = 400,
        French = 500,
        Italian = 600,
        Polish = 700,
        Hungarian = 800,
        Dutch = 900,
        Swedish = 1000,
        Portuguese = 1100,
        Slovenian = 1200,
        Romanian = 1300,
        Vietnamese = 1400,
        Turkish = 1500,
        Chinese = 1600,
        ChineseTraditional = 1610,
        Korean = 1700,
        Balkan = 1800,
        Greek = 1900,
    }
}