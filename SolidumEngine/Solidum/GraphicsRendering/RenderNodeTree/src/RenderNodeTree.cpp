#include "../include/RenderNodeTree.h"



RenderNodeTree::RenderNodeTree()
{
	_nodeQueryMap = new std::map<uint64_t, RenderNode*>;
	_rootNodes = new std::map<IShader*, RenderNode*>;
	_orderedRootNodes = new std::list<RenderNode*>;
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

void RenderNodeTree::setExecutionOrder(const std::list<SHADER_RENDER_TYPE>& order)
{
	for each(SHADER_RENDER_TYPE type in order) {

		for (auto itr = _rootNodes->begin(); itr != _rootNodes->end(); itr++) {

			if (itr->second->getShader()->getRenderMode() == type) {

				_orderedRootNodes->push_back(itr->second);
			}
		}
	}
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
	for each(RenderNode* node in *_orderedRootNodes) {

		while (node->getChild() != nullptr) {
			node->render();
			node = node->getChild();
		}

		node->render();
	}
}
