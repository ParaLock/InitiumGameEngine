#include "../include/DynamicStruct.h"



void * DynamicStruct::getParameter(std::string varName)
{
	if (varName == "GPUBUFFER") {
		return _GPUBuff->getParameter("BUFFER");
	}
	return nullptr;
}

DynamicStruct::DynamicStruct()
{
	_typeSizeMap = new std::map<std::string, size_t>;
	_variableMap = new std::map<std::string, DynamicStructMember*>;
}


DynamicStruct::~DynamicStruct()
{
	delete _typeSizeMap;
	delete _variableMap;
}

void DynamicStruct::load()
{
	InitData* realBuilder = static_cast<InitData*>(getContext()->getResourceInitParams());

	_name = realBuilder->_name;
	_hasGPUBuff = realBuilder->_hasGPUBuff;

}

void DynamicStruct::unload()
{
}

void DynamicStruct::updateVar(std::string varName, void * pData)
{
	auto itr = _variableMap->find(varName);

	if (itr != _variableMap->end()) {
		DynamicStructMember *var = _variableMap->at(varName);

		size_t size = var->getSize();
		size_t startAddr = var->getStartAddr();
		size_t endAddr = var->getEndAddr();

		if (startAddr + size > endAddr) {
			std::cout << "DYNAMIC BUFF: Var overflow";
		}
		else {
			memcpy(static_cast<__int8*>(_pBuffCPUMem) + startAddr, pData, size);
		}
	}
	else {
		std::cout << "DYNAMIC BUFF: Var not found";
	}
}

void DynamicStruct::updateGPU()
{
	if (_GPUBuff != nullptr) {

		GPUBuffer* realBuff = _GPUBuff;

		realBuff->Write(_pBuffCPUMem, _lastVarOffset, 0);
	}
}

void DynamicStruct::initMemory(ResourceCreator* resCreator)
{
	_pBuffCPUMem = new __int8[_lastVarOffset];

	SecureZeroMemory(_pBuffCPUMem, _lastVarOffset);

	if (_hasGPUBuff) {

		_GPUBuff = (GPUBuffer*)resCreator->createResourceImmediate<GPUBuffer>(&GPUBuffer::InitData
			(_lastVarOffset, BUFFER_TYPE::SHADER_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE), std::to_string(getRandomNumber()) + _name,
			[](IResource*) {});
	}
}

std::vector<std::string> DynamicStruct::getVarNameList()
{
	std::vector<std::string> varNameList;

	for (std::map<std::string, DynamicStructMember*>::iterator itr =
		_variableMap->begin(); itr != _variableMap->end(); itr++)
	{
		varNameList.push_back(itr->first);

		int debugRef = -1;
	}

	return varNameList;
}

void DynamicStruct::addVariable(std::string varName, size_t varSize)
{
	if (numVars == 0) {
		DynamicStructMember *var =
			new DynamicStructMember(varSize, 0, varSize);

		_variableMap->insert({ varName, var });
		_lastVarOffset += varSize;
	}
	else {
		DynamicStructMember *var =
			new DynamicStructMember(varSize, _lastVarOffset, _lastVarOffset + varSize);

		_variableMap->insert({ varName, var });
		_lastVarOffset += varSize;
	}

	numVars++;
}
