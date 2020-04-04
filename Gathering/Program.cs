using System;
using System.Xml;

namespace Gathering
{
    class Program
    {
        [STAThread]
        private static void Main(string[] args)
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
            miningNode.SetAttribute("Enabled", "True");

            Gathering.ConfigsString = xmlDoc.OuterXml;
        }
    }
}