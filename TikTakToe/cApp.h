#pragma once
#include "wx/wx.h"
#include "cMain.h"
class cApp : public wxApp
{
private:
	cMain* frame = nullptr;

public:
	virtual bool OnInit();
};

