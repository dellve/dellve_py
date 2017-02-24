import abc
import concurrent
import grpc

from dellve_managers.nvidia import *
from dellve_proto.system_manager_service_pb2 import *
 
class Api(object):
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def get_device_count(self):
        pass 