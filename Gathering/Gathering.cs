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
        internal static CGGameObject NodeObject = null;
        internal static XmlDocument Profile = new XmlDocument();
        internal static int HotspotIndex = -1;
        internal static long GatherWaitTill = 0;
        internal static int GatherAttempts = 0;
        internal static Dictionary<string, long> BlacklistedNodes = new Dictionary<string, long>();

        public override string Name { get { return "Gathering"; } }

        public override PulseFlags PulseFlags { get { return PulseFlags.All; } }

        private Composite _root;
        private bool started = false;

        public Gathering()
        {
            Console.WriteLine("Gathering Initialized");
            //Profile.Load("D:\\AgonyWoW\\x64\\Release\\Profiles\\Gathering\\Herbalist\\Mining+Herbing 1-75 [Start at Goldshire].xml");
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

        public override void Start()
        {
            Root.Start(null);
            started = true;
        }

        public override void Pulse()
        {
            if (!Agony.SDK.Game.IsInGame) return;
            Root.Start(null);
            Root.Tick(null);
            Root.Stop(null);
        }

        public override void Stop()
        {
            Root.Stop(null);
            started = false;
        }

        public override string ShowConfigs(string configs)
        {
            if(!string.IsNullOrEmpty(configs))
            {
                Configs = new XmlDocument();
                Configs.Load(configs);
            }
            new ConfigsWindow().ShowDialog();
            return Configs.OuterXml;
        }
    }
}