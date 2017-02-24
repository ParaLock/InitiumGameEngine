#include "../include/Material.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::load(IResourceBuilder * builder)
{
	MaterialBuilder* realBuilder = static_cast<MaterialBuilder*>(builder);

	isLoaded = true;
}

void Material::unload()
{
	isLoaded = false;
}

void Material::createPass(std::string name, Shader * shader, GPUPipeline * pipeline)
{
	MaterialPass* newPass = new MaterialPass;

	shader->attachPipeline(pipeline);
	
	newPass->setShader(shader);
	newPass->setGPUPipeline(pipeline);

	_passes.insert({name, newPass });
}

MaterialPass * Material::getPass(std::string name)
{
	return _passes[name];
}

std::vector<uint64_t> Material::generateClientRenderNodes(mesh * mesh, Texture * texture)
{
	std::vector<uint64_t> _nodes;
	
	RenderNodeTree* renderTree = GraphicsCore::getInstance()->getRenderNodeTree();

	for (auto itr = _passes.begin(); itr != _passes.end(); itr++) {

		uint64_t nodeID = renderTree->getUniqueNodeID();

		renderTree->addNode(new MeshRenderNode(mesh, texture, itr->second), nodeID);

		_nodes.push_back(nodeID);
	}

	return _nodes;
}

