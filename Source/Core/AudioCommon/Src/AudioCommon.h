// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef _AUDIO_COMMON_H_
#define _AUDIO_COMMON_H_

#include "Common.h"
#include "AudioCommonConfig.h"
#include "../../../PluginSpecs/pluginspecs_dsp.h"
#include "SoundStream.h"


class CMixer;

extern DSPInitialize g_dspInitialize;
extern SoundStream *soundStream;
extern AudioCommonConfig ac_Config;

namespace AudioCommon 
{
	SoundStream *InitSoundStream(CMixer *mixer = NULL);
	void ShutdownSoundStream();
	std::vector<std::string> GetSoundBackends();
}

#endif // _AUDIO_COMMON_H_
