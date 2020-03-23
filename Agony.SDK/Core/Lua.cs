using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agony.SDK.Core
{
    public class Lua
    {
        public static List<object> Call(string functionName, List<int> returns, params object[] parameters)
        {            
            return Agony.Lua.Call(functionName, returns, parameters);
        }
    }
}
