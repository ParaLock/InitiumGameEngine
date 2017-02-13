#include "../include/RenderPass.h"


RenderPass::RenderPass()
{
}

RenderPass::~RenderPass()
{
}

void RenderPass::execute(RenderDataStream* stream)
{
	_shader->attachPipeline(_pipelineStateObject);

	int i = 0;
	int indexCount = 0;

	while (stream->dataAvalible()) {

		RenderDataBatch dataBatch = stream->readNext();
	
		IResource* data = dataBatch.getData();

		if (data->getLoadStatus()) {

			switch (dataBatch.getType())
			{
			case STREAM_DATA_TYPE::MATERIAL:

				_shader->updateMaterialUniforms(data->getCore<Material>());

				break;
			case STREAM_DATA_TYPE::MESH:

				_shader->setMesh(data->getCore<mesh>());

				indexCount = data->getCore<mesh>()->numIndices;

				break;
			case STREAM_DATA_TYPE::TEXTURE:

				_shader->setModelTexture(data->getCore<Texture>());

				break;
			case STREAM_DATA_TYPE::TRANSFORM:

				_shader->updateModelUniforms(data->getCore<Transform>());
				
				break;
			case STREAM_DATA_TYPE::LIGHT:
				
				_shader->updateLightUniforms(data->getCore<ILight>());

				break;
			case STREAM_DATA_TYPE::CAMERA:

				_shader->updateCameraUniforms(data->getCore<camera>());

				break;
			default:
				break;
			}
		}
	}

	_shader->updateGPU();
	_shader->execute(indexCount);

	stream->resetStreamIndex();
}
