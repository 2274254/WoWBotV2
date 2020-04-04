using Agony.Sandbox;
using AgonyLauncher.Data;
using AgonyLauncher.Logger;
using AgonyLauncher.Types;
using System;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace AgonyLauncher.Windows
{
    /// <summary>
    /// Interaction logic for PluginsWindow.xaml
    /// </summary>
    public partial class PluginsWindow : Window
    {
        internal static PluginDomain Domain = null;
        internal static PluginsWindow Instance = null;
        public readonly ObservableCollection<InstalledPluginDataGridItem> Items = new ObservableCollection<InstalledPluginDataGridItem>();
        
        public PluginsWindow()
        {
            InitializeComponent();
            Instance = this;
            PluginsGrid.ItemsSource = Items;
            RefreshPlugins();
            RebuildPluginDomain();
        }

        private void PluginEnabledCheckBoxChecked(object sender, RoutedEventArgs e)
        {
            var settings = (InstalledPluginDataGridItem)((CheckBox)sender).Tag;
            settings.IsActive = true;
            Settings.Save();
        }

        private void PluginEnabledCheckBoxUnchecked(object sender, RoutedEventArgs e)
        {
            var settings = (InstalledPluginDataGridItem)((CheckBox)sender).Tag;
            settings.IsActive = false;
            Settings.Save();
        }

        private void DataGridRowContextMenuOpening(object sender, ContextMenuEventArgs e)
        {

        }

        private void EnableMenu_Click(object sender, RoutedEventArgs e)
        {
            var settings = (InstalledPluginDataGridItem)((MenuItem)sender).Tag;
            //var itemInList = Items.First(x => x == settings);//.IsActive = true;
            settings.IsActive = true;
            settings.RaisePropertyChanged("IsActive");
            Settings.Save();
        }

        private void OpenLocationMenu_Click(object sender, RoutedEventArgs e)
        {
            var settings = (InstalledPluginDataGridItem)((MenuItem)sender).Tag;
            Process.Start(settings.Location);
        }

        private void DisableMenu_Click(object sender, RoutedEventArgs e)
        {
            var settings = (InstalledPluginDataGridItem)((MenuItem)sender).Tag;
            settings.IsActive = false;
            settings.RaisePropertyChanged("IsActive");
            Settings.Save();
        }

        private void ButtonEnableAll_Click(object sender, RoutedEventArgs e)
        {
            foreach (InstalledPluginDataGridItem plugin in PluginsGrid.SelectedItems)
            {
                plugin.IsActive = true;
                plugin.RaisePropertyChanged("IsActive");
            }
            Settings.Save();
        }

        private void ButtonDisableAll_Click(object sender, RoutedEventArgs e)
        {
            foreach (InstalledPluginDataGridItem plugin in PluginsGrid.SelectedItems)
            {
                plugin.IsActive = false;
                plugin.RaisePropertyChanged("IsActive");
            }
            Settings.Save();
        }

        private void ButtonUninstall_Click(object sender, RoutedEventArgs e)
        {
            var selectedItems = new InstalledPluginDataGridItem[PluginsGrid.SelectedItems.Count];
            PluginsGrid.SelectedItems.CopyTo(selectedItems, 0);
            foreach (InstalledPluginDataGridItem item in selectedItems)
            {
                var plugin = item.Plugin;
                Settings.Instance.InstalledPlugins.UninstallPlugin(plugin);
            }
            Settings.Save();
            RebuildPluginDomain();
        }

        private void ButtonNewPlugin_Click(object sender, RoutedEventArgs e)
        {
            int countBefore = Items.Count;
            (new NewPluginWindow { Owner = GetWindow(this) }).ShowDialog();
            if(countBefore != Items.Count)
            {
                Settings.Save();
                RebuildPluginDomain();
            }
        }

        public void RefreshPlugins()
        {
            Items.Clear();
            if(Settings.Instance != null && Settings.Instance.InstalledPlugins != null)
            {
                foreach (var plugin in Settings.Instance.InstalledPlugins)
                {
                    Items.Add(new InstalledPluginDataGridItem(plugin));
                }
            }
        }

        public void RemovePlugin(AgonyPlugin plugin)
        {
            var items = new InstalledPluginDataGridItem[PluginsGrid.Items.Count];
            PluginsGrid.SelectedItems.CopyTo(items, 0);
            foreach (InstalledPluginDataGridItem item in items)
            {
                if (item != null && item.Plugin != null && item.Plugin.Equals(plugin))
                {
                    Items.Remove(item);
                }
            }
        }

        public void RebuildPluginDomain()
        {
            try
            {
                if (Domain != null) PluginDomain.UnloadDomain(Domain);
                Domain = PluginDomain.CreateDomain("AgonyLauncherTmp");
                foreach(InstalledPluginDataGridItem item in Items)
                {
                    if(!string.IsNullOrEmpty(item.Plugin.GetOutputFilePath()))
                    {
                        try
                        {
                            Domain.LoadAddon(item.Plugin.GetOutputFilePath(), new string[1]);
                        }
                        catch (Exception ex)
                        {
                            Log.Instance.DoLog("Failed to load plugin in temporary domain", Log.LogType.Error);
                            Log.Instance.DoLog(ex.ToString(), Log.LogType.Error);
                        }
                    }
                }
            }
            catch (Exception) { }
        }

        public void AddLastPlugin()
        {
            Dispatcher.Invoke(() =>
            {
                var plugin = Settings.Instance.InstalledPlugins.LastOrDefault();
                if (plugin == null)
                {
                    return;
                }
                Items.Add(new InstalledPluginDataGridItem(plugin));
            });
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            //e.Cancel = true;
            //Hide();
        }

        private void ButtonRecomile_Click(object sender, RoutedEventArgs e)
        {
            foreach (InstalledPluginDataGridItem item in PluginsGrid.SelectedItems)
            {
                if (item != null && item.Plugin != null)
                {
                    if
                    (
                       item.Plugin.State == PluginState.Ready ||
                       item.Plugin.State == PluginState.CompilingError ||
                       item.Plugin.State == PluginState.Unknown ||
                       item.Plugin.State == PluginState.UpdatingError
                    )
                    {
                        Task.Factory.StartNew(() =>
                        {
                            item.Plugin.Compile();
                        });
                    }
                }
            }
            Settings.Save();
            RebuildPluginDomain();
        }

        private void ButtonUpdate_Click(object sender, RoutedEventArgs e)
        {
            foreach (InstalledPluginDataGridItem item in PluginsGrid.SelectedItems)
            {
                if (item != null && item.Plugin != null)
                {
                    if
                    (
                        item.Plugin.State == PluginState.Ready ||
                        item.Plugin.State == PluginState.CompilingError ||
                        item.Plugin.State == PluginState.Unknown ||
                        item.Plugin.State == PluginState.UpdatingError
                    )
                    {
                        Task.Factory.StartNew(() =>
                        {
                            item.Plugin.Update();
                        });
                    }
                }
            }
            Settings.Save();
            RebuildPluginDomain();
        }

        private void ButtonSettings_Click(object sender, RoutedEventArgs e)
        {
            foreach (InstalledPluginDataGridItem item in PluginsGrid.SelectedItems)
            {
                if (item != null && item.Plugin != null)
                {
                    try
                    {
                        var configs = Domain.ShowPluginConfigs(item.Plugin.GetOutputFilePath());
                        if (configs != null)
                        {
                            item.Plugin.Configs = configs;
                        }
                    }
                    catch (Exception ex)
                    {
                        Log.Instance.DoLog("Failed to show plugin configs", Log.LogType.Error);
                        Log.Instance.DoLog(ex.ToString(), Log.LogType.Error);
                    }
                    
                }
            }
            Settings.Save();
        }
    }
}