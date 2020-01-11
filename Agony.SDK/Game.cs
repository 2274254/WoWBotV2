using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agony.SDK
{
    public class Game
    {
        public static bool IsInGame { get { return Agony.Game.IsInGame; } }
        public static string GameVersion { get { return Agony.Game.GameVersion; } }
    }
}
