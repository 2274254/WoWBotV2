using Agony.SDK.CommonBot;
using Agony.SDK.Enumerations;
using Agony.SDK.Utils;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Agony.SDK
{
    public static class Bot
    {
        internal static BotBase CurrentBot = null;
        internal static Dictionary<string, string> PluginConfigs = new Dictionary<string, string>();
        internal static string CurrentProfile = "";

        public static void Initialize()
        {
            foreach(var assembly in AppDomain.CurrentDomain.GetAssemblies())
            {
                IEnumerable<Type> plugins = assembly.GetTypes().Where(y => typeof(PluginBase).IsAssignableFrom(y) && !y.IsAbstract && !y.IsInterface);
                foreach(var plugin in plugins)
                {
                    var pluginBase = (PluginBase)Activator.CreateInstance(plugin);
                    if (pluginBase.Type == PluginType.BotBase)
                    {
                        var configs = PluginConfigs.ContainsKey(assembly.FullName) ? PluginConfigs[assembly.FullName] : "";
                        CurrentBot = (BotBase)pluginBase;
                        CurrentBot.Initialize(configs, CurrentProfile);
                        Console.WriteLine(string.Format("Initialized {0} BotBase with profile: {1}", CurrentBot.Name, CurrentProfile));
                    }
                }
            }
            Agony.Game.OnTick += Game_OnTick;
        }

        public static void Starts()
        {
            //Trigger Start on all plugins...
            if (Bot.CurrentBot != null)
            {
                Logger.Log(LogLevel.Debug, "Called on start on the botbase");
                Bot.CurrentBot.Start();
            }

            Logger.Log(LogLevel.Debug, "After called on start on the botbase");
            //TODO: Plugins, Combat routine later once they exists...
        }

        public static void Stops()
        {
            //Trigger Start on all plugins...
            if (Bot.CurrentBot != null)
            {
                Logger.Log(LogLevel.Debug, "Called on stop on the botbase");
                Bot.CurrentBot.Stop();
            }
            Logger.Log(LogLevel.Debug, "After called on stop on the botbase");
            //TODO: Plugins, Combat routine later once they exists...
        }

        private static void Game_OnTick(System.EventArgs args)
        {
            if(CurrentBot != null)
            {
                CurrentBot.Pulse();
            }
        }
    }
}