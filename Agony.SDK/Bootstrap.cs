using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Threading;
using Agony.SDK.Events;
using Agony.SDK.Enumerations;
using Agony.SDK.Utils;
using System.Linq;

namespace Agony.SDK
{
    public static class Bootstrap
    {
        internal static readonly Process CurrentProcess = Process.GetCurrentProcess();
        internal static bool _initialized;
        internal static readonly List<Type> SkipInitialization = new List<Type>();

        public static void Init(Dictionary<string, string> pluginConfigs, string currentProfile)
        {
            if (_initialized)
            {
                return;
            }
            _initialized = true;

            Bot.PluginConfigs = pluginConfigs;
            Bot.CurrentProfile = currentProfile;

            if(pluginConfigs.Count > 0)
            {
                Logger.Log(LogLevel.Info, "Init Bootstrap with profile: " + Bot.CurrentProfile + " and configs count = " + Bot.PluginConfigs.Count + " First config = " + Bot.PluginConfigs.First().Value);
            }
            
            // Set thread culture
            CultureInfo.DefaultThreadCurrentCulture = CultureInfo.InvariantCulture;
            CultureInfo.DefaultThreadCurrentUICulture = CultureInfo.InvariantCulture;
            Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;
            Thread.CurrentThread.CurrentUICulture = CultureInfo.InvariantCulture;
            // Run Bootstrap Init
            BootstrapRun.Initialize();
        }
    }

    internal static class BootstrapRun
    {
        internal static readonly Dictionary<Action, string> ToLoadActions = new Dictionary<Action, string>
        {
            { Bot.Initialize, null },
        };

        internal static void Initialize()
        {
            // Add the SDK loading to a special locked action list
            Loading.OnLoadingComplete += delegate
            {
                // Spectator mode check
                try
                {
                    Logger.Info("----------------------------------");
                    Logger.Info("Loading SDK Bootstrap");
                    Logger.Info("----------------------------------");

                    // Unlock Loading event
                    Loading.Locked = false;
                }
                catch (Exception)
                {
                    // ignored
                }

                // Invoke all actions
                foreach (var entry in ToLoadActions)
                {
                    TryLoad(entry.Key, entry.Value);
                }
                ToLoadActions.Clear();

                Bot.Starts();

                //Chat.Print("<font color=\"#0080ff\" >>> Welcome back, Buddy</font>");
                Logger.Info("----------------------------------");
                Logger.Info("SDK Bootstrap fully loaded!");
                Logger.Info("----------------------------------");
            };

            // Initialize loading event
            Loading.Initialize();
        }

        internal static void TryLoad(Action action, string message)
        {
            try
            {
                if (Bootstrap.SkipInitialization.Contains(action.GetType()))
                {
                    Logger.Debug("Skipping initialization for " + action.GetType().Name);
                    return;
                }
                action();
                if (!string.IsNullOrWhiteSpace(message))
                {
                    Logger.Log(LogLevel.Info, message);
                }
            }
            catch (Exception e)
            {
                Logger.Log(LogLevel.Error, "SDK Bootstrap error:\n{0}", e);
            }
        }
    }
}