using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using Action = Agony.SDK.TreeSharp.Action;

namespace Battleground.Decorators
{
    public static class ReleaseCorpse
    {
        static bool ShouldTakeAction()
        {
            if(Agony.Game.Me.IsDead() && !Agony.Game.Me.IsGhost())
            {
                return true;
            }
            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                Logger.Log(LogLevel.Info, "[Gathering] Releasing corpse.");
                Agony.SDK.Pathing.MoveTo.Reset();
                Agony.PathingController.Reset();
                //
                //TODO: Release corpse...
                Game.Me.RepopMe();
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}