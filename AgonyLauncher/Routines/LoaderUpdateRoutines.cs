using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows;
using AgonyLauncher.Data;
using AgonyLauncher.Utils;
using AgonyLauncher.Windows;

namespace AgonyLauncher.Routines
{
    internal static class LoaderUpdateRoutines
    {
        internal static void InstallFilesRoutine(UpdateWindow ui, Dictionary<string, object> args)
        {
            if(ui != null)
            {
                ui.CurrentProgress = ui.MaxProgress;
                ui.OveralCurrentProgress = ui.OveralMaxProgress;
                ui.Status = "Installing files";
                ui.Details = "Copying files, please wait...";
            }
            foreach (
                var file in
                    Directory.GetFiles(Settings.Instance.Directories.SystemDirectory, "*.dll",
                        SearchOption.AllDirectories)
                        .Where(
                            file =>
                                !Md5Hash.Compare(Md5Hash.ComputeFromFile(file),
                                    Md5Hash.ComputeFromFile(
                                        Path.Combine(Settings.Instance.Directories.LibrariesDirectory,
                                            Path.GetFileName(file))))))
            {
                try
                {
                    FileHelper.CopyFile(file, Settings.Instance.Directories.LibrariesDirectory);
                }
                catch (Exception)
                {
                    MessageBox.Show(string.Format("Failed to copy file: {0}", Path.GetFileName(file)), "Installing files", MessageBoxButton.OK, MessageBoxImage.Information);
                }
            }
            foreach (var file in Directory.GetFiles(Environment.CurrentDirectory, "*.old", SearchOption.AllDirectories))
            {
                try
                {
                    File.Delete(file);
                }
                catch (Exception)
                {
                    // ignored
                }
            }
            if (args.ContainsKey("restartRequired") && (bool)args["restartRequired"])
            {
                EnvironmentHelper.Restart(true);
            }
            PathRandomizer.Randomize();
        }
    }
}
