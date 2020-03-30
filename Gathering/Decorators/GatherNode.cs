using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using SharpDX;
using Action = Agony.SDK.TreeSharp.Action;

namespace Gathering.Decorators
{
    public static class GatherNode
    {
        static bool ShouldTakeAction()
        {
            if(Gathering.NodeObject != null)
            {
                //If interactable ?
                return true;
            }
            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                Logger.Log(LogLevel.Info, "[Gathering] Gathering node.");

            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}