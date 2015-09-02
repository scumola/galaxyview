#ifndef __RESULT_H__
#define __RESULT_H__
/// \file Result.h
/// \brief header file for USED_FOR in GalaxyView

// Result.h -- header file of C++ Wrapper for sqlite library in GalaxyView
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

#include "Row.h"

class Row;

class Result
{
friend class Query;

public:
	Result(const Result& r);
	~Result();

	/// \return bool - returns true if this result could load all data
	bool Ok();

	/// \return unsigned int - number of rows in this result
	unsigned int Size() { return (unsigned int)(m_rows.size()); }

	/// \return bool - returns true if there are no rows in this result
	bool Empty() { return ((m_rows.size()==0)?true:false); }

	void operator=(const Result& r);

	/// Overloaded operator to give array style access
	Row operator[](unsigned int);

protected:
	/// Protected constructor
	Result(sqlite_vm* vm);

	/// Loads Row Data on init
	void LoadData();

	/// pointer to sqlite virtual machine
	sqlite_vm* m_vm;

	/// list with all rows loaded by LoadData()
	vector<Row> m_rows;
};

#endif

