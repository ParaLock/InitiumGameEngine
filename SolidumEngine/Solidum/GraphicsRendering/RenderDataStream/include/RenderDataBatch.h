#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

class RenderDataBatch
{
private:
	STREAM_DATA_TYPE _type;
	IResource* _data;
public:
	RenderDataBatch(STREAM_DATA_TYPE type, IResource* data);
	~RenderDataBatch();

	STREAM_DATA_TYPE getType() { return _type; };
	IResource* getData() { return _data; }
};

