using AgonyLauncher.Data;
using AgonyLauncher.Installers;
using AgonyLauncher.Logger;
using AgonyLauncher.Utils;
using System;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace AgonyLauncher.Windows
{
    /// <summary>
    /// Interaction logic for RemotePluginInstallerWindow.xaml
    /// </summary>
    public partial class RemotePluginInstallerWindow : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public ObservableCollection<PluginToInstall> Items { get; set; }

        private bool _isWorking;
        public bool IsWorking
        {
            get { return _isWorking; }
            set
            {
                _isWorking = value;
                RaisePropertyChanged("IsWorking");
            }
        }

        private bool _isLoading;
        public bool IsLoading
        {
            get { return _isLoading; }
            set
            {
                _isLoading = value;
                RaisePropertyChanged("IsLoading");
            }
        }

        public string[] ProjectsToInstall { get; set; }
        public string Url { get; set; }
        public AgonyPlugin RepoHolder { get; set; }

        public RemotePluginInstallerWindow()
        {
            InitializeComponent();
            DataContext = this;
            Items = new ObservableCollection<PluginToInstall>();
            Owner = PluginsWindow.Instance;
            ShowInTaskbar = false;
            WindowStartupLocation = Owner == null ? WindowStartupLocation.CenterScreen : WindowStartupLocation.CenterOwner;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
        }

        private void Window_ContentRendered(object sender, EventArgs e)
        {
            PrepareInstallation();
        }

        private void InstallButton_OnClick(object sender, RoutedEventArgs e)
        {
            Install(Items.Where(p => p.Install));
        }

        private void CancelButton_OnClick(object sender, RoutedEventArgs e)
        {
            Close();
        }

        public async void PrepareInstallation()
        {
            IsLoading = true;
            IsWorking = true;
            await Task.Run(() =>
            {
                RepoHolder.Update(false, false);
            });
            if (RepoHolder.State == PluginState.Ready)
            {
                foreach (var p in GetPlugins())
                {
                    Items.Add(p);
                }
            }
            else
            {
                Items.Add(new PluginToInstall("Failed to download required data", false, false, "Error"));
            }
            IsLoading = false;
            IsWorking = false;
            if (ProjectsToInstall.Length > 0)
            {
                InstallSelected(Items);
            }
        }

        public async void Install(IEnumerable<PluginToInstall> plugins)
        {
            IsWorking = true;
            await Task.Run(() =>
            {
                PluginInstaller.PerformInstall(Url, plugins);
            });
            if (IsActive && plugins.All(a => a.Success))
            {
                Close();
            }
            IsWorking = false;
        }

        public void InstallSelected(IEnumerable<PluginToInstall> plugins)
        {
            Install(plugins.Where(p => p.Install).OrderBy(p => Array.IndexOf(ProjectsToInstall, p.PluginName)));
        }

        public IEnumerable<PluginToInstall> GetPlugins()
        {
            try
            {
                var foundProjects = PluginInstaller.GetProjectsFromRepo(RepoHolder.GetRemotePluginRepositoryDirectory());
                return
                    foundProjects.Select(p => new Tuple<string, bool>(p, Settings.Instance.InstalledPlugins.IsPluginInstalled(Url, p)))
                        .Select(t => new PluginToInstall(t.Item1, ProjectsToInstall.Contains(Path.GetFileNameWithoutExtension(t.Item1)), !t.Item2, t.Item2 ? "Installed" : ""));
            }
            catch (Exception e)
            {
                Log.Instance.DoLog(string.Format("Unexpected error while searching for project files during plugin installation. Exception: {0}", e), Log.LogType.Error);
                return new[] { new PluginToInstall("Error while getting project files", false, false, "Error") };
            }
        }

        private void RaisePropertyChanged(string propName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }

        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {
            var checkBox = (CheckBox)e.OriginalSource;
            var dataGridRow = VisualTreeHelpers.FindAncestor<DataGridRow>(checkBox);
            if (dataGridRow == null)
            {
                return;
            }
            var item = dataGridRow.DataContext as PluginToInstall;
            item.Install = checkBox.IsChecked ?? false;
        }

        private void CheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            var checkBox = (CheckBox)e.OriginalSource;
            var dataGridRow = VisualTreeHelpers.FindAncestor<DataGridRow>(checkBox);
            if (dataGridRow == null)
            {
                return;
            }
            var item = dataGridRow.DataContext as PluginToInstall;
            item.Install = checkBox.IsChecked ?? false;
        }
    }

    public class PluginToInstall : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private string _pluginName;
        public string PluginFullName { get { return _pluginName; } }
        public string PluginName
        {
            get { return Path.GetFileNameWithoutExtension(_pluginName); }
            set
            {
                _pluginName = value;
                RaisePropertyChanged("PluginName");
            }
        }
        private string _status;
        public string Status
        {
            get { return _status; }
            set
            {
                _status = value;
                RaisePropertyChanged("Status");
            }
        }
        private bool _enabled;
        public bool Enabled
        {
            get { return _enabled; }
            set
            {
                _enabled = value;
                RaisePropertyChanged("Enabled");
            }
        }
        private bool _install;
        public bool Install
        {
            get { return _install; }
            set
            {
                _install = value;
                RaisePropertyChanged("Install");
            }
        }
        public bool Success { get; set; }
        public PluginToInstall(string pluginName, bool install = false, bool enabled = true, string status = "")
        {
            PluginName = pluginName;
            Install = install && enabled;
            Enabled = enabled;
            Status = status;
            Success = true;
        }
        public void RaisePropertyChanged(string propName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }
    }
}