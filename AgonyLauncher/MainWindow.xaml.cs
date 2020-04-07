using Agony.Sandbox.Shared;
using AgonyLauncher.Globals;
using AgonyLauncher.Routines;
using AgonyLauncher.Utils;
using AgonyLauncher.Windows;
using Microsoft.Win32;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;

namespace AgonyLauncher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        internal static int PId = 0;
        internal static AgonyStatus Status = AgonyStatus.Stopped;
        internal static string ProfilePath = "";
        public PluginsWindow Plugins = new PluginsWindow();

        public MainWindow()
        {
            InitializeComponent();
            Loaded += MainWindow_Loaded;
            Closing += MainWindow_Closing;
            Plugins.Closed += Plugins_Closed;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var processReady = InjectionRoutine.GetWoWProcesses().Where(p => !InjectionRoutine.IsProcessInjected(p) && !string.IsNullOrEmpty(p.MainWindowTitle));
            if(processReady.Count() != 1)
            {
                new ProcessWindow() { Owner = this }.ShowDialog();
            }
            else
            {
                PId = processReady.First().Id;
            }
            Title = "[" + PId + "] PrivateBuddy";
            Events.RaiseOnMainWindowLoaded(this, e);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            LoaderUpdateRoutines.InstallFilesRoutine(null, new System.Collections.Generic.Dictionary<string, object>());
            //UpdateSystem();
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            EnvironmentHelper.ShutDown(true);
        }

        private void Plugins_Closed(object sender, System.EventArgs e)
        {
            Plugins = new PluginsWindow();
            Plugins.Closed += Plugins_Closed;
        }

        internal void Log(string text, string color)
        {
            Paragraph p = new Paragraph(new Run(text));
            //p.Foreground = new Brush();
            LogBox.Blocks.Add(p);
        }

        private void ButtonLoadProfile_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            var result = fileDialog.ShowDialog();
            if (result.HasValue && result.Value)
            {
                Log("Selected profile: " + fileDialog.FileName, "#FFFFFF");
                ProfilePath = fileDialog.FileName;
            }
        }

        private void ComboBoxMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ButtonLoadProfile.IsEnabled = true;
        }

        private void ButtonPlugins_Click(object sender, RoutedEventArgs e)
        {
            Plugins.ShowDialog();
        }

        public static void UpdateSystem()
        {
            Logger.Log.Instance.DoLog("Running agony system updater.");
            var updateWindow = new UpdateWindow();
            updateWindow.BeginUpdate(
                new UpdateWindow.UpdateWindowDelegate[]
                {
                    /*LoaderUpdateRoutines.InitializeUpdateRoutine,
                    LoaderUpdateRoutines.LoaderUpdateRoutine,
                    LoaderUpdateRoutines.SystemFilesUpdateRoutine,
                    LoaderUpdateRoutines.PatchFilesUpdateRoutine,*/
                    LoaderUpdateRoutines.InstallFilesRoutine
                }, null);
            Logger.Log.Instance.DoLog("Agony system updater has finished updating.");
        }

        private void ButtonStartStop_Click(object sender, RoutedEventArgs e)
        {
            if(Status == AgonyStatus.Stopped)
            {
                Status = AgonyStatus.Running;
                ButtonStartStop.Content = "Stop";
            }
            else
            {
                Status = AgonyStatus.Stopped;
                ButtonStartStop.Content = "Start";
            }
        }
    }
}