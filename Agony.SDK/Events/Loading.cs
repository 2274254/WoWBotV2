using Agony.SDK.Enumerations;
using Agony.SDK.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace Agony.SDK.Events
{
    public static class Loading
    {
        public delegate void LoadingCompleteHandler(EventArgs args);

        // Events
        public static event LoadingCompleteHandler OnLoadingComplete;

        // OnLoadingComplete
        public static bool IsLoadingComplete { get; internal set; }
        internal static readonly List<Action> AsyncLockedActions = new List<Action>();
        internal static readonly List<Action> AlwaysLoadActions = new List<Action>();
        internal static readonly List<Delegate> LoadingCompleteNotified = new List<Delegate>();

        // ReSharper disable once InconsistentNaming
        internal static bool Locked = true;
        internal static bool _allAddonsLoaded;

        internal static void Initialize()
        {
            // Listen to required events
            //Game.OnTick += OnTick;

            //TODO: FIX THIS:
            Task.Factory.StartNew(() =>
            {
                Thread.Sleep(100);
                IsLoadingComplete = true;
                CallLoadingComplete();
            });
        }

        internal static void OnTick(EventArgs args)
        {
            // OnLoadingComplete
            if(Game.IsInGame)
            {
                IsLoadingComplete = true;
                CallLoadingComplete();
            }
            else
            {
                IsLoadingComplete = false;
            }
        }

        internal static void CallLoadingComplete()
        {
            if (Locked)
            {
                foreach (var action in AsyncLockedActions)
                {
                    try
                    {
                        var asyncAction = action;
                        ThreadPool.QueueUserWorkItem(delegate { asyncAction(); }, null);
                    }
                    catch (Exception e)
                    {
                        Logger.Warn("Failed to load async locked action, SDK internal error!");
                        Logger.Error(e.ToString());
                    }
                }
                AsyncLockedActions.Clear();
            }
            else
            {
                foreach (var action in AlwaysLoadActions)
                {
                    try
                    {
                        action();
                    }
                    catch (Exception e)
                    {
                        Logger.Warn("Failed to load internal action, SDK error!");
                        Logger.Error(e.ToString());
                    }
                }
                AlwaysLoadActions.Clear();

                var loadingEvent = (OnLoadingComplete);
                if (loadingEvent != null)
                {
                    foreach (var handler in loadingEvent.GetInvocationList().Where(o => !LoadingCompleteNotified.Contains(o)).ToArray())
                    {
                        // Add handler to notified list
                        LoadingCompleteNotified.Add(handler);

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
}