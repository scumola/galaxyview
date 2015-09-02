#if !defined(GVGALAXY_H_)
#define GVGALAXY_H_
/// \file GVGalaxy.h
/// \brief header file to load turn data into memory in GalaxyView

// GVGalaxy.h -- header file to load turn data into memory in GalaxyView
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

#include "GVdb.h"
#include "GVGalaxyObject.h"
#include "GVPlanet.h"
#include "GVGame.h"
#include "bookmark.h"

#include <list>
using namespace std;

/**
	This class stores all loaded GVGalaxyObjects.
	Objects are loaded with a call to LoadTurn() and
	can be freed with FreeTurn()
*/
class GVGalaxy
{
  public:
	GVGalaxy ();
	~GVGalaxy ();

	/// Set current turn
	void SetTurn (long turnnumber)
	{
		if(turnnumber<0) m_turn = 0; 
		else m_turn = turnnumber;
	}

	/// Sets current master game
	/// all galaxy functions go to that
	void SetDatabase(GVdb* db, hDB handle);

	/// Load turn # from database
	/// Loads all GVGalaxyObjects from the database for turn 'turnnumber'
	bool LoadTurn (long turnnumber);

	/// delete all objects with turnnumber from memory
	void FreeTurn (long turnnumber);

	/// get number of planets loaded with turnnumber
	unsigned int GetNumPlanets (long turnnumber);

	/// return them
	void GetPlanets (GVPlanet ** ptr, long turnnumber);

	/// \return GVGame - data from preferencesgame
	GVGame* GetGame() { return m_game; }

	/// \return GVBookmarkManger - data from the bookmarks table
	GVBookmarkManager* GetBookmarks() { return m_bookmarks; }

	/// Save all data 
	void Save();

  protected:
    
	// gamesettings
	GVGame* m_game;

	// bookmakrs
	GVBookmarkManager* m_bookmarks;

	/// Special Load Method - called by LoadTurn
	bool LoadTurnPlanets (long turnnumber);

	/// current turn
	long m_turn;

	list < GVGalaxyObject * >m_objects;

	// current database data
	GVdb* m_db;
	hDB m_handle;
};

#endif

