using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using Action = Agony.SDK.TreeSharp.Action;

namespace Gathering.Decorators
{
    public static class WalkToCorpse
    {
        static bool ShouldTakeAction()
        {
            if (Game.Me != null && Game.Me.CurrentHP <= 1)
            {
                return true;
            }
            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                Logger.Log(LogLevel.Info, "[Gathering] Walking to corpse.");

            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}