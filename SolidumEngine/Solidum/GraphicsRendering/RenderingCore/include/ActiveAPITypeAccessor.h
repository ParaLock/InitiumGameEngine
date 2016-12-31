#pragma once
#include "../../../sysInclude.h"

class ActiveAPITypeAccessor
{
public:
	ActiveAPITypeAccessor();
	~ActiveAPITypeAccessor();

	static SUPPORTED_GRAPHICS_API _apiInUse;

	static void initAccessor(SUPPORTED_GRAPHICS_API apiInUse) { _apiInUse = apiInUse; };
};

