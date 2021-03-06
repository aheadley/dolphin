// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#include "InputConfig.h"
#include "CommonPaths.h"
#include "../Core/ConfigManager.h"
#include "../Core/HW/Wiimote.h"

InputPlugin::~InputPlugin()
{
	// delete pads
	for (ControllerEmu* pad : controllers)
		delete pad;
}

bool InputPlugin::LoadConfig(bool isGC)
{
	IniFile inifile;
	IniFile game_ini;
	bool useProfile[MAX_BBMOTES] = {false, false, false, false, false};
	std::string num[MAX_BBMOTES] = {"1", "2", "3", "4", "BB"};
	std::string profile[MAX_BBMOTES];
	std::string path;

	if (SConfig::GetInstance().m_LocalCoreStartupParameter.GetUniqueID() != "00000000")
	{
		std::string type;
		if (isGC)
		{
			type = "Pad";
			path = "Profiles/GCPad/";
		}
		else
		{
			type = "Wiimote";
			path = "Profiles/Wiimote/";
		}
		game_ini.Load(File::GetSysDirectory() + GAMESETTINGS_DIR DIR_SEP + SConfig::GetInstance().m_LocalCoreStartupParameter.GetUniqueID() + ".ini");
		game_ini.Load(File::GetUserPath(D_GAMESETTINGS_IDX) + SConfig::GetInstance().m_LocalCoreStartupParameter.GetUniqueID() + ".ini", true);
		for (int i = 0; i < 4; i++)
		{
			if (game_ini.Exists("Controls", type + "Profile" + num[i]))
			{
				if (game_ini.Get("Controls", type + "Profile" + num[i], &profile[i]))
				{
					if (File::Exists(File::GetUserPath(D_CONFIG_IDX) + path + profile[i] + ".ini"))
						useProfile[i] = true;
					else
					{
						// TODO: Having a PanicAlert for this is dumb.
						PanicAlertT("Selected controller profile does not exist");
					}
				}
			}
		}
	}

	if (inifile.Load(File::GetUserPath(D_CONFIG_IDX) + ini_name + ".ini"))
	{
		int n = 0;
		for (ControllerEmu* pad : controllers)
		{
			// Load settings from ini
			if (useProfile[n])
			{
				IniFile profile_ini;
				profile_ini.Load(File::GetUserPath(D_CONFIG_IDX) + path + profile[n] + ".ini");
				pad->LoadConfig(profile_ini.GetOrCreateSection("Profile"));
			}
			else
			{
				pad->LoadConfig(inifile.GetOrCreateSection(pad->GetName()));
			}

			// Update refs
			pad->UpdateReferences(g_controller_interface);

			// Next profile
			n++;
		}
		return true;
	}
	else
	{
		controllers[0]->LoadDefaults(g_controller_interface);
		controllers[0]->UpdateReferences(g_controller_interface);
		return false;
	}
}

void InputPlugin::SaveConfig()
{
	std::string ini_filename = File::GetUserPath(D_CONFIG_IDX) + ini_name + ".ini";

	IniFile inifile;
	inifile.Load(ini_filename);

	for (ControllerEmu* pad : controllers)
		pad->SaveConfig(inifile.GetOrCreateSection(pad->GetName()));

	inifile.Save(ini_filename);
}
