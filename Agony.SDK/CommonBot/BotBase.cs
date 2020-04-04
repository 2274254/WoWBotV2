using Agony.SDK.TreeSharp;
using System;
using System.Xml;

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

    public abstract class BotBase : PluginBase
    {
        public override PluginType Type { get { return PluginType.BotBase; } }
        public virtual PulseFlags PulseFlags { get { return PulseFlags.All; } }
        public virtual Composite Root {  get { return null; } }
        public virtual void Start() { }
        public virtual void Stop() { }
        public virtual void Initialize(string configs = "", string profile = "") { }
        public virtual void Pulse() { }
    }
}
