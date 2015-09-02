/// \file GVMapPanel.cpp
/// \brief class file for rendering the map in GalaxyView

// GVMapPanel.cpp -- class file for rendering the map in GalaxyView
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

#include "GVMapPanel.h"

enum _map_constants {
	MAP_SCALE_X = 5,
	MAP_SCALE_Y = 5,
	MAP_SCALE_TICK = 5,
	MAP_SCALE_TICKS = 3,
	MAP_SHOW_SMALL_TICKS_THRES = 200,
	MAP_SCROLL_TICK = 5,
	MAP_ZOOM_FACTOR = 10,
	MAP_ZOOM_MIN = 20,
	MAP_ZOOM_MAX = 3200,
	MAP_SCROLL_SCROLLBARWIDTH = 2
};

double debugx;
double debugy;

GVMapEvent::~GVMapEvent ()
{
	for (list < GVMapObject * >::iterator i = m_objects.begin ();
		 i != m_objects.end (); i++) {
		delete (*i);
	}

	m_objects.erase (m_objects.begin (), m_objects.end ());
}

void
GVMapEvent::AddCoordinate (double x, double y)
{
	m_objects.push_back (new GVMapObject (x, y));
}

void
GVMapEvent::AddID (unsigned int id)
{
	m_objects.push_back (new GVMapObject (id));
}

GVMapEvent::GVMapEvent (MapEventType t):m_type (t)
{
}

GVMapPanel::GVMapPanel (wxWindow * parent)
: wxScrolledWindow (parent, -1, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL),
	m_zoom (100)
{
	wxScrolledWindow::SetScrollbars (MAP_SCROLL_TICK, MAP_SCROLL_TICK, 100, 100);

	SetBackgroundColour (*wxBLACK);
	m_turn = -1;

	// TODO: Static options set
	m_options = MAPOPT_ALL;

	m_size = 100.0;
	m_center = true;

	m_planets = NULL;

	m_buffer = NULL;
	m_repaint = true;

	m_buffer_w = -1;
	m_buffer_h = -1;
}

GVMapPanel::~GVMapPanel ()
{
	FreeData();
	if(m_buffer) delete m_buffer;
}

void
GVMapPanel::SetMapSize (double s, bool center /* = false */ )
{
	m_size = s;
	m_center = center;

	SetScrollbars();

	GenerateMap();
}


