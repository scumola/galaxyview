/// \file GVInfoPlanets.cpp
/// \brief Child Class for the table view

// GVInfoPlanets.cpp
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

#include "GVInfoPlanets.h"

static const char* coltitles[] = {
	_T("ID"),
	_T("Name"),
	_T("Owner"),
	_T("Size"),
	_T("Resources"),
	_T("Population"),
	_T("Colonists"),
	_T("Material"),
	_T("Capital"),
	_T("Industry"),
	_T("Posture"),
	_T("Source")
};

GVInfoPlanets::GVInfoPlanets(wxWindow* parent)
: wxPanel(parent)
{
	m_cols[0] = PlanetsID;
	m_cols[1] = PlanetsName;
	m_cols[2] = PlanetsOwner;
	m_cols[3] = PlanetsSource;
	m_cols[4] = PlanetsNULL;

	m_options = new wxPanel(this, -1);

	wxCheckBox* box = new wxCheckBox(this, -1, "Show All Planets");

	m_planets = new wxGrid(this, -1);
	SetupGrid();

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* optionsizer = new wxBoxSizer(wxHORIZONTAL);
	optionsizer->Add(box, 1, wxGROW, 0);

	sizer->Add(optionsizer, 0, wxALL | wxEXPAND, 10);
	sizer->Add(m_planets, 1, wxEXPAND | wxALL, 10);


	SetSizer(sizer);
}

GVInfoPlanets::~GVInfoPlanets()
{

}

void
GVInfoPlanets::SetupGrid()
{
	m_planets->SetEditable(false);
	m_planets->CreateGrid(0, 0, wxGrid::wxGridSelectRows);
	m_planets->SetRowLabelSize (0);
	m_planets->SetColLabelSize(20);
}


void
GVInfoPlanets::Update()
{
	SetupCols();

	// TODO: Update Data from Database
}

void
GVInfoPlanets::SetupCols()
{
	int numCols = 0;
	for(int i=0;i<GVINFOPLANETS_NUM_COLS;i++) {
		if(m_cols[i]==PlanetsNULL) break;

		m_planets->SetColLabelValue(i, coltitles[m_cols[i]]);
		numCols++;
	}
	m_planets->AppendCols(numCols);
}
