#if !defined(GVPARSER_H)
#define GVPARSER_H
/// \file GVparser.h
/// \brief header file for XML parser interface in GalaxyView

// GVparser.h -- header file for XML parser interface in GalaxyView
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

#include "wx/wxprec.h"

#if !defined(WX_PREC)
#include "wx/wx.h"
#endif

#include "expat.h"

/// \brief this class is the interface to the expat parser
//

class GVparser
{
  public:
	GVParser ();
	~GVParser ();

	/// callback for a tag start
	virtual void Start (void *data, const char *el, const char **attr);

	/// callback for tag end
	virtual void End (void *data, const char *el);

	/// set alternate element handlers - setting a new handler will return the old one
	virtual XML_StartElementHandler
		StartElementHandler (XML_StartElementHandler start);
	virtual XML_StartElementHandler StartElementHandler ();

	virtual XML_EndElementHandler EndElementHandler (XML_EndElementHandler
													 end);
	virtual XML_EndElementHandler EndElementHandler ();

  private:
	  XML_parser m_parser;
};

#endif
