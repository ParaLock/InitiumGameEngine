#include "../include/RenderDataBatch.h"


RenderDataBatch::RenderDataBatch(STREAM_DATA_TYPE type, IResource * data)
{
	_type = type;
	_data = data;
}

RenderDataBatch::~RenderDataBatch()
{
}
