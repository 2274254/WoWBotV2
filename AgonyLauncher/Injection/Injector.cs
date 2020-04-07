using System;
using System.Reflection;
using System.Runtime.InteropServices;
using NLog;

namespace AgonyLauncher.Injection
{
    [Obfuscation(Exclude = false, Feature = "ctrl flow")]
    internal class Injector
    {
        private static readonly NLog.Logger NLog = LogManager.GetCurrentClassLogger();

        [DllImport("libinj.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Is32Bit(int process_id);
        [DllImport("libinj.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Inject(int process_id, string dll, int method, IntPtr handle = default(IntPtr));
        [DllImport("libinj.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern string getLastError();

        internal static bool InjectCore(int procId, string path)
        {
            return Inject(procId, path, 1);
        }
    }
}