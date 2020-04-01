using SharpDX;
using System.Collections.Generic;

namespace Agony.SDK.Pathing
{
    public static class MoveTo
    {
        static List<Vector3> waypoints = new List<Vector3>();
        static Vector3 targetLocation = Vector3.Zero;
        static Vector3 nextWaypointPosition = Vector3.Zero;
        static int nextWaypointIndex = 0;

        static MoveTo()
        {
            Agony.Game.OnTick += Game_OnTick;
        }

        private static void Game_OnTick(System.EventArgs args)
        {
            if(targetLocation != Vector3.Zero && nextWaypointPosition != Vector3.Zero)
            {
                var playerPosition = Agony.Game.Me.Position;
                var distanceToWaypoint = Vector3.Distance(playerPosition, nextWaypointPosition);
                System.Console.WriteLine("Distance to next waypoint: " + distanceToWaypoint);
                if (distanceToWaypoint < 3)
                {
                    nextWaypointIndex++;
                    if(nextWaypointIndex < waypoints.Count)
                    {
                        nextWaypointPosition = waypoints[nextWaypointIndex];
                        PathingController.ClickToMove(nextWaypointPosition.X, nextWaypointPosition.Y, nextWaypointPosition.Z);
                    }
                    else
                    {
                        waypoints = new List<Vector3>();
                        targetLocation = Vector3.Zero;
                        nextWaypointPosition = Vector3.Zero;
                        nextWaypointIndex = 0;
                    }
                }
                else if(Agony.Game.Me.CurrentSpeed < 1)
                {
                    PathingController.Reset();
                    PathingController.ClickToMove(nextWaypointPosition.X, nextWaypointPosition.Y, nextWaypointPosition.Z);
                }
            }
        }

        public static void Move(Vector3 location)
        {
            if (targetLocation == location) return;
            var playerPosition = Agony.Game.Me.Position;
            waypoints = PathingController.CalculatePath(0, playerPosition, location);
            if(waypoints.Count > 1)
            {
                targetLocation = location;
                nextWaypointIndex = 1;
                nextWaypointPosition = waypoints[nextWaypointIndex];
                PathingController.ClickToMove(nextWaypointPosition.X, nextWaypointPosition.Y, nextWaypointPosition.Z);
            }
        }

        public static void Reset()
        {
            waypoints = new List<Vector3>();
            targetLocation = Vector3.Zero;
            nextWaypointPosition = Vector3.Zero;
            nextWaypointIndex = 0;
        }
    }
}