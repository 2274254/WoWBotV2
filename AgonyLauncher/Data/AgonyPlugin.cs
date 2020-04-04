using AgonyLauncher.Git;
using AgonyLauncher.Globals;
using AgonyLauncher.Logger;
using AgonyLauncher.PluginHandlers;
using AgonyLauncher.Types;
using AgonyLauncher.Windows;
using NLog;
using System;
using System.IO;
using System.Linq;
using System.Threading;
using System.Xml;

namespace AgonyLauncher.Data
{
    [Serializable]
    public class AgonyPlugin
    {
        private static readonly NLog.Logger NLog = LogManager.GetCurrentClassLogger();

        public string Url { get; private set; }
        public string ProjectFilePath { get; private set; }
        public bool Enabled { get; set; }
        public PluginState State { get; private set; }
        public PluginType Type { get; set; }
        public string Author { get; set; }
        public string Version { get; set; }
        public bool IsVipPlugin { get; set; }

        public string Configs { get; set; }

        public bool IsAvailable
        {
            get
            {
                if (IsVipPlugin)
                {
                    return false;
                    //return Authenticator.IsVip;
                }
                else
                {
                    if (!string.IsNullOrEmpty(Author))
                    {
                        if (Author.Contains("H3XC0R3")) //Testing
                        {
                            while (true)
                            {
                                return IsAvailable;
                            }
                        }
                    }
                }
                return true;
            }
        }

        public bool IsLocal
        {
            get { return string.IsNullOrEmpty(Url); }
        }

        public AgonyPlugin(string url, string projectFilePath)
        {
            Url = url;
            ProjectFilePath = projectFilePath;
            if (!IsLocal)
            {
                ProjectFilePath = Path.Combine(GetRemotePluginRepositoryDirectory(), Path.GetFileName(ProjectFilePath));
            }
            State = PluginState.Unknown;
        }

        public string GetProjectName()
        {
            return Path.GetFileNameWithoutExtension(ProjectFilePath);
        }

        public string GetHash()
        {
            return (ProjectFilePath + Url).GetHashCode().ToString("X");
        }

        public string GetUniqueName()
        {
            return string.Format("{0}_{1}", GetProjectName(), GetHash());
        }

        public string GetExtension()
        {
            return (Type == PluginType.Executable ? ".exe" : ".dll");
        }

        public string GetDefaultOutputFileName()
        {
            return Path.GetFileNameWithoutExtension(ProjectFilePath) + GetExtension();
        }

        public string GetUniqueOutputFileName()
        {
            return GetUniqueName() + GetExtension();
        }

        public string GetOutputFilePath()
        {
            switch (Type)
            {
                case PluginType.Library: return Path.Combine(Settings.Instance.Directories.LibrariesDirectory, GetDefaultOutputFileName());
                case PluginType.Executable: return Path.Combine(Settings.Instance.Directories.AssembliesDirectory, GetUniqueOutputFileName());
            }
            return string.Empty;
        }

        public string GetRemotePluginRepositoryDirectory()
        {
            return string.IsNullOrEmpty(Url)
                ? ""
                : Path.Combine(Settings.Instance.Directories.RepositoryDirectory, Url.GetHashCode().ToString("X"));
        }

        internal bool TrySetValidProjectFile()
        {
            var directory = GetRemotePluginRepositoryDirectory();

            if (!Directory.Exists(directory))
            {
                return false;
            }

            var projectFiles =
                Directory.GetFiles(directory, "*", SearchOption.AllDirectories)
                    .Where(p => Constants.SupportedProjects.Any(p.EndsWith))
                    .ToArray();
            var projectName = Path.GetFileName(ProjectFilePath);

            if (projectFiles.All(p => Path.GetFileName(p) != projectName))
            {
                return false;
            }

            ProjectFilePath = projectFiles.First(p => Path.GetFileName(p) == Path.GetFileName(projectName));
            return true;
        }

        public void RefreshDisplay(PluginsWindow window = null)
        {
            //TODO: rework with PropertyChanged
            window = window ?? PluginsWindow.Instance;
            if (window != null)
            {
                var item = PluginsWindow.Instance.PluginsGrid.Items.OfType<InstalledPluginDataGridItem>().FirstOrDefault(i => i.Plugin.Equals(this));
                if (item != null)
                {
                    item.RaisePropertyChanged("Status");
                    //PluginsWindow.Instance.PluginsGrid.Items.Refresh();
                    //Thread.Sleep(1000);
                }
            }
        }

