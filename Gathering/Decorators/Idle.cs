using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using Action = Agony.SDK.TreeSharp.Action;

namespace Gathering.Decorators
{
    public static class Idle
    {
        static bool ShouldTakeAction()
        {
            var player = Game.Me;
            //If i need to wait for what ever reason...
            if(player == null || player.IsInCombat() || player.IsCasting() || Gathering.GatherWaitTill > Game.FrameTimeMS)//OR IS CASTING/CHANNELING/OR IN COMBAT...
            {
                return true;
            }
            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                Logger.Log(LogLevel.Info, "[Gathering] Waiting...");
                PathingController.Reset();
                Gathering.HotspotIndex = -1;
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}