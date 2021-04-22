#include "cMain.h"


// Layout:
//
//  hBox1
//  +---------------------------------------------------------------+
//  |vBox2			|vBox1											|
//	|				|												|
//	|				|												|
//	|				|-----------------------------------------------|
//	|				|												|
//	|				|												|
//	|	Some Pic	|					buttonGrid					|
//	|	& text		|												|
//	|				|												|
//	|				|-----------------------------------------------|
//	|				|												|
//	|				|												|
//  +---------------------------------------------------------------+

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_TIMER(wxID_TIMER1, cMain::OnTimer1)
	EVT_TIMER(wxID_TIMER2, cMain::OnTimer2)
wxEND_EVENT_TABLE();



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "TF2 Tic Tac Toe", wxDefaultPosition, wxSize(1000, 900), wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER ^ wxMAXIMIZE_BOX) // no resizing
{
	wxColour colorGray;
	colorGray.Set("#ededed");

	hasSoundPlayed = false;
	increment = 0;
	timer1.SetOwner(this,wxID_TIMER1);
	timer2.SetOwner(this, wxID_TIMER2);

	// menus
	menubar1 = new wxMenuBar;
	gameMenu = new wxMenu;

	gameMenu->Append(wxID_MENURESET, wxT("&Reset"));
	gameMenu->Append(wxID_EXIT, wxT("&Quit"));
	menubar1->Append(gameMenu, wxT("&Menu"));
	Connect(wxID_MENURESET, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMain::OnReset));
	Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(cMain::OnQuit));
	menubar1->SetBackgroundColour(colorGray);
	SetMenuBar(menubar1);

	wxPanel* panel1 = new wxPanel(this, -1);
	wxPanel* panel2 = new wxPanel(panel1, -1, wxDefaultPosition, wxSize(300,600));
	wxPanel* panel3 = new wxPanel(panel1, -1, wxDefaultPosition, wxSize(600, 1));
	wxPanel* panel4 = new wxPanel(panel1, -1, wxDefaultPosition, wxSize(600, 1));

	
	font1 = new wxFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxStaticLine* sl1 = new wxStaticLine(panel1, wxID_ANY, wxDefaultPosition, wxSize(3, 800));
	button3x3 = new wxButton * [9];

	wxBoxSizer* vBox1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vBox2 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hBox1 = new wxBoxSizer(wxHORIZONTAL);
	wxGridSizer* grid1 = new wxGridSizer(3, 3, 5, 5);

	//pyroWinSound1 = new wxSound("Resources/Pyro_laughlong01.wav");
	//spyWinSound1 = new wxSound("Resources/Spy_specialcompleted03.wav");
	//tf_achievementSound = new wxSound("Resources/Achievement_earned.wav");
	pyroLaughShortSound1 = new wxSound("Resources/Pyro_laughshort01.wav");
	spySnortSound1 = new wxSound("Resources/Spy_laughlong01.wav");

	pyroWinSound1m = new wxMediaCtrl(panel1, wxID_PYROWINSOUND1M, "Resources/Pyro_laughlong01.wav");
	spyWinSound1m = new wxMediaCtrl(panel1, wxID_SPYWINSOUND1M, "Resources/Spy_specialcompleted03.wav");
	tf_achievementSoundm = new wxMediaCtrl(panel1, wxID_ACHIEVEMENTSOUND, "Resources/Achievement_earned.wav");
	bluWinSound1m = new wxMediaCtrl(panel1,wxID_BLUWINSOUND1,"Resources/Sf14_merasmus_minigame_all_bluwin_01.wav");
	bluWinSound2m = new wxMediaCtrl(panel1,wxID_BLUWINSOUND2,"Resources/Sf14_merasmus_minigame_all_bluwin_02.wav");
	bluWinSound3m = new wxMediaCtrl(panel1,wxID_BLUWINSOUND3,"Resources/Sf14_merasmus_minigame_all_bluwin_03.wav");
	bluWinSound4m = new wxMediaCtrl(panel1,wxID_BLUWINSOUND4,"Resources/Sf14_merasmus_minigame_all_bluwin_04.wav");
	redWinSound1m = new wxMediaCtrl(panel1,wxID_REDWINSOUND1,"Resources/Sf14_merasmus_minigame_all_redwin_01.wav");
	redWinSound2m = new wxMediaCtrl(panel1,wxID_REDWINSOUND2,"Resources/Sf14_merasmus_minigame_all_redwin_02.wav");
	redWinSound3m = new wxMediaCtrl(panel1,wxID_REDWINSOUND3,"Resources/Sf14_merasmus_minigame_all_redwin_03.wav");
	redWinSound4m = new wxMediaCtrl(panel1,wxID_REDWINSOUND4,"Resources/Sf14_merasmus_minigame_all_redwin_04.wav");
	yourTeamWonM = new wxMediaCtrl(panel1, wxID_YOURTEAMWONSOUND, "Resources/your_team_won.wav");

	pyroWinSound1m->SetVolume(0.3);
	spyWinSound1m->SetVolume(0.3);
	tf_achievementSoundm->SetVolume(0.2);
	bluWinSound1m->SetVolume(0.2);
	bluWinSound2m->SetVolume(0.2);
	bluWinSound3m->SetVolume(0.2);
	bluWinSound4m->SetVolume(0.2);
	redWinSound1m->SetVolume(0.2);
	redWinSound2m->SetVolume(0.2);
	redWinSound3m->SetVolume(0.2);
	redWinSound4m->SetVolume(0.2);
	// yourTeamWonM already adjusted volume in the file

	text1 = new wxStaticText(panel1, -1, "Click buttons to start", wxDefaultPosition, wxDefaultSize,
		wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
	text1->SetFont(*font1);

	bitmapPyro1 = new wxBitmap("Resources/Icon_pyro.jpg", wxBITMAP_TYPE_JPEG);
	sBitmapPyro1 = new wxStaticBitmap(panel1, wxID_ANY, *bitmapPyro1, wxDefaultPosition, wxSize(400, 400));
	bitmapSpy1 = new wxBitmap("Resources/Icon_spy_blue.jpg", wxBITMAP_TYPE_JPEG);
	sBitmapSpy1 = new wxStaticBitmap(panel1, -1, *bitmapSpy1, wxDefaultPosition, wxSize(400, 400));

	bitmapPyroIcon = new wxBitmap("Resources/pyroIcon.png", wxBITMAP_TYPE_PNG);
	bitmapSpyIcon = new wxBitmap("Resources/spyIcon.jpg", wxBITMAP_TYPE_JPEG);





	hBox1->Add(vBox2, 1, wxLEFT | wxEXPAND);
	hBox1->Add(sl1, 0, wxALIGN_CENTER_VERTICAL);
	hBox1->Add(vBox1,1,wxRIGHT|wxEXPAND);

	vBox1->Add(panel3,1,wxTOP|wxEXPAND);
	vBox1->Add(grid1,1,wxALIGN_CENTER_HORIZONTAL);
	vBox1->Add(panel4,1,wxBOTTOM|wxEXPAND);

	vBox2->Add(sBitmapPyro1, 1, wxALIGN_CENTER_HORIZONTAL);
	vBox2->Add(text1, 0, wxALIGN_CENTER_HORIZONTAL);
	vBox2->Add(sBitmapSpy1, 1, wxALIGN_CENTER_HORIZONTAL);

	panel1->SetBackgroundColour(colorGray);
	panel2->SetBackgroundColour(colorGray);
	panel3->SetBackgroundColour(colorGray);
	panel4->SetBackgroundColour(colorGray);

	nField = new int[9];
	




	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			button3x3[y * 3 + x] = new wxButton(panel1, wxID_BUTTONGRID_FIRST_BUTTON + y * 3 + x, wxEmptyString, wxDefaultPosition, wxSize(135, 135));
			grid1->Add(button3x3[y * 3 + x], 1, wxEXPAND | wxALL);
			button3x3[y * 3 + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this); 
			nField[y * 3 + x] = 0;
		}
	}
	panel1->SetSizer(hBox1);
	//grid3x3->Layout();

	Center();
}

