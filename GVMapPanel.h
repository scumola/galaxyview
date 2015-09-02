#if !defined(GVMAPPANEL_H_)
#define GVMAPPANEL_H_
/// \file GVMapPanel.h
/// \brief header file for rendering the map in GalaxyView

// GVMapPanel.h -- header file for rendering the map in GalaxyView
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

#include <list>
using namespace std;

#include "GVApp.h"
#include "GVPlanet.h"

enum MapZoomDirection
{
	MAP_ZOOM_IN,
	MAP_ZOOM_OUT
};

enum MapEventType
{
	MAP_NOSELECTION,
	MAP_PLANETSELECTED,
	MAP_GROUPSELECTED,
	MAP_BORDER
};

enum MapOptions
{
	// Meta Data
	MAPOPT_SCALE = 0x0001,
	MAPOPT_SCALETEXT = 0x0002,
	MAPOPT_DRAW_CENTER = 0x0004,

	// Planet Options

	// Group Options

	// Debug
	MAPOPT_DEBUG_COORD = 0x8000,


	MAPOPT_ALL = 0xFFFF
};

class GVMapObject
{
  public:
	GVMapObject (double _x, double _y):id (0), x (_x), y (_y)
	{
	};
	GVMapObject (unsigned int _id):id (_id), x (0.0), y (0.0)
	{
	};

	unsigned int id;
	double x;
	double y;
};

class GVMapEvent
{
  public:
	// event for one object 
	GVMapEvent (MapEventType t);
	~GVMapEvent ();

	void AddCoordinate (double x, double y);
	void AddID (unsigned int id);

  protected:
	  MapEventType m_type;

	  list < GVMapObject * >m_objects;
};

class GVMapPanel:public wxScrolledWindow
{
  public:
	GVMapPanel (wxWindow * parent);
	~GVMapPanel ();

/*
	Actives/Deactives Rendering of a map detail
	void SetDetail(GVMapDetail det, bool b);
*/

	void SetTurn (long turn);
	void SetMapSize (double s, bool center = false);

//      virtual void OnDraw(wxDC& dc);

	void OnScroll (wxScrollWinEvent & event);
	void OnPaint (wxPaintEvent & event);

	void OnMouseWheel (wxMouseEvent & event);
	void OnMouseMove(wxMouseEvent& evt);
	void OnErase(wxEraseEvent& evt);
	void OnSize(wxSizeEvent& evt);

	void DoZoom(MapZoomDirection z);

	bool Enable(bool e);

	int GetZoom() { return m_zoom; }
	void SetZoom(int zoom);

  protected:
	void ReCreateBuffer(long x, long y, long ox, long oy);

	void PaintPlanets(wxDC* dc, long ox, long oy);

	wxRealPoint CalcOffsetToMap(long inX, long inY);
	void ScrollTo(double x, double y);

	void SetScrollbars();
	void GenerateMap();
	void FreeData();

	// zoom factor
	int m_zoom;

	// map size
	int m_size;

	// map boundaries
	int m_ulx;
	int m_uly;
	int m_lrx;
	int m_lry;
	
	// is the map centered around 0,0
	bool m_center;

	// turn number to display
	long m_turn;

	// display on/off options
	unsigned int m_options;

	// buffer
	wxBitmap* m_buffer;
	int m_buffer_w;
	int m_buffer_h;
	wxMemoryDC m_buffer_dc;
	bool m_repaint;

	// Planet Data
	unsigned int m_planets_num;
	GVPlanet** m_planets;

	DECLARE_EVENT_TABLE ()
};

#endif
