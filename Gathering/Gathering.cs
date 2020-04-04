using Agony;
using Agony.SDK.CommonBot;
using Agony.SDK.TreeSharp;
using Gathering.Decorators;
using System;
using System.Collections.Generic;
using System.Xml;

namespace Gathering
{
    public class Gathering : BotBase
    {
        internal static XmlDocument Configs = new XmlDocument();
        internal static string ConfigsString = "";
        internal static CGGameObject NodeObject = null;
        internal static XmlDocument Profile = new XmlDocument();
        internal static int HotspotIndex = -1;
        internal static long GatherWaitTill = 0;
        internal static int GatherAttempts = 0;
        internal static Dictionary<string, long> BlacklistedNodes = new Dictionary<string, long>();

        public override string Name { get { return "Gathering"; } }

        public override PulseFlags PulseFlags { get { return PulseFlags.All; } }

        private Composite _root;
        private bool hasProfile = false;

        public override void Initialize(string configs = "", string profile = "")
        {
            try
            {
                if (!string.IsNullOrEmpty(configs))
                {
                    Configs = new XmlDocument();
                    Configs.LoadXml(configs);
                }
                if (!string.IsNullOrEmpty(profile))
                {
                    //Profile.Load("D:\\AgonyWoW\\x64\\Release\\Profiles\\Gathering\\Herbalist\\Mining+Herbing 1-75 [Start at Goldshire].xml");
                    Profile.LoadXml(profile);
                    hasProfile = true;
                }
                else
                {

                }
            }
            catch(Exception ex)
            {

            }
        }

        public override Composite Root
        {
            get
            {
                return _root ?? (_root = new PrioritySelector(
                    ReleaseCorpse.BehaviorComposite,
                    WalkToCorpse.BehaviorComposite,
                    Idle.BehaviorComposite,
                    RepairEquipment.BehaviorComposite,
                    ClearBags.BehaviorComposite,
                    UseMount.BehaviorComposite,
                    GoToZone.BehaviorComposite,
                    FindNode.BehaviorComposite,
                    MoveToNode.BehaviorComposite,
                    GatherNode.BehaviorComposite
                ));
            }
        }

        public override void Pulse()
        {
            if (!hasProfile || !Agony.SDK.Game.IsInGame) return;
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