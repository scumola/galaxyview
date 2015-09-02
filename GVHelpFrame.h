#if !defined(GVHELPFRAME_H__)
#define GVHELPFRAME_H__

#if defined(__WIN32__)
#pragma warning(disable:4786)
#endif

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#if !defined(WX_PREC)
#include "wx/wx.h"
#endif

#include "wx/event.h"
#include "wx/toolbar.h"
#include "wx/xrc/xmlres.h"
#include "wx/menuitem.h"
#include "wx/image.h"
#include "wx/fs_zip.h"
#include "wx/splash.h"
#include "wx/sizer.h"
#include "wx/splitter.h"
#include "wx/notebook.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/zipstrm.h"
#include "wx/tokenzr.h"
#include "wx/html/htmlwin.h"


class GVHelpFrame:public wxFrame
{
  public:
	GVHelpFrame (wxWindow * parent);

	/// Sets the "Home-Page" of this Help Frame
	/// \param page wxString url to homepage
	/// \return bool true on success
	bool SetIndex (wxString & page);

	void OnPaint (wxPaintEvent &);
	void OnClose (wxCloseEvent &);
	void OnHome (wxCommandEvent &);
	void OnBack (wxCommandEvent &);
	void OnForward (wxCommandEvent &);

  private:
	  wxString m_index;
	wxToolBar *m_toolbar;

  DECLARE_EVENT_TABLE ()};

#endif
