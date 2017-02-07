#ifndef DELLVE_OPERATION_HPP
#define DELLVE_OPERATION_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	DELLve headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DELLveError.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	STL headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>

/**
 * { item_description }
 */
namespace DELLve {
  	
  	/**
  	 * @brief      Class for operation.
  	 */
	class Operation {

		typedef std::function<Error(const std::string&)> MessageCallback;
		
		/**
		 * { item_description }
		 */
		MessageCallback mMessageSendCallback;

	public:
		
		/**
		 * @brief      Receives a message from operation controller.
		 *
		 * @param[in]  message  The message
		 *
		 * @return     { description_of_the_return_value }
		 */
		Error recvMessage ( const std::string& message ) {
			return NoError;
		}

		/**
		 * @brief      Sends a message.
		 *
		 * @param[in]  message  The message
		 *
		 * @return     { description_of_the_return_value }
		 */
		Error sendMessage ( const std::string& message ) {			 
			return mMessageSendCallback(message);
		}

		/**
		 * @brief      Sets the message send callback.
		 *
		 * @param[in]  callback  The callback
		 *
		 * @return     { description_of_the_return_value }
		 */
		Error setMessageSendCallback ( const MessageCallback& callback ) {
			mMessageSendCallback = callback;

			return NoError;
		}
	};
};

#endif // DELLVE_OPERATION_HPP