#include "../include/FrustumCullingLayer.h"


FrustumCullingLayer::FrustumCullingLayer()
{
}


FrustumCullingLayer::~FrustumCullingLayer()
{
}

void FrustumCullingLayer::execute(RenderDataGroup & data)
{
	//Placeholder gist code!!

	std::list<RenderDataPacket*> allNodes;

	data.getAllRenderData(allNodes);

	bool cullObject = false;

	for each(RenderDataPacket* node in allNodes) {
		//Compare node bb with frustum
		//Do Frustrum culling

		if (cullObject) {

			//data.removePacket(node);
		}
	}
}
