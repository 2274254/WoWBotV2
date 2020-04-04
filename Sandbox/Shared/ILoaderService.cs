using System.Collections.Generic;
using System.ServiceModel;

namespace Agony.Sandbox.Shared
{
    public enum AgonyStatus
    {
        Stopped = 0,
        Running = 1
    }
    [ServiceContract]
    public interface ILoaderService
    {
        [OperationContract]
        List<SharedAddon> GetAssemblyList(int gameid);

        [OperationContract]
        Configuration GetConfiguration(int pid);

        [OperationContract]
        void Recompile(int pid);

        [OperationContract]
        AgonyStatus GetStatus();
    }
}