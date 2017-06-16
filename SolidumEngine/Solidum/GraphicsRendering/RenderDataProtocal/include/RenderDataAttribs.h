#pragma once
#include "../../../sysInclude.h"

class BoundingSphere;

struct RenderDataAttributes {

	struct OcclusionCulling {

		bool _isFrustrumCullable;
		BoundingSphere* _bSphere;

	} occlusionCulling;

	struct Visibility {
		bool _isVisible;
	} visibility;
};