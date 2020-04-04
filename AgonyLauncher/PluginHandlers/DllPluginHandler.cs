using AgonyLauncher.Data;
using System.Diagnostics;
using System.IO;

namespace AgonyLauncher.PluginHandlers
{
    internal class DllPluginHandler : PluginHandler
    {
        internal override void Compile(AgonyPlugin plugin)
        {
            plugin.SetState(PluginState.Ready);
            plugin.Type = PluginType.Library;
            var dllPath = plugin.GetOutputFilePath();
            File.Copy(plugin.ProjectFilePath, dllPath);
            plugin.Version = FileVersionInfo.GetVersionInfo(dllPath).FileVersion;
        }
    }
}