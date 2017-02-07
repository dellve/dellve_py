
#include "gtest/gtest.h"

#include "DELLvePluginProxy.hpp"

#include <iostream>
#include <cstdlib>

using namespace DELLve;

TEST(PluginProxyTest, BypassFunctionTest) {
	PluginProxy pluginProxy("libPluginProxyTestPlugin.so");

	int testInput = 0; // input value
	int testOutput = 1; // output value

	testOutput = pluginProxy.call<int(int)>("Function1")(testInput);
	
	ASSERT_EQ(testInput, testOutput);
}

TEST(PluginProxyTest, ReturnByReferenceTest) {
	PluginProxy pluginProxy("libPluginProxyTestPlugin.so");

	int testInput = 0; // input value
	int testOutput = 1; // output value

	pluginProxy.call<void(int, int*)>("Function2")(testInput, &testOutput);
	
	ASSERT_EQ(testInput, testOutput);
}

TEST(PluginProxyTest, PassByReference) {
	PluginProxy pluginProxy("libPluginProxyTestPlugin.so");

	std::string testInput = "abcd";
	std::string testOutput = "dcba";

	pluginProxy.call<void(const char*, int)>("Function3")(testInput.c_str(), testInput.size());

	// NOTE: we pass const char* to the function, so it shouldn't be able to modify it;
	// 		 however, plugin is compiled separately from this test, so C/C++ compiler
	// 		 has no way to enforce type safety here, and plugin can easily modify const data

	ASSERT_EQ(0, testInput.compare(testOutput));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
