using Agony.Sandbox.Shared;
using AgonyLauncher.Globals;
using AgonyLauncher.Protections;
using AgonyLauncher.Services;
using AgonyLauncher.Utils;
using System;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
//using System.Threading;
using System.Windows;
using System.Windows.Navigation;

namespace AgonyLauncher
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        //private Mutex _mutex;
        private bool _createdNew;

        protected override void OnStartup(StartupEventArgs e)
        {
            //Thread.Sleep(300);
            //AppDomain.CurrentDomain.ProcessExit += OnProcessExit;
            //_mutex = new Mutex(true, "AgonyLauncher", out _createdNew);
            _createdNew = true;
            if (!_createdNew)
            {
                try
                {
                    var proxy = ServiceFactory.CreateProxy<IAgonyApiService>("AgonyApiService");
                    proxy.ShowMainWindow();
                    proxy.StartUp(Environment.GetCommandLineArgs());
                }
                catch (Exception)
                {
                    // ignored
                }
                EnvironmentHelper.ShutDown();
            }
            else
            {
                // Setup protections
                foreach (var protection in (from t in Assembly.GetExecutingAssembly().GetTypes() where t.BaseType == typeof(Protection) select (Protection)Activator.CreateInstance(t)).ToList())
                {
                    #if !DEBUG
                    protection.Initialize();
                    #endif
                }
                EnvironmentHelper.SetValidEnvironment();
                Events.RaiseOnStartUp(e);
            }
            base.OnStartup(e);
        }

        /*
        private void OnProcessExit(object sender, EventArgs eventArgs)
        {
            if (_mutex != null && _createdNew)
            {
                try
                {
                    _mutex.ReleaseMutex();
                }
                catch (Exception)
                {
                    // ignored
                }
            }
        }
        */

        protected override void OnExit(ExitEventArgs e)
        {
            Events.RaiseOnExit(e);
        }

        private void HyperlinkLaunch_RequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
            e.Handled = true;
        }
    }
}