
import abc
import concurrent
import grpc
import threading
import sched
import time
import dellve_proto
import dellve_system_monitor.api

# Select GRPC service
ServiceAPI = dellve_proto.benchend.BenchendServicer

class ServiceProvider(ServiceAPI):
    def __init__(self, system_monitor=None):
        ServiceAPI.__init__(self)

        if not isinstance(system_monitor, dellve_system_monitor.api.API):
            raise TypeError() # TODO: add error message

        self.system_monitor = system_monitor
        self.metric_stream_on = False

    def getServerInfo(self, request, context):      
        service_info = {
            "numGpuDevices": self.system_monitor.get_num_gpu_devices()
            # Note: add more fields here as API grows
        }

        return dellve_proto.types.ServiceInfo(**service_info)

    def startMetricStream(self, request, context):
        self.metric_stream_on = True

        while self.metric_stream_on:
            yield dellve_proto.types.MetricStreamData(**{
                'gpuUtil': self.system_monitor.get_gpu_util(0),
                'memUtil': self.system_monitor.get_mem_util(0)
            })

    def stopMetricStream(self, request, context):
        self.metric_stream_on = False

        return dellve_proto.types.Status()


class Service(object):
    def __init__(self, stub=True):
        if stub:
            import dellve_system_monitor.stub
            system_monitor = dellve_system_monitor.stub.SystemMonitor()
        else:
            import dellve_system_monitor.nvidia
            system_monitor = dellve_system_monitor.nvidia.SystemMonitor()

        self.provider = ServiceProvider(system_monitor=system_monitor)

    def start(self, port=5555):
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