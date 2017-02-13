#include "../include/RenderDataStream.h"



RenderDataStream::RenderDataStream()
{
	_stream = new std::vector<RenderDataBatch>;
}

RenderDataStream::~RenderDataStream()
{
	delete _stream;
}

RenderDataBatch RenderDataStream::readNext()
{
	RenderDataBatch res(STREAM_DATA_TYPE::INVALID, nullptr);
		
	if (!_stream->empty()) {
		res = _stream->at(_streamIndex);
		_streamIndex--;
	}


	return res;
}

void RenderDataStream::resetStreamIndex()
{
	_streamIndex = _stream->size() - 1;
}

void RenderDataStream::writeNext(IResource * res, STREAM_DATA_TYPE type)
{
	_stream->push_back(RenderDataBatch(type, res));

	_streamIndex = _stream->size() - 1;
}

