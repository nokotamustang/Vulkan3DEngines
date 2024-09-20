#pragma once

#include "engine_device.hpp"
#include <string>
#include <vector>


namespace Engine {

	struct PipelineConfig {
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class Pipeline {
	public:
		Pipeline(EngineDevice& device, const PipelineConfig& config, const std::string& vertFilePath, const std::string& fragFilePath);
		~Pipeline();

		Pipeline(const Pipeline&) = delete; // Delete the copy constructor
		void operator=(const Pipeline&) = delete; // Delete the assignment operator

		static PipelineConfig defaultPipelineConfig(uint32_t width, uint32_t height);

		void bind(VkCommandBuffer commandBuffer);

	private:
		EngineDevice& engineDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;

		static std::vector<char> readFile(const std::string& filePath);
		void createGraphicsPipeline(const PipelineConfig& config, const std::string& vertFilePath, const std::string& fragFilePath);

		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule); // Pointer to a pointer because the function will be modifying the shader module
	};
}