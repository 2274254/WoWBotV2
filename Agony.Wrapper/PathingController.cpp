#include "PathingController.h"
#include "../Agony/Game.h"
#include "../Agony/Navigation.h"

namespace Agony
{
    //float PathingController::lastClickPositionX = 0;
    //float PathingController::lastClickPositionY = 0;
    //float PathingController::lastClickPositionZ = 0;

    void PathingController::ClickToMove(float x, float y, float z)
    {
        if (lastClickPositionX != x && lastClickPositionY != y && lastClickPositionZ != z)
        {
            lastClickPositionX = x;
            lastClickPositionY = y;
            lastClickPositionZ = z;
            Vector3 point = Vector3(x, y, z);//Make sure this is the right order.
            Agony::Native::Navigation::ClickToMove(&point);
        }
    }

    System::Collections::Generic::List<SharpDX::Vector3>^ PathingController::CalculatePath(int instanceId, SharpDX::Vector3 from, SharpDX::Vector3 to)
    {
        System::Collections::Generic::List<SharpDX::Vector3>^ returnList = gcnew System::Collections::Generic::List<SharpDX::Vector3>();        
        Vector3 start = Vector3(from.X, from.Y, from.Z);
        Vector3 end = Vector3(to.X, to.Y, to.Z);
        Agony::Native::Navigation::GetInstance()->Initialize(instanceId);
        int waypointsLenght = 0;
        auto waypoints = Agony::Native::Navigation::GetInstance()->CalculatePath(instanceId, start, end, false, &waypointsLenght, false);
        for (int i = 0; i < waypointsLenght; i++)
        {
            returnList->Add(SharpDX::Vector3(waypoints[i].x, waypoints[i].y, waypoints[i].z));
        }
        /*
        Drawings::CurrentWaypoint = 0;
        Drawings::Waypoints = Agony::Native::Navigation::GetInstance()->CalculatePath(instanceId, start, end, false, &Drawings::WaypointsLenght, false);
        for (int i = 0; i < Drawings::CurrentWaypoint; i++)
        {
            returnList->Add(SharpDX::Vector3(Drawings::Waypoints[i].x, Drawings::Waypoints[i].y, Drawings::Waypoints[i].z));
        }
        */
        return returnList;
    }

    void PathingController::MoveTo(float x, float y, float z)
    {
        auto playerPosition = Agony::Native::Game::Me()->GetPosition();
        Agony::Native::Navigation* navigation = Agony::Native::Navigation::GetInstance();

        Vector3 start = Vector3(playerPosition.x, playerPosition.y, playerPosition.z);
        Vector3 end = Vector3(x, y, z);

        int instanceId = 0;
        

        


    }

    void PathingController::Reset()
    {
        lastClickPositionX = 0;
        lastClickPositionY = 0;
        lastClickPositionZ = 0;
    }
}
