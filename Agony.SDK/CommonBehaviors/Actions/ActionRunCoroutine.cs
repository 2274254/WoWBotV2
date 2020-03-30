using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Action = Agony.SDK.TreeSharp.Action;

namespace Agony.SDK.CommonBehaviors.Actions
{
    public class ActionRunCoroutine : Action
    {
        ActionRunCoroutine(Func<Object, Task<Boolean>> ctx)
        {

        }
    }
}
