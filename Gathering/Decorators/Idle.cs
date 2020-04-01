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
            //If i need to wait for what ever reason...
            if(Game.Me == null || Game.Me.IsInCombat())//OR IS CASTING/CHANNELING/OR IN COMBAT...
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
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}