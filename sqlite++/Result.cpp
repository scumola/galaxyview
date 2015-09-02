/// \file Result.cpp
/// \brief class file for USED_FOR in GalaxyView

// Result.cpp -- Part of C++ Wrapper for sqlite library in GalaxyView
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

#include <sqlite.h>

#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

#include "SQLiteFile.h"
#include "Query.h"
#include "Result.h"
#include "Row.h"

Result::Result(sqlite_vm* vm)
{
	m_vm = vm;
	if(m_vm) {
		LoadData();
	}
}

Result::Result(const Result& r)
{
	m_vm = r.m_vm;
}

Result::~Result()
{
	if(m_vm) {
		sqlite_finalize(m_vm, NULL);
	}
/*
	vector<Row*>::iterator i;
	for(i=m_rows.begin();i!=m_rows.end();i++) {
		Row* r = (*i);
		delete r;
	}
*/
	m_rows.erase(m_rows.begin(), m_rows.end());
}

void
Result::operator=(const Result& res)
{
	if(m_vm) {
		sqlite_finalize(m_vm, NULL);
	}

	m_rows = res.m_rows;

	m_vm = res.m_vm;
}

bool
Result::Ok() 
{
	if(m_vm) return true;
	return false;
}

void
Result::LoadData()
{
	int ret = SQLITE_ROW;
	int numColumns = 0;
	const char** values;
	const char** columns;
//	Row* r = 0;

	while(ret==SQLITE_ROW)
	{
		ret = sqlite_step(m_vm, &numColumns, &values, &columns);
		if(ret==SQLITE_DONE) {
			break;
		}
/*
		r = new Row(numColumns, values, columns);
		m_rows.push_back(r);
*/
		m_rows.push_back(Row(numColumns, values, columns));
	};
}

Row
Result::operator[](unsigned int i)
{
/*
	Row* r = m_rows[i];
	return *r;
*/
	return m_rows[i];
}

