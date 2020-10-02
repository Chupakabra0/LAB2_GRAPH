#include <cmath>                                        // для функции sin
#include <Windows.h>
#include <iostream>                                     // для стандартных потоков ввода-вывода
#include <numbers>

#include "Window.h"

using namespace std;

auto Hello() -> void {
	std::cout << "Lab 2" << std::endl << "Author: Alex Safiyulin" << std::endl;
}

auto main() -> int {

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	Hello();

	auto* window = chupakabra::graphics::Initializer::InitializeWindow(4.6, 400u);
	
	if (!window) {
		return EXIT_FAILURE;
	}

	auto colorRgb = 0.f;
	
	while (!glfwWindowShouldClose(window->GetWindow())) {
		glClearColor(static_cast<GLclampf>(cos(colorRgb * std::numbers::pi / 90.f)), static_cast<GLclampf>(abs(sin(colorRgb * std::numbers::pi / 90.f))),
			static_cast<GLclampf>(sin(colorRgb * std::numbers::pi / 90.f)) + static_cast<GLclampf>(cos(colorRgb * std::numbers::pi / 90.f)),static_cast<GLclampf>(1.f));

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();

		colorRgb <= 180.f ? colorRgb += 0.005f : colorRgb = 0.f;
	}

	delete window;

	chupakabra::graphics::Deinitializer::Deinitialize();
	
	return EXIT_SUCCESS;
}