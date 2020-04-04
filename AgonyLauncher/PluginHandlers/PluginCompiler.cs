using AgonyLauncher.Data;
using System.Collections.Generic;
using System.IO;

namespace AgonyLauncher.PluginHandlers
{
    internal abstract class PluginHandler
    {
        internal abstract void Compile(AgonyPlugin plugin);
    }

    internal static class PluginCompiler
    {
        internal static readonly Dictionary<string, PluginHandler> Handlers;
        static PluginCompiler()
        {
            Handlers = new Dictionary<string, PluginHandler>
            {
                [".csproj"] = new ProjectPluginHandler(),
                [".vbproj"] = new ProjectPluginHandler(),
                [".agoplg"] = new SignedPluginHandler(),
                [".exe"] = new ExePluginHandler(),
                [".dll"] = new DllPluginHandler()
            };
        }

        internal static void Compile(AgonyPlugin plugin)
        {
            var format = Path.GetExtension(plugin.ProjectFilePath);
            PluginHandler handler;
            if (Handlers.TryGetValue(format, out handler))
            {
                handler.Compile(plugin);
            }
        }
    }
}