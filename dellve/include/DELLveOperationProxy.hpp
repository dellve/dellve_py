#ifndef DELLVE_OPERATION_PROXY_HPP
#define DELLVE_OPERATION_PROXY_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	DELLve headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DELLveError.hpp"
#include "DELLvePluginProxy.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	STL headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <string>

namespace DELLve {

	class OperationProxy {
		/**
		 * { item_description }
		 */
		void* mHandle;

		// class DeleteCallback {
		// 	std::function<void(void)> mCallback;
		// public:
		// 	DeleteCallback ( const std::function<void(void)>& callback ) 
		// 		: mCallback(callback) {}
		// 	~DeleteCallback() {
		// 		mCallback();
		// 	}
		// };

		// /**
		//  * Operation handle
		//  */
		// std::shared_ptr<DeleteCallback> mHandleDeleteCallback;

		/**
		 * Operation name
		 */
		const std::string mOperationName;

		/**
		 * Host plugin proxy
		 */
		std::shared_ptr<PluginProxy> mPluginProxy;

	public:
		/**
		 * @brief      { function_description }
		 *
		 * @param[in]  pluginProxy    The plugin proxy
		 * @param[in]  operationName  The operation name
		 */
		OperationProxy ( const std::shared_ptr<PluginProxy>& pluginProxy,
						 const std::string& operationName ) : 
						 mOperationName(operationName), 
						 mPluginProxy(pluginProxy) {

			mPluginProxy->call<Error(void**)>(getApiPrefixName() + "newOperation")(&mHandle);
		}

		/**
		 * @brief      Destroys the object.
		 */
		~OperationProxy () {
			// mPluginProxy->call<Error(void*)>(mOperationName + "deleteOperation")(mHandle);
			mPluginProxy->call<Error(void*)>(getApiPrefixName() + "deleteOperation")(mHandle);
			// TODO: check error
		}

	private:

		/**
		 * @brief      { struct_description }
		 *
		 * @tparam     T     { description }
		 */
		template<typename T> 
		struct CallFactory;  

		/**
		 * @brief      { struct_description }
		 *
		 * @tparam     R     { description }
		 * @tparam     Args  { description }
		 */
		template<typename R, typename ... Args> 
		struct CallFactory<std::function<R(Args...)>> {
			/**
			 * @brief      { function_description }
			 *
			 * @param      operationProxy  The operation proxy
			 * @param[in]  methodName      The method name
			 *
			 * @return     { description_of_the_return_value }
			 */
		    static std::function<R(Args...)> create ( OperationProxy* operationProxy, 
		    										  const std::string& methodName ) {
		    	
		    	auto callHandle = operationProxy->mHandle;
		    	auto callName = operationProxy->getApiPrefixName() + methodName;
		    	auto callObject = operationProxy->mPluginProxy->call<R(void*, Args...)>(callName);
		    	return [=](Args ... args) {
		    		return callObject(callHandle, args...);
		    	};
		    };
		};

	public:

		/**
		 * @brief      Gets the name.
		 *
		 * @return     The name.
		 */
		const std::string& getName() const {
			return mOperationName;
		}

		const std::string& getApiPrefixName() const {
			const static std::string mApiPrefixName = "__" + mOperationName + "__";

			return mApiPrefixName;
		}

		/**
		 * @brief      { function_description }
		 *
		 * @param[in]  methodName  The method name
		 *
		 * @tparam     T           { description }
		 *
		 * @return     { description_of_the_return_value }
		 */
		template<typename T>
		std::function<T> call (const std::string& methodName) {
			return CallFactory<std::function<T>>::create(this, methodName);
		};
	};
};

#endif // DELLVE_OPERATION_PROXY_HPP
