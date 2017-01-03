#include "../include/GPUPipelineFactory.h"


GPUPipelineFactory::GPUPipelineFactory()
{
}


GPUPipelineFactory::~GPUPipelineFactory()
{
}

GPUPipeline * GPUPipelineFactory::createPipeline(LPCWSTR pipelineDescFile)
{
	GPUPipeline *newPipeline;

	std::wstring filePathWStr(pipelineDescFile);

	std::string filepathSTLStr = StringManipulation::ws2s(filePathWStr);

	switch (ActiveAPITypeAccessor::_apiInUse) {
		case DIRECTX11:
			newPipeline = new dxGPUPipeline(filepathSTLStr);
			break;
	}

	std::ifstream file(pipelineDescFile);

	std::vector<std::string*> *line = new std::vector<std::string*>;

	if (!file.is_open())
	{
		printf("Pipeline descriptor file open failed!\n");
	}
	else {
		char buf[256];

		while (!file.eof())
		{
			file.getline(buf, 256);

			if (buf[0] != 0)
				line->push_back(new std::string(buf));
		}

		GPUPipelineElementParentShader shaderContext = GPUPipelineElementParentShader::SOL_NON;

		std::string meshDataLayoutContext = "null";
		std::string generalDataContext = "null";

		std::vector<ShaderInputLayout*> inputLayouts;

		for (size_t i = 0; i < line->size(); i++) {

			std::vector<std::string> splitStr = StringManipulation::split(line->at(i), ' ');

			std::string debugTest = splitStr.at(0);

			if (splitStr.at(0) == "VS_SHADER_END") {
				shaderContext = GPUPipelineElementParentShader::SOL_NON;
			}

			if (splitStr.at(0) == "PS_SHADER_END") {
				shaderContext = GPUPipelineElementParentShader::SOL_NON;
			}

			if (splitStr.at(0) == "VS_SHADER_BEGIN") {
				shaderContext = GPUPipelineElementParentShader::SOL_VS;
			}

			if (splitStr.at(0) == "PS_SHADER_BEGIN") {
				shaderContext = GPUPipelineElementParentShader::SOL_PS;
			}

			if (splitStr.at(0) == "INIT") {
				if (splitStr.at(1) == "GBUFFER") {

					GraphicsResourcePoolManagerAccessor::poolManager->getPool("render_target_pool")->addResource(
						RenderTargetFactory::createRenderTarget(1, 1, TEX_FORMAT::RGBA_32BIT_FLOAT),
						splitStr.at(2), true);	

					int debugRef = -1;

				}

				if (splitStr.at(1) == "SAMPLER") {
					TEX_ADDR_MODES addrMode;
					TEX_FILTERS filterType;

					if (splitStr.at(2) == "WRAP") {
						addrMode = TEX_ADDR_MODES::TEX_ADDR_MODE_WRAP;
					}
					if (splitStr.at(2) == "CLAMP") {
						addrMode = TEX_ADDR_MODES::TEX_ADDR_MODE_CLAMP;
					}

					if (splitStr.at(3) == "LINEAR") {
						filterType = TEX_FILTERS::TEX_FILTER_LINEAR;
					}

					if (splitStr.at(3) == "POINT") {
						filterType = TEX_FILTERS::TEX_FILTER_POINT;
					}

					GraphicsResourcePoolManagerAccessor::poolManager->getPool("texture_sampler_pool")->addResource(
						TextureSamplerFactory::createTextureSampler(filterType, ANISOTRPHIC_FILTER_LEVELS::NO_ANISOTROPHIC_FILTERING, addrMode),
						splitStr.at(4), true);

					int debugRef = -1;
				}
			}
		
			
			if (splitStr.at(0) == "BIND") {

				if (splitStr.at(1) == "GBUFFER" && splitStr.at(2) == "OUTPUT") {

					RenderTarget* renderTarget = (RenderTarget*)GraphicsResourcePoolManagerAccessor::poolManager->
						getPool("render_target_pool")->getResource(splitStr.at(3));



					newPipeline->attachRenderTarget(renderTarget, splitStr.at(3), shaderContext, true);	
				
				}
				else if (splitStr.at(1) == "GBUFFER" && splitStr.at(2) == "INPUT") {

					RenderTarget* renderTarget = (RenderTarget*)GraphicsResourcePoolManagerAccessor::poolManager->
						getPool("render_target_pool")->getResource(splitStr.at(3));

					newPipeline->attachRenderTarget(renderTarget, splitStr.at(3), shaderContext, false);
				}
				if (splitStr.at(1) == "TEXTURE_HOOK") {

					newPipeline->attachTextureHook(splitStr.at(2), shaderContext);
				}

				if (splitStr.at(1) == "BUFFER_HOOK") {

					newPipeline->attachBufferHook(splitStr.at(2), shaderContext);
				

					int debugRef = -1;
				}

				if (splitStr.at(1) == "SAMPLER") {

					TextureSampler* texSampler = (TextureSampler*)GraphicsResourcePoolManagerAccessor::poolManager->
						getPool("texture_sampler_pool")->getResource(splitStr.at(2));
					newPipeline->attachTextureSampler(texSampler, splitStr.at(2), shaderContext);
				}
			}

			if (splitStr.at(0) == "PIPELINE_OP") {

				bool executionContext;
				GPUPipelineSupportedOP op;
				GPUPipelineElementType opTargetType;

				std::string targetName = "null";

				if (splitStr.at(1) == "DEFERRED") {
					executionContext = true;
				}
				else {
					executionContext = false;
				}

				if (splitStr.at(2) == "CLEAR") {
					op = GPUPipelineSupportedOP::SOL_CLEAR;
				}


				if (splitStr.at(2) == "SWAPFRAME") {

					op = GPUPipelineSupportedOP::SOL_SWAPFRAME;
				}

				if (splitStr.at(3) == "GBUFFER") {
					opTargetType = GPUPipelineElementType::SOL_RENDER_TARGET;
					targetName = splitStr.at(4);
				}

				if (splitStr.at(3) == "ZBUFFER") {
					opTargetType = GPUPipelineElementType::SOL_ZBUFFER;
				}

				newPipeline->attachOP(op, targetName,
					opTargetType, executionContext);
			}

			if (splitStr.at(0) == "DEPTH_TEST") {

				if (splitStr.at(1) == "enable") {
					newPipeline->setDepthTest(true);
				}
				else {
					newPipeline->setDepthTest(false);
				}
			}

			if (splitStr.at(0) == "BLENDING") {
				if (splitStr.at(1) == "enable") {

					newPipeline->setBlending(true);
				}
				else {
					newPipeline->setBlending(false);
				}
			}
		}
	}

	return newPipeline;
}
