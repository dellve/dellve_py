#ifndef DELLVE_BENCHMARK_HPP
#define DELLVE_BENCHMARK_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	DELLve headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DELLveError.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// 	STL headers
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////
//	DELLveBenchmark Public API MACRO
////////////////////////////////////////////////////////////////////////////////////////////////////

#define DELLveBenchmark(Operation) extern "C"														\
{																									\
	DELLve::Error __ ## Operation ## __ ## newOperation 											\
		(Operation** operation) {																	\
			*operation = new Operation();															\
			return NoError;																			\
		}																							\
	DELLve::Error __ ## Operation ## __ ## deleteOperation											\
		(Operation* operation) {																	\
			delete operation;																		\
			return NoError;																			\
		}																							\
	DELLve::Error __ ## Operation ## __ ## recvMessage												\
		(Operation* operation, const char* message) { 												\
			return operation->recvMessage(std::string(message));									\
		}																							\
	DELLve::Error __ ## Operation ## __ ## setMessageSendCallback									\
	 	(Operation* operation, void* opController, void* callback) {								\
			typedef Error (*Callback)(void*, const char*);											\
			return operation->setMessageSendCallback([=](const std::string& message) {				\
				return (*(Callback) callback)(opController, message.c_str());						\
			});																						\
		}																							\
}

// #undef DELLveExportOperationMethod

#endif // DELLVE_BENCHMARK_HPP
