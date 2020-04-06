using Agony.SDK.Enumerations;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using Action = Agony.SDK.TreeSharp.Action;

namespace Battleground.Decorators
{
    public static class RepairEquipment
    {
        static bool ShouldTakeAction()
        {
            //If i am alive, and my bags are full.
            //return true;

            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                Logger.Log(LogLevel.Info, "[Battleground] Repairing equipments.");

            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}