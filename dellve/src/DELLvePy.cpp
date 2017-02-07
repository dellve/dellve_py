#include <pybind11/pybind11.h>

#include "DELLveOperationController.hpp"
#include "DELLvePluginController.hpp"

#include <iostream>
#include <functional>

namespace py = pybind11;

using namespace DELLve;

PYBIND11_PLUGIN(dellve) {
    py::module m("dellve", 
    	"Python interface to DELLveBench HPC benchmark plugin-suite");

    py::class_<OperationController, std::shared_ptr<OperationController>>(m, "Operation")
    	.def("send", 
            [](OperationController& self, const std::string& message) {
                Error err = self.send(message); 

                if (err != NoError) {
                    // TODO: deal with it!
                }
            })
        .def("set_recv_callback", 
            [](OperationController& self, py::function callback) {
                Error err = self.setRecvCallback([=](const std::string& message) { 
                    callback(message); 
                });

                if (err != NoError) {
                    // TODO: deal with it
                }
            })
        .def("__repr__", 
            [](const OperationController& self) {
                return "<dellve.Operation " + self.getName() + ">";
            });

    py::class_<PluginController, std::shared_ptr<PluginController>>(m, "Plugin")
        .def(py::init<const std::string &>())
        .def("get_operation", 
            [](PluginController& self, const std::string& operationName) {
                return self.getOperationController(operationName);
            });

    return m.ptr();
}
