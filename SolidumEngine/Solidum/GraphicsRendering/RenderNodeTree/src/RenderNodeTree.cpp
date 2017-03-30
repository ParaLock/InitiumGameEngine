#include "../include/RenderNodeTree.h"



RenderNodeTree::RenderNodeTree()
{
	_nodeQueryMap = new std::map<uint64_t, RenderNode*>;
	_rootNodes = new std::map<IShader*, RenderNode*>;
}


RenderNodeTree::~RenderNodeTree()
{
}

uint64_t RenderNodeTree::getUniqueNodeID()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<uint64_t> dist(0, UINT_MAX);

	return dist(mt);
}

void RenderNodeTree::setExecutionOrder(std::vector<SHADER_RENDER_TYPE> order)
{
	_renderOrder = order;
}

void RenderNodeTree::addNode(RenderNode * node, uint64_t id)
{
	_nodeQueryMap->insert({id, node});

	auto itr = _rootNodes->find(node->getShader());

	if (itr != _rootNodes->end()) {

		RenderNode* rootNode = _rootNodes->at(node->getShader());

		RenderNode* childNode = rootNode;

		while (true) {

			if (childNode->getChild() != nullptr) {
				childNode = childNode->getChild();
			}
			else {
				childNode->setChild(node);
				node->setParent(childNode);

				return;
			}
		}
	}
	else {
		_rootNodes->insert({node->getShader(), node});
	}
}

void RenderNodeTree::updateGlobalRenderParams(GlobalRenderingParams params)
{
	for (auto itr = _rootNodes->begin(); itr != _rootNodes->end(); itr++) {

		RenderNode* child = itr->second;
		while (child != nullptr) {
			child->updateGlobalRenderParams(params);

			child = child->getChild();
		}
	}
}

void RenderNodeTree::updateNodeLocalRenderParams(LocalRenderingParams params, uint64_t nodeid)
{
	auto itr = _nodeQueryMap->find(nodeid);

	if (itr != _nodeQueryMap->end()) {
		RenderNode* node = _nodeQueryMap->at(nodeid);

		node->updateLocalRenderParams(params);
	}
}

void RenderNodeTree::updateNodeVisibility(bool isVisible, uint64_t nodeid)
{
	auto itr = _nodeQueryMap->find(nodeid);

	if (itr != _nodeQueryMap->end()) {
		RenderNode* node = _nodeQueryMap->at(nodeid);

		node->setVisibility(isVisible);
	}
}

std::vector<RenderNode*> RenderNodeTree::queryAllLights()
{
	std::vector<RenderNode*> lights;

	for (auto itr = _rootNodes->begin(); itr != _rootNodes->end(); itr++) {

		RenderNode* child = itr->second;
		while (child != nullptr) {

			if (child->getType() == RENDER_NODE_TYPE::LIGHT_RENDER_NODE && child->getVisibility() == true) {
				lights.push_back(child);
			}

			child = child->getChild();
		}
	}

	return lights;
}

std::vector<RenderNode*> RenderNodeTree::queryAllShadowCastingLights()
{
	std::vector<RenderNode*> lights;

	for (auto itr = _rootNodes->begin(); itr != _rootNodes->end(); itr++) {

		RenderNode* child = itr->second;
		while (child != nullptr) {

			if (child->getType() == RENDER_NODE_TYPE::LIGHT_RENDER_NODE && child->getVisibility() == true) {

				bool* isCaster = (bool*)child->getVar("IS_SHADOW_CASTER");

				if (*isCaster) {

					lights.push_back(child);
				}
			}
			child = child->getChild();
		}
	}

	return lights;
}

std::vector<RenderNode*> RenderNodeTree::queryAllMeshes()
{
	std::vector<RenderNode*> meshes;

	for (auto itr = _rootNodes->begin(); itr != _rootNodes->end(); itr++) {

		RenderNode* child = itr->second;
		while (child != nullptr) {

			if (child->getType() == RENDER_NODE_TYPE::MESH_RENDER_NODE && child->getVisibility() == true) {
				meshes.push_back(child);
			}

			child = child->getChild();
		}
	}

	return meshes;
}

void RenderNodeTree::removeNode(uint64_t id)
{
	auto itr = _nodeQueryMap->find(id);

	if (itr != _nodeQueryMap->end()) {
		RenderNode* node = _nodeQueryMap->at(id);

		if (node->getChild() != nullptr) {

			node->getChild()->setParent(node->getParent());
		}

		delete node;
	}
}

void RenderNodeTree::frustrumCull()
{

}

void RenderNodeTree::optimize()
{
}

void RenderNodeTree::walkTree()
{
	std::vector<RenderNode*> _orderedRootNodes;

	for (int i = 0; i < _renderOrder.size(); i++) {
		for (auto itr = _rootNodes->begin(); itr != _rootNodes->end(); itr++) {
			RenderNode* node = itr->second;

			if (node->getShader()->getRenderMode() == _renderOrder[i]) {
				_orderedRootNodes.push_back(node);
			}
		}
	}

	for (int i = 0; i < _orderedRootNodes.size(); i++) {

		RenderNode* node = _orderedRootNodes[i];

		while (node->getChild() != nullptr) {
			node->render();
			node = node->getChild();
		}

		node->render();
	}
}
