#include <cmath>                                        // для функции sin
#include <Windows.h>

#include "RenderSystem.h"
#include "Window.h"

using namespace std;

template <class T>
auto Println(const T i, ostream& out = cout) -> void {
	out << i << endl;
}

auto Hello() -> void {
	std::cout << "Lab 2" << std::endl << "Author: Alex Safiyulin" << std::endl;
}

auto MakeTriangle(GLFWwindow* window, chupakabra::render::IRenderSystem* renderer) -> void {
	glfwMakeContextCurrent(window);
	renderer->Render(window);
	glfwSwapBuffers(window);
}

auto MakeTriangle(chupakabra::graphics::Window& window, chupakabra::render::IRenderSystem* renderer) -> void {
	MakeTriangle(window.GetWindow(), renderer);
}

auto main() -> int {

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	Hello();

	auto* system = new chupakabra::render::OldRenderSystem();
	system->Initialize();

	chupakabra::graphics::Window w1(300u, "W1"), w2(300u, "W2");
	auto* window = glfwCreateWindow(300, 300, "Window", nullptr, nullptr);

	if (!window) {
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	// Инициализируем GLEW
	glewExperimental = true; // Флаг необходим в Core-режиме OpenGL
	if (glewInit() != GLEW_OK) {
		Println("Невозможно инициализировать GLEW", std::cerr);
		return EXIT_FAILURE;
	}

	// Включим режим отслеживания нажатия клавиш, для проверки ниже
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	auto colorRgb = 0.f;
	
	while (!glfwWindowShouldClose(window)) {
		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {

			MakeTriangle(w1, system);
			MakeTriangle(w2, system);
			MakeTriangle(window, system);

			glfwPollEvents();
			glfwMakeContextCurrent(window);
		}

		colorRgb <= 180.f ? colorRgb += 0.005f : colorRgb = 0.f;
	}

	delete system;
	glfwTerminate();
	
	return EXIT_SUCCESS;
}