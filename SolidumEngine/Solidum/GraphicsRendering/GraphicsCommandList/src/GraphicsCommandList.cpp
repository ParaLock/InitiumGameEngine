#include "../include/GraphicsCommandList.h"

GraphicsCommandList::~GraphicsCommandList()
{
}

void GraphicsCommandList::sortBlocks(std::list<GraphicsCommandBlock*>& list_in)
{
	std::list<GraphicsCommandBlock*>::iterator& pivot = list_in.begin();

	while (pivot != list_in.end()) {

		for (auto& itr = list_in.begin(); itr != list_in.end(); itr++) {

			if (*itr < *pivot) {
				std::swap(*itr, *pivot);
			}
		}

		pivot++;
	}
}

IGraphicsCommandBlock * GraphicsCommandList::getNextCmdBlock(int priority)
{
	auto& block = GraphicsCommandBlock(priority, *_resourceCreator);

	_activeCmdBlockListStore.push_back(block);

	_activeCmdBlockListSorted.push_back(&_activeCmdBlockListStore.back());

	return &_activeCmdBlockListStore.back();
}

void GraphicsCommandList::executeCommands()
{
	//sortBlocks(_activeCmdBlockListSorted);

	for each(GraphicsCommandBlock* cmdBlock in _activeCmdBlockListSorted) {
		cmdBlock->execute();
	}

	_activeCmdBlockListStore.clear();
	_activeCmdBlockListSorted.clear();
}
