/// \file Row.cpp
/// \brief class file for USED_FOR in GalaxyView

// Row.cpp -- Part of C++ Wrapper for sqlite library in GalaxyView
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

Row::Row(int num, const char** values, const char** columns)
{
	m_num = num;
	m_data = new string*[num];
	for(int i=0;i<num;i++) {
		m_cols[columns[i]] = i;

		if(values[i]) {
			m_data[i] = new string(values[i]);
		} else {
			m_data[i] = NULL;
		}
	}
}

Row::~Row()
{
	for(int i=0;i<m_num;i++) {
		delete m_data[i];
	}
	delete[] m_data;
}

Row::Row(const Row& r)
{
	m_num = r.m_num;
	m_data = new string*[m_num];

	m_cols = r.m_cols;
	
	for(int i=0;i<m_num;i++) {
		if(r.m_data[i]) {
			m_data[i] = new string((*r.m_data[i]));
		} else {
			m_data[i] = NULL;
		}
	}
}

void
Row::operator=(const Row& r)
{
	m_num = r.m_num;
	m_data = new string*[m_num];

	m_cols = r.m_cols;
	
	for(int i=0;i<m_num;i++) {
		m_data[i] = r.m_data[i];
	}
}

int
Row::GetCol(string s)
{
	map<string,int>::iterator i = m_cols.find(s);
	if(i==m_cols.end()) {
		throw string("Column ") + s + string(" doesn't exist.");
	}

	return (*i).second;
}

int
Row::GetInteger(int i)
{
	string s = (*this)[i];
	int value = atoi(s.c_str());

	return value;
}

const char*
Row::operator[](int i)
{
	if(m_data[i]) {
		return m_data[i]->c_str();
	} else {
		return NULL;
	}
}

const char*
Row::operator[](string s)
{
	if(m_data[GetCol(s)]) {
		return m_data[GetCol(s)]->c_str();
	} else {
		return NULL;
	}
}

