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

	std::list<std::shared_ptr<RenderDataPacket>> allNodes;

	data.getAllRenderData(allNodes);

	bool cullObject = false;

	for each(std::shared_ptr<RenderDataPacket> node in allNodes) {
		//Compare node bb with frustum
		//Do Frustrum culling

		if (cullObject) {

			//data.removePacket(node);
		}
	}
}
