using AgonyLauncher.Windows;
using Microsoft.Win32;
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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace AgonyLauncher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
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
                Log("Profile: " + fileDialog.FileName, "#FFFFFF");
            }
        }

        private void ComboBoxMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ButtonLoadProfile.IsEnabled = true;
        }

        private void ButtonPlugins_Click(object sender, RoutedEventArgs e)
        {
            new PluginsWindow().ShowDialog();
        }
    }
}
