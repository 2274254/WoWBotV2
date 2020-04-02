using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.Pathing;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using SharpDX;
using System;
using System.Collections.Generic;
using Action = Agony.SDK.TreeSharp.Action;

namespace Gathering.Decorators
{
    public static class WalkToCorpse
    {
        static bool ShouldTakeAction()
        {
            if (Game.Me.IsGhost())
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
                var player = Game.Me;
                //var test = Lua.Call("GetProfessionInfo", new List<int>(){ 2, 2, 1, 1, 1, 1, 1, 1, 1, 1 }, 5);
                //Logger.Log(LogLevel.Debug, test[0].ToString() + " = " + Convert.ToInt32(test[2]) + "/" + Convert.ToInt32(test[3]));
                if(Vector3.Distance(player.Position, Game.CorpseLocation) < 40)
                {
                    MoveTo.Reset();
                    PathingController.ClickToMove(player.Position.X, player.Position.Y, player.Position.Z);
                    player.RetrieveCorpse();
                    Logger.Log(LogLevel.Debug, "Retrieving corpse");
                }
                else if(player.CurrentSpeed == 0)
                {
                    MoveTo.Move(Game.CorpseLocation);
                }
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}