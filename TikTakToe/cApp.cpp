#include "cApp.h"

wxIMPLEMENT_APP(cApp); // forgot about this one...

bool cApp::OnInit()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // breaks at memory leak
	//_CrtSetBreakAlloc(151460);
	//_CrtSetBreakAlloc(151340);
	//_CrtSetBreakAlloc(118441);
	//_CrtSetBreakAlloc(118320);
	//_CrtSetBreakAlloc(58473);
	//_CrtSetBreakAlloc(58358);
	//_CrtSetBreakAlloc(58352);
	//_CrtSetBreakAlloc(58327);
	//_CrtSetBreakAlloc(48595);

	wxInitAllImageHandlers(); // or wxImage::AddHandler(wxJPEGHandler) for jpg images
	srand((unsigned)time(NULL));


	frame = new cMain();
	frame->Show();
	return true;
}