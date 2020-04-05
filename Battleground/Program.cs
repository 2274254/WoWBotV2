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

            XmlElement mainNode = xmlDoc.CreateElement(string.Empty, "Battleground", string.Empty);
            xmlDoc.AppendChild(mainNode);

            Gathering.ConfigsString = xmlDoc.OuterXml;
        }
    }
}