void
GVMapPanel::OnPaint(wxPaintEvent& event)
{
	
	wxPaintDC dc(this);
	dc.BeginDrawing();
	dc.Clear();

	wxRect rect;
	GetClientSize (&rect.width, &rect.height);

	if(!IsEnabled()) {
		// draw a red X across the screen if the map isn't enabled

		dc.SetPen(*wxRED_PEN);
		dc.DrawLine(0,0, rect.width, rect.height);
		dc.DrawLine(rect.width,0,0, rect.height);

	} else if(m_turn==-1) {
		// Let the user know that no data has been loaded

		dc.SetTextBackground(*wxBLACK);
		dc.SetTextForeground(*wxWHITE);
		dc.DrawText("No Turn Data",(rect.width/2)-48,rect.height/2);
		
	} else {

		// no buffer, no painting
		if(!m_buffer)
			return;
		
		int x, y;
		long offsetX, offsetY;
		long roffX, roffY;
		
		long factor;			///< used in scaling the image

		factor = rect.width < rect.height ? rect.height : rect.width;

		float scale = float(m_size) / factor;
		
		GetViewStart (&x, &y);

		offsetX = x;
		offsetY = y;

		double zoom = m_zoom / 100.0;

		offsetX *= MAP_SCROLL_TICK;
		offsetY *= MAP_SCROLL_TICK;

		if (m_center) {
			roffX = (long)(offsetX - (m_size * zoom / 2.0));
			roffY = (long)(offsetY - (m_size * zoom / 2.0));
		}
		else {
			roffX = offsetX;
			roffY = offsetY;
		}

		// Get Planets

		rect.x = offsetX;
		rect.y = offsetY;
		GetClientSize (&rect.width, &rect.height);

		// Repaint Check
		if(m_repaint) {
			long mapSize = long(m_size * zoom);
			if(mapSize<rect.width && mapSize<rect.height) {
				long ox = (rect.width - mapSize) / 2;
				long oy = (rect.height - mapSize) / 2;
				ReCreateBuffer(offsetX, offsetY, ox, oy);
			} else {
				ReCreateBuffer(offsetX, offsetY, 0, 0);
			}
			m_repaint = false;
		}

		wxPaintDC dc(this);
		dc.BeginDrawing();

		// Check Map Size
		dc.Blit(0, 0, rect.width, rect.height, &m_buffer_dc, 0, 0);

		{
			if (m_options & MAPOPT_SCALE) {
				dc.SetPen (*wxGREY_PEN);
				dc.DrawLine (MAP_SCALE_X,
							rect.height - MAP_SCALE_Y,
							MAP_SCALE_X,
							rect.height - MAP_SCALE_Y - MAP_SCALE_TICK);

				int newX = int (MAP_SCALE_X + (10.0f * zoom));
				dc.DrawLine (newX, rect.height - MAP_SCALE_Y,
							newX,
							rect.height - MAP_SCALE_Y - MAP_SCALE_TICK);

				dc.DrawLine (MAP_SCALE_X,
							rect.height - MAP_SCALE_Y, newX,
							rect.height - MAP_SCALE_Y);

				if (m_zoom >= MAP_SHOW_SMALL_TICKS_THRES) {
					for (int i = 1; i < 10; i++) {
						newX = int (MAP_SCALE_X + (i * zoom));
						dc.DrawLine (newX, rect.height - MAP_SCALE_Y,
									newX,
									rect.height - MAP_SCALE_Y - MAP_SCALE_TICKS);
					}
				}
			}
			if (m_options & MAPOPT_SCALETEXT) {
				char tmp[10];
				sprintf (tmp, "%i%%", m_zoom);
				dc.SetTextForeground (*wxWHITE);
				dc.SetTextBackground (*wxBLACK);
				dc.DrawText (tmp, MAP_SCALE_X,
							MAP_SCALE_Y + MAP_SCALE_TICK);
			}
			if (m_options & MAPOPT_DEBUG_COORD) {
				char tmp[100];
				sprintf (tmp, "%.0f,%.0f", float (roffX) / zoom,
						float (roffY) / zoom);
				dc.SetTextForeground (*wxGREEN);
				dc.SetTextBackground (*wxBLACK);
				dc.DrawText (tmp, MAP_SCALE_X ,
							MAP_SCALE_Y + MAP_SCALE_TICK + 12);

				sprintf(tmp, "%.0f,%0.f", debugx, debugy);
				dc.DrawText(tmp, MAP_SCALE_X, MAP_SCALE_Y + MAP_SCALE_TICK + 24);
			}
			if (m_options & MAPOPT_DRAW_CENTER) {
				if(m_center) {
					dc.CrossHair (-roffX, -roffY);
				}
			}

		}


	}
	dc.EndDrawing();


}

void
GVMapPanel::ReCreateBuffer(long x, long y, long ox, long oy)
{
	m_buffer_dc.SetBrush(*wxBLACK_BRUSH);
	m_buffer_dc.DrawRectangle(0,0,m_buffer_w, m_buffer_h);

	wxPen p(*wxWHITE_PEN);
	p.SetStyle(wxDOT_DASH);
	m_buffer_dc.SetPen(p);
	m_buffer_dc.DrawRectangle(ox, oy, int(m_size*(float(m_zoom)/100)), 
							  int(m_size*(float(m_zoom)/100)));

	x -= ox;
	y -= oy;

	PaintPlanets(&m_buffer_dc, x, y);
}

