using AgonyLauncher.Globals;
using AgonyLauncher.Installers;
using System;
using System.Web;

namespace AgonyLauncher.UriScheme
{
    internal static class UriHandler
    {
        internal static void Process(string url)
        {
            var uri = new Uri(url);
            switch (uri.Authority)
            {
                case "install":
                    var host = HttpUtility.ParseQueryString(uri.Query).Get("host");
                    var projects = HttpUtility.ParseQueryString(uri.Query).Get("project") ?? "";
                    PluginInstaller.InstallPluginsFromRepo(host, projects.Split(';'));
                break;
                default: //legacy
                    var urischeme = Constants.UriSchemePrefix + "://";
                    url = url.Replace(urischeme, "https://github.com/");
                    PluginInstaller.InstallPluginsFromRepo(url);
                break;
            }
        }
    }
}