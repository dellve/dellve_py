
import abc
import concurrent
import grpc

from dellve_managers.nvidia import *
from dellve_proto.system_manager_service_pb2 import *
 
class Interface(object):
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def get_device_count(self):
        pass 

class ServiceProvider(SystemManagerServicer):
    def __init__(self, manager):
        if not isinstance(manager, Interface):
            raise TypeError(manager)
        self.manager = manager

    def getSystemInfo(self, request, context):
        return SystemInfo(numGpuDevices=self.manager.get_device_count())
    
class Service(object):

    def __init__(self):
        self.provider = ServiceProvider(NvidiaSystemManager())

    def start(self, url='localhost', port=5555):
        Executor = concurrent.futures.ThreadPoolExecutor

        server = grpc.server(Executor(max_workers))

        add_SystemManagerServicer_to_server(ServiceProvider(), server)

        server.add_insecure_port('[::]:%d' % port)

        server.start()

        try:
            while True:
                time.sleep(60 * 60 * 24) # sleep for a day
        except KeyboardInterrupt:
            server.stop(0)

if __name__ == '__main__':
    Service().start()