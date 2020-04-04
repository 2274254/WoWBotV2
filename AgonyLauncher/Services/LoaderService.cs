using System.Collections.Generic;
using System.Linq;
using AgonyLauncher.Data;
using Agony.Sandbox.Shared;
using NLog;

namespace AgonyLauncher.Services
{
    public class LoaderService : ILoaderService
    {
        private static readonly NLog.Logger NLog = LogManager.GetCurrentClassLogger();
        private static readonly List<int> LoggedGames = new List<int>();

        public List<SharedAddon> GetAssemblyList(int gameid)
        {
            var logList = string.Join(";",
                Settings.Instance.InstalledPlugins.Where(plugin => plugin.Enabled && (plugin.Type == PluginType.Executable))
                    .Select(a => a.ToString())
                    .Concat(new[] { string.Empty }));

            if (LoggedGames.Contains(gameid))
            {
                LoggedGames.Add(gameid);
                NLog.Info("[GetAssemblyList] [UniqueGame] GameID: {2}, List: {3}", gameid, logList);
            }

            NLog.Info("[GetAssemblyList] GameID: {2}, List: {3}", gameid, logList);

            return
                Settings.Instance.InstalledPlugins.Where(plugin => plugin.Enabled && plugin.Type == PluginType.Executable && plugin.State == PluginState.Ready)
                    .Select(plugin => new SharedAddon { PathToBinary = plugin.GetOutputFilePath() })
                    .ToList();
        }

        public Configuration GetConfiguration(int pid)
        {
            return new Configuration
            {
                DataDirectory = Settings.Instance.Directories.AppDataDirectory,
                WrapperDllPath = PathRandomizer.WrapperDllPath,
                LibrariesDirectory = Settings.Instance.Directories.LibrariesDirectory,
                Permissions = null, //possible security issue
            };
        }

        public void Recompile(int pid)
        {
            Settings.Instance.InstalledPlugins.RecompileSelectedPlugins();
        }
    }
}