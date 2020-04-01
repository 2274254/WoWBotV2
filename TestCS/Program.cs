using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace TestCS
{
    class Program
    {
        internal static XmlDocument Profile = new XmlDocument();
        internal static int HotspotIndex = -1;
        static void Main(string[] args)
        {
            Profile.Load("D:\\AgonyWoW\\x64\\Release\\Profiles\\Gathering\\Herbalist\\Mining+Herbing 1-75 [Start at Goldshire].xml");

            XmlNode hotspots = Profile["HBProfile"]["Hotspots"];
            if (HotspotIndex == -1 || HotspotIndex == hotspots.ChildNodes.Count)
            {
                HotspotIndex = 0;
            }

            var currentHotspot = hotspots.ChildNodes.Item(HotspotIndex);
            var x = float.Parse(currentHotspot.Attributes.GetNamedItem("X").Value);
            var y = float.Parse(currentHotspot.Attributes.GetNamedItem("Y").Value);
            var z = float.Parse(currentHotspot.Attributes.GetNamedItem("Z").Value);

            Console.ReadLine();
        }
    }
}
