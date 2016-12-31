#include "../include/dxDeviceManager.h"

dxDeviceManager::dxDeviceManager()
{
	dxDev = new dxDevice();
}


dxDeviceManager::~dxDeviceManager()
{
	delete dxDev;
}

void dxDeviceManager::dxCreateDev(dxConfigBlock *config)
{
	dxDev->Initialize(config);
}

dxDevice * dxDeviceManager::getDxCore()
{
	return dxDev;
}