void
GVMapPanel::PaintPlanets(wxDC* dc, long x, long y)
{
	float zoom = float(m_zoom)/100;

	dc->SetPen(*wxWHITE_PEN);
	dc->SetBrush(*wxWHITE_BRUSH);

	for (unsigned int i = 0; i < m_planets_num; i++) {
		m_planets[i]->Draw (dc, x, y, m_size, zoom, m_center);
		// TODO: Drawing Options
	}
}

void
GVMapPanel::OnMouseWheel (wxMouseEvent & evt)
{
	int offsetX, offsetY;
	double x,y;
	GetViewStart (&offsetX, &offsetY);

	int localX = evt.m_x;
	int localY = evt.m_y;

	// Get Size of Client Window
	int cheight, cwidth;
	GetClientSize (&cwidth, &cheight);

	this->ScreenToClient (&localX, &localY);

	if (localX < 0) {
		localX = 0;
	}
	if (localY < 0) {
		localY = 0;
	}
	if (localX > cwidth) {
		localX = cwidth;
	}
	if(localY > cheight) {
		localY = cheight;
	}

	
	long rX = offsetX * MAP_SCROLL_TICK;
	long rY = offsetY * MAP_SCROLL_TICK;
	rX += localX;
	rY += localY;

	wxRealPoint rp = CalcOffsetToMap(rX, rY); 
	x = rp.x;
	y = rp.y;

	bool in;
	if (evt.GetWheelRotation () > 0) {
		m_zoom += MAP_ZOOM_FACTOR;
		in = true;
	}
	else {
		m_zoom -= MAP_ZOOM_FACTOR;
		in = false;
	}

	if (m_zoom < MAP_ZOOM_MIN)
		m_zoom = MAP_ZOOM_MIN;
	if (m_zoom > MAP_ZOOM_MAX)
		m_zoom = MAP_ZOOM_MAX;

	SetScrollbars();
	ScrollTo(x,y);

	m_repaint = true;
	Refresh ();
}

void
GVMapPanel::OnMouseMove(wxMouseEvent& evt)
{
	int x,y;
	GetViewStart (&x, &y);

	long offsetX = x * MAP_SCROLL_TICK;
	long offsetY = y * MAP_SCROLL_TICK;

	offsetX += evt.m_x;
	offsetY += evt.m_y;

	wxRealPoint p = CalcOffsetToMap(offsetX, offsetY); 

	debugx = p.x;
	debugy = p.y;

	Refresh();
}

void
GVMapPanel::ScrollTo(double x, double y)
{
	float zoom = float(m_zoom)/100;

	long uX = long( (x*zoom) );
	long uY = long( (y*zoom) );

	if(m_center) {
		long size = long( (m_size/2)*zoom );
		uX += size;
		uY += size;
	}


	int cheight, cwidth;
	GetClientSize (&cwidth, &cheight);

	cheight = cheight >> 1;
	cwidth = cwidth >> 1;

	/*
	cheight /= MAP_SCROLL_TICK;
	cwidth /= MAP_SCROLL_TICK;
	*/

	uX -= cwidth;
	uY -= cheight;

	uX /= MAP_SCROLL_TICK;
	uY /= MAP_SCROLL_TICK;

	this->Scroll(uX, uY);
}

void
GVMapPanel::OnScroll (wxScrollWinEvent & event)
{
	event.Skip();
	m_repaint = true;
	Refresh();
}

void
GVMapPanel::OnSize(wxSizeEvent& evt)
{
	if(m_buffer_w == evt.GetSize().GetWidth() && m_buffer_h == evt.GetSize().GetHeight()) return;

	m_buffer_h = evt.GetSize().GetHeight();
	m_buffer_w = evt.GetSize().GetWidth();

	if(m_buffer) {
		delete m_buffer;
	}

	m_buffer_dc.SelectObject(wxNullBitmap);
	m_buffer = new wxBitmap(m_buffer_w, m_buffer_h);
	m_buffer_dc.SelectObject(*m_buffer);
	m_repaint = true;
}

