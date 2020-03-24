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

            /*Logger.Log(LogLevel.Info, "Will attempt to get GetUnitPosition from c#");
            var playerPosition = Lua.Call("GetUnitPosition", new System.Collections.Generic.List<int>() { 1, 1, 1 }, "player");
            if(playerPosition.Count == 3)
            {
                Logger.Log(LogLevel.Info, $"Player position = {(double)playerPosition[0]}, {(double)playerPosition[1]}, {(double)playerPosition[2]}");
            }*/
        }
    }
}