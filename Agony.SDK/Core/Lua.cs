using System.Collections.Generic;

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
