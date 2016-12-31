#include "../include/ShaderGeneralDataBuffer.h"



ShaderGeneralDataBuffer::ShaderGeneralDataBuffer(std::string name)
{
	_typeSizeMap = new std::map<std::string, size_t>;
	_variableMap = new std::map<std::string, ShaderGeneralDataVar*>;

	_name = name;
}


ShaderGeneralDataBuffer::~ShaderGeneralDataBuffer()
{
	delete _typeSizeMap;
	delete _variableMap;
}

void ShaderGeneralDataBuffer::registerVarType(std::string typeName, size_t typeSize)
{
	auto itr = _typeSizeMap->find(typeName);

	if (itr == _typeSizeMap->end()) {
		_typeSizeMap->insert({typeName, typeSize});
	}
}

void ShaderGeneralDataBuffer::updateVar(std::string varName, void * pData)
{
	auto itr = _variableMap->find(varName);

	if (itr != _variableMap->end()) {
		ShaderGeneralDataVar *var = _variableMap->at(varName);

		size_t size = var->getSize();
		size_t startAddr = var->getStartAddr();
		size_t endAddr = var->getEndAddr();

		if (startAddr + size > endAddr) {
			std::cout << "SHADER GENERAL DATA BUFF: Var overflow";
		}
		else {
			memcpy(static_cast<__int8*>(_pBuffCPUMem) + startAddr, pData, size);
		}
	}
	else {
		std::cout << "SHADER GENERAL DATA BUFF: Var not found";
	}
}

void ShaderGeneralDataBuffer::initMemory()
{
	_pBuffCPUMem = new __int8[_lastVarOffset];

	SecureZeroMemory(_pBuffCPUMem, _lastVarOffset);

	_GPUBuff = GPUBufferFactory::
		createBuffer(_lastVarOffset, BUFFER_TYPE::SHADER_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE);

	_GPUBuff->Write(_pBuffCPUMem, _lastVarOffset, 0);
}

void ShaderGeneralDataBuffer::updateGPU()
{
	if(_pBuffCPUMem != nullptr)
		_GPUBuff->Write(_pBuffCPUMem, _lastVarOffset, 0);
}

std::vector<std::string> ShaderGeneralDataBuffer::getVarNameList()
{
	std::vector<std::string> varNameList;

	for (std::map<std::string, ShaderGeneralDataVar*>::iterator itr =
		_variableMap->begin(); itr != _variableMap->end(); itr++) 
	{
		varNameList.push_back(itr->first);

		int debugRef = -1;
	}

	return varNameList;
}

void ShaderGeneralDataBuffer::addVariable(std::string varName, std::string varType)
{
	auto itr = _typeSizeMap->find(varType);

	if (itr != _typeSizeMap->end()) {

		if (numVars == 0) {
			size_t typeSize = _typeSizeMap->at(varType);
			ShaderGeneralDataVar *var =
				new ShaderGeneralDataVar(typeSize, 0, typeSize);

			_variableMap->insert({ varName, var });
			_lastVarOffset += typeSize;
		}
		else {
			size_t typeSize = _typeSizeMap->at(varType);
			ShaderGeneralDataVar *var =
				new ShaderGeneralDataVar(typeSize, _lastVarOffset, _lastVarOffset + typeSize);

			_variableMap->insert({ varName, var });
			_lastVarOffset += typeSize;
		}
	}

	numVars++;
}
