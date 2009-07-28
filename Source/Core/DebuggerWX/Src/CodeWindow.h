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


#ifndef CODEWINDOW_H_
#define CODEWINDOW_H_

#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>

#include "Thread.h"
#include "CoreParameter.h"

class CRegisterWindow;
class CBreakPointWindow;
class CMemoryWindow;
class CJitWindow;
class CCodeView;

class CCodeWindow
	: public wxFrame
{
	public:

		CCodeWindow(const SCoreStartupParameter& _LocalCoreStartupParameter, wxWindow* parent,
			wxWindowID id = wxID_ANY,
			const wxString& title = _T("Dolphin-Debugger"),
		const wxPoint& pos = wxPoint(950, 100),
		const wxSize& size = wxSize(400, 500),
		long style = wxDEFAULT_FRAME_STYLE | wxCLIP_CHILDREN | wxNO_FULL_REPAINT_ON_RESIZE);

		~CCodeWindow();

		void Load_(IniFile &file);
		void Load(IniFile &file);
		void Save(IniFile &file) const;

		void Update();
		void NotifyMapLoaded();


		bool UseInterpreter();
		bool BootToPause();
		bool AutomaticStart();
		bool UnlimitedJITCache();
		bool JITBlockLinking();
		//bool UseDualCore(); // not used
        void JumpToAddress(u32 _Address);

	private:

		enum
		{
			// ==============================================================
			// Menu Entries
			// CPU Mode
			IDM_INTERPRETER = 2000, // These cannot interfere with enums in Globals.h!
			//IDM_DUALCORE, // not used
			IDM_AUTOMATICSTART, IDM_BOOTTOPAUSE,
			IDM_JITUNLIMITED, IDM_JITBLOCKLINKING,  // JIT
			IDM_JITOFF,
			IDM_JITLSOFF, IDM_JITLSLXZOFF, IDM_JITLSLWZOFF, IDM_JITLSLBZXOFF,
			IDM_JITLSPOFF, IDM_JITLSFOFF,
			IDM_JITIOFF,
			IDM_JITFPOFF,
			IDM_JITPOFF,
			IDM_JITSROFF,

			// Views
			IDM_FONTPICKER,
			IDM_LOGWINDOW,
			IDM_REGISTERWINDOW,
			IDM_BREAKPOINTWINDOW,
			IDM_MEMORYWINDOW,
			IDM_JITWINDOW,
			IDM_SOUNDWINDOW,
			IDM_VIDEOWINDOW,

			// Symbols
			IDM_CLEARSYMBOLS,
			IDM_CLEANSYMBOLS, // not used
			IDM_SCANFUNCTIONS,
			IDM_LOADMAPFILE,
			IDM_SAVEMAPFILE, IDM_SAVEMAPFILEWITHCODES,
			IDM_CREATESIGNATUREFILE,
            IDM_RENAME_SYMBOLS,
			IDM_USESIGNATUREFILE,
			//IDM_USESYMBOLFILE, // not used
			IDM_PATCHHLEFUNCTIONS,

			// JIT
			IDM_CLEARCODECACHE,
			IDM_LOGINSTRUCTIONS,
			IDM_SEARCHINSTRUCTION,

			// Profiler
			IDM_PROFILEBLOCKS,
			IDM_WRITEPROFILE,

			// ==============================================================
			// Toolbar
			ID_TOOLBAR,
			IDM_DEBUG_GO,
			IDM_STEP,
			IDM_STEPOVER,
			IDM_SKIP,
			IDM_SETPC,
			IDM_GOTOPC,
			IDM_ADDRBOX,
			
			// ==============================================================
			// Debugger GUI Objects
			ID_CODEVIEW,
			ID_CALLSTACKLIST,
			ID_CALLERSLIST,
			ID_CALLSLIST,
			ID_SYMBOLLIST
		};

		enum
		{
			Toolbar_DebugGo,
			Toolbar_Pause,
			Toolbar_Step,
			Toolbar_StepOver,
			Toolbar_Skip,
			Toolbar_GotoPC,
			Toolbar_SetPC,
			Bitmaps_max
		};

		// Settings
		bool bAutomaticStart; bool bBootToPause;
		bool bRegisterWindow;
		bool bBreakpointWindow;
		bool bMemoryWindow;
		bool bJitWindow;
		bool bSoundWindow;
		bool bVideoWindow;

		// Sub dialogs
		wxMenuBar* pMenuBar;
		CRegisterWindow* m_RegisterWindow;
		CBreakPointWindow* m_BreakpointWindow;
		CMemoryWindow* m_MemoryWindow;
		CJitWindow* m_JitWindow;

		wxMenuItem* jitblocklinking, *jitunlimited, *jitoff;
		wxMenuItem* jitlsoff, *jitlslxzoff, *jitlslwzoff, *jitlslbzxoff;
		wxMenuItem* jitlspoff;
		wxMenuItem* jitlsfoff;
		wxMenuItem* jitfpoff;
		wxMenuItem* jitioff;
		wxMenuItem* jitpoff;
		wxMenuItem* jitsroff;

		CCodeView* codeview;
		wxListBox* callstack;
		wxListBox* symbols;
		wxListBox* callers;
		wxListBox* calls;
		Common::Event sync_event;

		wxBitmap m_Bitmaps[Bitmaps_max];

		DECLARE_EVENT_TABLE()

		void OnSymbolListChange(wxCommandEvent& event);
		void OnSymbolListContextMenu(wxContextMenuEvent& event);
		void OnCallstackListChange(wxCommandEvent& event);
		void OnCallersListChange(wxCommandEvent& event);
		void OnCallsListChange(wxCommandEvent& event);
		void OnCodeStep(wxCommandEvent& event);
		void OnCodeViewChange(wxCommandEvent &event);
		void SingleCPUStep();

		void OnAddrBoxChange(wxCommandEvent& event);

		void OnToggleRegisterWindow(wxCommandEvent& event);
		void OnToggleBreakPointWindow(wxCommandEvent& event);
		void OnToggleMemoryWindow(wxCommandEvent& event);
		void OnToggleJitWindow(wxCommandEvent& event);
		void OnToggleSoundWindow(wxCommandEvent& event);
		void OnToggleVideoWindow(wxCommandEvent& event);
		void OnChangeFont(wxCommandEvent& event);
	
		void OnHostMessage(wxCommandEvent& event);
		void OnSymbolsMenu(wxCommandEvent& event);
		void OnJitMenu(wxCommandEvent& event);
		void OnProfilerMenu(wxCommandEvent& event);

		void OnCPUMode(wxCommandEvent& event); // CPU Mode menu	
		void OnJITOff(wxCommandEvent& event);	

		void CreateMenu(const SCoreStartupParameter& _LocalCoreStartupParameter);
		void CreateSymbolsMenu();

		void UpdateButtonStates();
		void UpdateLists();
		void UpdateCallstack();
		void RecreateToolbar();
		void PopulateToolbar(wxToolBar* toolBar);
		void OnStatusBar(wxMenuEvent& event); void OnStatusBar_(wxUpdateUIEvent& event);
		void DoTip(wxString text);
		void OnKeyDown(wxKeyEvent& event);

		void InitBitmaps();
		void CreateGUIControls(const SCoreStartupParameter& _LocalCoreStartupParameter);		
};

#endif /*CODEWINDOW_*/
