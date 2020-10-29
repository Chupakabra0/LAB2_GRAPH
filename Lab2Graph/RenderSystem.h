#pragma once
#include <iostream>
#include <numbers>

#include "Window.h"

#define abstract = 0

namespace chupakabra {
	namespace render {
		namespace Cube {
			inline float vertices[] = {
				-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
				0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
				0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
				0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

				-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
				0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
				0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
				0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
				-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
				-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

				-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
				-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
				-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
				-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

				0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
				0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
				0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
				0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
				0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
				0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
				0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
				0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
				0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
				-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
				0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
				0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
				0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
				-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
			};
			
			inline unsigned int VBO = 1;

			inline void init() {
				glGenBuffers(1, &VBO);

				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
			}


		};

		namespace Squares {
			inline GLfloat vertices[] = {
				0, 0, 0,
				1, 0, 0,
				1, 1, 0,
				0, 1, 0,

				0, 0, 0,
				0, 1, 0,
				-1, 1, 0,
				-1, 0, 0
			};
			inline GLfloat colors[] = {

				255, 0, 0,
				255, 0, 0,
				255, 0, 0,
				255, 0, 0,

				0, 0, 255,
				0, 0, 255,
				0, 0, 255,
				0, 0, 255
			};
		}

		class IRenderSystem {
		public:
			IRenderSystem() = default;
			virtual ~IRenderSystem() = default;

			virtual auto Initialize() -> void abstract;
			virtual auto Render() -> void abstract;
			virtual auto RenderTriangleArray() -> void abstract;
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
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			}
			
			auto Render() -> void override {
				glClear(GL_COLOR_BUFFER_BIT);

				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_COLOR_ARRAY);

				glVertexPointer(3, GL_FLOAT, 0, Squares::vertices);
				glColorPointer(3, GL_FLOAT, 0, Squares::colors);

				glDrawArrays(GL_QUADS, 0, 8);

				glDisableClientState(GL_COLOR_ARRAY);
				glDisableClientState(GL_VERTEX_ARRAY);
			}

			auto RenderTriangleArray() -> void override {
				auto colorRgb = 0.f;
				glClearColor(static_cast<GLclampf>(sin(colorRgb * std::numbers::pi / 180.f)), static_cast<GLclampf>(abs(cos(colorRgb * std::numbers::pi / 180.f))),
					static_cast<GLclampf>(abs(sin(colorRgb * std::numbers::pi / 180.f) + cos(colorRgb * std::numbers::pi / 180.f))), static_cast<GLclampf>(1.0f));
				glClear(GL_COLOR_BUFFER_BIT);

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

			auto RenderVBO() -> void override {
				auto colorRgb = 0.f;
				glClearColor(static_cast<GLclampf>(sin(colorRgb * std::numbers::pi / 180.f)), static_cast<GLclampf>(abs(cos(colorRgb * std::numbers::pi / 180.f))),
					static_cast<GLclampf>(abs(sin(colorRgb * std::numbers::pi / 180.f) + cos(colorRgb * std::numbers::pi / 180.f))), static_cast<GLclampf>(1.0f));

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glEnable(GL_DEPTH_TEST);
				glMatrixMode(GL_MODELVIEW); //set the matrix to model view mode
				glPushMatrix(); // push the matrix
				glRotatef(static_cast<GLfloat>(50.0 * glfwGetTime()), static_cast<GLfloat>(1.0), static_cast<GLfloat>(1.0), static_cast<GLfloat>(0.0)); //apply transformation
				glGenBuffers(1, &Cube::VBO);

				//Установка активности VBO

				glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof Cube::vertices, Cube::vertices, GL_STATIC_DRAW);
				glVertexPointer(static_cast<GLint>(3), GL_FLOAT, static_cast<GLsizei>(0u), nullptr);
				glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
				glEnableVertexAttribArray(0);
				glEnableClientState(GL_VERTEX_ARRAY);

				glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), static_cast<GLsizei>(sizeof Cube::vertices / sizeof(Cube::vertices[0] / 5)));
				
				glPopMatrix();

				glDisableClientState(GL_VERTEX_ARRAY);
			}
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
			auto Render() -> void override {

				glClear(GL_COLOR_BUFFER_BIT);

				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_COLOR_ARRAY);

				glVertexPointer(3, GL_FLOAT, 0, Squares::vertices);
				glColorPointer(3, GL_FLOAT, 0, Squares::colors);

				glDrawArrays(GL_QUADS, 0, 8);

				glDisableClientState(GL_COLOR_ARRAY);
				glDisableClientState(GL_VERTEX_ARRAY);
			}

			auto RenderTriangleArray() -> void override {
				auto colorRgb = 0.f;
				glClearColor(static_cast<GLclampf>(sin(colorRgb * std::numbers::pi / 180.f)), static_cast<GLclampf>(abs(cos(colorRgb * std::numbers::pi / 180.f))),
					static_cast<GLclampf>(abs(sin(colorRgb * std::numbers::pi / 180.f) + cos(colorRgb * std::numbers::pi / 180.f))), static_cast<GLclampf>(1.0f));
				glClear(GL_COLOR_BUFFER_BIT);

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

			auto RenderVBO() -> void override {
				auto colorRgb = 0.f;
				glClearColor(static_cast<GLclampf>(sin(colorRgb * std::numbers::pi / 180.f)), static_cast<GLclampf>(abs(cos(colorRgb * std::numbers::pi / 180.f))),
					static_cast<GLclampf>(abs(sin(colorRgb * std::numbers::pi / 180.f) + cos(colorRgb * std::numbers::pi / 180.f))), static_cast<GLclampf>(1.0f));

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glEnable(GL_DEPTH_TEST);
				glMatrixMode(GL_MODELVIEW); //set the matrix to model view mode
				glPushMatrix(); // push the matrix
				glRotatef(static_cast<GLfloat>(50.0 * glfwGetTime()), static_cast<GLfloat>(1.0), static_cast<GLfloat>(1.0), static_cast<GLfloat>(0.0)); //apply transformation
				glGenBuffers(1, &Cube::VBO);

				//Установка активности VBO

				glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof Cube::vertices, Cube::vertices, GL_STATIC_DRAW);
				glVertexPointer(static_cast<GLint>(3), GL_FLOAT, static_cast<GLsizei>(0u), nullptr);
				glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
				glEnableVertexAttribArray(0);
				glEnableClientState(GL_VERTEX_ARRAY);

				glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), static_cast<GLsizei>(sizeof Cube::vertices / sizeof(Cube::vertices[0] / 5)));
				glPopMatrix(); //pop the matrix

				glDisableClientState(GL_VERTEX_ARRAY);
			}
		};
	}
	
}
