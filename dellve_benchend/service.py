
import abc
import concurrent
import grpc
import threading
import sched
import time
import dellve_proto
# import dellve_system_manager

# Select GRPC service
ServiceAPI = dellve_proto.benchend.BenchendServicer

# # Select prefered system manager
# SystemManager = dellve_system_manager.nvidia.SystemManager
# assert issubclass(SystemManager, dellve_system_manager.Api)

# class ServiceProvider(ServiceAPI):
#     def getServerInfo(self, request, context):
#         raise NotImplementedError()

#     def startMetricStream(self, request, context):
#         raise NotImplementedError()

#     def stopMetricStream(self, request, context):
#         raise NotImplementedError()

class ServiceProviderStub(ServiceAPI):
    def __init__(self):
        ServiceAPI.__init__(self)
        self.stream_on = False

    def getServerInfo(self, request, context):      
        service_info = {
            "numGpuDevices": 1
            # Note: add more fields here as API grows
        }

        return dellve_proto.types.ServiceInfo(**service_info)

    def startMetricStream(self, request, context):
        self.stream_on = True

        metric_stream_data = {
            'gpuUtil': 100,
            'memUtil': 100
        }

        while self.stream_on:
            yield dellve_proto.types.MetricStreamData(**metric_stream_data)

    def stopMetricStream(self, request, context):
        self.stream_on = False

        return dellve_proto.types.Status()


class Service(object):
    def __init__(self, stub=True):
        if stub:
            self.provider = ServiceProviderStub()
        else:
            self.provider = ServiceProvider()

    def start(self, url='localhost', port=5555):
        Executor = concurrent.futures.ThreadPoolExecutor

        server = grpc.server(Executor(10))

        dellve_proto.benchend.add_BenchendServicer_to_server(self.provider, server)

        server.add_insecure_port('[::]:%d' % port)

        server.start()

        try:
            while True:
                time.sleep(60 * 60 * 24) # sleep for a day
        except KeyboardInterrupt:
            server.stop(0)

if __name__ == '__main__':
    Service().start()