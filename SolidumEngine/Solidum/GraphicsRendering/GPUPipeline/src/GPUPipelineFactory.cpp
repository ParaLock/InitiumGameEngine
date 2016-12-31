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

	switch (ActiveAPITypeAccessor::_apiInUse) {
		case DIRECTX11:
			newPipeline = new dxGPUPipeline();
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
		std::vector<ShaderGeneralDataBuffer*> varBuffers;

		for (size_t i = 0; i < line->size(); i++) {

			std::vector<std::string> splitStr = StringManipulation::split(line->at(i), ' ');

			std::string debugTest = splitStr.at(0);

			if (splitStr.at(0) == "VS_SHADER_END") {
				shaderContext = GPUPipelineElementParentShader::SOL_NON;
			}

			if (splitStr.at(0) == "PS_SHADER_END") {
				shaderContext = GPUPipelineElementParentShader::SOL_NON;
			}

			if (splitStr.at(0) == "GENERAL_DATA_END") {
				generalDataContext = "null";

				varBuffers.back()->initMemory();

				newPipeline->attachGeneralShaderDataBuffer(varBuffers.back(), varBuffers.back()->getName(), shaderContext);
		
				int debugRef = -1;
			}

			if (splitStr.at(0) == "MESH_DATA_END") {
				meshDataLayoutContext = "null";

				inputLayouts.back()->generateInputLayout();

				for (unsigned int i = 0; i < inputLayouts.size(); i++)
				newPipeline->attachShaderInputLayout(inputLayouts[i], inputLayouts[i]->getName());
			}

			if (meshDataLayoutContext != "null") {

				inputLayouts.back()->addInput(splitStr.at(0), splitStr.at(1));
			}

			if (generalDataContext != "null") {
				varBuffers.back()->addVariable(splitStr.at(1), splitStr.at(0));
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

			if (splitStr.at(0) == "GENERAL_DATA" && splitStr.at(1) == "IN") {
				generalDataContext = "GENERAL_DATA";

				varBuffers.push_back(new ShaderGeneralDataBuffer(splitStr.at(2)));

				varBuffers.back()->registerVarType("MATRIX", sizeof(float[4][4]));
				varBuffers.back()->registerVarType("FLOAT", sizeof(float));
				varBuffers.back()->registerVarType("FLOAT2", sizeof(float[2]));
				varBuffers.back()->registerVarType("FLOAT3", sizeof(float[3]));
				varBuffers.back()->registerVarType("FLOAT4", sizeof(float[4]));
			}

			if (splitStr.at(0) == "MESH_DATA" && splitStr.at(1) == "IN") {

				meshDataLayoutContext = splitStr.at(1);

				switch (ActiveAPITypeAccessor::_apiInUse) {
					case DIRECTX11:
						inputLayouts.push_back(new dxShaderInputLayout(splitStr.at(2)));
					break;
				}
			}

			if (splitStr.at(0) == "MESH_DATA" && splitStr.at(1) == "OUT") {
				meshDataLayoutContext = splitStr.at(1);

				switch (ActiveAPITypeAccessor::_apiInUse) {
					case DIRECTX11:
						inputLayouts.push_back(new dxShaderInputLayout(splitStr.at(2)));
					break;
				}
			}
		
			
			if (splitStr.at(0) == "BIND") {

				if (splitStr.at(1) == "GBUFFER" && splitStr.at(2) == "OUTPUT") {

					RenderTarget* renderTarget = (RenderTarget*)GraphicsResourcePoolManagerAccessor::poolManager->
						getPool("render_target_pool")->getResource(splitStr.at(3));

					newPipeline->attachRenderTarget(renderTarget, splitStr.at(3), shaderContext, true);	
				
				}
				else if (splitStr.at(1) == "GBUFFER" && splitStr.at(2) == "INPUT") {

					RenderTarget* renderTarget = static_cast<RenderTarget*>(GraphicsResourcePoolManagerAccessor::poolManager->
						getPool("render_target_pool")->getResource(splitStr.at(3)));

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

				if (splitStr.at(1) == "DEFERRED") {
					executionContext = true;
				}
				else {
					executionContext = false;
				}

				if (splitStr.at(3) == "GBUFFER") {
					RenderTarget* renderTarget = (RenderTarget*)GraphicsResourcePoolManagerAccessor::poolManager->
						getPool("render_target_pool")->getResource(splitStr.at(4));

					if (splitStr.at(2) == "CLEAR") {
						newPipeline->attachOP(renderTarget, GPUPipelineSupportedOP::SOL_CLEAR,
							GPUPipelineElementType::SOL_RENDER_TARGET, executionContext);
					}		
				}		
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
