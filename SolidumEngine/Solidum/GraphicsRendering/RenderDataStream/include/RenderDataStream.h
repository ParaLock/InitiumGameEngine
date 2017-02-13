#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "RenderDataBatch.h"


class RenderDataStream
{
private:
	std::vector<RenderDataBatch> *_stream;

	int _streamIndex = 0;
public:
	RenderDataStream();
	~RenderDataStream();

	RenderDataBatch readNext();

	void writeNext(IResource* res, STREAM_DATA_TYPE type);

	bool dataAvalible() { return (_streamIndex != -1) ? true : false; }

	void resetStreamIndex();

	void flushStream() { _stream->clear(); };
};

