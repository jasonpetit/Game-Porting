#pragma once

enum
{
	STATE_UNDEFINED = 0,
	STATE_MAINMENU,
	STATE_PLAYING,
	STATE_INCREDITS,

	STATE_WANTEXIT,
};

class State
{
public:
	State();
	State(int id);
	virtual void ProcessInput(SDL_Event &event);
	virtual bool Init();
	virtual bool Run();
	virtual void End();

	int GetStateID() const;
	void SetNextState(int state);
	int GetStateTarget() const;

protected:
	void DrawText(float x, float y, TTF_Font *font, SDL_Surface *target, const std::string &str, SDL_Color textColor);
	SDL_Color MakeColor(Uint8 r, Uint8 g, Uint8 b);
	
	int stateID;
	int nextState;

private:
};

bool ChangeState(State *newState);