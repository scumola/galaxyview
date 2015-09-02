/// \file GVToolsCalculator.cpp
/// \brief class file for GVToolsPage in GalaxyView

// GVToolsCalculator.cpp -- class file for GVTools in GalaxyView
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

#include "GVToolsCalculator.h"
#include "GVTools.h"

IMPLEMENT_DYNAMIC_CLASS(GVToolsCalculator, GVToolsPage)

GVToolsCalculator::GVToolsCalculator()
{
}

void
GVToolsCalculator::OnCreate()
{
	// Called after the Panel is created
}

void
GVToolsCalculator::Save()
{
	// Do whatever you need to do to save things
}

void
GVToolsCalculator::Load()
{
	// Do whatever you need to do to load things
}


BEGIN_EVENT_TABLE (GVToolsCalculator, GVToolsPage)
END_EVENT_TABLE()

