using AgonyLauncher.Data;
using AgonyLauncher.Types;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
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
        readonly ObservableCollection<InstalledPluginDataGridItem> Items = new ObservableCollection<InstalledPluginDataGridItem>();
        
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
        }

        private void PluginEnabledCheckBoxUnchecked(object sender, RoutedEventArgs e)
        {
            var settings = (InstalledPluginDataGridItem)((CheckBox)sender).Tag;
            settings.IsActive = false;
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
        }

        private void ButtonEnableAll_Click(object sender, RoutedEventArgs e)
        {
            foreach (InstalledPluginDataGridItem plugin in PluginsGrid.SelectedItems)
            {
                plugin.IsActive = true;
                plugin.RaisePropertyChanged("IsActive");
            }
        }

        private void ButtonDisableAll_Click(object sender, RoutedEventArgs e)
        {
            foreach (InstalledPluginDataGridItem plugin in PluginsGrid.SelectedItems)
            {
                plugin.IsActive = false;
                plugin.RaisePropertyChanged("IsActive");
            }
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
        }

        private void ButtonNewPlugin_Click(object sender, RoutedEventArgs e)
        {
            (new NewPluginWindow { Owner = GetWindow(this) }).ShowDialog();
        }

        public void RefreshPlugins()
        {
            Items.Clear();
            foreach (var plugin in Settings.Instance.InstalledPlugins)
            {
                Items.Add(new InstalledPluginDataGridItem(plugin));
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
    }
}
