#pragma once
#include <string>

#include "include\glew.h"
#include "include\glfw3.h"

namespace chupakabra {
	namespace graphics {
		/// <summary>
		/// Wrapper GLFWwindow class
		/// </summary>
		class Window {
		public:
			/// <summary>
			/// Default constructor
			/// </summary>
			Window() = default;
			/// <summary>
			/// Copy-constructor
			/// </summary>
			/// <param name="window"> Window to copy </param>
			explicit Window(const Window& window) 
				: Window({ window.GetWidth(), window.GetWidth() }, window.GetTitle(), window.GetMonitor(), window.GetShare()) {}

			/// <summary>
			/// Square window constructor
			/// </summary>
			/// <param name="size"> Window's height and width </param>
			/// <param name="title"> Window's title </param>
			/// <param name="monitor"> Window's monitor to use fullscreen </param>
			/// <param name="share"> Window's share context </param>
			explicit Window(const size_t& size, const std::string& title = "Application",
				GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr)
				: Window({ size, size }, title, monitor, share) {}

			/// <summary>
			/// Common window constructor
			/// </summary>
			/// <param name="size"> Window's height and width </param>
			/// <param name="title"> Window's title </param>
			/// <param name="monitor"> Window's monitor to use fullscreen </param>
			/// <param name="share"> Window's share context </param>
			explicit Window(const std::pair<size_t, size_t>& size, const std::string& title = "Application",
				GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr)
				: width(size.first), height(size.second), title(title), monitor(monitor), share(share) {
				this->window = glfwCreateWindow(size.first, size.second, title.c_str(), monitor, share);
			}

			/// <summary>
			/// Window's destructor
			/// </summary>
			virtual ~Window() = default;

			/// <summary>
			/// Get window's width
			/// </summary>
			[[nodiscard]] auto GetWidth() const -> size_t {
				return this->width;
			}
			/// <summary>
			/// Set window's width
			/// </summary>
			/// <param name="width"> Value to set </param>
			auto SetWidth(const size_t& width) -> void {
				if (this->width == width) return;
				this->width = width;
				this->RefreshSize();
			}

			/// <summary>
			///	Get window's height
			/// </summary>
			[[nodiscard]] auto GetHeight() const -> size_t {
				return this->height;
			}
			/// <summary>
			/// Set window's width
			/// </summary>
			/// <param name="height"> Value to set </param>
			auto SetHeight(const size_t& height) -> void {
				if (this->height == height) return;
				this->height = height;
				this->RefreshSize();
			}

			/// <summary>
			///	Get window's title
			/// </summary>
			[[nodiscard]] auto GetTitle() const -> std::string {
				return this->title;
			}
			/// <summary>
			/// Set window's title
			/// </summary>
			/// <param name="title"> Value to set </param>
			auto SetTitle(const std::string& title) -> void {
				if (this->title == title) return;
				this->title = title;
				this->RefreshTitle();
			}

			/// <summary>
			/// Get window's monitor
			/// </summary>
			[[nodiscard]] auto GetMonitor() const -> GLFWmonitor* {
				return this->monitor;
			}
			/// <summary>
			/// Set window's monitor
			/// </summary>
			/// <param name="monitor"> Monitor to set. If nullptr, sets windowed-mode </param>
			/// <param name="position"> Position to set </param>
			/// <param name="size"> Content size to set </param>
			/// <param name="refreshRate"> Screen refresh rate to set in Hz </param>
			auto SetMonitor(GLFWmonitor* monitor, const std::pair<size_t, size_t>& position,
				const std::pair<size_t, size_t>& size, const size_t refreshRate) -> void {
				if (this->monitor != monitor) return;
				this->monitor = monitor;
				this->RefreshMonitor(position, size, refreshRate);
			}

			/// <summary>
			/// Window's shared window 
			/// </summary>
			[[nodiscard]] auto GetShare() const -> GLFWwindow* {
				return this->share;
			}
			// TODO Set share

			/// <summary>
			///	GLFWwindow instance
			/// </summary>
			[[nodiscard]] auto GetWindow() const -> GLFWwindow* {
				return this->window;
			}
			// TODO Set or create window

		protected:
			/// <summary>
			/// Window's width
			/// </summary>
			size_t width = 0u;
			/// <summary>
			/// Window's height
			/// </summary>
			size_t height = 0u;
			/// <summary>
			/// Window's title
			/// </summary>
			std::string title = "Application";
			/// <summary>
			/// Window's monitor
			/// </summary>
			GLFWmonitor* monitor = nullptr;
			/// <summary>
			/// Window's shared window
			/// </summary>
			GLFWwindow* share = nullptr;
			/// <summary>
			/// GLFWwindow instance
			/// </summary>
			GLFWwindow* window = nullptr;

			/// <summary>
			/// Restores size values
			/// </summary>
			/// <returns></returns>
			auto RefreshSize() const -> void {
				glfwSetWindowSize(this->window, this->width, this->height);
			}

			/// <summary>
			/// Restore title
			/// </summary>
			/// <returns></returns>
			auto RefreshTitle() const -> void {
				glfwSetWindowTitle(this->window, this->title.c_str());
			}

			/// <summary>
			/// Restore monitor
			/// </summary>
			/// <param name="position"> Position to set </param>
			/// <param name="size"> Content size to set </param>
			/// <param name="refreshRate"> Screen refresh rate to set in Hz </param>
			/// <returns></returns>
			auto RefreshMonitor(const std::pair<size_t, size_t>& position,
				const std::pair<size_t, size_t>& size, const size_t refreshRate) const -> void {
				glfwSetWindowMonitor(this->window, this->monitor, position.first, position.second, size.first, size.second, refreshRate);
			}
		};

		class Initializer {
		public:
			static auto InitializeWindow(const double version, const size_t size, const std::string& title = "Application", GLFWmonitor* monitor = nullptr, Window* share = nullptr) -> Window* {
				return InitializeWindow(version, { size, size }, title, monitor, share);
			}
			
			static auto InitializeWindow(const double version, const std::pair<size_t, size_t>& size = { 100u, 100u }, const std::string& title = "Application", GLFWmonitor* monitor = nullptr, Window* share = nullptr) -> Window* {
				// Is GLFW initialized
				if (!glfwInit()) {
					return nullptr;
				}

				// Set GLFW version
				glfwWindowHint(GLFW_VERSION_MAJOR, static_cast<int>(version));
				glfwWindowHint(GLFW_VERSION_MINOR, static_cast<int>(version * 10) % 10);

				GLFWwindow* shareWindow = nullptr;
				if (share) {
					shareWindow = share->GetWindow();
				}
				
				auto* window = new Window(size, title, monitor, shareWindow);
				
				if (!window->GetWindow()) {
					return nullptr;
				}
				
				glfwMakeContextCurrent(window->GetWindow());
				
				// Set GLEW experimental
				glewExperimental = true;
				
				// Is GLEW initialized
				if (glewInit() != GLEW_OK) {
					return nullptr;
				}

				return window;
			}
		};

		class Deinitializer {
		public:
			static auto Deinitialize() -> void {
				glfwTerminate();
			}
		};
	}
}