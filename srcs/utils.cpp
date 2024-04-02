#include <sstream>
#include <iostream>

int myAtoi(const char* str) {
	std::istringstream iss(str);
	int result = 0;
	if (!(iss >> result)) {
		std::cerr << "Error: Invalid input" << std::endl;
		return -1;
	}
	return result;
}

// int main() {
// 	const char* str = "12345";
// 	int value = myAtoi(str);
// 	std::cout << "Converted value: " << value << std::endl;
// 	return 0;
// }