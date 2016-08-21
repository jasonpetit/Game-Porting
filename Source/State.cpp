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