        public void SetState(PluginState state, bool refreshDisplay = true)
        {
            if (!IsAvailable)
            {
                state = PluginState.VipOnly;
            }
            if (State != state)
            {
                State = state;
                if (refreshDisplay)
                {
                    RefreshDisplay();
                }
            }
        }

        public void Compile(bool refreshDisplay = true)
        {
            Log.Instance.DoLog(string.Format("Compiling project: \"{0}\".", ProjectFilePath));
            SetState(PluginState.Compiling, refreshDisplay);

            if (!File.Exists(ProjectFilePath) && !IsLocal)
            {
                if (!TrySetValidProjectFile())
                {
                    SetState(PluginState.CompilingError, refreshDisplay);

                    Log.Instance.DoLog(string.Format("Project file: \"{0}\" not found. Compilation for plugin: \"{1}\" failed.", Path.GetFileName(ProjectFilePath), this), Log.LogType.Error);
                    return;
                }
            }

            try
            {
                PluginCompiler.Compile(this);
                SetState(PluginState.Ready, refreshDisplay);
            }
            catch (Exception ex)
            {
                SetState(PluginState.CompilingError, refreshDisplay);
                Log.Instance.DoLog(string.Format("Exception during compilation.\r\nProject: \"{0}\"\r\nException: {1}", ProjectFilePath, ex), Log.LogType.Error);
            }
        }

        public void Update(bool compile = true, bool updateDisplay = true)
        {
            if (!IsLocal)
            {
                Log.Instance.DoLog(string.Format("Updating plugin: \"{0}\" with url: \"{1}\" and project name: \"{2}\"",
                    GetProjectName(), Url, Path.GetFileName(ProjectFilePath)));

                SetState(PluginState.Updating, updateDisplay);
                var directory = GetRemotePluginRepositoryDirectory();

                if (!GitDownloader.UpdateRepository(directory))
                {
                    if (!GitDownloader.Download(Url, directory))
                    {
                        SetState(PluginState.UpdatingError, updateDisplay);

                        Log.Instance.DoLog(
                            string.Format(
                                "Failed to update plugin: \"{0}\" with url: \"{1}\" and project name: \"{2}\".",
                                GetProjectName(), Url, Path.GetFileName(ProjectFilePath)), Log.LogType.Error);
                        return;
                    }
                }
            }

            if (compile)
            {
                Compile();
            }
            else
            {
                SetState(PluginState.Ready, updateDisplay);
            }

            Log.Instance.DoLog(
                string.Format(
                    "Finished updating plugin: \"{0}\", result: {4} (url: \"{1}\", project: \"{2}\", directory \"{3}\")",
                    GetProjectName(), Url, Path.GetFileName(ProjectFilePath), GetRemotePluginRepositoryDirectory(), State));
        }

        public bool IsValid()
        {
            return IsLocal
                ? File.Exists(ProjectFilePath)
                : Directory.Exists(GetRemotePluginRepositoryDirectory()) ||
                  (File.Exists(ProjectFilePath) || TrySetValidProjectFile());
        }

        public override bool Equals(object obj)
        {
            var plugin = obj as AgonyPlugin;
            if (plugin == null)
            {
                return false;
            }
            return IsLocal == plugin.IsLocal &&
                   (IsLocal
                       ? ProjectFilePath == plugin.ProjectFilePath
                       : Url.ToLower() + GetProjectName() == plugin.Url.ToLower() + plugin.GetProjectName());
        }

        public override string ToString()
        {
            return IsLocal ? ProjectFilePath : string.Format("{0}+{1}", Url, Path.GetFileName(ProjectFilePath));
        }
    }

    public enum PluginType
    {
        Unknown,
        Library,
        Executable,
    }

    public enum PluginState
    {
        Unknown,
        Ready,
        Updating,
        UpdatingError,
        CompilingError,
        Compiling,
        WaitingForUpdate,
        WaitingForCompile,
        VipOnly,
    }
}