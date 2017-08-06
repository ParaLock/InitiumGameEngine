#pragma once

class RefCounted
{
private:
	unsigned int _refCount;
public:
	RefCounted();
	~RefCounted();
};

