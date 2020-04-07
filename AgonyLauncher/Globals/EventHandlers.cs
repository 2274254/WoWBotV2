using AgonyLauncher.Injection;
using AgonyLauncher.Logger;
using AgonyLauncher.Routines;
using AgonyLauncher.Services;
using AgonyLauncher.Utils;
using System;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows;

namespace AgonyLauncher.Globals
{
    public static class EventHandlers
    {
        static EventHandlers()
        {
            AppDomain.CurrentDomain.UnhandledException  += OnUnhandledException;
            AppDomain.CurrentDomain.AssemblyResolve     += OnAssemblyResolve;
            Events.OnStartUp                            += OnStartUp;
            Events.OnExit                               += OnExit;
            Events.OnMainWindowLoaded                   += OnMainWindowLoaded;
        }

        public static void Initialize()
        {
        }

        private static void OnUnhandledException(object sender, UnhandledExceptionEventArgs args)
        {
            var exception = (Exception)args.ExceptionObject;
            if (args.IsTerminating)
            {
                Settings.Save();
            }
            Log.Instance.DoLog(string.Format("Unhandled Exception.\r\nException: {0}\r\n", exception), Log.LogType.Error);
            MessageBox.Show(string.Format("Unhandled Exception!\n{0}\n\n", exception), "AgonyLauncher Unhandled Exception", MessageBoxButton.OK, MessageBoxImage.Error);
        }

        private static Assembly OnAssemblyResolve(object sender, ResolveEventArgs args)
        {
            foreach (var file in Directory.GetFiles(Settings.Instance.Directories.DependenciesDirectory))
            {
                if (Path.GetFileNameWithoutExtension(file) == (new AssemblyName(args.Name).Name))
                {
                    return Assembly.LoadFrom(file);
                }
            }
            return null;
        }

        private static void OnStartUp(StartupEventArgs startupEventArgs)
        {
            Log.Instance.DoLog(string.Format("Initializing AgonyLauncher [{0}]", Assembly.GetExecutingAssembly().GetName().Version));

            // Load Settings
            Settings.Load();

            // Cleanup logs folder
            foreach (var file in Directory.GetFiles(Settings.Instance.Directories.LogsDirectory, "*.txt", SearchOption.AllDirectories))
            {
                if (Path.GetFileName(file) != Path.GetFileName(Log.Instance.LogFilePath))
                {
                    try
                    {
                        File.Delete(file);
                    }
                    catch
                    {
                        // ignored
                    }
                }
            }

            // Cleanup temp folder
            try
            {
                DirectoryHelper.DeleteDirectory(Settings.Instance.Directories.TempDirectory, false);
            }
            catch (Exception)
            {
                // ignored
            }

            // Delete invalid files from the Assemblies directory
            foreach (var file in Directory.GetFiles(Settings.Instance.Directories.AssembliesDirectory, "*", SearchOption.AllDirectories))
            {
                if (Settings.Instance != null && Settings.Instance.InstalledPlugins != null && !Settings.Instance.InstalledPlugins.Any(plugin => plugin.IsValid() && File.Exists(plugin.GetOutputFilePath())))
                {
                    try
                    {
                        File.Delete(file);
                    }
                    catch
                    {
                        // ignored
                    }
                }
            }

            // Delete unused repositories
            var directories = Directory.GetDirectories(Settings.Instance.Directories.RepositoryDirectory);
            foreach (var dir in directories)
            {
                if (Settings.Instance != null && Settings.Instance.InstalledPlugins != null &&
                    !Settings.Instance.InstalledPlugins.Any(
                        plugin =>
                            !plugin.IsLocal &&
                            string.Equals(plugin.GetRemotePluginRepositoryDirectory(), dir,
                                StringComparison.CurrentCultureIgnoreCase)))
                {
                    try
                    {
                        DirectoryHelper.DeleteDirectory(dir);
                    }
                    catch (Exception)
                    {
                        // ignored
                    }
                }
            }
            // Load language
            //MultiLanguage.Text = LocalizedText.Load(Settings.Instance.SelectedLanguage ?? Language.Default);
            Log.Instance.DoLog("AgonyLauncher initialized successfully.");
        }

        private static void OnExit(ExitEventArgs exitEventArgs)
        {
            Log.Instance.DoLog("AgonyLauncher is exiting.");
            // Cleanup
            try
            {
                DirectoryHelper.DeleteDirectory(Settings.Instance.Directories.TempCoreDirectory);
                Log.Instance.DoLog(string.Format("Deleted temporary core directory: \"{0}\"", Settings.Instance.Directories.TempCoreDirectory));
            }
            catch (Exception ex)
            {
                Log.Instance.DoLog(string.Format("Failed to delete temporary core directory: \"{0}\", exception: {1}", Settings.Instance.Directories.TempCoreDirectory, ex), Log.LogType.Error);
            }
            // Save settings
            Settings.Save();
            Log.Instance.DoLog("AgonyLauncher has exited.\r\n");
        }

        private static void OnMainWindowLoaded(MainWindow window, RoutedEventArgs args)
        {
            ApiService.Init();
            LoaderServiceRoutine.StartService();

            // Set memory layout
            Bootstrap.SetMemoryLayout();

            // Remove invalid addons
            Settings.Instance.InstalledPlugins.RemoveInvalidPlugins();

            InjectionRoutine.StartRoutine();
        }
    }
}