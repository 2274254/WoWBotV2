using Agony.SDK.CommonBot;
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
                        CurrentBot = (BotBase)pluginBase;
                        CurrentBot.Initialize(PluginConfigs.ContainsKey(assembly.FullName) ? PluginConfigs[assembly.FullName] : "", CurrentProfile);
                        Console.WriteLine(string.Format("Initialized {0} BotBase with profile: ", CurrentBot.Name, CurrentProfile));
                    }
                }
            }
            Agony.Game.OnTick += Game_OnTick;
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