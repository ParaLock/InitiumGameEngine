#pragma once

#include "../../dxDevice/include/dxDevice.h"

#ifndef _DXDEVICE_MANAGER_H
#define _DXDEVICE_MANAGER_H

class dxDeviceManager
{
private:
	dxDevice *dxDev;
public:
	dxDeviceManager();
	~dxDeviceManager();

	void dxCreateDev(dxConfigBlock *config);

	dxDevice * getDxCore();
};

#endif