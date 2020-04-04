using Agony.Sandbox.Shared;
using AgonyLauncher.Logger;
using AgonyLauncher.Services;
using System;
using System.ServiceModel;
using System.Windows;

namespace AgonyLauncher.Routines
{
    public static class ApiServiceRoutine
    {
        private static ServiceHost _loaderServiceHost;
        public static void StartService()
        {
            _loaderServiceHost = ServiceFactory.CreateService<IAgonyApiService, AgonyApiService>(true, "AgonyApiService");
            _loaderServiceHost.Faulted += OnLoaderServiceFaulted;
        }
        private static void OnLoaderServiceFaulted(object sender, EventArgs eventArgs)
        {
            Log.Instance.DoLog("IAgonyApiService faulted, trying restart", Log.LogType.Error);

            _loaderServiceHost.Faulted -= OnLoaderServiceFaulted;
            _loaderServiceHost.Abort();

            try
            {
                StartService();
            }
            catch (Exception ex)
            {
                Log.Instance.DoLog(string.Format("IElobuddyApiService failed to start, exception: {0}", ex), Log.LogType.Error);
                MessageBox.Show("IAgonyApiService failed to start. Please restart the loader!", "Fatal Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}