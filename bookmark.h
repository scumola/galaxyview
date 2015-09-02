#if !defined(BOOKMARK_H_)
#define BOOKMARK_H_
/// \file bookmark.h
/// \brief header file for creating and maintaining bookmarks in GalaxyView

// bookmark.h -- header file for creating and maintaining bookmarks in
// GalaxyView
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

#include <map>
using namespace std;

#include "wx/string.h"

#include "GVdb.h"

class GVFrame;

class BookmarkData {
public:
	BookmarkData();

	char id;					// single character identifier

	wxString description;		// more readable text

	int  dirty;					// has this bookmark changed since
								// instantiated 
	int  app_width;				// width of the application window
	int  app_height;			// height of the application window
	int  app_x;					// screen location, x
	int  app_y;					// screen location, y

	// for the location of the splits
	int  split_width;			// x position of the vertical splitter
	int  split_height;			// y position of the horizontal
								// splitter

	// map info
	int  map_zoom;				// zoom factor of the map
	int  ulx;					// corners of the map in light years
	int  uly;
	int  lrx;
	int  lry;
};

class GVBookmarkManager
{
public:
	GVBookmarkManager(GVdb*, hDB);
	~GVBookmarkManager();
	
	void SetAppDim(int app_width, int app_height);
	void SetAppLoc(int app_x, int app_y);

	void SetSplitWidth(int split_width);
	void SetSplitHeight(int split_height);

	void SetMapZoom(int map_zoom);

	void SetMapExtent(int ulx, int uly, int lrx, int lry);
	
	BookmarkData* GetBookmark(char c);

	// Load/Save to Database
	void LoadBookmarks();
	void SaveBookmarks();

	bool CreateBookmark(GVFrame* frm, char c, wxString& description);
	bool DeleteBookmark(char c);
	bool SaveBookmark(GVFrame* frame, char c);
	bool LoadBookmark(GVFrame*, char c);

private:
	BookmarkData* m_curBookmark;
	map<char, BookmarkData*> m_data;

	GVdb* m_db;
	hDB m_handle;
};

#endif
