using System.Windows;

namespace AgonyLauncher.Globals
{
    public static class Events
    {
        public delegate void OnStartUpDelegate(StartupEventArgs e);

        public static event OnStartUpDelegate OnStartUp;

        public delegate void OnExitDelegate(ExitEventArgs e);

        public static event OnExitDelegate OnExit;

        static Events()
        {
            EventHandlers.Initialize();
        }

        public static void RaiseOnExit(ExitEventArgs e)
        {
            if (OnExit != null)
            {
                OnExit(e);
            }
        }

        public static void RaiseOnStartUp(StartupEventArgs e)
        {
            if (OnStartUp != null)
            {
                OnStartUp(e);
            }
        }
    }
}
