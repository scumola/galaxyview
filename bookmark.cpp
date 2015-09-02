/// \file bookmark.cpp
/// \brief class file for creating and maintaining bookmarks in GalaxyView

// bookmark.cpp -- class file for creating and maintaining bookmarks
// in GalaxyView
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

#include "bookmark.h"
#include "GVFrame.h"

// Constructor to set default values
BookmarkData::BookmarkData()
{

}

// empty constructor will instantiate the default 'A' bookmark
GVBookmarkManager::GVBookmarkManager(GVdb* db, hDB handle)
: m_db(db), m_handle(handle),m_curBookmark(NULL)
{
	LoadBookmarks();
}


// if the bookmark is dirty, save it to the db
GVBookmarkManager::~GVBookmarkManager ()
{
	map<char,BookmarkData*>::iterator i;
	for(i=m_data.begin();i!=m_data.end();i++) {
		delete (BookmarkData*)(*i).second;
	}
	m_data.erase(m_data.begin(),m_data.end());
}

void
GVBookmarkManager::SetAppDim(int app_width, int app_height)
{
	m_curBookmark->app_height = app_height;
	m_curBookmark->app_width = app_width;
}

void
GVBookmarkManager::SetAppLoc(int app_x, int app_y)
{
	m_curBookmark->app_x = app_x;
	m_curBookmark->app_y = app_y;
}

void
GVBookmarkManager::SetSplitWidth(int split_width)
{
	m_curBookmark->split_width = split_width;
}

void
GVBookmarkManager::SetSplitHeight(int split_height)
{
	m_curBookmark->split_height = split_height;
}

void
GVBookmarkManager::SetMapZoom(int map_zoom) 
{
	m_curBookmark->map_zoom = map_zoom;
}

void 
GVBookmarkManager::SetMapExtent(int ulx, int uly, int lrx, int lry)
{
	m_curBookmark->ulx = ulx;
	m_curBookmark->uly = uly;
	m_curBookmark->lrx = lrx;
	m_curBookmark->lry = lry;
}

BookmarkData*
GVBookmarkManager::GetBookmark(char c)
{
	map<char,BookmarkData*>::iterator i = m_data.find(c);
	if(i==m_data.end()) {
		return NULL;
	} else {
		return (*i).second;
	}
}

void
GVBookmarkManager::SaveBookmarks()
{
	SQLiteFile* sql = m_db->GetSQL(m_handle);
	sql->Execute("DELETE FROM bookmarks");

	Query q = sql->GetQuery();

	map<char,BookmarkData*>::iterator i;
	for(i=m_data.begin();i!=m_data.end();i++) 
	{
		BookmarkData* bd = (*i).second;
		q << "INSERT INTO bookmarks VALUES("
		  << "\'" << bd->id << "\', "
		  << "\'" << bd->description.c_str() << "\', "
		  << bd->app_width << ", "
		  << bd->app_height << ", "
		  << bd->app_x << ", "
		  << bd->app_y << ", "
		  << bd->split_width << ", "
		  << bd->split_height << ", "
		  << bd->map_zoom << ", "
		  << bd->ulx << ", "
		  << bd->uly << ", "
		  << bd->lrx << ", "
		  << bd->lry << ")";
        q.Execute();
	}
}

void
GVBookmarkManager::LoadBookmarks()
{
	Query q = m_db->GetSQL(m_handle)->GetQuery();

	q << "SELECT * from bookmarks";
	Result result = q.Store();

	for(unsigned int i=0;i<result.Size();i++) 
	{
		Row r = result[i];
		BookmarkData* data = new BookmarkData;
		data->id = r["id"][0];
		data->description = r["description"];

		data->dirty = false;
		data->app_height = r.GetInteger(r.GetCol("app_height"));
		data->app_width = r.GetInteger(r.GetCol("app_width"));
		data->app_x = r.GetInteger(r.GetCol("app_x"));
		data->app_y = r.GetInteger(r.GetCol("app_y"));
		data->map_zoom = r.GetInteger(r.GetCol("map_zoom"));
		data->split_height = r.GetInteger(r.GetCol("split_height"));
		data->split_width = r.GetInteger(r.GetCol("split_width"));
		data->ulx = r.GetInteger(r.GetCol("map_ulx"));
		data->uly = r.GetInteger(r.GetCol("map_uly"));
		data->lrx = r.GetInteger(r.GetCol("map_lrx"));
		data->lry = r.GetInteger(r.GetCol("map_lry"));

		m_data[data->id] = data;
	}
}

bool
GVBookmarkManager::CreateBookmark(GVFrame* frame, char c, wxString& description)
{
	// only allow bookmarks from A to Z
	if(c<'A' || c>'Z') return false;

	map<char,BookmarkData*>::iterator i = m_data.find(c);
	
	if(i!=m_data.end()) {
		// Delete old bookmark
		delete (*i).second;
		m_data.erase(i);
	}
	// Add New Bookmark
	BookmarkData* bd = new BookmarkData;
	bd->id = c;
	bd->description = description;
	m_data[c] = bd;
	
	m_curBookmark = bd;

	// Save Settings
	SaveBookmark(frame, c);

	return true;
}

bool 
GVBookmarkManager::DeleteBookmark(char c)
{
	map<char,BookmarkData*>::iterator i = m_data.find(c);

	if(i!=m_data.end()) {
		BookmarkData* bd = (*i).second;
		delete bd;
		m_data.erase(i);
		return true;
	} else {
		return false;
	}
}

bool
GVBookmarkManager::LoadBookmark(GVFrame* frame, char c)
{
	map<char,BookmarkData*>::iterator i = m_data.find(c);

	if(i!=m_data.end()) {
		m_curBookmark = (*i).second;

		// Load Settings
		frame->SetSize(m_curBookmark->app_width, m_curBookmark->app_height);
		frame->Move(m_curBookmark->app_x, m_curBookmark->app_y);
		frame->GetVSplitter()->SetSashPosition(m_curBookmark->split_height);
		frame->GetHSplitter()->SetSashPosition(m_curBookmark->split_width);
		frame->GetMapPanel()->SetZoom(m_curBookmark->map_zoom);

		return true;
	} else {
		return false;
	}
}

bool
GVBookmarkManager::SaveBookmark(GVFrame* frame, char c)
{
	// only allow bookmarks from A to Z
	if(c<'A' || c>'Z') return false;

	map<char,BookmarkData*>::iterator i = m_data.find(c);
	
	// Check if we already have that bookmark_data
	if(i!=m_data.end()) {
		// We already have that bookmark_data
		m_curBookmark = (*i).second;
	} else {
		// Bookmark doesn't exist yet - create it
		
		// Add New Bookmark
		BookmarkData* bd = new BookmarkData;
		bd->id = c;
		bd->description = _T("Auto Save");
		m_data[c] = bd;
		
		m_curBookmark = bd;
	}

	// Save Settings
	m_curBookmark->app_width = frame->GetSize().GetWidth();
	m_curBookmark->app_height = frame->GetSize().GetHeight();
	m_curBookmark->app_x = frame->GetPosition().x;
	m_curBookmark->app_y = frame->GetPosition().y;	
	m_curBookmark->split_height = frame->GetVSplitter()->GetSashPosition();
	m_curBookmark->split_width = frame->GetHSplitter()->GetSashPosition();
	m_curBookmark->map_zoom = frame->GetMapPanel()->GetZoom();

	return true;
}
