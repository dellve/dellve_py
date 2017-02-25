
import random

import dellve_system_monitor.api

class SystemMonitor(dellve_system_monitor.api.API):

    def get_num_gpu_devices(self):
    	raise nvmlDeviceGetCount()

    def get_gpu_util(self, device_id):
    	return random.randint(0, 100)

    def get_mem_util(self, device_id):
    	return random.randint(0, 100)
