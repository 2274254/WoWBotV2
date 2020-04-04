namespace Agony.SDK.CommonBot
{
    public enum PluginType
    {
        Plugin = 0,
        CombatRoutine = 1,
        BotBase = 2
    }

    public abstract class PluginBase
    {
        public virtual PluginType Type { get { return PluginType.Plugin; } }
        public virtual string Name { get { return ""; } }
        public virtual string ShowConfigs(string configs) { return null; }
    }
}