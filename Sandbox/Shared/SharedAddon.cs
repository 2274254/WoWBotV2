using System.Runtime.Serialization;

namespace Sandbox.Shared
{
    [DataContract]
    public class SharedAddon
    {
        [DataMember]
        public string PathToBinary { get; set; }
    }
}
