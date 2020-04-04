using System;
using System.Diagnostics;
using System.ServiceModel;
using AgonyLauncher.Globals;
using AgonyLauncher.Installers;
using AgonyLauncher.Logger;
using AgonyLauncher.Routines;
using AgonyLauncher.UriScheme;
using AgonyLauncher.Utils;

namespace AgonyLauncher.Services
{
    public static class ApiService
    {
        public static void Init()
        {
            SetupUriScheme();
            ApiServiceRoutine.StartService();
        }

        public static void SetupUriScheme()
        {
            try
            {
                UriSchemeInstaller.InstallUriScheme(Constants.UriSchemePrefix, EnvironmentHelper.FileName);
            }
            catch (Exception ex)
            {
                Log.Instance.DoLog(String.Format("Failed to setup elobuddy uri scheme! Exception: {0}", ex), Log.LogType.Error);
            }
        }

        public static void StartUp(string[] args)
        {
            if (args == null || args.Length == 0)
            {
                return;
            }
            if (args.Length > 1)
            {
                var urischeme = Constants.UriSchemePrefix + "://";
                if (args[1].StartsWith(urischeme))
                {
                    UriHandler.Process(args[1]);
                }
            }
        }
    }

    [ServiceContract]
    public interface IAgonyApiService
    {
        [OperationContract]
        void StartUp(string[] args);

        [OperationContract]
        void ShowMainWindow();
    }

    public class AgonyApiService : IAgonyApiService
    {
        public void StartUp(string[] args)
        {
            ApiService.StartUp(args);
        }

        public void ShowMainWindow()
        {
            var handle = Process.GetCurrentProcess().MainWindowHandle;
            NativeImports.ShowWindow(handle, 5);
            NativeImports.SetForegroundWindow(handle);
        }
    }
}