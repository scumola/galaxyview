#if !defined(GVGALAXYOBJECT_H_)
#define GVGALAXYOBJECT_H_
/// \file GVGalaxyObject.h
/// \brief header file for simple object that exists in GalaxyView

// GVGalaxyObject.h -- header file for simple object that exists in GalaxyView
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

/// Enum with all possible object types in galaxyview
enum GVObjectType
{
	GVObj_Planet,
	GVObj_Race,
	GVObj_Bookmark,
};

/// Base class for all galaxyview objects
/// objects can be drawn to a DC or displayed in a table etc...
class GVGalaxyObject
{
  public:
	GVGalaxyObject (unsigned int id, unsigned int turn):m_id (id),
		m_turn (turn)
	{
	};
	virtual ~ GVGalaxyObject () {
	};

  /**
   * overloaded method to draw this object to the map using the paintdc dc
   * \param dc: wxPaintDC
   * \param offsetX: X-offset of map (scrolling)
   * \param offsetY: Y-offset of map (scrolling)
   * \param size: size of the map
   * \param zoom: zoom factor of the map
   * \param center: map centered on 0,0
   * TODO: Change to use a "GVMapable" object, instead of single params
   */
	virtual void Draw (wxDC* dc, long ox, long oy, double size, double zoom,
					   bool center) = 0;

	/// \return long - turnnumber
	long turn ()
	{
		return m_turn;
	};

	/// \return unsigned int - database id
	unsigned int id ()
	{
		return m_id;
	};

	virtual GVObjectType type () = 0;

  protected:
	// database id
	unsigned int m_id;

	// turn number this object is part if -1 it is part of everyturn
	long m_turn;

};

#endif
