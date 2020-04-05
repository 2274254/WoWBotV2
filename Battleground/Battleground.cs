using Agony;
using Agony.SDK.CommonBot;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using Gathering.Decorators;
using System;
using System.Collections.Generic;
using System.Xml;

namespace Gathering
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
    }
}