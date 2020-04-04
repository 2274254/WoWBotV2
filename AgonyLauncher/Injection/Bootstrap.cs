using System;
using System.IO.MemoryMappedFiles;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows;
using AgonyLauncher.Data;
using AgonyLauncher.Logger;

namespace AgonyLauncher.Injection
{
    internal static class Bootstrap
    {
        internal static MemoryMappedFile _memoryMappedFile;

        [Obfuscation(Exclude = false, Feature = "ctrl flow")]
        internal static void SetMemoryLayout()
        {
            try
            {
                if (_memoryMappedFile == null)
                {
                    _memoryMappedFile = MemoryMappedFile.CreateOrOpen("Local\\Agony", 1024, MemoryMappedFileAccess.ReadWrite);
                }
                var bsMemoryLayout = new BootstrapMemoryLayout(PathRandomizer.CoreDllPath, PathRandomizer.SandboxDllPath, PathRandomizer.WrapperDllPath, "", true);
                using (var writer = _memoryMappedFile.CreateViewAccessor())
                {
                    var len = Marshal.SizeOf(typeof(BootstrapMemoryLayout));
                    var arr = new byte[len];
                    var ptr = Marshal.AllocHGlobal(len);
                    Marshal.StructureToPtr(bsMemoryLayout, ptr, true);
                    Marshal.Copy(ptr, arr, 0, len);
                    Marshal.FreeHGlobal(ptr);
                    writer.WriteArray(0, arr, 0, arr.Length);
                }
            }
            catch (Exception e)
            {
                var errorString = string.Format("Failed to set memory layout!\r\nException: {0}", e);
                Log.Instance.DoLog(errorString, Log.LogType.Error);
                MessageBox.Show(errorString, "", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)]
        internal struct BootstrapMemoryLayout
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
            private readonly String SandboxDllPath;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
            private readonly String WrapperDllPath;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
            private readonly String CoreDllPath;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
            private readonly String Hash;

            [MarshalAs(UnmanagedType.Bool)]
            private readonly bool IsBuddy;

            internal BootstrapMemoryLayout(string corePath, string sandboxPath, string elobuddyPath, string hash, bool isBuddy)
            {
                CoreDllPath = corePath;
                SandboxDllPath = sandboxPath;
                WrapperDllPath = elobuddyPath;
                Hash = hash;
                IsBuddy = isBuddy;
            }
        };
    }
}
