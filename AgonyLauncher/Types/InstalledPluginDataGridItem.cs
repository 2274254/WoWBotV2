using AgonyLauncher.Data;
using System.ComponentModel;
using System.IO;

namespace AgonyLauncher.Types
{
    public class InstalledPluginDataGridItem : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public AgonyPlugin Plugin { get; private set; }
        private string mAssemblyName;
        public string AssemblyName
        {
            get { return mAssemblyName; }
            set
            {
                mAssemblyName = value;
                RaisePropertyChanged("AssemblyName");
            }
        }

        private string mAuthor;
        public string Author
        {
            get { return mAuthor; }
            set
            {
                mAuthor = value;
                RaisePropertyChanged("Author");
            }
        }

        private string mType;
        public string Type
        {
            get { return mType; }
            set
            {
                mType = value;
                RaisePropertyChanged("Type");
            }
        }

        private string mVersion;
        public string Version
        {
            get { return mVersion; }
            set
            {
                mVersion = value;
                RaisePropertyChanged("Version");
            }
        }

        private string mLocation;
        public string Location
        {
            get { return mLocation; }
            set
            {
                mLocation = value;
                RaisePropertyChanged("Location");
            }
        }

        public bool IsActive
        {
            get { return Plugin.Enabled && IsAvailable; }
            set { Plugin.Enabled = value; }
        }

        public string Status
        {
            get { return Plugin.State.ToString(); }
        }

        public bool IsAvailable
        {
            get { return Plugin.IsAvailable; }
        }

        public InstalledPluginDataGridItem(AgonyPlugin plugin)
        {
            if (!plugin.IsAvailable)
            {
                plugin.SetState(PluginState.VipOnly);
            }

            Plugin = plugin;
            Refresh();
        }

        public void Refresh()
        {
            AssemblyName = Plugin.GetProjectName();
            Author = Plugin.Author;
            Type = Plugin.Type.ToString();
            Version = Plugin.Version;
            Location = Plugin.IsLocal ? Path.GetDirectoryName(Plugin.ProjectFilePath) : Plugin.Url;
            RaisePropertyChanged("Status");
        }

        public void RaisePropertyChanged(string propName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }
    }
}