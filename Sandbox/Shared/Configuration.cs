using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Security;

namespace Agony.Sandbox.Shared
{
    [DataContract]
    public class Configuration
    {

        [DataMember]
        public string DataDirectory { get; set; }

        [DataMember]
        public string WrapperDllPath { get; set; }

        [DataMember]
        public string LibrariesDirectory { get; set; }

        [DataMember]
        public PermissionSet Permissions { get; set; }

        [DataMember]
        public bool IsVip { get; set; }

        [DataMember]
        public string CurrentProfile { get; set; }

        [DataMember]
        public Dictionary<string, string> PluginConfigs { get; set; }

        public override string ToString()
        {
            var excludedProperties = new HashSet<string>
            {
                "Permissions"
            };
            var properties = GetType().GetProperties(BindingFlags.Public | BindingFlags.Instance);
            return string.Join("\n", from propertyInfo in properties
                where !excludedProperties.Contains(propertyInfo.Name) && Attribute.IsDefined(propertyInfo, typeof (DataMemberAttribute))
                select propertyInfo.Name + ":" + propertyInfo.GetValue(this, null));
        }
    }
}