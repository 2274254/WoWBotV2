using Agony.SDK.TreeSharp;
using System;

namespace Agony.SDK.CombatManager
{
    public static class TargetSelector
    {
        private static CGUnit _target = null;
        public static CGUnit ForcedTarget = null;
        private static Composite _root;

        public static CGUnit GetTarget()
        {
            return ForcedTarget ?? _target;
        }

        static TargetSelector()
        {
            _root = new PrioritySelector(
                
            );
            Agony.Game.OnPreTick += Game_OnPreTick;
        }

        private static void Game_OnPreTick(EventArgs args)
        {
            if (!Game.IsInGame) return;
            if (ForcedTarget == null && Game.Me.IsInCombat())
            {
                //Find best target to attack...
                _root.Start(null);
                _root.Tick(null);
                _root.Stop(null);
            }
        }
    }
}