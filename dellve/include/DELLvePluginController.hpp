#ifndef DELLVE_PLUGIN_CONTROLLER_HPP
#define DELLVE_PLUGIN_CONTROLLER_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	DELLve headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DELLveError.hpp"
#include "DELLvePluginProxy.hpp"
#include "DELLveOperationController.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	STL headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <string>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	PluginController
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DELLve {

	class PluginController {

		/**
		 * Plugin proxy (used to dispatch calls from PluginController to DLL)
		 */
		std::shared_ptr<PluginProxy> mPluginProxy;

	public:
		PluginController ( const std::string& fileName ) {
			mPluginProxy = std::shared_ptr<PluginProxy>(new PluginProxy(fileName));
		}

		/**
		 * @brief      Gets the operation controller.
		 *
		 * @param[in]  operationName  The operation name
		 *
		 * @return     The operation controller.
		 */
		std::shared_ptr<OperationController> 
		getOperationController ( const std::string& operationName ) const {
			std::shared_ptr<OperationProxy> operationProxy
				(new OperationProxy(mPluginProxy, operationName));
			return std::shared_ptr<OperationController>
				(new OperationController(operationProxy));
		};
  	};
};

#endif // DELLVE_PLUGIN_CONTROLLER_HPP
