#if !defined(GVERROR_H_)
#define GVERROR_H_
/// \file GVError.h
/// \brief header file for error reporting in GalaxyView

// GVError.h -- header file for error reporting in GalaxyView
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

#ifdef __BORLANDC__
#pragma hdrstop
#endif

class GVError
{
  public:
	enum gverr
	{
		GV_OK,
		GV_NO_DB,
		GV_DB_NOT_INITIALIZED,
		GV_BAD_FILE,
		GV_BAD_ERROR = -1,
		GV_USE_LAST_ERROR = -2
	};
  private:
	static bool instanceFlag;
	static GVError single;
	enum GVError::gverr lastError;

	  GVError ()
	{
		//private constructor
	}

  public:
	static GVError *GetInstance ();
	const char *GetErrorMessage (enum GVError::gverr errorNbr =
								 GVError::GV_USE_LAST_ERROR);
	void SetError (enum GVError::gverr errorNbr);
	enum gverr GetError ()
	{
		return lastError;
	};

	~GVError () {
		instanceFlag = false;
	}
};

#endif
