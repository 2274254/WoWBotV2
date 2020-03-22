using System;
using Agony.SDK;
using Agony.SDK.Core;
using Agony.SDK.Enumerations;
using Agony.SDK.Events;
using Agony.SDK.Utils;

namespace TestAddon
{
    class Program
    {
        private static void Main(string[] args)
        {
            Logger.Log(LogLevel.Info, "TestAddon has been loaded!");
            Loading.OnLoadingComplete += LoadingComplete;
            Messages.OnMessage += Messages_OnMessage;

            //var playerPosition = Lua.Execute("GetUnitPosition('player')");
            //Logger.Log(LogLevel.Info, $"Player position = {playerPosition}");
        }

        private static void Messages_OnMessage(Messages.WindowMessage args)
        {
            Console.WriteLine("ON MESSAGE...");
            if (args.Message == WindowMessages.KeyUp && args.Handle.WParam == 0x74)
            {
                Console.WriteLine("PRESSED THE RELOAD KEY");
            }
        }

        static void LoadingComplete(EventArgs args)
        {
            Logger.Log(LogLevel.Info, "LoadingComplete triggered inside TestAddon!");
            Logger.Log(LogLevel.Info, "Game version = " + Game.GameVersion);
        }
    }
}
