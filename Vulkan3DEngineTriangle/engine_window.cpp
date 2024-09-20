#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>

#include "engine_window.hpp"

namespace Engine {
	Window::Window(int width, int height, std::string title) : width(width), height(height), title(title), isRunning(true) {
		initWindow();
	}

	Window::~Window() {
		glfwDestroyWindow(window); // Destroy the window
		glfwTerminate(); // Terminate GLFW
	}

	void Engine::Window::initWindow() {
		glfwInit(); // Initialize GLFW
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Don't create an OpenGL context, since we're using Vulkan
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable window resizing for now
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); // Create the window
	}

	void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		// Create the window surface using GLFW
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void Window::testVulcan() {
		// First sample code to test Vulkan is working
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		GLFWwindow* window = glfwCreateWindow(1600, 900, "Vulkan window", nullptr, nullptr);

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::cout << extensionCount << " extensions supported\n";

		glm::mat4 matrix;
		glm::vec4 vec;
		auto test = matrix * vec;

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}

		glfwDestroyWindow(window);

		glfwTerminate();
	}


}
