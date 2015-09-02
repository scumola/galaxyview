/// \file GVParseReport.cpp
/// \brief XML report parser, derived from XMLParser

// GVParseReport.cpp
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

#include <iostream>

#include "GVdb.h"

#include "GVParseReport.h"
#include "GVGalaxyNGReport.h"

/// Constructor for the GNG report parser

/// We set the minimum acceptable version number that this parser can
/// handle. this is because of feature set matching.

GVGalaxyNGReport::GVGalaxyNGReport ()
{
	m_version_parsable = "6.3.1";
}

/// Report Parser container

/// This method sets up the parse environment before calling the
/// parser. 
/// \param db a pointer to the GVdb object
/// \param handle a handle to the specific game database
/// \param filename the file to be parsed

bool
GVGalaxyNGReport::ParseReport(GVdb* db, hDB handle, wxString& filename)
{
		// initialization:
		//   create the stream to read from the file
		//   set the error singleton to show that all is OK
	m_file = new wxFileInputStream (filename);
	GVError::GetInstance ()->SetError (GVError::GV_OK);

		// if the file can't be read, record that, let the calling
		// program know that we didn't load data
	if (!m_file->Ok ()) {
		GVError::GetInstance ()->SetError (GVError::GV_BAD_FILE);
		return false;
	}
	m_input = new wxTextInputStream (*m_file);

		// initialize some state variables
	SetLookingForBlank (false);
	SetFoundXML (false);

		// set the start state for the parser, fire it off
	Push(ReportNullState);
	m_depth = 0;

	return Parse(db, handle);
}

/// this method actually parses the turn report

/// this parser can read a turn report with or without email
/// headers. The bulletins can also be optional, but you'll only find
/// this in forecasts
/// \param db pointer to the GVdb instance
/// \param handle handle of the actual database instance

bool
GVGalaxyNGReport::Parse (GVdb * db, hDB handle)
{
	int	val = 0;
	bool moreLines = true;

	m_returnValue = true;

	bool foundBulletin = false;


		// read lines from the file while there're some in it
	while (moreLines) {
		m_inputLine = m_input->ReadLine ();
		if (m_file->GetLastError () == wxSTREAM_EOF) {
			moreLines = false;
		}

			// if true, this orders file still has mail headers
		if(!foundBulletin) {
			if (m_inputLine.Find (_T ("Bulletins for")) != -1) {
				m_bulletins.Add (m_inputLine);
				foundBulletin = true;
				continue;
			}
		}

			// skip further processing of lines if we haven't found
			// the bulletins yet
		if(!foundBulletin)
			continue;

			// first empty line means end of mail headers - all mail
			// headers are skipped
		if (GetLookingForBlank ()) {
			if (m_inputLine.Length () == 0) {
				SetLookingForBlank (false);
				continue;
			}
			else {
					// its still a mail header continue with next line
				continue;
			}
		}

			// Bulletins - if we're in the bulletin section add them
			// to the list, otherwise check for the opening of the XML
			// section
		if (!GetFoundXML ()) {
			if (m_inputLine.Find ("<?xml") != -1) {
				SetFoundXML (true);
			}
			else {
				m_bulletins.Add (m_inputLine);
			}
		}
		else {
				// now throw the remainder of the file off to the
				// actual XML parser
			XMLParser::Parse (m_inputLine, val);

		}
	}

		// Parsed Ok - Save Data to database
	if (m_returnValue) {
 		m_bulletins.Store (db, handle);
		m_options.Store(db, handle);
		m_aliens.Store(db, handle);
		m_status.Store(db, handle); // Status has to be after aliens, otherwise aliens deletes the own race
		m_planets.Store(db, handle);
	}

	return m_returnValue;
}


GVGalaxyNGReport::~GVGalaxyNGReport ()
{
	delete m_input;
	delete m_file;
}

void
GVGalaxyNGReport::SetLookingForBlank (bool val)
{
	m_lookingForBlank = val;
}

bool
GVGalaxyNGReport::GetLookingForBlank ()
{
	return m_lookingForBlank;
}

void
GVGalaxyNGReport::SetFoundXML (bool val)
{
	m_foundXML = val;
}

bool
GVGalaxyNGReport::GetFoundXML ()
{
	return m_foundXML;
}


