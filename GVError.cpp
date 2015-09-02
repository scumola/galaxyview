/// \file GVError.cpp
/// \brief class file for error reporting in GalaxyView

// GVError.cpp -- class file for error reporting in GalaxyView
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


#include "GVError.h"

#include <iostream>

bool GVError::instanceFlag = false;
GVError GVError::single;

static struct _errmsg
{
	enum GVError::gverr errorNbr;
	char* msg;
}

m_errmsg[] =
{
	{
	GVError::GV_OK, "No error"}
	, {
	GVError::GV_NO_DB, "Database missing"}
	, {
	GVError::GV_DB_NOT_INITIALIZED, "Database not initialized"}
	, {
	GVError::GV_BAD_FILE, "Could not open file for input: "}
	, {
	GVError::GV_BAD_ERROR, "Unrecognized error"}
	, {
	GVError::GV_USE_LAST_ERROR, ""}
};

GVError *
GVError::GetInstance ()
{
	return &single;
}

void
GVError::SetError (enum GVError::gverr errorNbr)
{
	lastError = errorNbr;
}

const char *
GVError::GetErrorMessage (enum GVError::gverr errorNbr)
{
	if (errorNbr == GVError::GV_USE_LAST_ERROR)
		errorNbr = lastError;

	for (int i = 0; m_errmsg[i].errorNbr != GVError::GV_BAD_ERROR; i++) {
		if (m_errmsg[i].errorNbr == errorNbr)
			return m_errmsg[i].msg;
	}

	return "Bad Error Message";
}


#if defined(GVERROR_MAIN_NEEDED)

using namespace std;

int
main ()
{
	GVError *sc1, *sc2;

	sc1 = GVError::GetInstance ();
	cout << sc1->GetErrorMessage (GVError::GV_OK) << endl;
	sc2 = GVError::GetInstance ();
	cout << sc2->GetErrorMessage (GVError::GV_NO_DB) << endl;
	sc1->SetError (GVError::GV_DB_NOT_INITIALIZED);
	cout << sc2->GetErrorMessage () << endl;

	return 0;
}
#endif
