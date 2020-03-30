using Agony.SDK.TreeSharp;
using System;

namespace Agony.SDK.CommonBot
{
    public enum BotState
    {
        Stopped,
        Paused,
        Waiting,
        Running
    }

    [Flags]
    public enum PulseFlags : uint
    {
        Objects = 1,
        Plugins = 2,
        BotEvents = 8,
        Navigator = 16,
        Targeting = 32,
        Looting = 64,
        InfoPanel = 128,
        Lua = 256,
        CharacterManager = 512,
        Avoidance = 1024,
        All = 4294967295
    }

    public class BotBase
    {
        public virtual string Name { get { return ""; } }
        public virtual PulseFlags PulseFlags { get { return PulseFlags.All; } }
        public virtual Composite Root {  get { return null; } }
        public virtual void Start() { }
        public virtual void Stop() { }
        public virtual void Initialize() { }
        public virtual void Pulse() { }
    }
}
