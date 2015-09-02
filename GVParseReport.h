#if !defined(GVPARSEREPORT_H_)
#define GVPARSEREPORT_H_
/// \file GVParseReport.h
/// \brief header file for parsing XML turn reports in GalaxyView

// GVParseReport.h -- header file for parsing XML turn reports in GalaxyView
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

#include "wx/txtstrm.h"
#include "wx/wfstream.h"
#include "wx/string.h"

#include "XMLParser.h"
#include "GVError.h"

#include <list>

#include "GVStateLookup.h"

class GVParseReport : public XMLParser
{
public:
	GVParseReport() {};
	virtual ~GVParseReport() { m_state.clear(); };

	virtual bool ParseReport(GVdb* db, hDB handle, wxString& filename) = 0;


protected:
	void Push (enum XMLState s)
	{
		m_state.push_back (s);
	}
	void Pop ()
	{
		if (m_state.size () > 0)
			m_state.pop_back ();
	}

	enum XMLState Top() {
		return m_state.back();
	}

	std::list < enum XMLState > m_state;
};

#endif
