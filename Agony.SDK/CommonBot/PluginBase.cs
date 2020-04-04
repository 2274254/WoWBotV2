namespace Agony.SDK.CommonBot
{
    public abstract class PluginBase
    {
        public virtual string Name { get { return ""; } }
        public virtual string ShowConfigs(string configs) { return null; }
    }
}