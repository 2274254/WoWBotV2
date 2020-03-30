using System;

namespace Agony.Sandbox
{
    /// <summary>
    ///     Input class will handle any input commands, mainly key commands which link back to a reload, recompile and an
    ///     unload but are not limited to.
    /// </summary>
    internal static class Input
    {
        /// <summary>
        ///     Request a subscribe onto the windows process commands to listen to any input commands.
        /// </summary>
        public static void Subscribe()
        {
            //SandboxConfig.ReloadKey
            AppDomain.CurrentDomain.AssemblyResolve += SandboxDomain.DomainOnAssemblyResolve;
            //Game.OnWndProc += Game_OnWndProc;
        }

        /// <summary>
        ///     Input Commands subscribed event function.
        /// </summary>
        /// <param name="args">
        ///     <see cref="WndEventArgs" />
        /// </param>
        /*internal static void Game_OnWndProc(WndEventArgs args)
        {
            if (args.Msg == 0x0101 /*WM_KEYUP* /)
            {
                if (args.WParam == SandboxConfig.ReloadKey)
                {
                    Console.WriteLine("RELOAD KEY PRESSED");
                    Sandbox.Reload();
                }

                if (args.WParam == SandboxConfig.ReloadAndRecompileKey)
                {
                    Console.WriteLine("Recompile KEY PRESSED");
                    Sandbox.Recompile();
                }

                if (args.WParam == SandboxConfig.UnloadKey)
                {
                    Console.WriteLine("Unload KEY PRESSED");
                    Sandbox.Unload();
                }
            }
        }*/
    }
}