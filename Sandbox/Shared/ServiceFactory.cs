using System;
using System.ServiceModel;

namespace Sandbox.Shared
{
    public static class ServiceFactory
    {
        private const string PipeName = "Agony";

        public static TInterfaceType CreateProxy<TInterfaceType>() where TInterfaceType : class
        {
            try
            {
                return
                    new ChannelFactory<TInterfaceType>(
                        new NetNamedPipeBinding(),
                        new EndpointAddress("net.pipe://localhost/" + PipeName)).CreateChannel();
            }
            catch (Exception e)
            {
                throw new Exception(
                    "Failed to connect to assembly pipe for communication. The targetted assembly may not be loaded yet. Desired interface: " +
                    typeof (TInterfaceType).Name, e);
            }
        }
    }
}
