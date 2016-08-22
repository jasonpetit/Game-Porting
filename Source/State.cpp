#include "SDLHeaders.h"
#include "libheaders.h"
#include "State.h"

extern State *activeState;

bool ChangeState(State *newState)
{
	if(activeState != nullptr)
		activeState->End();

	activeState = newState;
	return activeState->Init();
}

State::State(int id) : stateID(id)
{

}

State::State() : stateID(STATE_UNDEFINED)
{

}

void State::ProcessInput(SDL_Event &event)
{

}

bool State::Init()
{
	return true;
}

bool State::Run()
{
	return true;
}

void State::End()
{

}

int State::GetStateID() const
{
	return stateID;
}

void State::SetNextState(int state)
{
	nextState = state;
}

int State::GetStateTarget() const
{
	return nextState;
}

void State::DrawText(float x, float y, TTF_Font *font, SDL_Surface *target, const std::string &str, SDL_Color textColor)
{
	SDL_Surface *message = TTF_RenderText_Solid(font, str.c_str(), textColor);
	SDL_Rect offset;
	offset.x = Sint16(x);
	offset.y = Sint16(y);
	SDL_BlitSurface(message, NULL, target, &offset);
	SDL_FreeSurface(message);
}

SDL_Color State::MakeColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Color returnColor = { r, g, b };
	return returnColor;
}
