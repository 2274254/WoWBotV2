using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.Pathing;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using SharpDX;
using System.Threading;
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
                if(Vector3.Distance(playerPosition, Gathering.NodeObject.Position) < 3 && Game.Me.CurrentSpeed == 0)
                {
                    Gathering.GatherWaitTill = Game.FrameTimeMS + 3000;
                    //PathingController.ClickToMove(playerPosition.X, playerPosition.Y, playerPosition.Z);//Stop moving.
                    //Thread.Sleep(100);
                    Gathering.NodeObject.Interact();
                    Logger.Log(LogLevel.Debug, "Interacting with node: " + Gathering.NodeObject.Name);
                    Gathering.GatherAttempts++;
                    if(Gathering.GatherAttempts >= 2)
                    {
                        Gathering.BlacklistedNodes.Add(Gathering.NodeObject.Guid.LoWord+"-"+Gathering.NodeObject.Guid.HiWord, Game.FrameTimeMS + (1000 * 60 * 5));
                        Logger.Log(LogLevel.Debug, "Blacklisted node: " + Gathering.NodeObject.Name);
                    }
                    Gathering.NodeObject = null;
                }
                else
                {
                    MoveTo.Move(Gathering.NodeObject.Position);
                    Logger.Log(LogLevel.Debug, "Moving to node: " + Gathering.NodeObject.Name);
                }
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}