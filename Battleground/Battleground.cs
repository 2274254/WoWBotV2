using Agony;
using Agony.SDK.CommonBot;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using Agony.WoWInternals;
using Battleground.Decorators;
using System;
using System.Collections.Generic;
using System.Xml;

namespace Battleground
{
    public class Battleground : BotBase
    {
        internal static XmlDocument Configs = new XmlDocument();
        internal static string ConfigsString = "";
        internal static CGGameObject NodeObject = null;
        internal static XmlDocument Profile = new XmlDocument();
        internal static int HotspotIndex = -1;
        internal static long GatherWaitTill = 0;
        internal static int GatherAttempts = 0;
        internal static Dictionary<string, long> BlacklistedNodes = new Dictionary<string, long>();

        public override string Name { get { return "Battleground"; } }

        public override PulseFlags PulseFlags { get { return PulseFlags.All; } }

        private Composite _root;

        public override void Initialize(string configs = "", string profile = "")
        {
            try
            {
                if (!string.IsNullOrEmpty(configs))
                {
                    Configs = new XmlDocument();
                    Configs.LoadXml(configs);
                }
            }
            catch(Exception ex)
            {
                Logger.Log(Agony.SDK.Enumerations.LogLevel.Error, ex.Message + Environment.NewLine + ex.StackTrace);
            }
        }

        public override Composite Root
        {
            get
            {
                return _root ?? (_root = new PrioritySelector(
                    ReleaseCorpse.BehaviorComposite,
                    RepairEquipment.BehaviorComposite,
                    Idle.BehaviorComposite,
                    UseMount.BehaviorComposite
                    
                ));
            }
        }

        public override void Start()
        {
            Console.WriteLine("Received Start");
            LuaEvents.AttachEvent("UPDATE_BATTLEFIELD_STATUS", OnUpdateBattlefieldStatus);
            LuaEvents.AttachEvent("GOSSIP_SHOW", OnUpdateBattlefieldStatus);
        }

        public override void Stop()
        {
            Console.WriteLine("Received Stop");
            LuaEvents.DetachEvent("UPDATE_BATTLEFIELD_STATUS", OnUpdateBattlefieldStatus);
            LuaEvents.DetachEvent("GOSSIP_SHOW", OnUpdateBattlefieldStatus);
        }

        public override void Pulse()
        {
            if (!Agony.SDK.Game.IsInGame) return;
            Root.Start(null);
            Root.Tick(null);
            Root.Stop(null);
        }

        public override string ShowConfigs(string configs)
        {
            if(!string.IsNullOrEmpty(configs))
            {
                ConfigsString = configs;
            }
            new ConfigsWindow().ShowDialog();
            return ConfigsString;
        }

        //WOW LUA EVENTS
        public void OnUpdateBattlefieldStatus(object sender, LuaEventArgs args)
        {
            var name = args.EventName;
            //local status, mapName, _, _, _, queueType, gameType = GetBattlefieldStatus(1);
            Logger.Log(Agony.SDK.Enumerations.LogLevel.Info, "Received " + args.EventName + " in C#");
            int i = 1;
            foreach(var arg in args.Args)
            {
                if (arg == null)
                {
                    Logger.Log(Agony.SDK.Enumerations.LogLevel.Debug, string.Format("Arg {0} is null", i));
                }
                else if (arg.GetType() == typeof(UIntPtr))
                {
                    Logger.Log(Agony.SDK.Enumerations.LogLevel.Debug, string.Format("Arg {0} = {1}", i, (UIntPtr)arg));
                }
                else if (arg.GetType() == typeof(string))
                {
                    Logger.Log(Agony.SDK.Enumerations.LogLevel.Debug, string.Format("Arg {0} = {1}", i, (string)arg));
                }
                else if (arg.GetType() == typeof(double))
                {
                    Logger.Log(Agony.SDK.Enumerations.LogLevel.Debug, string.Format("Arg {0} = {1}", i, (double)arg));
                }
                else if (arg.GetType() == typeof(bool))
                {
                    Logger.Log(Agony.SDK.Enumerations.LogLevel.Debug, string.Format("Arg {0} = {1}", i, (bool)arg));
                }
                i++;
            }
        }
    }
}