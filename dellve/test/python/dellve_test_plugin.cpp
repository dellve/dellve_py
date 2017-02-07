
#include "DELLveOperation.hpp"
#include "DELLveBenchmark.hpp"

using namespace DELLve;

#include <iostream>

struct TestOperation : public Operation {

	/**
	 * @brief      Receives a message from operation controller.
	 *
	 * @param[in]  message  The message
	 *
	 * @return     { description_of_the_return_value }
	 */
	Error recvMessage ( const std::string& message ) {		
		return sendMessage(message);
	}
};

DELLveBenchmark(TestOperation);