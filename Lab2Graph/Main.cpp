#include <cmath>                                        // ��� ������� sin
#include <Windows.h>

#include "RenderSystem.h"
#include "Window.h"
#include "Helpers.h"

using namespace std;

auto main() -> int {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Hello();

	auto* renderNew = new chupakabra::render::RenderSystem();
	renderNew->Initialize();

	chupakabra::graphics::Window w1(300u, "W1"), w2(300u, "W2");
	auto* window = glfwCreateWindow(300, 300, "Window", nullptr, nullptr);

	if (!window) {
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	// �������������� GLEW
	glewExperimental = true; // ���� ��������� � Core-������ OpenGL
	if (glewInit() != GLEW_OK) {
		Println("���������� ���������������� GLEW", std::cerr);
		return EXIT_FAILURE;
	}

	// ������� ����� ������������ ������� ������, ��� �������� ����
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	auto colorRgb = 0.f;

	chupakabra::render::Cube::init();
	while (!glfwWindowShouldClose(window)) {
		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {

			MakeVBO(w1, renderNew);
			MakeVBO(w2, renderNew);
			MakeVBO(window, renderNew);

			glfwPollEvents();
			glfwMakeContextCurrent(window);
		}

		colorRgb <= 180.f ? colorRgb += 0.005f : colorRgb = 0.f;
	}

	delete renderNew;
	glfwTerminate();
	
	return EXIT_SUCCESS;
}