#include "../include/dxShader.h"

dxShader::dxShader(LPCWSTR fileName, std::string shaderStageType)
{
	varNameCBuffMap = new std::map<std::string, dxDynamicCBuffer*>;

	//pointTexSampler = TextureSamplerFactory::createTextureSampler(TEX_FILTER_POINT, NO_ANISOTROPHIC_FILTERING, TEX_ADDR_MODE_CLAMP);

	//pointTexSampler->parentShaderType = PARENT_SHADER_TYPE_PIXEL;
	//pointTexSampler->resSlot = 0;

	texSamplerWrap = TextureSamplerFactory::createTextureSampler(TEX_FILTER_LINEAR, NO_ANISOTROPHIC_FILTERING, TEX_ADDR_MODE_WRAP);

	texSamplerWrap->parentShaderType = PARENT_SHADER_TYPE_PIXEL;
	texSamplerWrap->resSlot = 0;

	cBuffers = new std::vector<dxDynamicCBuffer*>;

	buildShaderVarIO(fileName);

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	D3DX11CompileFromFile(fileName, 0, 0, "Vshader", "vs_5_0", 0, 0, 0, &vertexShaderCode, 0, 0);
	dxDev->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);

	D3DX11CompileFromFile(fileName, 0, 0, "Pshader", "ps_5_0", 0, 0, 0, &pixelShaderCode, 0, 0);
	dxDev->CreatePixelShader(pixelShaderCode->GetBufferPointer(), pixelShaderCode->GetBufferSize(), NULL, &pixelShader);

	if (shaderStageType == "geometry_stage") {

		D3D11_INPUT_ELEMENT_DESC iedSolid[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		dxDev->CreateInputLayout(iedSolid, 3, vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), &InputLayout);
	}
	else if (shaderStageType == "post_process_stage") {

		D3D11_INPUT_ELEMENT_DESC iedLight[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		dxDev->CreateInputLayout(iedLight, 2, vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), &InputLayout);
	}
	else {

		D3D11_INPUT_ELEMENT_DESC iedSolid[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		dxDev->CreateInputLayout(iedSolid, 3, vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), &InputLayout);
	}
}


dxShader::~dxShader()
{
	delete varNameCBuffMap;
	delete cBuffers;
}

void dxShader::attachTex(ITexture * tex)
{
	texture = tex;

	texture->parentShaderType = PARENT_SHADER_TYPE_PIXEL;
	texture->resSlot = 0;
}

void dxShader::updateVar(std::string varName, void * data)
{
	dxDynamicCBuffer *cBuff = varNameCBuffMap->at(varName);

	std::tuple<size_t, size_t> var = cBuff->updateVar(varName, data);
}

void dxShader::updateGPU()
{
	for (size_t i = 0; i < cBuffers->size(); ++i)
	{
		cBuffers->at(i)->updateGPU();
	}
}

void dxShader::buildShaderVarIO(LPCWSTR fileName)
{
	std::ifstream file(fileName);

	std::vector<std::string*> *line = new std::vector<std::string*>;

	if (!file.is_open())
	{
		printf("Shader file open failed!\n");
	}
	else {
		char buf[256];

		while (!file.eof())
		{
			file.getline(buf, 256);

			if (buf[0] != 0)
				line->push_back(new std::string(buf));
		}

		bool parsingCBuffVars = false;

		dxDynamicCBuffer *newCBuff;

		for (size_t i = 0; i < line->size(); i++) {

			std::vector<std::string> tokens = StringManipulation::split(line->at(i), ' ');

			std::string tabCleanStr = tokens.at(0);
				
			tabCleanStr.erase(std::remove(tabCleanStr.begin(), tabCleanStr.end(), '\t'), tabCleanStr.end());

			if (tabCleanStr == "cbuffer") {
				newCBuff = new dxDynamicCBuffer(tokens.at(1));
				cBuffers->push_back(newCBuff);
				parsingCBuffVars = true;
			}

			if (tabCleanStr == "};") {

				parsingCBuffVars = false;
			}

			if (parsingCBuffVars) {

				if (tabCleanStr != "{") {

					std::string semicolonCleanStr = tokens.at(1);

					semicolonCleanStr.erase(std::remove(semicolonCleanStr.begin(), semicolonCleanStr.end(), ';'), semicolonCleanStr.end());

					int breakpoint = 1;

					if (tabCleanStr == "matrix") {
						newCBuff->addVar(semicolonCleanStr, sizeof(D3DXMATRIX));
						varNameCBuffMap->insert({ semicolonCleanStr, newCBuff});
					}

					if (tabCleanStr == "float") {
						newCBuff->addVar(semicolonCleanStr, sizeof(float));
						varNameCBuffMap->insert({ semicolonCleanStr, newCBuff });
					}

					if (tabCleanStr == "float3") {

						newCBuff->addVar(semicolonCleanStr, sizeof(D3DXVECTOR3));
						varNameCBuffMap->insert({ semicolonCleanStr, newCBuff });
					}

					if (tabCleanStr == "float4") {
						newCBuff->addVar(semicolonCleanStr, sizeof(D3DXVECTOR4));
						varNameCBuffMap->insert({ semicolonCleanStr, newCBuff });
					}
				}
			}
		}

		int parentShaderList[2];

		parentShaderList[0] = PARENT_SHADER_TYPE_VERTEX;
		parentShaderList[1] = PARENT_SHADER_TYPE_PIXEL;

		for (size_t i = 0; i < cBuffers->size(); ++i)
		{
			cBuffers->at(i)->initConstructedCBuffer(parentShaderList[i]);
		}
	}
}

void dxShader::Bind()
{
	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	dxDevContext->VSSetShader(vertexShader, NULL, 0);
	dxDevContext->PSSetShader(pixelShader, NULL, 0);

	dxDevContext->IASetInputLayout(InputLayout);

	texSamplerWrap->Bind();
	//pointTexSampler->Bind();

	if (texture != NULL) 
		texture->Bind();



	for (size_t i = 0; i < cBuffers->size(); ++i) {

		cBuffers->at(i)->Bind();

	}
}
