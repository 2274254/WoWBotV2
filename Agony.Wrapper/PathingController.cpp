#include "PathingController.h"
#include "../Agony/Navigation.h"

namespace Agony
{
    void PathingController::ClickToMove(float x, float y, float z)
    {
        Vector3 point = Vector3(x, y, z);//Make sure this is the right order.
        Agony::Native::Navigation::ClickToMove(&point);
    }
}