void
GVMapPanel::SetTurn(long turn)
{
	m_turn = turn;
	if(m_turn!=-1) {
		GenerateMap();
	}
	m_repaint = true;
	Refresh();
}

void
GVMapPanel::GenerateMap()
{
	FreeData();
	m_planets_num = GVApp::GetGalaxy ()->GetNumPlanets (m_turn);
	m_planets = new GVPlanet*[m_planets_num];
	GVApp::GetGalaxy()->GetPlanets(m_planets, m_turn);
}

void
GVMapPanel::FreeData()
{
	if(m_planets) {
		delete[] m_planets;
		m_planets = NULL;
	}
}

void
GVMapPanel::SetScrollbars()
{
	int size = int( (m_size*( float(m_zoom)/100 )) / MAP_SCALE_TICK ) + 1;
	wxScrolledWindow::SetScrollbars(MAP_SCALE_TICK, MAP_SCALE_TICK, size, size);
}

wxRealPoint
GVMapPanel::CalcOffsetToMap(long inX, long inY)
{
	double zoom = double(m_zoom) / 100;
	double xx;
	double yy;

	wxRect rect;
	GetClientSize (&rect.width, &rect.height);
	long mapSize = long(m_size * zoom);
	long ox=0,oy=0;
	if(mapSize<rect.width && mapSize<rect.height) {
		ox = (rect.width - mapSize) / 2;
		oy = (rect.height - mapSize) / 2;
		ox = long(ox / zoom);
		oy = long(oy / zoom);
	}

	xx = double(inX)/zoom;
	yy = double(inY)/zoom;

	if(m_center) {
		double size = m_size / 2;
		xx -= size;
		yy -= size;
	}

	xx -= ox;
	yy -= oy;

	return wxRealPoint(xx,yy);
}

void 
GVMapPanel::DoZoom(MapZoomDirection z)
{
	if(z==MAP_ZOOM_IN) {
		m_zoom += MAP_ZOOM_FACTOR;
		if(m_zoom>MAP_ZOOM_MAX) m_zoom = MAP_ZOOM_MAX;
	} else {
		m_zoom -= MAP_ZOOM_FACTOR;
		if(m_zoom<MAP_ZOOM_MIN) m_zoom = MAP_ZOOM_MIN;
	}

	int x,y;
	GetViewStart (&x, &y);

	long offsetX = x * MAP_SCROLL_TICK;
	long offsetY = y * MAP_SCROLL_TICK;

	int cwidth, cheight;
	GetClientSize(&cwidth, &cheight);

	offsetX += cwidth >> 1;
	offsetY += cheight >> 1;

	wxRealPoint p = CalcOffsetToMap(offsetX, offsetY); 
	ScrollTo(p.x, p.y);

	SetScrollbars();
	m_repaint = true;
	Refresh();
}

void
GVMapPanel::OnErase(wxEraseEvent& evt)
{
	// Do Nothing
}

bool
GVMapPanel::Enable(bool e)
{
	if(e) {
		SetScrollbars();
	} else {
		wxScrolledWindow::SetScrollbars(0,0,0,0);
	}
	return wxScrolledWindow::Enable(e);
}

void
GVMapPanel::SetZoom(int zoom)
{
	m_zoom = zoom;
	Refresh();
}

BEGIN_EVENT_TABLE (GVMapPanel, wxScrolledWindow)
	EVT_SCROLLWIN (GVMapPanel::OnScroll)
	EVT_PAINT (GVMapPanel::OnPaint)
	EVT_MOUSEWHEEL (GVMapPanel::OnMouseWheel) 
	EVT_MOTION(GVMapPanel::OnMouseMove)
	EVT_ERASE_BACKGROUND(GVMapPanel::OnErase)
	EVT_SIZE(GVMapPanel::OnSize)
END_EVENT_TABLE ()

