
import atexit
import dellve_system_monitor.api
import os
from pynvml import * 

def _start_nvml():
    try:
        nvmlInit()
    except NVMLError, err:
        print "Failed to initialize NVML: ", err
        print "Exiting..."
        os.exit(1)

_start_nvml()

def _stop_nvml():
    try:
        nvmlShutdown()
    except NVMLError, err:
        print "Error shutting down NVML: ", err
        os.exit(1)

atexit.register(_stop_nvml)

class SystemMonitor(dellve_system_monitor.api.API):
    def get_num_gpu_devices(self):
        return nvmlDeviceGetCount()

    def get_gpu_util(self, device_id):
        device_obj = nvmlDeviceGetHandleByIndex(device_id)
        device_util_rates = nvmlDeviceGetUtilizationRates(device_obj)
        return int(device_util_rates.gpu)

    def get_mem_util(self, device_id):
        device_obj = nvmlDeviceGetHandleByIndex(device_id)
        device_util_rates = nvmlDeviceGetUtilizationRates(device_obj)
        return int(device_util_rates.memory)
