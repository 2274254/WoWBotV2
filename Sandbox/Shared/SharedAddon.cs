using System.Runtime.Serialization;

namespace Agony.Sandbox.Shared
{
    [DataContract]
    public class SharedAddon
    {
        [DataMember]
        public string PathToBinary { get; set; }
    }
}
