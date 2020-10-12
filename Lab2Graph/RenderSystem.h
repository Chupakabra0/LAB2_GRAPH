#pragma once
#include <iostream>
#include <numbers>

#include "Window.h"

#define abstract = 0

namespace chupakabra {
	namespace render {

		class IRenderSystem {
		public:
			IRenderSystem() = default;
			virtual ~IRenderSystem() = default;

			virtual auto Initialize() -> void abstract;
			virtual auto Render(GLFWwindow* window) -> void abstract;
			// TODO virtual auto Render(graphics::Window& window) -> void abstract;
			virtual auto RenderTriangleArray(GLfloat* vertices, GLfloat* colors) -> void abstract;
			virtual auto RenderVBO() -> void abstract;
		};

		class RenderSystem : public IRenderSystem {
		public:
			RenderSystem() : IRenderSystem() {}
			virtual ~RenderSystem() = default;

			auto Initialize() -> void override {
				if (!glfwInit()) {
					std::cerr << "Ошибка при инициализации GLFW" << std::endl;
					return;
				}
				glfwWindowHint(GLFW_SAMPLES, 8);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			}
			auto Render(GLFWwindow* window) -> void override {}
			// TODO auto Render(graphics::Window& window) -> void override {}
			auto RenderTriangleArray(GLfloat* vertices, GLfloat* colors) -> void override {}
			auto RenderVBO() -> void override {}
		};

		class OldRenderSystem : public RenderSystem {
		public:
			OldRenderSystem() : RenderSystem() {}
			virtual ~OldRenderSystem() = default;

			auto Initialize() -> void override {
				if (!glfwInit()) {
					std::cerr << "Ошибка при инициализации GLFW" << std::endl;
					return;
				}
				glfwWindowHint(GLFW_SAMPLES, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			}
			auto Render(GLFWwindow* window) -> void override {
			//TODO auto Render(graphics::Window& window) -> void override {
				auto colorRgb = 0.f;
				glClearColor(static_cast<GLclampf>(sin(colorRgb * std::numbers::pi / 180.f)), static_cast<GLclampf>(abs(cos(colorRgb * std::numbers::pi / 180.f))),
					static_cast<GLclampf>(abs(sin(colorRgb * std::numbers::pi / 180.f) + cos(colorRgb * std::numbers::pi / 180.f))), static_cast<GLclampf>(1.0f));
				glClear(GL_COLOR_BUFFER_BIT);
				colorRgb <= 180.f ? colorRgb += 0.1f : colorRgb = 0.f;

				glLoadIdentity();
				glRotatef(static_cast<GLfloat>(glfwGetTime() * 50.f), static_cast<GLfloat>(0.f), static_cast<GLfloat>(0.f), static_cast<GLfloat>(1.f));
				glBegin(GL_TRIANGLES);
				glColor3f(1.f, 0.f, 0.f);
				glVertex3f(-0.6f, -0.4f, 0.f);
				glColor3f(0.f, 1.f, 0.f);
				glVertex3f(0.6f, -0.4f, 0.f);
				glColor3f(0.f, 0.f, 1.f);
				glVertex3f(0.f, 0.6f, 0.f);
				glEnd();
			}

			auto RenderTriangleArray(GLfloat* vertices, GLfloat* colors) -> void override {
				glClear(GL_COLOR_BUFFER_BIT);

				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_COLOR_ARRAY);

				glVertexPointer(3, GL_FLOAT, 0, vertices);
				glColorPointer(3, GL_FLOAT, 0, colors);

				glDrawArrays(GL_QUADS, 0, 8);

				glDisableClientState(GL_COLOR_ARRAY);
				glDisableClientState(GL_VERTEX_ARRAY);
			}

			auto RenderVBO() -> void override {
				
			}
		};
	}
	
}
