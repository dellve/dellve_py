
import system_manager

from pynvml import * 

class NvidiaSystemManager(system_manager.Interface):

	def __init__(self):
		self.device_count = nvmlDeviceGetCount()

	def get_device_count(self):
		return self.device_count



