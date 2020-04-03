using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace AgonyLauncher.Windows
{
    /// <summary>
    /// Interaction logic for PluginsWindow.xaml
    /// </summary>
    public partial class PluginsWindow : Window
    {
        public PluginsWindow()
        {
            InitializeComponent();
            PluginsGrid.ItemsSource = Settings.Plugins;
        }

        private void PluginEnabledCheckBoxChecked(object sender, RoutedEventArgs e)
        {
            var settings = (Plugin)((CheckBox)sender).Tag;
            settings.Enabled = true;
        }

        private void PluginEnabledCheckBoxUnchecked(object sender, RoutedEventArgs e)
        {
            var settings = (Plugin)((CheckBox)sender).Tag;
            settings.Enabled = false;
        }

        private void DataGridRowContextMenuOpening(object sender, ContextMenuEventArgs e)
        {

        }

        private void EnableMenu_Click(object sender, RoutedEventArgs e)
        {
            var settings = (Plugin)((MenuItem)sender).Tag;
            settings.Enabled = true;
        }

        private void DisableMenu_Click(object sender, RoutedEventArgs e)
        {
            var settings = (Plugin)((MenuItem)sender).Tag;
            settings.Enabled = false;
        }

        private void ButtonEnableAll_Click(object sender, RoutedEventArgs e)
        {
            foreach (Plugin plugin in PluginsGrid.SelectedItems)
            {
                plugin.Enabled = true;
            }
        }

        private void ButtonDisableAll_Click(object sender, RoutedEventArgs e)
        {
            foreach (Plugin plugin in PluginsGrid.SelectedItems)
            {
                plugin.Enabled = false;
            }
        }
    }
}
