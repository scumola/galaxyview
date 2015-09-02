/// \file GVToolsTreatyEditor.cpp
/// \brief class file for GVToolsPage in GalaxyView

// GVToolsTreatyEditor.cpp -- class file for GVTools in GalaxyView
//
// Copyright 2003, Quarterflash Design Group
//
// Licensed under GPL version 2 - see COPYING for details
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "GVToolsTreatyEditor.h"
#include "GVTools.h"

IMPLEMENT_DYNAMIC_CLASS(GVToolsTreatyEditor, GVToolsPage)

GVToolsTreatyEditor::GVToolsTreatyEditor()
{
}

GVToolsTreatyEditor::~GVToolsTreatyEditor()
{
	if(m_grid) delete m_grid;
//	if(m_gridsizer) delete m_gridsizer;
}

void
GVToolsTreatyEditor::OnCreate()
{
	// Called after the Panel is created
	m_gridpanel = XRCCTRL(*this, "treatyeditor_gridpanel", wxPanel);
	
	m_gridsizer = new wxFlexGridSizer(1, 1, 5, 5);
	m_gridsizer->AddGrowableCol(0);
	m_gridsizer->AddGrowableRow(0);

	m_grid = new wxGrid (m_gridpanel, -1, wxPoint (0, 0), wxSize (400, 300));
	m_grid->CreateGrid (0, 0);
	m_grid->AppendRows (1);
	m_grid->AppendCols (3);
	m_grid->SetColLabelSize (20);
	m_grid->SetColSize (0, 80);
	m_grid->SetColSize (1, 255);
	m_grid->SetColSize (2, 60);
	m_grid->SetColLabelValue (0, _("Race"));
	m_grid->SetColLabelValue (1, _("Planets or Coordinates"));
	m_grid->SetColLabelValue (2, _("Expires"));
	m_grid->EnableGridLines (TRUE);
	m_grid->EnableEditing (FALSE);
	m_grid->SetRowLabelSize (0);

	m_grid->ForceRefresh ();

	m_gridsizer->Add(m_grid, 1, wxEXPAND | wxALL);
	m_gridpanel->SetSizer(m_gridsizer);
}

void
GVToolsTreatyEditor::Save()
{
	// Do whatever you need to do to save things
}

void
GVToolsTreatyEditor::Load()
{
	// Do whatever you need to do to load things
}


BEGIN_EVENT_TABLE (GVToolsTreatyEditor, GVToolsPage)
END_EVENT_TABLE()

/*
wxPanel *
GVTools::CreateTreatyEditorTool ()
{
	wxPanel *panel = new wxPanel (this);

	wxBoxSizer *panel_sizer = new wxBoxSizer (wxHORIZONTAL);
	wxGrid *grid = new wxGrid (panel, -1, wxPoint (0, 0), wxSize (400, 300));
	wxBoxSizer *button_sizer = new wxBoxSizer (wxVERTICAL);

	// the two list controls for selecting planets or races
	wxListCtrl *races_lst =
		new wxListCtrl (panel, 16, wxDefaultPosition, wxDefaultSize,
						wxLC_SINGLE_SEL);
	wxListCtrl *planets_lst =
		new wxListCtrl (panel, 18, wxDefaultPosition, wxDefaultSize,
						wxLC_SINGLE_SEL);

	// the buttons needed
	wxButton *new_btn =
		new wxButton (panel, 13, _("New"), wxDefaultPosition, wxDefaultSize,
					  wxBU_EXACTFIT);
	wxButton *delete_btn =
		new wxButton (panel, 14, _("Delete"), wxDefaultPosition,
					  wxDefaultSize,
					  wxBU_EXACTFIT);
	wxButton *save_btn =
		new wxButton (panel, 19, _("Save"), wxDefaultPosition, wxDefaultSize,
					  wxBU_EXACTFIT);
	wxButton *print_btn =
		new wxButton (panel, 20, _("Print"), wxDefaultPosition, wxDefaultSize,
					  wxBU_EXACTFIT);

	button_sizer->Add (new_btn, 0, wxEXPAND | wxALL, 5);
	button_sizer->Add (delete_btn, 0, wxEXPAND | wxALL, 5);
	button_sizer->Add (new wxStaticText (panel, 15, _("Select Race")), 0,
					   wxEXPAND);
	button_sizer->Add (races_lst, 0, wxEXPAND);
	button_sizer->Add (new wxStaticText (panel, 17, _("Select Planet")), 0,
					   wxEXPAND);
	button_sizer->Add (planets_lst, 0, wxEXPAND);
	button_sizer->Add (save_btn, 0, wxEXPAND | wxALL, 5);
	button_sizer->Add (print_btn, 0, wxEXPAND | wxALL, 5);

	// create the grid
	grid->CreateGrid (0, 0);
	grid->AppendRows (1);
	grid->AppendCols (3);
	grid->SetColLabelSize (20);
	grid->SetColSize (0, 80);
	grid->SetColSize (1, 255);
	grid->SetColSize (2, 60);
	grid->SetColLabelValue (0, _("Race"));
	grid->SetColLabelValue (1, _("Planets or Coordinates"));
	grid->SetColLabelValue (2, _("Expires"));
	grid->EnableGridLines (TRUE);
	grid->EnableEditing (FALSE);
	grid->SetRowLabelSize (0);

	grid->ForceRefresh ();

	panel_sizer->Add (grid, 1, wxEXPAND);
	panel_sizer->Add (button_sizer, 0, wxEXPAND);

	panel->SetSizer (panel_sizer);

	return panel;
}
*/