cMain::~cMain()
{
	this->Hide(); // make it look like quitting much faster

	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		button3x3[i * 3 + j]->Destroy();
	//	}
	//}



	wxDELETEA(button3x3);
	wxDELETEA(nField);

	wxDELETE(text1);
	wxDELETE(bitmapPyro1);
	wxDELETE(bitmapSpy1);
	wxDELETE(bitmapPyroIcon);
	wxDELETE(bitmapSpyIcon);
	wxDELETE(font1);
	//delete tf_achievementSound;
	//delete pyroWinSound1;
	//delete spyWinSound1;
	wxDELETE(tf_achievementSoundm);
	wxDELETE(pyroWinSound1m);
	wxDELETE(spyWinSound1m);

	wxDELETE(bluWinSound1m);
	wxDELETE(bluWinSound2m);
	wxDELETE(bluWinSound3m);
	wxDELETE(bluWinSound4m);
	wxDELETE(redWinSound1m);
	wxDELETE(redWinSound2m);
	wxDELETE(redWinSound3m);
	wxDELETE(redWinSound4m);
	wxDELETE(yourTeamWonM);

	wxDELETE(spySnortSound1);
	wxDELETE(pyroLaughShortSound1);
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - wxID_BUTTONGRID_FIRST_BUTTON) % 3;
	int y = (evt.GetId() - wxID_BUTTONGRID_FIRST_BUTTON) / 3;


	//auto checkPyroWin = [=]()mutable -> void {
	//	if (tempCounter == 3) {
	//		hasPyroWon = true;
	//		gameOver = true;
	//		isGameDraw = false;
	//	}
	//};

	if (!gameOver) {
		if (increment % 2) { // Pyro's turn
			if (!nField[y * 3 + x]) {
				button3x3[y * 3 + x]->SetBitmap(*bitmapPyroIcon);
				nField[y * 3 + x] = PYRO;
				text1->SetLabel("Spy's Turn");
				increment++;
				pyroLaughShortSound1->Play();
			}
		}
		else { // Spy's turn
			if (!nField[y * 3 + x]) {
				button3x3[y * 3 + x]->SetBitmap(*bitmapSpyIcon);
				nField[y * 3 + x] = SPY;
				text1->SetLabel("Pyro's Turn");
				increment++;
				spySnortSound1->Play();
			}
		}

		// check if game is draw
		gameOver = true;
		isGameDraw = true;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (nField[i * 3 + j] == 0) {
					isGameDraw = false;
					gameOver = false;
				}
			}
		}
		// 0 1 2
		// 3 4 5
		// 6 7 8
		// this is the nField in 3x3
		if ((increment - 1) % 2) { // check if pyro wins
			if (nField[0] == PYRO && nField[1] == PYRO && nField[2] == PYRO) { gameOver = true; hasPyroWon = true; isGameDraw = false; }
			if (nField[3] == PYRO && nField[4] == PYRO && nField[5] == PYRO) { gameOver = true; hasPyroWon = true; isGameDraw = false; }
			if (nField[6] == PYRO && nField[7] == PYRO && nField[8] == PYRO) { gameOver = true; hasPyroWon = true; isGameDraw = false; }

			if (nField[0] == PYRO && nField[3] == PYRO && nField[6] == PYRO) { gameOver = true; hasPyroWon = true; isGameDraw = false; }
			if (nField[1] == PYRO && nField[4] == PYRO && nField[7] == PYRO) { gameOver = true; hasPyroWon = true; isGameDraw = false; }
			if (nField[2] == PYRO && nField[5] == PYRO && nField[8] == PYRO) { gameOver = true; hasPyroWon = true; isGameDraw = false; }

			if (nField[0] == PYRO && nField[4] == PYRO && nField[8] == PYRO) { gameOver = true; hasPyroWon = true; isGameDraw = false; }
			if (nField[2] == PYRO && nField[4] == PYRO && nField[6] == PYRO) { gameOver = true; hasPyroWon = true; isGameDraw = false; }
		}
		else {
			if (nField[0] == SPY && nField[1] == SPY && nField[2] == SPY) { gameOver = true; hasPyroWon = false; isGameDraw = false; }
			if (nField[3] == SPY && nField[4] == SPY && nField[5] == SPY) { gameOver = true; hasPyroWon = false; isGameDraw = false; }
			if (nField[6] == SPY && nField[7] == SPY && nField[8] == SPY) { gameOver = true; hasPyroWon = false; isGameDraw = false; }

			if (nField[0] == SPY && nField[3] == SPY && nField[6] == SPY) { gameOver = true; hasPyroWon = false; isGameDraw = false; }
			if (nField[1] == SPY && nField[4] == SPY && nField[7] == SPY) { gameOver = true; hasPyroWon = false; isGameDraw = false; }
			if (nField[2] == SPY && nField[5] == SPY && nField[8] == SPY) { gameOver = true; hasPyroWon = false; isGameDraw = false; }

			if (nField[0] == SPY && nField[4] == SPY && nField[8] == SPY) { gameOver = true; hasPyroWon = false; isGameDraw = false; }
			if (nField[2] == SPY && nField[4] == SPY && nField[6] == SPY) { gameOver = true; hasPyroWon = false; isGameDraw = false; }
		}
	}
	
	if (gameOver) {
		if (isGameDraw) 
			text1->SetLabel("Draw!");
		else {
			if (hasPyroWon) {
				text1->SetLabel("Mmmmph mmph!");
				bitmapPyro1->LoadFile("Resources/pyroWin.jpg", wxBITMAP_TYPE_JPEG);
				sBitmapPyro1->SetBitmap(*bitmapPyro1);
				bitmapSpy1->LoadFile("Resources/spyLose.jpg", wxBITMAP_TYPE_JPEG);
				sBitmapSpy1->SetBitmap(*bitmapSpy1);
				
			}
			else {
				text1->SetLabel("Spy Won!");
				bitmapPyro1->LoadFile("Resources/pyroLose.jpg", wxBITMAP_TYPE_JPEG);
				sBitmapPyro1->SetBitmap(*bitmapPyro1);
				bitmapSpy1->LoadFile("Resources/spyWin.jpg", wxBITMAP_TYPE_JPEG);
				sBitmapSpy1->SetBitmap(*bitmapSpy1);
			}
			if (!hasSoundPlayed) {
				if (hasPyroWon) {
					switch (rand() % 4)
					{
					case 0:
						redWinSound1m->Play();
						timer2.StartOnce(1312);
						break;
					case 1:
						redWinSound2m->Play();
						timer2.StartOnce(1364);
						break;
					case 2:
						redWinSound3m->Play();
						timer2.StartOnce(1306);
						break;
					case 3:
						redWinSound4m->Play();
						timer2.StartOnce(2289);
						break;
					}
					//timer2.StartOnce(2000); ///////// after many attempts, playing 2 sounds at the same time with a bit of delay is finally
												/////// achieved by using a timer and a timerEvent, since Sleep or a while loop
												/////// will always break the layout elements for a short time
												/////// also notice that wxSound can't do this, only wxMediaCtrl can
					timer1.StartOnce(4000);
					hasSoundPlayed = true;
				}
				else {
					switch (rand() % 4)
					{
					case 0:
						bluWinSound1m->Play();
						timer2.StartOnce(1207);
						break;
					case 1:
						bluWinSound2m->Play();
						timer2.StartOnce(1589);
						break;
					case 2:
						bluWinSound3m->Play();
						timer2.StartOnce(1161);
						break;
					case 3:
						bluWinSound4m->Play();
						timer2.StartOnce(2110);
						break;
					}
					//timer2.StartOnce(2000); // wait 2 Seconds to play next sound
					timer1.StartOnce(4000);
					hasSoundPlayed = true;
				}
			}
		}
	}


	evt.Skip();
}

