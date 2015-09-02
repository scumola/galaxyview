#if !defined(GVTOOLSTEXTEDOTOR_H_)
#define GVTOOLSTEXTEDITOR_H_
/// \file GVToolsTextEditor.h
/// \brief header file for GVToolsPage in GalaxyView

// GVToolsTextEditor.h -- header file for GVToolsPage in GalaxyView
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

#include "GVTools.h"

class GVToolsTextEditor : public GVToolsPage
{
	DECLARE_DYNAMIC_CLASS(GVToolsTextEditor)
public:
	GVToolsTextEditor ();

	void OnCreate();
	void Save();
	void Load();
protected:
	DECLARE_EVENT_TABLE ()
};

#endif
