using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;
using System.Windows;
using AgonyLauncher.Data;
using AgonyLauncher.Globals;
using AgonyLauncher.Injection;
using AgonyLauncher.Utils;

namespace AgonyLauncher.Routines
{
    public static class InjectionRoutine
    {
        private static bool _execute;

        public static bool Pause { get; set; }

        public static Thread InjectionThread { get; private set; }

        public static bool IsRunning
        {
            get { return InjectionThread != null && InjectionThread.IsAlive; }
        }

        public static void StartRoutine()
        {
            if (IsRunning)
            {
                return;
            }

            _execute = true;
            InjectionThread = new Thread(CoreInjectionRoutine) { IsBackground = true };
            InjectionThread.Start();
        }

        public static void StopRoutine(int timeout = 1500)
        {
            if (!IsRunning)
            {
                return;
            }

            _execute = false;
            Thread.Sleep(timeout);

            if (IsRunning)
            {
                InjectionThread.Abort();
            }
        }

        public static Process[] GetProcesses(string[] processesNames)
        {
            var list = new List<Process>();

            foreach (var name in processesNames)
            {
                list.AddRange(Process.GetProcessesByName(name));
            }

            return list.ToArray();
        }

        public static Process[] GetProcesses(string processName)
        {
            return GetProcesses(new[] { processName });
        }

        public static Process[] GetLeagueProcesses()
        {
            return GetProcesses(Constants.WowProcesses);
        }

        public static ProcessModule GetModule(string moduleName, Process p)
        {
            moduleName = moduleName.ToLower();
            for (var i = 0; i < p.Modules.Count; i++)
                if (p.Modules[i].ModuleName.ToLower() == moduleName)
                    return p.Modules[i];
            return null;
        }

        public static bool IsProcessInjected(Process p)
        {
            try
            {
                return GetModule("Agony.Core.dll", p) != null;
            }
            catch (Exception)
            {
                return true;
            }
        }

        public static bool IsAgonyInjected()
        {
            return Process.GetProcesses().Any(IsProcessInjected);
        }

        public static bool IsCurrentCoreFileInjected()
        {
            try
            {
                return
                    GetLeagueProcesses()
                        .Select(p => GetModule("Agony.Core.dll", p))
                        .Where(m => m != null)
                        .Any(m => string.Equals(m.FileName, PathRandomizer.CoreDllPath, StringComparison.CurrentCultureIgnoreCase));
            }
            catch (Exception)
            {
                return true;
            }
        }

        private static void CoreInjectionRoutine(object args)
        {
            Thread.Sleep(3000); // delay on startup

            while (_execute)
            {
                if (Pause)
                {
                    continue;
                }

                //ClientInjectionRoutine();

                //if (Settings.Instance.EnableInjection)
                {
                    foreach (var p in GetLeagueProcesses().Where(p => !IsProcessInjected(p) && !string.IsNullOrEmpty(p.MainWindowTitle)))
                    {
                        var pHash = Md5Hash.ComputeFromFile(p.MainModule.FileName);

                        /*if (!Md5Hash.Compare(LoaderUpdate.LeagueHash, pHash) && !DeveloperHelper.IsDeveloper)
                        {
                            MessageBox.Show(string.Format(MultiLanguage.Text.ErrorInjectionHashMissmatch, pHash.ToLower(), LoaderUpdate.LeagueHash.ToLower()),
                                "Injection Aborted", MessageBoxButton.OK, MessageBoxImage.Warning);

                            continue;
                        }*/

                        //var result = Injector.InjectCore(p.Id, Settings.Instance.Directories.TempCoreDllPath);
                        var result = Injector.InjectCore(p.Id, Path.Combine(Settings.Instance.Directories.LibrariesDirectory, "Agony.Core.dll"));
                        //Events.RaiseOnInject(p.Id, result);
                    }
                }
                Thread.Sleep(2500);
            }
        }
    }
}
