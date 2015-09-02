#include "GVToolBar.h"

GVToolBar::GVToolBar(GVFrame* parent)
: wxToolBar((wxWindow*)parent, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_DOCKABLE)
{
	//wxXmlResource::Get ()->LoadToolBar (this, wxT ("main_toolbar"));
	
	wxString resourceFile;
	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
	cf->Read (_T ("/GalaxyView/resources"), &resourceFile);

	this->SetToolBitmapSize(wxSize(20,20));

	GVToolBar::AddTool(ToolBar_10Back, _T("10 Back"), _T("10 Turns Back"), 
						_T("Set the current turn back by 10"), resourceFile, "resource/buttons/turn_back_ten.png");
	GVToolBar::AddTool(ToolBar_Back, _T("Back"), _T("1 Turn Back"), 
						_T("Selects the previous turn"), resourceFile, "resource/buttons/turn_previous.png");
	GVToolBar::AddTool(ToolBar_Forward, _T("Forward"), _T("1 Turn Forward"), 
						_T("Selects the next turn"), resourceFile, "resource/buttons/turn_next.png");
	GVToolBar::AddTool(ToolBar_10Forward, _T("10 Forward"), _T("10 Turns Forward"), 
						_T("Sets the current turn forward by 10"), resourceFile, "resource/buttons/turn_ahead_ten.png");
	AddSeparator();

	GVToolBar::AddTool(ToolBar_ZoomOut, _T("Zoom Out"), _T("Zooms Out"), 
						_T("Zooms out - you can see more"), resourceFile, "resource/buttons/zoom_out.png");
	GVToolBar::AddTool(ToolBar_ZoomIn, _T("Zoom In"), _T("Zooms In"), 
						_T("Zooms in - you can see more details"), resourceFile, "resource/buttons/zoom_in.png");
	GVToolBar::AddTool(ToolBar_ZoomMouse, _T("Zoom on Mouse"), _T("Zooms in/out on mouse position"), 
						_T("Mouse Zoom"), resourceFile, "resource/buttons/zoom_mouse.png");

	AddSeparator();

	GVToolBar::AddTool(ToolBar_PlayFilm, _T("Play Film"), _T("Animates current turns"), 
						_T("Diashow of current turns"), resourceFile, "resource/buttons/play_film.png");

	Realize();
}

GVToolBar::~GVToolBar()
{

}

void 
GVToolBar::AddTool(int toolid, const char* text, const char* help, const char* longhelp, const char* resource, const char* file)
{
	// Messages
	wxImage *img;


	wxZipInputStream stream (resource, file);
	img = new wxImage (stream);

	if (img) {
		wxBitmap bmp (img);
		wxToolBar::AddTool(toolid, text, bmp, wxNullBitmap, wxITEM_NORMAL, help, longhelp);
	}
	else {
		wxLogMessage (_T ("could not load toolbar icon"));
	}
	delete img;
}
