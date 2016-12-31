#pragma once

#include "../../dxDevice/include/dxDeviceManager.h"

#ifndef _DEV_ACCESSOR_H
#define _DEV_ACCESSOR_H

class dxDeviceAccessor
{
public:
	static void initAccessor(dxDeviceManager *dxDevManagerIN);

	static dxDevice* dxEncapsulator;
};

#endif
