#pragma once

#include "../../common.h"

class ShaderInputLayoutElement {
public:
	ShaderInputLayoutElement(std::string semantic, int type, UINT index, BYTE mask, bool hardCodedIndex) {
		_semantic = semantic;
		_type = type;
		_index = index;
		_mask = mask;
		_hardCodedIndex = hardCodedIndex;
	}

	bool _hardCodedIndex;

	UINT _index;
	std::string _semantic;
	INPUT_LAYOUT_ELEMENT_CLASS _class = INPUT_LAYOUT_ELEMENT_CLASS::PER_VERTEX_DATA;
	BYTE _mask;

	int _type;
};