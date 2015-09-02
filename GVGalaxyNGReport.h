//-*- c++ -*-
#if !defined(GVGALAXYNGREPORT_H_)
#define GVGALAXYNGREPORT_H_
/// \file GVGalaxyNGReport.h
/// \brief header file for parsing XML turn reports in GalaxyView

// GVGalaxyNGReport.h -- header file for parsing XML turn reports in GalaxyView
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

#include "GVParseReport.h"

#include "GVDBStatus.h"
#include "GVDBGeneral.h"
#include "GVDBBulletin.h"
#include "GVDBOptions.h"
#include "GVDBAliens.h"
#include "GVDBPlanets.h"
#include "bookmark.h"

/// Parser for GalaxyNG reports

/// This class contains the parser for GalaxyNG turn reports and
/// forecasts.

class GVGalaxyNGReport : public GVParseReport
{
public:
	enum Phase { EMailHeaders, Bulletins, Report };
  
	GVGalaxyNGReport ();
	~GVGalaxyNGReport ();

		/// Set method for skipping the email headers

		/// if the email headers are part of the turn report, then the
		/// first blank line ends the headers. This method maintains
		/// that state informatiom
		/// \param val flag for turning this state on or off
    void SetLookingForBlank (bool val);

		/// Checks whether we are still reading mail headers

		/// if this returns true then we know we can skip the line we
		/// just read as we are still slogging through the email
		/// headers. 
	bool GetLookingForBlank ();

		/// Set method for the XML state

		/// initialized to false, it's set to true once we've found
		/// the <?xml directive
		/// \param val flag for turning this state on or off
	void SetFoundXML (bool val);

		/// Checks whether we are ready to parse the xml

		/// if this returns true then we are ready to parse (or are
		/// parsing) the XML data for the turn
	bool GetFoundXML ();

		// callbacks for parsing parts of the input

		/// callback used when a start tag has been found

		/// \param el the name of the element
		/// \param attr an array containing the name and value of each
		/// attribute
	void TagStart (wxString & el, wxArrayString & attr);

		/// callback used when the end tag has been found

		/// \param el name of the element
	void TagEnd (wxString & el);

		/// callback used for the data contents of the tag

		/// \param chars string containing the characters
	void Characters (wxString & chars);

		/// sets up the 'environment' for the parser to operate in

		/// this method initializes the various states before passing
		/// the file off to the actual parser
		/// \param db pointer to the database container
		/// \param handle handle to the database instance we'll use to
		/// store the data
		/// \param filename the name of the file to be parsed
	virtual bool ParseReport(GVdb* db, hDB handle, wxString& filename);

		/// the actual parser that reads the file and stores the data

		/// \param db pointer to the database container
		/// \param handle handle to the database instance we'll use to
		/// store the data
	bool Parse(GVdb* db, hDB handle);

		/// retrieves latest error string
	wxString& GetError() { return m_error; }

		/// retrieves the current turn number
	long GetTurn() { return m_turn; }

		/// retrieves the name of the game
	wxString GetGamename() { return m_gamename; }

		/// retrieves the name of the race this report is for
	wxString GetPlayerRace() { return m_race; }

		/// retrieves the numerical id of the race this report is for
	int      GetPlayerRaceId() { return m_race_id; }

		/// retrieves the players password
	wxString GetPassword() { return m_password; }

		/// retrieves the set of options this game was started with
	GVGalaxyNGFeatures* GetFeatures() { return &m_features; }

private:

	wxFileInputStream *m_file;	/// <pointer to the report input stream
	wxTextInputStream *m_input;	/// <the text retrieved from the file

	wxString m_inputLine;		/// <the current line read from the file

	bool m_lookingForBlank;		/// <one of the file state variables
	bool m_foundXML;			/// <one of the file state variables

	int m_depth;				/// <how many levels deep we are in
								/// the file. really only used for
								/// debugging. 

	bool m_returnValue;			/// <result of the parse
	wxString m_error;			/// <description of last error that occured

	// Cached Report Data
	long m_turn;				/// <current turn number, from report
	wxString m_gamename;		/// <name of this game, from report
	wxString m_race;			/// <name of race this report is for
	int      m_race_id;			/// <id of race this report is for
	wxString m_password;		/// <player password
	wxString m_version_parsable; /// <report has to be at least this
								 /// version number to be parseable
	
	bool m_fullBombing;			/// <recording game option
	bool m_keepProduction;		/// <recording game option
	bool m_dontDropDead;		/// <recording game option
	bool m_sphericalGalaxy;		/// <recording game option

	int  m_map_ulx;
	int  m_map_uly;
	int  m_map_lrx;
	int  m_map_lry;
	
	GVDBPlanets m_planets;		/// <stores planet info parsed from report
	GVDBStatus m_status;		/// <stores info about current race
	GVDBBulletin m_bulletins;	/// <free format text that leads up to
								/// the report
	GVDBOptions m_options;		/// <player options
	GVDBAliens m_aliens;		/// <stores info about other races
	GVGalaxyNGFeatures m_features; /// <features game was created with
	
};

#endif

