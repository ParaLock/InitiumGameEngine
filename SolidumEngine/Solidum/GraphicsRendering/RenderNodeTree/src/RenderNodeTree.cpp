#include "../include/RenderNodeTree.h"



RenderNodeTree::RenderNodeTree()
{
	_nodeQueryMap = new std::map<uint64_t, RenderNode*>;
	_rootNodes = new std::map<RENDER_NODE_TYPE, RenderNode*>;
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

void RenderNodeTree::addNode(RenderNode * node, uint64_t id)
{
	_nodeQueryMap->insert({id, node});

	auto itr = _rootNodes->find(node->getType());
	
	if (itr == _rootNodes->end()) {
		_rootNodes->insert({ node->getType(), node });
		return;
	}
	
	RenderNode* root = _rootNodes->at(node->getType());

	while (root->getChild() != nullptr)
		root = root->getChild();


	root->setChild(node);

	node->setParent(root);
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

void RenderNodeTree::updateNodeVisibility(bool isVisible, uint64_t nodeid)
{
	auto itr = _nodeQueryMap->find(nodeid);

	if (itr != _nodeQueryMap->end()) {
		RenderNode* node = _nodeQueryMap->at(nodeid);

		node->getRenderParams()->setPerNodeParam_isVisible(isVisible);
	}
}

RenderParams * RenderNodeTree::getRenderNodeParams(uint64_t nodeid)
{
	if (_nodeQueryMap->find(nodeid) != _nodeQueryMap->end()) {
		
		RenderNode* foundNode = _nodeQueryMap->at(nodeid);

		RenderParams* params = foundNode->getRenderParams();
		

		return params;
	}

	return nullptr;
}

std::list<RenderNode*> RenderNodeTree::queryNodesByType(RENDER_NODE_TYPE type)
{
	std::list<RenderNode*> nodes;

	for (auto itr = _rootNodes->begin(); itr != _rootNodes->end(); itr++) {

		RenderNode* child = itr->second;
		while (child != nullptr) {

			if (child->getType() == type && child->isRenderViable() == true) {

				nodes.push_back(child);
			}

			child = child->getChild();
		}
	}

	return nodes;
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
	for (auto itr = _rootNodes->begin(); itr != _rootNodes->end(); itr++) {

		RenderNode* node = itr->second;

		while (node->getChild() != nullptr) {
			node->render();
			node = node->getChild();
		}

		node->render();
	}
}
