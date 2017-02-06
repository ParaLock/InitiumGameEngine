#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "RenderDataBatch.h"


class RenderDataStream
{
private:
	std::list<RenderDataBatch> *_stream;
public:
	RenderDataStream();
	~RenderDataStream();

	RenderDataBatch getNext();

	bool dataAvalible() { return (_stream->size() != 0) ? true : false; }

	void insertData(IResource* res, STREAM_DATA_TYPE type);
};

