#ifndef DELLVE_PLUGIN_PROXY_HPP
#define DELLVE_PLUGIN_PROXY_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	DELLve headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DELLveError.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	OS headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <dlfcn.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	STL headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <memory>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	PluginProxy Class
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DELLve {

	class PluginProxy {
		/**
		 * DLL handle
		 */
		void* mDlHandle;

	public:

		/**
		 * @brief      Constructs new plugin proxy object
		 *
		 * @param[in]  fileName  The dynamic library (a.k.a. plugin) file name
		 */
		PluginProxy ( const std::string& fileName ) {
			mDlHandle = dlopen(fileName.c_str(), RTLD_LAZY);

			if (!mDlHandle) {
				throw std::runtime_error("Plugin didn't load: " + fileName);
			}
		};

		/**
		 * @brief      Destruct the plugin proxy object.
		 */
		~PluginProxy() {
			dlclose(mDlHandle);
		}

		/**
		 * @brief      Loads a function from shared library or plugin.
		 *
		 * @param[in]  functionName  	Name of the function to load
		 *
		 * @tparam     FunctionType     Type of the function to load
		 *
		 * @return     Function object wrapper for the loaded function
		 */
		template<typename FunctionType>
		std::function<FunctionType> call (const std::string& functionName) const {
			/**
			 * Load DLL function address
			 */
			void* functionPointer = dlsym(mDlHandle, functionName.c_str());

			// TODO: make sure functionPointer is not NULL

			/**
			 * Wrap DLL function address into function object
			 */
			return std::function<FunctionType>(*(FunctionType*) functionPointer);
		};
	};
};

#endif // DELLVE_PLUGIN_PROXY_HPP
