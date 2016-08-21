#pragma once

class State
{
public:
	virtual void ProcessInput(SDL_Event &event) { }
	virtual bool Init() { return true; }
	virtual bool Run() { return true; }
	virtual void End() {}
private:
};

bool ChangeState(State *newState);