void
GVGalaxyNGReport::TagStart (wxString & el, wxArrayString & attr)
{
	enum XMLState t = Top();
	wxString logMessage = wxString("t:") + lookupStateName(t);
	wxLogMessage(logMessage);
	//cerr << "t: " << lookupStateName(t) << endl;
	if (t == ReportNullState) {
		if(el=="galaxy") {
			Push(ReportGalaxyState);
		} else {
			Push(ReportUnknownState);
		}
	} else if(t==ReportGalaxyState) {
		if(el=="variant") {
			Push(ReportVariantState);
		} else if(el=="version") {
			Push(ReportVersionState);
		} else if(el=="game") {
			// Save Gamename
			m_gamename = attr[1];
			Push(ReportGameState);
		} else {
			Push(ReportUnknownState);
		}
	} else if(t==ReportGameState) {
		if(el=="features") {
			Push(ReportFeaturesState);
		} else if(el=="turn") {
			m_turn = atoi(attr[1].c_str());

			//Set Status for all Objects
			m_status.SetTurn(m_turn);
			m_bulletins.SetTurn(m_turn);
			m_options.SetTurn(m_turn);
			m_aliens.SetTurn(m_turn);
			m_planets.SetTurn(m_turn);

			Push(ReportTurnState);
		} else {
			Push(ReportUnknownState);
		}
	} else if(t==ReportFeaturesState) {
		if(el=="size") {
			Push(ReportFeaturesSizeState);
		} else if(el=="numWorlds") {
			Push(ReportFeaturesWorldsState);
		} else if(el=="numRaces") {
			Push(ReportFeaturesNumRacesState);
		} else if(el=="fullBombing") {
			m_fullBombing = (attr[1]=="ON")?true:false;
			Push(ReportUnknownState);
		} else if(el=="keepProduction") {
			m_keepProduction = (attr[1]=="ON")?true:false;
			Push(ReportUnknownState);
		} else if(el=="dontDropDead") {
			m_dontDropDead = (attr[1]=="ON")?true:false;
			Push(ReportUnknownState);
		} else if(el=="sphericalGalaxy") {
			m_sphericalGalaxy = (attr[1]=="ON")?true:false;
			Push(ReportUnknownState);
		} else {
			m_returnValue = false;
			m_error += "Features Element had unknown element " + el + "\n";
		}
	} else if(t==ReportTurnState) {
		if(el=="race") {
			m_race = attr[1];
			m_race_id = atoi(attr[3].c_str());
			m_password = attr[5];

			m_status.m_name = m_race;
			m_status.m_id = m_race_id;
			m_status.m_password = m_password;

			Push(ReportRaceState);
		}
	} else if(t==ReportRaceState) {
		if(el=="options") {
			Push(ReportPlayerOptionsState);
		} else if(el=="report") {
			Push(ReportReportState);
		}
	} else if(t==ReportPlayerOptionsState) {
		m_options.Add(el, attr[1]);
		Push(ReportUnknownState);
	} else if(t==ReportReportState) {
		if(el=="status") {
			Push(ReportStatusState);
		} else if(el=="alienRaces") {
			Push(ReportAlienRacesState);
		} else if (el == "map") {
			Push(ReportMapState);
		} else if(el=="identifiedWorlds") {
		  int id;
		  if (attr[1] == m_race)
			id = m_race_id;
		  else {
			id = m_aliens.GetId(attr[1]);
		  }
		  m_planets.SetOwner(attr[1], id);
			Push(ReportIdentifiedWorldsState);
		} else if(el=="unidentifiedWorlds") {
			Push(ReportUnidentifiedWorldsState);
		} else if(el=="uninhabitedWorlds") {
			Push(ReportUninhabitedWorldsState);
		} else {
			Push(ReportUnknownState);
		}
	} else if (t == ReportMapState) {
		if (el == "ulx") {
			Push(ReportMapULXState);
		}
		if (el == "lrx") {
			Push(ReportMapLRXState);
		}
		if (el == "uly") {
			Push(ReportMapULYState);
		}
		if (el == "lry") {
			Push(ReportMapLRYState);
		}
	} else if(t==ReportStatusState) {
		if(el=="tech") {
			Push(ReportStatusTechState);
		} else if(el=="numPlanets") {
			Push(ReportStatusNumPlanetsState);
		} else if(el=="population") {
			Push(ReportStatusPopulationState);
		} else if(el=="industry") {
			Push(ReportStatusIndustryState);
		} else if(el=="stockpiles") {
			Push(ReportStatusStockpilesState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportStatusTechState) {
		if(el=="drive") {
			Push(ReportStatusDriveState);
		} else if(el=="weapons") {
			Push(ReportStatusWeaponsState);
		} else if(el=="shields") {
			Push(ReportStatusShieldsState);
		} else if(el=="cargo") {
			Push(ReportStatusCargoState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportStatusStockpilesState) {
		if(el=="capital") {
			Push(ReportStatusCapitalState);
		} else if(el=="material") {
			Push(ReportStatusMaterialState);
		} else if(el=="colonists") {
			Push(ReportStatusColonistsState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportAlienRacesState) {
		if(el=="alienRace") {
			m_aliens.AddNew(attr[1], attr[3]);
			Push(ReportAlienRaceState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportAlienRaceState) {
		if(el=="tech") {
			Push(ReportAlienTechState);
		} else if(el=="state") { //TODO: Changed to posture perhaps?
			Push(ReportAlienStateState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportAlienTechState) {
		if(el=="drive") {
			Push(ReportAlienDriveState);
		} else if(el=="weapons") {
			Push(ReportAlienWeaponsState);
		} else if(el=="shields") {
			Push(ReportAlienShieldsState);
		} else if(el=="cargo") {
			Push(ReportAlienCargoState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportIdentifiedWorldsState) {
		if(el=="world") {
			Push(ReportIWorldState);
			m_planets.Add(true, attr[1]);
			m_planets.SetStatus("Identified");
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportUnidentifiedWorldsState) {
		if(el=="world") {
			Push(ReportUWorldState);
			m_planets.Add(false, "");
			m_planets.SetStatus("Unidentified");
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportUninhabitedWorldsState) {
		if(el=="world") {
			Push(ReportHWorldState);
			m_planets.Add(false, "");
			m_planets.SetStatus("Uninhabited");
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportIWorldState) {
		if(el=="position") {
			Push(ReportIWorldPositionState);
		} else if(el=="resources") {
			Push(ReportIWorldResourcesState);
		} else if(el=="size") {
			Push(ReportIWorldSizeState);
		} else if(el=="population") {
			Push(ReportIWorldPopulationState);
		} else if(el=="industry") {
			Push(ReportIWorldIndustryState);
		} else if(el=="stockpiles") {
			Push(ReportIWorldStockpilesState);
		} else if(el=="production") {
			Push(ReportIWorldProductionState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportIWorldPositionState) {
		if(el=="x") {
			Push(ReportIWorldXState);
		} else if(el=="y") {
			Push(ReportIWorldYState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportIWorldStockpilesState) {
		if(el=="capital") {
			Push(ReportIWorldStockCapitalState);
		} else if(el=="material") {
			Push(ReportIWorldStockMaterialState);
		} else if(el=="colonists") {
			Push(ReportIWorldStockColonistsState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportUWorldState) {
		if(el=="position") {
			Push(ReportUWorldPositionState);
		} else {
			wxASSERT(false);
		}
	} else if(t==ReportUWorldPositionState) {
		if(el=="x") {
			Push(ReportUWorldXState);
		} else if(el=="y") {
			Push(ReportUWorldYState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else if(t==ReportHWorldState) {
		if(el=="position") {
			Push(ReportHWorldPositionState);
		} else {
			wxASSERT(false);
		}
	} else if(t==ReportHWorldPositionState) {
		if(el=="x") {
			Push(ReportHWorldXState);
		} else if(el=="y") {
			Push(ReportHWorldYState);
		} else {
			wxASSERT_MSG(false, "This should never happen.");
		}
	} else {
		Push(ReportUnknownState);
	}

	m_depth++;
}								/* End of start handler */

void
GVGalaxyNGReport::TagEnd (wxString & el)
{
	wxASSERT_MSG(m_depth>0, "Strange :)");
	enum XMLState t = Top();

	if(t==ReportAlienRaceState) {
		m_aliens.Close();
	} else if(t==ReportIWorldState) {
		m_planets.Close();
	} else if(t==ReportUWorldState) {
		m_planets.Close();
	} else if(t==ReportHWorldState) {
		m_planets.Close();
	}

	Pop ();
	m_depth--;
}								/* End of end handler */

void
GVGalaxyNGReport::Characters (wxString & chars)
{
	enum XMLState t = Top();

	if(t==ReportVariantState) {
		if(chars=="GalaxyNG") {

		} else {
			m_returnValue = false;
			m_error += "Possibly not a GalaxyNG report\n";
			wxLogMessage("Possibly not a GalaxyNG report");
		}
	} else if(t==ReportFeaturesSizeState) {
		m_features.size = atof(chars.c_str());
	} else if(t==ReportFeaturesWorldsState) {
		m_features.numRaces = atoi(chars.c_str());
	} else if(t==ReportFeaturesNumRacesState) {
		m_features.numRaces = atoi(chars.c_str());
	} else if(t==ReportStatusDriveState) {
		m_status.m_drive = atof(chars.c_str());
	} else if(t==ReportStatusWeaponsState) {
		m_status.m_weapons = atof(chars.c_str());
	} else if(t==ReportStatusShieldsState) {
		m_status.m_shields = atof(chars.c_str());
	} else if(t==ReportStatusCargoState) {
		m_status.m_cargo = atof(chars.c_str());
	} else if(t==ReportStatusNumPlanetsState) {
		m_status.m_numPlanets = atoi(chars.c_str());
	} else if(t==ReportStatusPopulationState) {
		m_status.m_population = atoi(chars.c_str());
	} else if(t==ReportStatusIndustryState) {
		m_status.m_industry = atoi(chars.c_str());
	} else if(t==ReportStatusCapitalState) {
		m_status.m_capital = atof(chars.c_str());
	} else if(t==ReportStatusMaterialState) {
		m_status.m_material = atof(chars.c_str());
	} else if(t==ReportStatusColonistsState) {
		m_status.m_colonists = atof(chars.c_str());
	} else if(t==ReportAlienDriveState) {
		m_aliens.SetDrive(atof(chars.c_str()));
	} else if(t==ReportAlienWeaponsState) {
		m_aliens.SetWeapons(atof(chars.c_str()));
	} else if(t==ReportAlienShieldsState) {
		m_aliens.SetShields(atof(chars.c_str()));
	} else if(t==ReportAlienCargoState)  {
		m_aliens.SetCargo(atof(chars.c_str()));
	} else if(t==ReportAlienStateState) {
		m_aliens.SetPosture(chars);
	} else if(t==ReportIWorldXState) {
		m_planets.SetX(atof(chars.c_str()));
	} else if(t==ReportIWorldYState) {
		m_planets.SetY(atof(chars.c_str()));
	} else if(t==ReportIWorldResourcesState) {
		m_planets.SetResources(atof(chars.c_str()));
	} else if(t==ReportIWorldSizeState) {
		m_planets.SetSize(atof(chars.c_str()));
	} else if(t==ReportIWorldPopulationState) {
		m_planets.SetPopulation(atof(chars.c_str()));
	} else if(t==ReportIWorldIndustryState) {
		m_planets.SetIndustry(atof(chars.c_str()));
	} else if(t==ReportIWorldStockCapitalState) {
		m_planets.SetCapital(atof(chars.c_str()));
	} else if(t==ReportIWorldStockMaterialState) {
		m_planets.SetMaterial(atof(chars.c_str()));
	} else if(t==ReportIWorldStockColonistsState) {
		m_planets.SetColonists(atof(chars.c_str()));
	} else if(t==ReportIWorldProductionState) {
		m_planets.SetProduction(chars);
	} else if(t==ReportUWorldXState) {
		m_planets.SetX(atof(chars.c_str()));
	} else if(t==ReportUWorldYState) {
		m_planets.SetY(atof(chars.c_str()));
	} else if(t==ReportHWorldXState) {
		m_planets.SetX(atof(chars.c_str()));
	} else if(t==ReportHWorldYState) {
		m_planets.SetY(atof(chars.c_str()));
	} else if(t==ReportMapULXState) {
		m_map_ulx = atoi(chars.c_str());
	} else if(t==ReportMapULYState) {
		m_map_uly = atoi(chars.c_str());
	} else if(t==ReportMapLRXState) {
		m_map_lrx = atoi(chars.c_str());
	} else if(t==ReportMapLRYState) {
		m_map_lry = atoi(chars.c_str());
	}
}


#if defined(GVParseReport_MAIN_NEEDED)

#include <iostream>

#include <stdio.h>
#include <string.h>

int
main (int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <xmlfile>" << std::endl;
		return 1;
	}
	else {
		std::cout << "Staring Parser..." << std::endl;
	}

	GVParseReport* pr = new GVParseReport (wxConvertMB2WX (argv[1]));

	// Test doesn't work anymore, perhaps write a work around later
	//pr->Parse();

	delete pr;

	return 0;
}								/* End of main */

#endif
