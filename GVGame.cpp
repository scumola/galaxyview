/// \file GVGame.cpp
/// \brief class file to load turn data into memory(preferencesgame) in GalaxyView

// GVGame.cpp -- class file to load turn data into memory(preferencesgame) in GalaxyView
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

#include "GVGame.h"

GVGame::GVGame(GVdb* db, hDB handle)
: m_db(db), m_handle(handle)
{
}

GVGame::~GVGame(void)
{
}

void
GVGame::SetPassword(wxString pw)
{
	GVGameData d;
	Load(&d);
	d.password = pw;
	Save(&d);
}

wxString
GVGame::GetPassword()
{
	GVGameData d;
	Load(&d);
	return d.password;
}

void
GVGame::SetGametype(wxString gt)
{
	GVGameData d;
	Load(&d);
	d.gametype = gt;
	Save(&d);
}

wxString
GVGame::GetGametype()
{
	GVGameData d;
	Load(&d);
	return d.gametype;
}

void
GVGame::SetGamename(wxString gn)
{
	GVGameData d;
	Load(&d);
	d.gamename = gn;
	Save(&d);
}

wxString 
GVGame::GetGamename()
{
	GVGameData d;
	Load(&d);
	return d.gamename;
}

void
GVGame::SetHomePlanetsNum(int num)
{
	GVGameData d;
	Load(&d);
	d.homeplanesnum = num;
	Save(&d);
}

int
GVGame::GetHomePlanetsNum()
{
	GVGameData d;
	Load(&d);
	return d.homeplanesnum;
}

void
GVGame::SetHomePlanetsSize(wxString sizes)
{
	GVGameData d;
	Load(&d);
	/* TODO: Add Type check for sizes(ie. "1000,300,200") */
	/* Perhaps check it also against homeplanetsnum? */
	d.homeplanetssize = sizes;
	Save(&d);
}

wxString 
GVGame::GetHomePlanetsSize()
{
	GVGameData d;
	Load(&d);
	return d.homeplanetssize;
}

void
GVGame::SetRacename(wxString race)
{
	GVGameData d;
	Load(&d);
	d.racename = race;
	Save(&d);
}

wxString
GVGame::GetRacename()
{
	GVGameData d;
	Load(&d);
	return d.racename;
}

void
GVGame::SetSize(float size)
{
	GVGameData d;
	Load(&d);
	d.size = size;
	Save(&d);
}

float
GVGame::GetSize()
{
	GVGameData d;
	this->Load(&d);
	return d.size;
}

void 
GVGame::Load(GVGameData* data)
{
	Query q = m_db->GetSQL(m_handle)->GetQuery();

	q << "SELECT * FROM preferencesgame";
	Result res = q.Store();

	if(res.Size()==1) {
		data->valid = true;
	} else {
		data->valid = false;
		return;
	}

	Row r = res[0];

	data->gamename = r["gamename"];
	data->gametype = r["gametype"];
	data->homeplanesnum = r.GetInteger(r.GetCol("homeplanetsnum"));
	data->homeplanetssize = r["homeplanetssize"];
	data->password = r["password"];
	data->racename = r["racename"];
	data->size = r.GetInteger(r.GetCol("size"));
}

void 
GVGame::Save(GVGameData* data)
{
	Query q = m_db->GetSQL(m_handle)->GetQuery();

	q << "INSERT INTO preferencesgame VALUES("
		<< "\'" << data->password.c_str() << "\', "
		<< "\'" << data->gametype.c_str() << "\', "
		<< "\'" << data->gamename.c_str() << "\', "
		<< data->homeplanesnum << ", "
		<< "\'" << data->homeplanetssize.c_str() << "\', "
		<< "\'" << data->racename.c_str() << "\', "
		<< data->size << ")";

	if(q.Execute()) {
		data->valid = true;
	} else {
		data->valid = false;
	}
}
