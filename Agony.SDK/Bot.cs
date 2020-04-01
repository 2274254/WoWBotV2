using Agony.SDK.CommonBot;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Agony.SDK
{
    public static class Bot
    {
        public static BotBase CurrentBot = null;

        public static void Initialize()
        {
            IEnumerable<Type> currentAssemblytypes = AppDomain.CurrentDomain.GetAssemblies().SelectMany(x => x.GetTypes()).Where(y => typeof(BotBase).IsAssignableFrom(y) && !y.IsAbstract && !y.IsInterface);
            Console.WriteLine(string.Format("Found {0} BotBase", currentAssemblytypes.Count()));
            if(currentAssemblytypes.Any())
            {
                CurrentBot = (BotBase)Activator.CreateInstance(currentAssemblytypes.First());
                Console.WriteLine(string.Format("Initialized {0} BotBase", CurrentBot.Name));
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