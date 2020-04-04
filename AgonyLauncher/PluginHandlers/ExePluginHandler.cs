using AgonyLauncher.Data;
using System.Diagnostics;
using System.IO;

namespace AgonyLauncher.PluginHandlers
{
    internal class ExePluginHandler : PluginHandler
    {
        internal override void Compile(AgonyPlugin plugin)
        {
            plugin.SetState(PluginState.Ready);
            plugin.Type = PluginType.Executable;
            var exePath = plugin.GetOutputFilePath();
            File.Copy(plugin.ProjectFilePath, exePath);
            plugin.Version = FileVersionInfo.GetVersionInfo(exePath).FileVersion;
        }
    }
}