#pragma once
#include "RenderSystem.h"
#include "Window.h"

template <class T>
auto Println(const T i, std::ostream& out = std::cout) -> void {
	out << i << std::endl;
}

auto Hello() -> void {
	std::cout << "Lab 2" << std::endl << "Author: Alex Safiyulin" << std::endl;
}

/// <summary>
/// Modifies making figure function
/// </summary>
/// <returns></returns>
auto MakeContext() {
	return [](GLFWwindow* window, chupakabra::render::IRenderSystem* renderer, void function(chupakabra::render::IRenderSystem*)) {
		glfwMakeContextCurrent(window);
		function(renderer);
		glfwSwapBuffers(window);
	};
}

/// <summary>
/// Create triangle with OpenGL class
/// </summary>
/// <param name="window"></param>
/// <param name="renderer"></param>
/// <returns></returns>
auto MakeTriangleArray(GLFWwindow* window, chupakabra::render::IRenderSystem* renderer) -> void {
	MakeContext()(window, renderer, [](chupakabra::render::IRenderSystem* renderer) {
		renderer->RenderTriangleArray();
	});
}

/// <summary>
/// Create triangle with chupakabra's class
/// </summary>
/// <param name="window"></param>
/// <param name="renderer"></param>
/// <returns></returns>
auto MakeTriangleArray(chupakabra::graphics::Window& window, chupakabra::render::IRenderSystem* renderer) -> void {
	MakeTriangleArray(window.GetWindow(), renderer);
}

/// <summary>
/// Create VBO with OpenGL class
/// </summary>
/// <param name="window"></param>
/// <param name="renderer"></param>
/// <returns></returns>
auto MakeVBO(GLFWwindow* window, chupakabra::render::IRenderSystem* renderer) -> void {
	MakeContext()(window, renderer, [](chupakabra::render::IRenderSystem* renderer) {
		renderer->RenderVBO();
	});
}

/// <summary>
/// Create VBO with chupakabra's class
/// </summary>
/// <param name="window"></param>
/// <param name="renderer"></param>
/// <returns></returns>
auto MakeVBO(chupakabra::graphics::Window& window, chupakabra::render::IRenderSystem* renderer) -> void {
	MakeVBO(window.GetWindow(), renderer);
}

/// <summary>
/// Create render with OpenGL class
/// </summary>
/// <param name="window"></param>
/// <param name="renderer"></param>
/// <returns></returns>
auto MakeRender(GLFWwindow* window, chupakabra::render::IRenderSystem* renderer) -> void {
	MakeContext()(window, renderer, [](chupakabra::render::IRenderSystem* renderer) {
		renderer->Render();
	});
}

/// <summary>
/// Create render with chupakabra's class
/// </summary>
/// <param name="window"></param>
/// <param name="renderer"></param>
/// <returns></returns>
auto MakeRender(chupakabra::graphics::Window& window, chupakabra::render::IRenderSystem* renderer) -> void {
	MakeRender(window.GetWindow(), renderer);
}