using System.ComponentModel;
using System.Xml.Linq;

namespace AgonyLauncher
{
    sealed public class Plugin : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        public Plugin()
        {

        }

        public Plugin ShadowCopy()
        {
            var cp = (Plugin)MemberwiseClone();
            return cp;
        }

        public bool _enabled;
        public bool Enabled
        {
            get { return _enabled; }
            set { _enabled = value; NotifyPropertyChanged("Enabled"); }
        }

        private string _name;
        public string Name
        {
            get { return _name; }
            set { _name = value; NotifyPropertyChanged("Name"); }
        }

        private string _author;
        public string Author
        {
            get { return _author; }
            set { _author = value; NotifyPropertyChanged("Author"); }
        }

        private string _path;
        public string Path
        {
            get { return _path; }
            set { _path = value; NotifyPropertyChanged("Path"); }
        }

        private string _version;
        public string Version
        {
            get { return _version; }
            set { _version = value; NotifyPropertyChanged("Version"); }
        }

        private string _status;
        public string Status
        {
            get { return _status; }
            set { _status = value; NotifyPropertyChanged("Status"); }
        }

        public XElement ConvertToXml()
        {
            var xml = new XElement("Plugin");
            xml.Add(new XAttribute("Enabled", Enabled));
            xml.Add(new XAttribute("Name", Name));
            xml.Add(new XAttribute("Author", Author));
            xml.Add(new XAttribute("Path", Path));
            xml.Add(new XAttribute("Version", Version));
            xml.Add(new XAttribute("Status", Status));
            return xml;
        }
    }
}
