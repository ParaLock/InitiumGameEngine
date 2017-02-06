#include "../include/RenderDataStream.h"



RenderDataStream::RenderDataStream()
{
	_stream = new std::list<RenderDataBatch>;
}

RenderDataStream::~RenderDataStream()
{
	delete _stream;
}

RenderDataBatch RenderDataStream::getNext()
{
	RenderDataBatch res = _stream->front();

	_stream->pop_front();

	return res;
}

void RenderDataStream::insertData(IResource * res, STREAM_DATA_TYPE type)
{
	_stream->push_back(RenderDataBatch(type, res));
}

