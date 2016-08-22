#pragma once

#include "SDLHeaders.h"
#include "libheaders.h"


struct Vector2D
{
	float x, y;
};


enum
{
	ANIMATE_FRAMES = 0,
	ANIMATE_SHEET,
};

struct AnimFrame
{
	SDL_Surface *Texture;
	float delay;
};

// It's a real shame we're stuck to SDL 1.2; SDL 2 has rotation and flipping options, among many other cool features

class Sprite
{
public:
	Sprite();

	void SetAnimationMode(int mode);
	void SetupSpriteSheet(SDL_Surface *sheet, int columnCount, int rowCount, int totalFrames, float frameWidth, float frameHeight, float offsetX, float offsetY, float stepX, float stepY);
	void Update();
	void Draw();
	void PauseAnimation();
	void PlayAnimation();
	void RestartAnimation();
	void StopAnimation();
	bool IsPaused() const;

	void AddFrame(SDL_Surface *tex, float duration);
	void AddSheetFrame(float duration);
	void SetInitialVelocity(float VelX, float VelY);
	float GetVelocityX() const;
	float GetVelocityY() const;
	void SetVelocityX(float newVelx);
	void SetVelocityY(float newVely);
	void SetPosition(float x, float y);
	Vector2D GetPosition() const;
	void Move(float x, float y);	// offset the sprite's position by x, y (relative to current position)

	void SetStretch(bool set);
	bool ShouldStretch() const;

	void SetLooping(bool l);
	void Reactivate();

	SDL_Rect GetRect() const;

	// ----------
	// this is so dumb...
	bool IsActive() const;
	void Destroy();
	// ----------
	
private:
	// position
	Vector2D pos;

	// current image clipping rect
	SDL_Rect imgRect;

	//rate of movement
	float velx, vely;

	float tickTime;

	//sprite sheet information (0-based)
	int m_currentColumn;
	int m_currentRow;
	int columnSize; // how many frames across?
	int rowSize; // how many frames down?
	int maxFrames; // for sprite sheets that don't fill the entire space: how many frames are contained in the sheet?
	SDL_Rect startingRect; // initial position in the sheet to start animating from
	float m_stepX;
	float m_stepY;

	int currentFrame;
	std::vector<AnimFrame> m_frames;
	SDL_Surface *m_sheet; // if using a sprite sheet, save it here so we can reference it for each AnimFrame

	int animMode;
	bool loop;

	bool paused;

	bool noRender;

	bool stretch;

	float globalTime;
};