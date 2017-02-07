#ifndef DELLVE_OPERATION_CONTROLLER_HPP
#define DELLVE_OPERATION_CONTROLLER_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	DELLve headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DELLveError.hpp"
#include "DELLveOperationProxy.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	STL headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <functional>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	Operation Controller
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DELLve {

	extern "C" Error OperationControllerRecvCallback ( void* controller, const char* message );

	/**
	 * @brief      Controlls underlying operation object
	 */
	class OperationController {

		/**
		 * @brief      { function_description }
		 *
		 * @param      controller  The controller
		 * @param[in]  message     The message
		 *
		 * @return     { description_of_the_return_value }
		 */
		friend Error OperationControllerRecvCallback ( void* controller, const char* message );

		/**
		 * Operation proxy (used to dispatch calls to DLL)
		 */
		std::shared_ptr<OperationProxy> mOperationProxy;
		
		/**
		 * Message receiver callback (used to return messages from DLL)
		 */
		std::function<void(const std::string&)> mRecvCallback;

	public:

		/**
		 * @brief      Contructs new operation controller
		 *
		 * @param[in]  proxy  Proxy to underlying operation object
		 */
		OperationController ( const std::shared_ptr<OperationProxy>& operationProxy ) : 
			mOperationProxy ( operationProxy ) {
			/**
			 * Set operation's send callback to this controller's callback
			 */

			/**
			 * NOTE: we set operation's SEND callback to operation controller's RECV callback
			 */
			
			mOperationProxy->call<Error(void*, void*)> 
				("setMessageSendCallback")((void*) this, (void*) &OperationControllerRecvCallback);
		}

		/**
		 * @brief      Gets the name.
		 *
		 * @return     The name.
		 */
		std::string getName() const {
			return mOperationProxy->getName();
		}

		/**
		 * @brief      Gets the api prefix name.
		 *
		 * @return     The api prefix name.
		 */
		std::string getApiPrefixName() const {
			return mOperationProxy->getApiPrefixName();
		}

		/**
		 * @brief      Sends a message from to the underlying operation
		 *
		 * @param[in]  message  The message to send
		 *
		 * @return     Error code
		 */
		Error send ( const std::string& message ) {
			return mOperationProxy->call<Error(const char*)>
				("recvMessage")(message.c_str());
		}

		/**
		 * @brief      Sets the message receiver callback.
		 *
		 * @param[in]  recvCallback  The message receiver callback
		 *
		 */
		Error setRecvCallback ( const std::function<void(const std::string&)>& recvCallback ) {
			mRecvCallback = recvCallback;

			return NoError;
		}
	};

	/**
	 * @brief      Callback that sends a message from an underlying operation to its controller
	 *
	 * @param      controller  Operation controller that receives the message
	 * @param[in]  message          Message body
	 *
	 * @return     Error code
	 */
	extern "C" {
		Error OperationControllerRecvCallback ( void* controller, const char* message ) {
			((OperationController*) controller)->mRecvCallback(std::string(message));

			return NoError;
		};
	};

	// void* OperationController::mRecvCallbackPtr = (void*) messageRecvCallback;
	
};


#endif // DELLVE_OPERATION_CONTROLLER_HPP
