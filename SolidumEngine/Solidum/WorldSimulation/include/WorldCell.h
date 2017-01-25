#pragma once
#include "../../sysInclude.h"

#include "WorldNode.h"

class WorldCell
{
private:
	std::list<WorldNode*> *nodes;
public:
	WorldCell();
	~WorldCell();

	void addNode(WorldNode* node);
};

