using System;
using System.IO;
using AgonyLauncher.Logger;
using AgonyLauncher.Utils;

namespace AgonyLauncher.Data
{
    internal static class PathRandomizer
    {
        internal static string SandboxDllPath
        {
            get { return Settings.Instance.Directories.TempSandboxDllPath; }
        }

        internal static string SandboxDllName
        {
            get { return Path.GetFileName(SandboxDllPath); }
        }

        internal static string WrapperDllPath
        {
            get { return Settings.Instance.Directories.TempWrapperDllPath; }
        }

        internal static string AgonyDllName
        {
            get { return Path.GetFileName(WrapperDllPath); }
        }

        internal static string CoreDllPath
        {
            get { return Settings.Instance.Directories.TempCoreDllPath; }
        }

        internal static string CoreDllName
        {
            get { return Path.GetFileName(CoreDllPath); }
        }

        internal static void Randomize(bool newDirectory = false)
        {
            if (newDirectory && Directory.Exists(Settings.Instance.Directories.TempCoreDirectory))
            {
                DirectoryHelper.DeleteDirectory(Settings.Instance.Directories.TempCoreDirectory);
            }

            // Set new directory
            if (!Directory.Exists(Settings.Instance.Directories.TempCoreDirectory))
            {
                // Create a random directory to store the core files
                Settings.Instance.Directories.TempCoreDirectory = Path.Combine(Path.GetTempPath(), RandomHelper.RandomString());
                Log.Instance.DoLog(string.Format("Created temporary core directory: \"{0}\"", Settings.Instance.Directories.TempCoreDirectory));
            }

            // Copy Agony.Core.dll file
            try
            {
                if (!File.Exists(Settings.Instance.Directories.TempCoreDllPath))
                {
                    Settings.Instance.Directories.TempCoreDllPath = Path.Combine(Settings.Instance.Directories.TempCoreDirectory, "Agony.Core.dll");
                }
                if (!Md5Hash.Compare(Md5Hash.ComputeFromFile(Settings.Instance.Directories.TempCoreDllPath), Md5Hash.ComputeFromFile(Settings.Instance.Directories.CoreDllPath)))
                {
                    FileHelper.SafeCopyFile(Settings.Instance.Directories.CoreDllPath, Settings.Instance.Directories.TempCoreDirectory, Path.GetFileName(Settings.Instance.Directories.TempCoreDllPath));
                    Log.Instance.DoLog(string.Format("Copied Agony.Core.dll to: \"{0}\"", Settings.Instance.Directories.TempCoreDllPath));
                }
            }
            catch (Exception)
            {
                // ignored
            }

            // Copy Agony.Sandbox.dll file
            try
            {
                if (!File.Exists(Settings.Instance.Directories.TempSandboxDllPath))
                {
                    Settings.Instance.Directories.TempSandboxDllPath =
                        Path.Combine(Settings.Instance.Directories.TempCoreDirectory,
                            RandomHelper.RandomString() + ".dll");
                }

                if (!Md5Hash.Compare(Md5Hash.ComputeFromFile(Settings.Instance.Directories.TempSandboxDllPath), Md5Hash.ComputeFromFile(Settings.Instance.Directories.SandboxDllPath)))
                {
                    FileHelper.SafeCopyFile(Settings.Instance.Directories.SandboxDllPath, Settings.Instance.Directories.TempCoreDirectory, Path.GetFileName(Settings.Instance.Directories.TempSandboxDllPath));

                    // as requested by finn
                    FileHelper.SafeCopyFile(Settings.Instance.Directories.SandboxDllPath, Settings.Instance.Directories.TempCoreDirectory);

                    Log.Instance.DoLog(string.Format("Copied Agony.Sandbox.dll to: \"{0}\"", Settings.Instance.Directories.TempSandboxDllPath));
                }
            }
            catch (Exception)
            {
                // ignored
            }

            // Copy Agony.Wrapper.dll file
            try
            {
                if (!File.Exists(Settings.Instance.Directories.TempWrapperDllPath))
                {
                    Settings.Instance.Directories.TempWrapperDllPath = Path.Combine(Settings.Instance.Directories.TempCoreDirectory, RandomHelper.RandomString() + ".dll");
                }

                if (!Md5Hash.Compare(Md5Hash.ComputeFromFile(Settings.Instance.Directories.TempCoreDirectory), Md5Hash.ComputeFromFile(Settings.Instance.Directories.WrapperDllPath)))
                {
                    FileHelper.SafeCopyFile(Settings.Instance.Directories.WrapperDllPath, Settings.Instance.Directories.TempCoreDirectory, Path.GetFileName(Settings.Instance.Directories.TempWrapperDllPath));
                    // as requested by finn
                    FileHelper.SafeCopyFile(Settings.Instance.Directories.WrapperDllPath, Settings.Instance.Directories.TempCoreDirectory);
                    Log.Instance.DoLog(string.Format("Copied Agony.Wrapper.dll to: \"{0}\"", Settings.Instance.Directories.TempWrapperDllPath));
                }
            }
            catch (Exception)
            {
                // ignored
            }
        }
    }
}