using Agony.Sandbox;
using Agony.SDK.CommonBot;
using AgonyLauncher.Data;
using AgonyLauncher.Types;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
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
        internal static PluginsWindow Instance = null;
        public readonly ObservableCollection<InstalledPluginDataGridItem> Items = new ObservableCollection<InstalledPluginDataGridItem>();
        
        public PluginsWindow()
        {
            InitializeComponent();
            Instance = this;
            PluginsGrid.ItemsSource = Items;
            RefreshPlugins();
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
        }

        private void ButtonNewPlugin_Click(object sender, RoutedEventArgs e)
        {
            (new NewPluginWindow { Owner = GetWindow(this) }).ShowDialog();
            Settings.Save();
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
        }

        private void ButtonSettings_Click(object sender, RoutedEventArgs e)
        {
            foreach (InstalledPluginDataGridItem item in PluginsGrid.SelectedItems)
            {
                if (item != null && item.Plugin != null)
                {
                    PluginDomain domain = PluginDomain.CreateDomain("AgonyLauncherTmp");
                    try
                    {
                        if(domain.LoadAddon(item.Plugin.GetOutputFilePath(), new string[1]))
                        {
                            var configs = domain.GetPluginBase();
                            if(configs != null)
                            {
                                item.Plugin.Configs = configs;
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.StackTrace);
                    }
                    PluginDomain.UnloadDomain(domain);
                }
            }
            Settings.Save();
        }
    }
}
