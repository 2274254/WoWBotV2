using AgonyLauncher.Globals;
using AgonyLauncher.Installers;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows;

namespace AgonyLauncher.Windows
{
    /// <summary>
    /// Interaction logic for NewPluginWindow.xaml
    /// </summary>
    public partial class NewPluginWindow : Window
    {
        private string _url = "";
        public NewPluginWindow()
        {
            InitializeComponent();
            LocalPluginRadiobutton.IsChecked = true;
            ShowInTaskbar = false;
        }

        private void Window_ContentRendered(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(_url))
            {
                ProcessInstallRequest(true, _url);
                Close();
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            LocalPluginTextBox_GotFocus(sender, e);
            var fileDialog = new OpenFileDialog
            {
                Filter = "project files |" + string.Concat(Constants.SupportedProjects.Select(s => "*" + s + ";")).TrimEnd(';'),
                FileName = ""
            };
            if (fileDialog.ShowDialog() == true)
            {
                LocalPluginTextBox.Text = fileDialog.FileName;
            }
        }

        private void LocalPluginTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            LocalPluginRadiobutton.IsChecked = true;
        }

        private void RemotePluginTextbox_GotFocus(object sender, RoutedEventArgs e)
        {
            RemotePluginRadiobutton.IsChecked = true;
        }

        private void InstallButton_Click(object sender, RoutedEventArgs e)
        {
            ProcessInstallRequest(LocalPluginRadiobutton.IsChecked != true, LocalPluginRadiobutton.IsChecked == true ? LocalPluginTextBox.Text : RemotePluginTextbox.Text);
        }

        private void ProcessInstallRequest(bool remotePlugin, string requestString)
        {
            if (!remotePlugin)
            {
                //TODO: check for valid path

                var args = new Dictionary<string, object> { { "projectPath", requestString } };
                var taskWindow = new TaskWindow { Owner = Owner };

                Hide();
                taskWindow.WindowTitle = "Plugin Installer";
                taskWindow.BeginTask(new TaskWindow.TaskWindowDelegate[] { InstallLocalPlugin }, args);

                if (taskWindow.Success)
                {
                    Close();
                }
                else
                {
                    Show();
                    MessageBox.Show(
                        string.Format("Failed to install plugin",
                            Path.GetFileNameWithoutExtension(LocalPluginTextBox.Text)),
                        "Plugin Installer",
                        MessageBoxButton.OK, MessageBoxImage.Exclamation);
                }
            }
            else
            {
                Hide();
                PluginInstaller.InstallPluginsFromRepo(requestString);
                Close();
            }
        }

        private static bool InstallLocalPlugin(TaskWindow ui, Dictionary<string, object> args)
        {
            var projectPath = (string)args["projectPath"];
            ui.CustomStatusString = true;
            ui.Status = "Installing local plugin " + Path.GetFileNameWithoutExtension(projectPath);
            return Settings.Instance.InstalledPlugins.InstallPlugin("", projectPath);
        }
    }
}
