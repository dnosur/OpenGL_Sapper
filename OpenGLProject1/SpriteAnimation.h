#pragma once
#include <iostream>
#include <filesystem>

#include "FrameSoundsController.h"
#include "ImagesController.h"
#include "Window.h"

#include "functions.h"

namespace fs = std::filesystem;

class SpriteAnimation
{
	ImagesController sprites;
	FrameSoundsController frameSounds;

	Window* window;

	char* title;

	char* folder;
	int frameRate;

	int currentSpriteIndex;

	bool repeat;
	bool stopOnEnd;
	bool play, pause;

	bool end;

	void LoadSpritesFromFolder();
public:
	SpriteAnimation();
	SpriteAnimation(const char* title, const char* folder, int frameRate, Window* window, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());
	SpriteAnimation(const char* title, std::vector<Image> sprites, int frameRate, Window* window, std::vector<FrameSound> frameSounds = std::vector<FrameSound>());

	void SetWindow(Window* window);

	std::vector<Image> GetSprites();
	void SetSprites(std::vector<Image> sprites);

	char* GetFolder();
	void LoadFromFolder(char* folder);

	int GetFrameRate();
	void SetFrameRate(int frameRate);

	bool IsRepeat();
	void SetRepeat(bool repeat);

	bool IsStopOnEnd();
	void SetStopOnEnd(bool stopOnEnd);

	void SetCurrentSprite(int spriteIndex);
	int GetCurrentSpriteIndex();

	void Play(Coord coord, Size size);

	bool IsEnd();

	bool IsPlay();
	void Pause();
	void Stop();

	void Restart();
};