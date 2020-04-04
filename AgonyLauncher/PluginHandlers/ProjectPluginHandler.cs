using AgonyLauncher.Compilers;
using AgonyLauncher.Data;
using AgonyLauncher.Logger;
using AgonyLauncher.Utils;
using System.Diagnostics;
using System.IO;

namespace AgonyLauncher.PluginHandlers
{
    internal class ProjectPluginHandler : PluginHandler
    {
        internal override void Compile(AgonyPlugin plugin)
        {
            var logFileName = string.Format("compile_log_{0}.txt", plugin.GetUniqueName());
            var logFile = Path.Combine(Settings.Instance.Directories.TempDirectory, logFileName);
            var compileResult = ProjectCompiler.Compile(plugin.ProjectFilePath, logFile);

            File.Delete(logFile);

            if (!compileResult.BuildSuccessful)
            {
                plugin.SetState(PluginState.CompilingError);
                var logFileSavePath = Path.Combine(Settings.Instance.Directories.LogsDirectory, logFileName);
                File.WriteAllBytes(logFileSavePath, compileResult.LogFile);
                Log.Instance.DoLog(string.Format("Failed to compile project: \"{0}\". Build log file saved to \"{1}\".", plugin.ProjectFilePath, logFileSavePath), Log.LogType.Error);
            }
            else
            {
                plugin.SetState(PluginState.Ready);
                plugin.Type = compileResult.Type;
                if (!plugin.IsLocal)
                {
                    var split = plugin.Url.Split('/');
                    plugin.Author = split.Length > 3 ? split[3] : "";
                }
                var exePath = plugin.GetOutputFilePath();
                var pdpPath = Path.Combine(Path.GetDirectoryName(exePath), compileResult.PdbFileName ?? "");
                FileHelper.SafeWriteAllBytes(exePath, compileResult.OutputFile);
                if (Settings.Instance.DeveloperMode && compileResult.PdbFile != null)
                {
                    FileHelper.SafeWriteAllBytes(pdpPath, compileResult.PdbFile);
                }
                else if (File.Exists(pdpPath))
                {
                    try
                    {
                        File.Delete(pdpPath);
                    }
                    catch
                    {
                        // ignored
                    }
                }
                plugin.Version = FileVersionInfo.GetVersionInfo(exePath).FileVersion;
                Log.Instance.DoLog(string.Format("Successfully compiled project: \"{0}\".", plugin.ProjectFilePath));
            }
        }
    }
}