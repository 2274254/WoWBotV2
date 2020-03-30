using Agony.SDK.Enumerations;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using Action = Agony.SDK.TreeSharp.Action;

namespace Gathering.Decorators
{
    public static class FindNode
    {
        static bool ShouldTakeAction()
        {
            if
            (
                Gathering.NodeObject == null ||
                Gathering.NodeObject.Type == Agony.WoWObjectType.Invalid
            )
            {
                Gathering.NodeObject = null;
                return true;
            }
            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                Logger.Log(LogLevel.Info, "[Gathering] Searching node.");

            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}