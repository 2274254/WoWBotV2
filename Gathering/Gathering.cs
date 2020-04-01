using Agony;
using Agony.SDK.CommonBot;
using Agony.SDK.TreeSharp;
using Gathering.Decorators;
using System;
using System.Xml;

namespace Gathering
{
    public class Gathering : BotBase
    {
        internal static CGGameObject NodeObject = null;
        internal static XmlDocument Profile = new XmlDocument();
        internal static int HotspotIndex = -1;

        public override string Name { get { return "Gathering"; } }

        public override PulseFlags PulseFlags { get { return PulseFlags.All; } }

        private Composite _root;
        private bool started = false;

        public Gathering()
        {
            Console.WriteLine("Gathering Initialized");
            Profile.Load("D:\\AgonyWoW\\x64\\Release\\Profiles\\Gathering\\Herbalist\\Mining+Herbing 1-75 [Start at Goldshire].xml");
        }

        public override Composite Root
        {
            get
            {
                return _root ?? (_root = new PrioritySelector(
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
            if(!started) Root.Start(null);
            Root.Tick(null);
        }

        public override void Stop()
        {
            Root.Stop(null);
            started = false;
        }
    }
}