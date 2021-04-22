#pragma once
#include "wx/wx.h"
#include "wx/statline.h"
#include "wx/sound.h"
#include "wx/utils.h"
#include "wx/mediactrl.h"
#include "wx/menu.h"
#define PYRO 1
#define SPY 2
#define wxID_TIMER1 19999
#define wxID_TIMER2 19998
#define wxID_PYROWINSOUND1M 20000
#define wxID_SPYWINSOUND1M 20001
#define wxID_ACHIEVEMENTSOUND 20002
#define wxID_BLUWINSOUND1 20003
#define wxID_BLUWINSOUND2 20004
#define wxID_BLUWINSOUND3 20005
#define wxID_BLUWINSOUND4 20006
#define wxID_REDWINSOUND1 20007
#define wxID_REDWINSOUND2 20008
#define wxID_REDWINSOUND3 20009
#define wxID_REDWINSOUND4 20010
#define wxID_YOURTEAMWONSOUND 20011
#define wxID_BUTTONGRID_FIRST_BUTTON 10000
#define wxID_MENURESET 15000

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	wxMenuBar* menubar1;
	wxMenu* gameMenu;


	wxButton** button3x3;
	int* nField;

	wxBitmap* bitmapPyro1;
	wxStaticBitmap* sBitmapPyro1;
	wxBitmap* bitmapSpy1;
	wxStaticBitmap* sBitmapSpy1;

	wxBitmap* bitmapPyroIcon;
	wxBitmap* bitmapSpyIcon;

	wxBitmap* emptyBitmap;

	wxStaticText* text1;
	wxFont* font1;
	//wxSound* spyWinSound1;
	//wxSound* pyroWinSound1;
	//wxSound* tf_achievementSound;
	wxMediaCtrl* spyWinSound1m;
	wxMediaCtrl* pyroWinSound1m;
	wxMediaCtrl* tf_achievementSoundm;
	wxMediaCtrl* bluWinSound1m;
	wxMediaCtrl* bluWinSound2m;
	wxMediaCtrl* bluWinSound3m;
	wxMediaCtrl* bluWinSound4m;
	wxMediaCtrl* redWinSound1m;
	wxMediaCtrl* redWinSound2m;
	wxMediaCtrl* redWinSound3m;
	wxMediaCtrl* redWinSound4m;
	wxMediaCtrl* yourTeamWonM;

	wxSound* spySnortSound1;
	wxSound* pyroLaughShortSound1;

	wxTimer timer1;
	wxTimer timer2;
	

	bool hasSoundPlayed;

	bool gameOver = false;
	bool isGameDraw = false;
	bool hasPyroWon = false;

	int increment;

	//OnSomething
	void OnButtonClicked(wxCommandEvent& evt);
	void OnTimer1(wxTimerEvent& evt);
	void OnTimer2(wxTimerEvent& evt);
	void OnReset(wxCommandEvent& evt);
	void OnQuit(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();	// must have wxBEGIN_EVENT_TABLE with it
};

