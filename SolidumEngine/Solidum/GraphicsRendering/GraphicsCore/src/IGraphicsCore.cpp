#include "../include/IGraphicsCore.h"

IGraphicsCore* IGraphicsCore::singletonInstance = nullptr;

IGraphicsCore * IGraphicsCore::getInstance()
{
	return singletonInstance;
}


IGraphicsCore::IGraphicsCore()
{
}


IGraphicsCore::~IGraphicsCore()
{
}
