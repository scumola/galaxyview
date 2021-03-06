#if !defined(GVGAME_H_)
#define GVGAME_H_
/// \file GVGame.h
/// \brief header file to load turn data into memory(preferencesgame) in GalaxyView

// GVGame.h -- header file to load turn data into memory(preferencesgame) in GalaxyView
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

struct GVGameData
{
	wxString password;
	wxString gametype;
	wxString gamename;
	int homeplanesnum;
	wxString homeplanetssize;
	wxString racename;
	float size;

	bool valid;
};

class GVGame
{
public:
	GVGame(GVdb* db, hDB handle);
	virtual ~GVGame(void);

	void SetPassword(wxString pw);
	wxString GetPassword();

	void SetGametype(wxString gt);
	wxString GetGametype();

	void SetGamename(wxString gn);
	wxString GetGamename();

	void SetHomePlanetsNum(int num);
	int GetHomePlanetsNum();

	void SetHomePlanetsSize(wxString sizes);
	wxString GetHomePlanetsSize();

	void SetRacename(wxString race);
	wxString GetRacename();

	void SetSize(float size);
	float GetSize();

	void Load(GVGameData* data);
	void Save(GVGameData* data);

protected:
	GVdb* m_db;
	hDB m_handle;
};


#endif
