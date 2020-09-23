#include <cmath>                                        // для функции sin
#include <windows.h>
#include <iostream>                                     // для стандартных потоков ввода-вывода

#include "libs\GL_AL\glew.h"
#include "libs\GL_AL\glfw3.h"

#define GLUT_DISABLE_ATEXIT_HACK

using namespace std;

auto Hello() -> void {
	std::cout << "Lab 2" << std::endl << "Author: Alex Safiyulin" << std::endl;
}

auto main(const int argc, char** argv) -> int {

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	Hello();
	
	return EXIT_SUCCESS;
}