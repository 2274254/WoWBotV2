using System.Collections.ObjectModel;
using System.Xml.Linq;

namespace AgonyLauncher
{
    public class Settings : SettingsBase
    {
        public static ObservableCollection<Plugin> Plugins = new ObservableCollection<Plugin>()
        {
            new Plugin(){ Enabled = true, Name="Demo 1", Path = "https://github.com/H3XC0R3/Demo1.git", Status = "Ready", Version = "v1.0.0"},
            new Plugin(){ Enabled = true, Name="Demo 2", Path = "https://github.com/H3XC0R3/Demo2.git", Status = "Ready", Version = "v4.0.1"},
            new Plugin(){ Enabled = true, Name="Demo 3", Path = "https://github.com/H3XC0R3/Demo3.git", Status = "Ready", Version = "v2.1.3"},
            new Plugin(){ Enabled = true, Name="Demo 4", Path = "https://github.com/H3XC0R3/Demo4.git", Status = "Ready", Version = "v4.2.7"},
            new Plugin(){ Enabled = true, Name="Demo 5", Path = "https://github.com/H3XC0R3/Demo5.git", Status = "Ready", Version = "v3.1.1"},
        };

        public override XElement ConvertToXml()
        {
            return null;
        }

        public override void LoadFromXml(XElement element)
        {
        }

        public override SettingsBase ShadowCopy()
        {
            return null;
        }
    }
}
