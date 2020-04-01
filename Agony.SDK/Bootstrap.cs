using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Threading;
using Agony.SDK.Events;
using Agony.SDK.Enumerations;
using Agony.SDK.Utils;

namespace Agony.SDK
{
    public static class Bootstrap
    {
        internal static readonly Process CurrentProcess = Process.GetCurrentProcess();
        internal static bool _initialized;
        internal static readonly List<Type> SkipInitialization = new List<Type>();

        public static void Init(string[] args)
        {
            if (_initialized)
            {
                return;
            }
            Logger.Log(LogLevel.Info, "Init Bootstrap");
            _initialized = true;
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
        internal static readonly Dictionary<Action, string> AlwaysLoadAction = new Dictionary<Action, string>
        {
            /*{ MainMenu.Initialize, null },
            { EntityManager.Initialize, null },
            { Item.Initialize, null },
            { SpellDatabase.Initialize, "SpellDatabase loaded." }*/
        };

        internal static readonly Dictionary<Action, string> ToLoadActions = new Dictionary<Action, string>
        {
#if !DEBUG
            /*{ Core.Initialize, null },
            { Auth.Initialize, null },
            { TargetSelector.Initialize, "TargetSelector loaded." },
            { Orbwalker.Initialize, "Orbwalker loaded." },
            { Prediction.Initialize, "Prediction loaded." },
            { DamageLibrary.Initialize, "DamageLibrary loaded." },
            { SummonerSpells.Initialize, "SummonerSpells loaded." },*/
#endif
        };
        internal static void Initialize()
        {
            // Initialize loading event
            Loading.Initialize();

            Loading.AsyncLockedActions.Add(delegate
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
            });

            // Load the menu
            Loading.AlwaysLoadActions.Add(delegate
            {
                // Default ticks per second
                //Game.TicksPerSecond = 25;

                // Invoke all actions
                foreach (var entry in AlwaysLoadAction)
                {
                    TryLoad(entry.Key, entry.Value);
                }
                AlwaysLoadAction.Clear();
            });

            // Add the SDK loading to a special locked action list
            Loading.OnLoadingComplete += delegate
            {
                // Invoke all actions
                foreach (var entry in ToLoadActions)
                {
                    TryLoad(entry.Key, entry.Value);
                }
                ToLoadActions.Clear();
                //Chat.Print("<font color=\"#0080ff\" >>> Welcome back, Buddy</font>");
                Logger.Info("----------------------------------");
                Logger.Info("SDK Bootstrap fully loaded!");
                Logger.Info("----------------------------------");
                Bot.Initialize();
            };
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
