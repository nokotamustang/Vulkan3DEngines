#pragma once

#include "engine_window.hpp"
#include "engine_pipeline.hpp"
#include "engine_device.hpp"
#include "engine_swap_chain.hpp"
#include <memory>
#include <vector>

namespace Engine {
	class App {
	public:
		static constexpr int WIDTH = 1600;
		static constexpr int HEIGHT = 900;

		App();
		~App();

		App(const App&) = delete;
		App& operator=(const App&) = delete;

		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		Window window = Window(WIDTH, HEIGHT, "Vulkan window");
		EngineDevice engineDevice = EngineDevice(window);
		PipelineConfig pipelineConfig = Pipeline::defaultPipelineConfig(WIDTH, HEIGHT);
		EngineSwapChain swapChain = EngineSwapChain(engineDevice, window.getExtent());
		std::unique_ptr<Pipeline> pipeline; // Unique pointer to a pipeline object as a smart pointer

		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}