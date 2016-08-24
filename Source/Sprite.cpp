#include "SDLHeaders.h"
#include "libheaders.h"
#include "Sprite.h"

#pragma warning(disable: 4244) // Conversion possible loss of data
#pragma warning(disable: 4018) // Signed/unsigned mismatch

extern SDL_Surface *Screen;

Sprite::Sprite() : tickTime(0.f),
					currentFrame(0),
					noRender(false),
					loop(true),
					animMode(ANIMATE_FRAMES),
					paused(false),
					stretch(false),
					velx(0),
					vely(0),
					pos(Vector2D()),
					imgRect(SDL_Rect()),
					startingRect(SDL_Rect())					
{
	tickTime = SDL_GetTicks();
	globalTime = tickTime;
}

void Sprite::SetAnimationMode(int mode)
{
	animMode = mode;
}

void Sprite::SetupSpriteSheet(SDL_Surface *sheet, int columnCount, int rowCount, int totalFrames, float frameWidth, float frameHeight, float offsetX, float offsetY, float stepX, float stepY)
{
	animMode = ANIMATE_SHEET;
	m_sheet = sheet;

	SDL_Rect rect;
	rect.x = offsetX;
	rect.y = offsetY;
	rect.w = frameWidth;
	rect.h = frameHeight;

	imgRect = startingRect = rect;

	maxFrames = totalFrames;
	columnSize = columnCount;
	rowSize = rowCount;

	m_stepX = stepX;
	m_stepY = stepY;
}

void Sprite::Update()
{
	if(m_frames.empty() || noRender)
		return;

	if(velx != 0 || vely != 0)
	{
		// Time based movement so the game doesn't go so dang fast
		float curTime = SDL_GetTicks();
		pos.x += velx; //* ((curTime - globalTime) * 0.1f);
		pos.y += vely; //* ((curTime - globalTime) * 0.1f);
		globalTime = curTime;
	}

	if(SDL_GetTicks() > tickTime + m_frames[currentFrame].delay)
	{
		tickTime = SDL_GetTicks();

		if(!IsPaused())
		{
			currentFrame++;
			if(currentFrame >= m_frames.size())
			{
				if(loop)
					currentFrame = 0;
				else noRender = true;
			}
			if(animMode == ANIMATE_SHEET)
			{
				m_currentColumn++;
				if(m_currentColumn >= columnSize)
				{
					m_currentColumn = 0;
					m_currentRow++;
					if(m_currentRow >= rowSize)	// reset to beginning
					{
						m_currentRow = 0;
						imgRect = startingRect;
					}
					else
					{
						imgRect.x = startingRect.x;
						imgRect.y += startingRect.h;
					}
				}
				else
				{
					imgRect.x += m_stepX;
					imgRect.y += m_stepY;
				}
			}
		}
	}
}

void Sprite::Draw()
{
	if(noRender || m_frames.empty())
		return;

	if(animMode == ANIMATE_SHEET)
	{
		SDL_Rect offset;
		offset.x = pos.x;
		offset.y = pos.y;
		SDL_BlitSurface(m_sheet, &imgRect, Screen, &offset);
	}
	else
	{
		if(m_frames[currentFrame].Texture == NULL)
			return;
		SDL_Rect offset;
		offset.x = pos.x;
		offset.y = pos.y;

		imgRect.w = m_frames[currentFrame].Texture->w;
		imgRect.h = m_frames[currentFrame].Texture->h;
		imgRect.x = 0;
		imgRect.y = 0;

		if(ShouldStretch())
			SDL_BlitSurface(m_frames[currentFrame].Texture, NULL, Screen, &offset);
		else
			SDL_BlitSurface(m_frames[currentFrame].Texture, &imgRect, Screen, &offset);
	}
}

void Sprite::PauseAnimation()
{
	paused = true;
}

void Sprite::PlayAnimation()
{
	paused = false;
}

void Sprite::RestartAnimation()
{
	tickTime = SDL_GetTicks();
	imgRect = startingRect;
	m_currentColumn = 0;
	m_currentRow = 0;
	paused = false;
	currentFrame = 0;
}

void Sprite::StopAnimation()
{
	currentFrame = 0;
	paused = true;
}

bool Sprite::IsPaused() const
{
	return paused;
}

void Sprite::AddFrame(SDL_Surface *tex, float duration)
{
	AnimFrame frame;
	frame.delay = duration;
	frame.Texture = tex;

	m_frames.push_back(frame);
}

void Sprite::AddSheetFrame(float duration)
{
	AnimFrame frame;
	frame.delay = duration;
	m_frames.push_back(frame);
}

void Sprite::SetInitialVelocity(float VelX, float VelY)
{
	velx = VelX;
	vely = VelY;
}

float Sprite::GetVelocityX() const
{
	return velx;
}

float Sprite::GetVelocityY() const
{
	return vely;
}

void Sprite::SetVelocityX(float newVelx)
{
	velx = newVelx;
}

void Sprite::SetVelocityY(float newVely)
{
	vely = newVely;
}

void Sprite::SetPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

Vector2D Sprite::GetPosition() const
{
	return pos;
}

void Sprite::Move(float x, float y)
{
	pos.x += x;
	pos.y += y;
}

void Sprite::SetStretch(bool set)
{
	stretch = set;
}

bool Sprite::ShouldStretch() const
{
	return stretch;
}

void Sprite::SetLooping(bool l)
{
	loop = l;
}

void Sprite::Reactivate()
{
	noRender = false;
	currentFrame = 0;
	imgRect = startingRect;
	m_currentColumn = 0;
	m_currentRow = 0;
	tickTime = SDL_GetTicks();
}

SDL_Rect Sprite::GetRect() const
{
	SDL_Rect ret = SDL_Rect();
	if(animMode == ANIMATE_SHEET)
	{
		ret.h = startingRect.h;
		ret.w = startingRect.w;
		ret.x = pos.x;
		ret.y = pos.y;
		return ret;
	}
	else if(!m_frames.empty())
	{
		ret.h = m_frames[currentFrame].Texture->h;
		ret.w = m_frames[currentFrame].Texture->w;
		ret.x = pos.x;
		ret.y = pos.y;
		return ret;
	}
	else return ret;
}

bool Sprite::IsActive() const
{
	return !noRender;
}

void Sprite::Destroy()
{
	noRender = true;
}
