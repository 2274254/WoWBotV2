using Agony.SDK.Enumerations;
using Agony.SDK.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace Agony.SDK.Events
{
    public static class Loading
    {
        public delegate void LoadingCompleteHandler(EventArgs args);

        // Events
        public static event LoadingCompleteHandler OnLoadingComplete;

        // OnLoadingComplete
        public static bool IsLoadingComplete { get; internal set; }
        internal static readonly List<Delegate> LoadingCompleteNotified = new List<Delegate>();

        // ReSharper disable once InconsistentNaming
        internal static bool Locked = true;
        internal static bool _allAddonsLoaded;

        internal static void Initialize()
        {
            // Listen to required events
            Agony.Game.OnEnterInGame += Game_OnEnterInGame;
            Agony.Game.OnExitInGame += Game_OnExitInGame;
            if(Game.IsInGame)
            {
                IsLoadingComplete = true;
                CallLoadingComplete();
            }
        }

        private static void Game_OnEnterInGame(EventArgs args)
        {
            IsLoadingComplete = true;
            CallLoadingComplete();
        }

        private static void Game_OnExitInGame(EventArgs args)
        {
            IsLoadingComplete = false;
            Bot.Stops();
        }

        internal static void CallLoadingComplete()
        {
            var loadingEvent = (OnLoadingComplete);
            if (loadingEvent != null)
            {
                foreach (var handler in loadingEvent.GetInvocationList().Where(o => !LoadingCompleteNotified.Contains(o)).ToArray())
                {
                    // Add handler to notified list
                    //LoadingCompleteNotified.Add(handler);

                    // Notify the handler
                    try
                    {
                        handler.DynamicInvoke(EventArgs.Empty);
                    }
                    catch (Exception e)
                    {
                        Logger.Log(LogLevel.Warn, "Failed to notify OnLoadingComlete listener!\n{0}", e);
                    }
                }
            }

            // Mark all addons loaded
            _allAddonsLoaded = true;
        }
    }
}