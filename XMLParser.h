#if !defined(XMLPARSER_H_)
#define XMLPARSER_H_
/// \file XMLParser.h
/// \brief header file for XML parsing

// XMLParser.h -- header file for XML parsing
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

// wxwindows includes
#include "wx/string.h"

#include "xtd/expat/xmlparse.h"

#define BUFFSIZE	8192


class XMLHandler
{
  public:
	virtual void TagStart (wxString & el, wxArrayString & attr)
	{
	};
	virtual void TagEnd (wxString & el)
	{
	};
	virtual void Characters (wxString & chars)
	{
	};
};


class XMLParser
{
  public:

	XMLParser ();
	virtual ~ XMLParser ();

	void SetCallback (XMLHandler * handler)
	{
		m_handler = handler;
	};

	virtual bool Parse (wxString, int &);
	void SetDepth (int depth)
	{
		m_depth = depth;
	};
	int GetDepth ()
	{
		return m_depth;
	};

	void IncrDepth ()
	{
		m_depth++;
	};
	void DecrDepth ()
	{
		m_depth--;
	};

	virtual void TagStart (wxString & el, wxArrayString & attr);
	virtual void TagEnd (wxString & el);
	virtual void Characters (wxString & chars);

  private:
	virtual int CurrentLineNumber ();
	virtual wxString ErrorString ();
	virtual int ErrorCode ();

	// data members
	XML_Parser m_parser;
	XMLHandler *m_handler;

	char m_buffer[BUFFSIZE];
	int m_depth;
	int m_errorNbr;
	int m_lineNbr;
};

#endif
