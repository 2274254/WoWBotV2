using AgonyLauncher.Data;
using AgonyLauncher.Globals;
using AgonyLauncher.Windows;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AgonyLauncher.Installers
{
    internal static class PluginInstaller
    {
        internal static void InstallPluginsFromRepo(string url, string[] projects = null, bool showUi = true)
        {
            // you wut mate?
            if (projects == null && !showUi)
            {
                return;
            }

            projects = projects ?? new string[] { };

            // setup ui
            var ui = new RemotePluginInstallerWindow
            {
                Url = url,
                ProjectsToInstall = projects,
                RepoHolder = new AgonyPlugin(url, "not_set")
            };
            //check if Ui should be displayed
            if (showUi)
            {
                ui.ShowDialog();
                return;
            }
            // install logic without ui
            // fetch the repo folder
            ui.RepoHolder.Update(false, false);
            // install
            PerformInstall(url, ui.GetPlugins().Where(p => p.Install).OrderBy(p => Array.IndexOf(projects, p.PluginName)));
        }

        internal static string[] GetProjectsFromRepo(string path)
        {
            return Directory.GetFiles(path, "*", SearchOption.AllDirectories).Where(p => Constants.SupportedProjects.Any(p.EndsWith)).ToArray();
        }

        internal static void PerformInstall(string url, IEnumerable<PluginToInstall> plugins)
        {
            foreach (var p in plugins)
            {
                p.Status = "Queued";
                p.Success = false;
            }
            foreach (var p in plugins)
            {
                p.Status = "Installing...";
                p.Success = Settings.Instance.InstalledPlugins.InstallPlugin(url, p.PluginFullName);
                p.Status = p.Success ? "Installed" : "Failed";
            }
        }
    }
}
