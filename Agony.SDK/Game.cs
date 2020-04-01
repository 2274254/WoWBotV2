namespace Agony.SDK
{
    public class Game
    {
        public static CGLocalPlayer Me { get { return Agony.Game.Me; } }
        public static bool IsInGame { get { return Agony.Game.IsInGame; } }
        public static string GameVersion { get { return Agony.Game.GameVersion; } }
    }
}