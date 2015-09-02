
#include "wx/toolbar.h"

#include "GVHelpFrame.h"



GVHelpFrame::GVHelpFrame (wxWindow * parent)
{
	wxXmlResource::Get ()->LoadFrame (this, parent, _T ("helpframe"));
	m_toolbar =
		(wxToolBar *) wxXmlResource::Get ()->LoadToolBar (this,
														  _
														  ("helpframe_toolbar"));

	this->Show (true);
	this->Raise ();
}

bool GVHelpFrame::SetIndex (wxString & page)
{
	m_index = page;

	wxHtmlWindow *
		helpWindow =
		XRCCTRL (*this, "helpframe_html", wxHtmlWindow);

	helpWindow->SetRelatedFrame (this, _T ("%s"));

	if (!helpWindow->LoadPage (page)) {
		wxLogMessage (_T ("Unable to load index page"));
	}

	return true;
}

void
GVHelpFrame::OnClose (wxCloseEvent & evt)
{
	this->Show (false);
}

void
GVHelpFrame::OnHome (wxCommandEvent & evt)
{
	wxHtmlWindow *helpWindow =
		XRCCTRL (*this, "helpframe_html", wxHtmlWindow);

	helpWindow->LoadPage (m_index);
}

void
GVHelpFrame::OnForward (wxCommandEvent & evt)
{
	wxHtmlWindow *helpWindow =
		XRCCTRL (*this, "helpframe_html", wxHtmlWindow);
	helpWindow->HistoryForward ();
}

void
GVHelpFrame::OnBack (wxCommandEvent & evt)
{
	wxHtmlWindow *helpWindow =
		XRCCTRL (*this, "helpframe_html", wxHtmlWindow);
	helpWindow->HistoryBack ();
}


/* hellcat0:
 * this is a bit of a hack because i didn't want to create a new class and overwrite  
 * the OnLinkClicked etc.
 */
void
GVHelpFrame::OnPaint (wxPaintEvent & evt)
{
	wxPaintDC dc (this);

	wxHtmlWindow *helpWindow =
		XRCCTRL (*this, "helpframe_html", wxHtmlWindow);

	if (helpWindow->HistoryCanBack ()) {
		m_toolbar->EnableTool (XRCID ("helpframe_back"), true);
	}
	else {
		m_toolbar->EnableTool (XRCID ("helpframe_back"), false);
	}
	if (helpWindow->HistoryCanForward ()) {
		m_toolbar->EnableTool (XRCID ("helpframe_forward"), true);
	}
	else {
		m_toolbar->EnableTool (XRCID ("helpframe_forward"), false);
	}
}

BEGIN_EVENT_TABLE (GVHelpFrame, wxFrame)
	EVT_PAINT (GVHelpFrame::OnPaint)
	EVT_CLOSE (GVHelpFrame::OnClose)
	EVT_TOOL (XRCID ("helpframe_home"), GVHelpFrame::OnHome)
	EVT_TOOL (XRCID ("helpframe_forward"), GVHelpFrame::OnForward)
	EVT_TOOL (XRCID ("helpframe_back"),
		  GVHelpFrame::OnBack) END_EVENT_TABLE ()