void cMain::OnTimer1(wxTimerEvent& evt) // play the spy/pyro winning voice
{
	if (hasPyroWon)
		pyroWinSound1m->Play();
	else
		spyWinSound1m->Play();
}

void cMain::OnTimer2(wxTimerEvent& evt) // play this sound
{
	yourTeamWonM->Play();
}

void cMain::OnReset(wxCommandEvent& evt)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			nField[i * 3 + j] = 0;
			button3x3[i * 3 + j]->SetBitmap(wxNullBitmap);
			button3x3[i * 3 + j]->Refresh();
		}
	}
	//increment = 0;
	text1->SetLabel(wxT("Click buttons to start"));
	
	gameOver = false;
	isGameDraw = false;
	bitmapPyro1->LoadFile("Resources/Icon_pyro.jpg", wxBITMAP_TYPE_JPEG);
	sBitmapPyro1->SetBitmap(*bitmapPyro1);
	bitmapSpy1->LoadFile("Resources/Icon_spy_blue.jpg", wxBITMAP_TYPE_JPEG);
	sBitmapSpy1->SetBitmap(*bitmapSpy1);
	hasSoundPlayed = false;

	evt.Skip();
}

void cMain::OnQuit(wxCommandEvent& WXUNUSED(evt))
{
	Close(true);
}

// TODO:
// add new button image and resize buttons  ....... OK
// add spy snort sound, pyro "ha" sound ........ OK
// merasmus BLU win and RED win voice ........OK
// victory sound to replace achievement sound .........OK
// add a reset menu ..............................OK
// add more sound variants for pyro and spy
// add a spy special move and some visual effects?