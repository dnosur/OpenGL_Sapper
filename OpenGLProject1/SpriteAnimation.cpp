#include "SpriteAnimation.h"

void SpriteAnimation::LoadSpritesFromFolder()
{
	this->sprites.Clear();

	if (!fs::exists(folder) || !fs::is_directory(folder)) {
		std::cerr << "Directory does not exist: " << folder << std::endl;
		return;
	}

	for (const auto& entry : fs::directory_iterator(folder)) {
		if (fs::is_regular_file(entry.path())) {
			std::string name = std::string(title) + entry.path().filename().string();
			std::cout << "File: " << entry.path() << " " << name << std::endl;
			this->sprites.Load(entry.path().string().c_str(), name.c_str());
		}
	}
}

SpriteAnimation::SpriteAnimation()
{
	window = nullptr;
	folder = nullptr;
	title = (char*)"Undefined";

	frameRate = 0;
	currentSpriteIndex = -1;
	play = pause = repeat = stopOnEnd = end = false;
}

SpriteAnimation::SpriteAnimation(const char* title, const char* folder, int frameRate, Window* window, std::vector<FrameSound> frameSounds)
{
	copyStr((char*)title, this->title);
	copyStr((char*)folder, this->folder);
	play = pause = repeat = stopOnEnd = end = false;
	currentSpriteIndex = -1;
	this->frameRate = frameRate;
	this->window = window;

	this->frameSounds.SetFrameSounds(frameSounds);
	LoadSpritesFromFolder();
}

SpriteAnimation::SpriteAnimation(const char* title, std::vector<Image> sprites, int frameRate, Window* window, std::vector<FrameSound> frameSounds)
{
	copyStr((char*)title, this->title);
	SetSprites(sprites);
	folder = nullptr;

	this->frameRate = frameRate;
	this->window = window;
	currentSpriteIndex = -1;

	play = pause = repeat = stopOnEnd = end = false;

	//this->frameSounds.SetFrameSounds(frameSounds);
	this->sprites.SetImages(sprites);
}

void SpriteAnimation::SetWindow(Window* window)
{
	this->window = window;
}

std::vector<Image> SpriteAnimation::GetSprites()
{
	return sprites.GetImages();
}

void SpriteAnimation::SetSprites(std::vector<Image> sprites)
{
	this->sprites.SetImages(sprites);
}

char* SpriteAnimation::GetFolder()
{
	return folder;
}

void SpriteAnimation::LoadFromFolder(char* folder)
{
	copyStr(folder, this->folder);
	LoadSpritesFromFolder();
}

int SpriteAnimation::GetFrameRate()
{
	return frameRate;
}

void SpriteAnimation::SetFrameRate(int frameRate)
{
	if (frameRate < 0) {
		return;
	}
	this->frameRate = frameRate;
}

bool SpriteAnimation::IsRepeat()
{
	return repeat;
}

void SpriteAnimation::SetRepeat(bool repeat)
{
	this->repeat = repeat;
}

bool SpriteAnimation::IsStopOnEnd()
{
	return stopOnEnd;
}

void SpriteAnimation::SetStopOnEnd(bool stopOnEnd)
{
	this->stopOnEnd = stopOnEnd;
}

void SpriteAnimation::SetCurrentSprite(int spriteIndex)
{
	if (spriteIndex < 0 || spriteIndex >= sprites.GetImages().size()) {
		return;
	}
	currentSpriteIndex = spriteIndex;
}

int SpriteAnimation::GetCurrentSpriteIndex()
{
	return currentSpriteIndex;
}

void SpriteAnimation::Play(Coord coord, Size size)
{
	if (end || pause) {
		return;
	}

	static float timePassed = 0.0f;

	float deltaTime = window->GetTimer().GetDeltaTime();

	timePassed += deltaTime;

	if (timePassed >= (1.0f / frameRate)) {
		timePassed = 0;
		currentSpriteIndex = (currentSpriteIndex + 1) % sprites.GetSize();
	}

	frameSounds.Update(currentSpriteIndex);

	sprites.DrawImage(sprites.GetImages()[currentSpriteIndex].title, coord, size, window->GetSize(), Color(1, 1, 1), true);
	if (currentSpriteIndex >= sprites.GetSize() - 1 && !repeat) {
		currentSpriteIndex = 0;
		play = false;
		end = true;
		return;
	}

	play = true;
}

bool SpriteAnimation::IsEnd()
{
	return end;
}

bool SpriteAnimation::IsPlay()
{
	return play;
}

void SpriteAnimation::Pause()
{
	pause = false;
}

void SpriteAnimation::Stop()
{
	end = true;
	play = false;
	pause = false;
	currentSpriteIndex = 0;
}

void SpriteAnimation::Restart()
{
	end = false;
	play = false;
	pause = false;

	currentSpriteIndex = 0;
	frameSounds.Restart();
}
