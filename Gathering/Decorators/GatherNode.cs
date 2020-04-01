using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.Pathing;
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
                var playerPosition = Game.Me.Position;
                if(Vector3.Distance(playerPosition, Gathering.NodeObject.Position) < 3)
                {
                    Gathering.NodeObject.Interact();
                    Logger.Log(LogLevel.Debug, "Interacting with node ?");
                }
                else
                {
                    MoveTo.Move(Gathering.NodeObject.Position);
                    Logger.Log(LogLevel.Debug, "Moving to node ?");
                }
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}