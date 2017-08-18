#pragma once

class IResource;

class IRenderFlowGraphIOInterface {
public:
	virtual void assignHookResourceByName(std::string& hookName, IResource* res) = 0;
private:
};