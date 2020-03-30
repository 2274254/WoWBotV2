using Agony;
using Agony.SDK.CommonBot;
using Agony.SDK.TreeSharp;
using Gathering.Decorators;

namespace Gathering
{
    public class Gathering : BotBase
    {
        internal static CGGameObject NodeObject = null;

        public override string Name { get { return "Gathering"; } }

        public override PulseFlags PulseFlags { get { return PulseFlags.All; } }

        private Composite _root;

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
        }

        public override void Pulse()
        {
            if (!Agony.SDK.Game.IsInGame) return;
            Root.Tick(null);
        }

        public override void Stop()
        {
            Root.Stop(null);
        }
    }
}