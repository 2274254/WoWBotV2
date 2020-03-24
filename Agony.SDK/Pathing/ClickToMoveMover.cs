using System.Numerics;

namespace Agony.SDK.Pathing
{
    class ClickToMoveMover
    {
        public static void MoveTowards(Vector3 location)
        {
            PathingController.ClickToMove(location.X, location.Y, location.Z);
        }
    }
}