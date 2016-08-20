#pragma once

class State
{
public:
	virtual bool Init() { return true; }
	virtual bool Run() { return true; }
	virtual void End() {}
private:
};