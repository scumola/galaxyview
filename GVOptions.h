#if !defined(GVOPTIONS_H)
#define GVOPTIONS_H
/// \file GVOptions.h
/// \brief header file for viewer options

// GVOptions.h -- header file for viewer options
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


#include "wx/confbase.h"
#include "wx/fileconf.h"
#include "wx/string.h"

#include <vector>

using namespace std;

class GVConfig:public wxFileConfig
{
  public:
	GVConfig ():wxFileConfig ("GalaxyView")
	{
	}

	 ~GVConfig ();

	// get/set attributes
	void nbrOfCircles (int value)
	{
		m_nbrOfCircles = value;
	};
	int nbrOfCircles (void)
	{
		return m_nbrOfCircles;
	};

	void rangeInterval (float value)
	{
		m_rangeInterval = value;
	};
	float rangeInterval (void)
	{
		return m_rangeInterval;
	};

	void filmDelay (int value)
	{
		m_filmDelay = value;
	};
	int filmDelay (void)
	{
		return m_filmDelay;
	};

	void showMousePosition (bool value)
	{
		m_showMousePosition = value;
	};
	bool showMousePosition (void)
	{
		return m_showMousePosition;
	};

	void saveContext (bool value)
	{
		m_saveContext = value;
	};
	bool saveContext (void)
	{
		return m_saveContext;
	};

	void secureGroupDisplay (bool value)
	{
		m_secureGroupDisplay = value;
	};
	bool secureGroupDisplay (void)
	{
		return m_secureGroupDisplay;
	};

	void nbrBattleSimulations (int value)
	{
		m_nbrBattleSimulations = value;
	};
	int nbrBattleSimulations (void)
	{
		return m_nbrBattleSimulations;
	};

	void battleListDetailLevel (int value)
	{
		m_battleListDetailLevel = value;
	};
	int battleListDetailLevel (void)
	{
		return m_battleListDetailLevel;
	};

	void borderAgreementExpires (bool value)
	{
		m_borderAgreementExpires = value;
	};
	bool borderAgreementExpires (void)
	{
		return m_borderAgreementExpires;
	};

	void borderAgreementExpiresTurns (int value)
	{
		m_borderAgreementExpiresTurns = value;
	};
	int borderAgreementExpiresTurns (void)
	{
		return m_borderAgreementExpiresTurns;
	};


  private:
	struct bookmark_data
	{
		wxString name;
		int zoom;
		float map_x_pos;
		float map_y_pos;
	};
	int m_nbrOfCircles;
	float m_rangeInterval;
	int m_filmDelay;
	bool m_showMousePosition;
	bool m_saveContext;
	vector < struct bookmark_data >m_bookmarks;
	bool m_secureGroupDisplay;
	int m_nbrBattleSimulations;
	int m_battleListDetailLevel;
	int m_borderAgreementExpires;
	int m_borderAgreementExpiresTurns;

};



#endif
