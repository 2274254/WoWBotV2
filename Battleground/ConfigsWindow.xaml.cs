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
using System.Xml;

namespace Battleground
{
    /// <summary>
    /// Interaction logic for ConfigsWindow.xaml
    /// </summary>
    public partial class ConfigsWindow : Window
    {
        public ConfigsWindow()
        {
            InitializeComponent();
        }

        private void ButtonSaveAndClose_Click(object sender, RoutedEventArgs e)
        {
            XmlDocument xmlDoc = new XmlDocument();

            XmlDeclaration xmlDeclaration = xmlDoc.CreateXmlDeclaration("1.0", "UTF-8", null);
            XmlElement root = xmlDoc.DocumentElement;
            xmlDoc.InsertBefore(xmlDeclaration, root);

            XmlElement mainNode = xmlDoc.CreateElement(string.Empty, "Gathering", string.Empty);
            xmlDoc.AppendChild(mainNode);

            //
            XmlElement herbalistNode = xmlDoc.CreateElement(string.Empty, "Herbalist", string.Empty);
            mainNode.AppendChild(herbalistNode);
            herbalistNode.SetAttribute("Enabled", "True");

            //
            XmlElement miningNode = xmlDoc.CreateElement(string.Empty, "Mining", string.Empty);
            mainNode.AppendChild(miningNode);
            miningNode.SetAttribute("Enabled", CheckboxMiningEnabled.IsChecked.Value ? "True" : "False");

            Battleground.ConfigsString = xmlDoc.OuterXml;

            Close();
        }

        private void ButtonCancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
