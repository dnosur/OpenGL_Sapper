#pragma once
#include <al.h>
#include <alc.h>
#include <cstddef>
#include <iostream>

class SoundSystem
{
	ALCdevice* device;
	ALCcontext* context;
	ALchar* devicename;
public:

	SoundSystem(ALchar* devicename = NULL);
	~SoundSystem();
};

