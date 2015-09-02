#if !defined(GVOPENGAMEDIALOG_H)
#define GVOPENGAMEDIALOG_H

#include "wx/xrc/xmlres.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/treectrl.h"

class GVOpenGameDialog:public wxDialog
{
  public:
  /**
   * Constructor: creates a new frame for GalaxyView open game dialog
   * \param parent: wxWindow parent window
   * \param withNew: show new button in open dialog
   */
	GVOpenGameDialog (wxWindow * parent, bool withNew = false);


  /**
   * Add a game to select to this dialog
   * \param game wxString gamename 
   */
	void AddGame (wxString game, bool active);

  /**
   * \return wxString selected string
   */
	wxString GetSelection ()
	{
		return m_selection;
	}

  /**
   * Sorts Games
   */
	void SortGames ();


	// callbacks 
	void OnOK (wxCommandEvent & event);
	void OnCancel(wxCommandEvent& event);
	void OnSelectionChanged (wxCommandEvent & event);
	void OnNew (wxCommandEvent & event);

  private:
	wxString m_selection;
	wxTreeItemId m_treeroot;
	wxTreeItemId m_activeroot;
	wxTreeItemId m_inactiveroot;


	DECLARE_EVENT_TABLE ()
};

#endif
