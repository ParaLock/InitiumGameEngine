#pragma once
#include "../../../sysInclude.h"
#include "RenderDataAttribs.h"

struct RenderData {
	RenderDataAttributes attribs;

	std::shared_ptr<void> _data;
};

class RenderDataPacket
{
private:
	RENDER_DATA_TYPE _type;

	std::shared_ptr<RenderData> _data;
public:
	RenderDataPacket();
	~RenderDataPacket();

	template<typename T>
	void addData(T data) { 
		
		_data = std::make_shared<RenderData>();

		_data->_data = std::make_shared<T>(data);
	};

	template<typename T>
	T* getData() {
		
		return (T*)_data->_data.get();

	};

	RenderDataAttributes& getAttributes() { return _data->attribs; }

	void setType(RENDER_DATA_TYPE type) { _type = type; };

	RENDER_DATA_TYPE getType() { return _type; };
};

