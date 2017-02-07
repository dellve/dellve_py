
#include <utility>

extern "C" {
	/**
	 * @brief      Test funtion (used to test PluginProxy class)
	 *
	 * @param[in]  input  Input value (should be returned to caller unchanged)
	 *
	 * @return     Value equivalent to input value
	 */
	int Function1(int input) {
		return input;
	}

	/**
	 * @brief      Test function (used to test PluginProxy class)
	 *
	 * @param[in]  input   Input value (should be returned to caller unchanged)
	 * @param      output  Output value (should contain input value upon return)
	 */
	void Function2(int input, int* output) {
		*output = input;
	}

	/**
	 * @brief      Test function (used to test PluginProxy class)
	 *
	 * @param      array  Character string (should be reversed on exit)
	 * @param[in]  len    Character string length
	 */
	void Function3(char* array, int len) {
		if (!len) return;
		std::swap(array[0], array[len-1]);
		Function3(array + 1, len - 2);
	}
}