#pragma once
#include "../../../sysInclude.h"

class RenderDataPacket
{
private:
	RENDER_DATA_TYPE _type;

	std::shared_ptr<void> _data;
public:
	RenderDataPacket();
	~RenderDataPacket();

	template<typename T>
	void addData(T data) { 
		
		_data = std::make_shared<T>(data);
	};

	template<typename T>
	T* getData() {
		
		return (T*)_data.get();

	};

	void setType(RENDER_DATA_TYPE type) { _type = type; };

	RENDER_DATA_TYPE getType() { return _type; };
};

