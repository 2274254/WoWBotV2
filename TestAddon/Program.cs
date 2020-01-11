using System;
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
        }

        static void LoadingComplete(EventArgs args)
        {
            Logger.Log(LogLevel.Info, "LoadingComplete triggered inside TestAddon!");
            Console.WriteLine("Game version = " + Agony.SDK.Game.GameVersion);
        }
    }
}
