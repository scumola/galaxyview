/// \file GVToolsBattleSimulator.cpp
/// \brief class file for GVToolsPage in GalaxyView

// GVToolsBattleSimulator.cpp -- class file for GVTools in GalaxyView
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

#include "GVToolsBattleSimulator.h"
#include "GVTools.h"

IMPLEMENT_DYNAMIC_CLASS(GVToolsBattleSimulator, GVToolsPage)

GVToolsBattleSimulator::GVToolsBattleSimulator()
{
}

void
GVToolsBattleSimulator::OnCreate()
{
	// Called after the Panel is created
}

void
GVToolsBattleSimulator::Save()
{
	// Do whatever you need to do to save things
}

void
GVToolsBattleSimulator::Load()
{
	// Do whatever you need to do to load things
}


BEGIN_EVENT_TABLE (GVToolsBattleSimulator, GVToolsPage)
END_EVENT_TABLE()

