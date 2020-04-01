using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.Pathing;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using SharpDX;
using Action = Agony.SDK.TreeSharp.Action;

namespace Gathering.Decorators
{
    public static class MoveToNode
    {
        static bool ShouldTakeAction()
        {
            if (Gathering.NodeObject != null)
            {
                var playerPosition  = Game.Me.Position;
                var nodePosition    = Gathering.NodeObject.Position;
                if (Vector3.Distance(playerPosition, nodePosition) > 3)
                {
                    return true;
                }
            }
            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                Logger.Log(LogLevel.Info, "[Gathering] Moving to node.");
                if (Gathering.NodeObject != null)
                {
                    var playerPosition = Game.Me.Position;
                    var nodePosition = Gathering.NodeObject.Position;
                    if (Vector3.Distance(playerPosition, nodePosition) > 3)
                    {
                        MoveTo.Move(nodePosition);
                    }
                }
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}