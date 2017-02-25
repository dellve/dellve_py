import abc
import concurrent
import grpc
 
class API(object):

    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def get_num_gpu_devices(self):
    	raise NotImplementedError()

    @abc.abstractmethod
    def get_gpu_util(self, device_id):
    	raise NotImplementedError()

    @abc.abstractmethod
    def get_mem_util(self, device_id):
    	raise NotImplementedError()