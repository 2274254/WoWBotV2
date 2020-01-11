using System;
using System.Runtime.InteropServices;

namespace Sandbox
{
    public static class CLRByPasser
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32.dll")]
        public static extern bool VirtualProtect(IntPtr lpAddress, uint dwSize, uint flNewProtect, out uint lpflOldProtect);

        public static void ByPass()
        {
            var functionAddress = GetProcAddress(GetModuleHandle("mscoree"), "CLRCreateInstance");
            try
            {
                uint oldProtect;
                VirtualProtect(functionAddress, 8, 0x40, out oldProtect);
                unsafe
                {
                    *(long*)((void*)functionAddress) = -8007118662488031304L;
                }
                Marshal.WriteIntPtr(functionAddress, 1, new IntPtr(0x7F7F7F7F));
                VirtualProtect(functionAddress, 8, oldProtect, out oldProtect);
            }
            catch (Exception)
            {
            }
        }
    }
}