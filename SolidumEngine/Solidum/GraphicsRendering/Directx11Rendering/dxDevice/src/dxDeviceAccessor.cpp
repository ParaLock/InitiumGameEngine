#include "..\include\dxDeviceAccessor.h"


dxDevice* dxDeviceAccessor::dxEncapsulator = NULL;

void dxDeviceAccessor::initAccessor(dxDeviceManager *dxDevManagerIN)
{
	dxDevice *dxCore = dxDevManagerIN->getDxCore();

	dxEncapsulator = dxCore;
}
