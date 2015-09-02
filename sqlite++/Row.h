#ifndef __ROW_H__
#define __ROW_H__
/// \file Row.h
/// \brief header file for USED_FOR in GalaxyView

// Row.h -- header file of C++ Wrapper for sqlite library in GalaxyView
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

class Row
{
friend class Result;

public:
	~Row();

	Row(const Row& r);
	void operator=(const Row& r);

	/// Returns column number by column name
	/// \param string - column name
	/// \return int - column number
	int GetCol(string);

	const char* operator[](int);
	const char* operator[](string);

	/// Converts the column to an integer and returns it
	/// \param int - column number
	/// \return int - integer value of that data
	int GetInteger(int);

	/// \return bool - true if this row is loaded correct
	bool Ok() { return (m_num==-1)?false:true; }

protected:
	Row(int num, const char** values, const char** columns);

	/// number of columns
	int m_num;

	/// name to column number map
	map<string,int> m_cols;

	/// row data
	string** m_data;

};

#endif

