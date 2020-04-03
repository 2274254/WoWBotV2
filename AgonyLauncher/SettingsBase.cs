using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace AgonyLauncher
{
    public abstract class SettingsBase : INotifyPropertyChanged
    {
        /// <summary>Must be set in the Load overide. It's used for disabling change notification while loading </summary>
        protected bool IsLoaded { get; set; }

        public abstract void LoadFromXml(XElement element);
        public abstract XElement ConvertToXml();

        public abstract SettingsBase ShadowCopy();

        #region INotifyPropertyChanged

        public event PropertyChangedEventHandler PropertyChanged;
        protected bool NotifyPropertyChanged<T>(ref T oldValue, ref T newValue, string propertyName)
        {
            if (Equals(oldValue, newValue))
                return false;
            oldValue = newValue;
            if (IsLoaded)
            {
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
                //if (Settings != null)
                    //Settings.QueueSave();
            }
            return true;
        }

        #endregion

        protected T GetElementValue<T>(XElement element, T defaultValue = default(T))
        {
            if (element != null)
            {
                if (defaultValue is Enum)
                {
                    return (T)Enum.Parse(typeof(T), element.Value);
                }
                return (T)Convert.ChangeType(element.Value, typeof(T));
            }
            return defaultValue;
        }

    }
}