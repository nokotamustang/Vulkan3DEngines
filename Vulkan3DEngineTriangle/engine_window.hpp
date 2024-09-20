#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace Engine {
	class Window {
	public:
		Window(int width, int height, std::string title);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		inline int getWidth() { return width; }
		inline int getHeight() { return height; }
		inline std::string getTitle() { return title; }
		inline GLFWwindow* getWindow() { return window; }
		bool shouldClose() { return glfwWindowShouldClose(window); }
		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
		void testVulcan();
		VkExtent2D getExtent() {
			return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
		}

	private:
		int width, height;
		std::string title;
		GLFWwindow* window;
		bool isRunning;
		void initWindow();
	};
};