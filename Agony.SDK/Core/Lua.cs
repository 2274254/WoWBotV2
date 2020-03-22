using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agony.SDK.Core
{
    public class Lua
    {
        public static T Call<T>(string functionName, params object[] parameters)
        {            
            return Agony.Lua.Call<T>(functionName, parameters);
        }
    }
}
