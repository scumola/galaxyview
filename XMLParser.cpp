/// \file XMLParser.cpp
/// \brief class file for xml parsing

// XMLParser.cpp -- class file for xml parsing
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

#include "XMLParser.h"

#include <iostream>

using namespace std;

static void
wrapper_Characters (void *data, const XML_Char * _chars, int len)
{
	XMLParser *xp = (XMLParser *) data;
	if (!xp)
		return;

	wxString chars (wxConvertMB2WX (_chars), len);

	xp->Characters (chars);
}

static void
wrapper_TagStart (void *data, const XML_Char * name,
				  const XML_Char ** attributes)
{
	// if data is null we probably should report this somehow to the user
	XMLParser *xp = (XMLParser *) data;
	if (!xp)
		return;

	wxString el (wxConvertMB2WX (name));
	wxArrayString attr;

	unsigned int i = 0;
	while (attributes[i]) {
		wxString currentAttr (wxConvertMB2WX (attributes[i]));
		attr.Add (currentAttr);
		i++;
	};

	xp->TagStart (el, attr);
}

static void
wrapper_TagEnd (void *data, const XML_Char * name)
{
	// if data is null we probably should report this somehow to the user
	XMLParser *xp = (XMLParser *) data;
	wxString el (wxConvertMB2WX (name));
	if (xp)
		xp->TagEnd (el);
}

XMLParser::XMLParser ()
{
	m_parser = XML_ParserCreate (NULL);
	m_depth = 0;

	// set userdate to this parser, so we can retrieve a pointer to this
	// class from the wrapper functions 
	XML_SetUserData (m_parser, this);
	XML_SetElementHandler (m_parser, wrapper_TagStart, wrapper_TagEnd);
	XML_SetCharacterDataHandler (m_parser, wrapper_Characters);
	m_handler = NULL;
};

XMLParser::~XMLParser ()
{
	XML_ParserFree (m_parser);
};


void
XMLParser::TagStart (wxString & el, wxArrayString & attr)
{
	m_depth++;
	if (m_handler)
		m_handler->TagStart (el, attr);
}								/* End of start handler */

void
XMLParser::TagEnd (wxString & el)
{
	m_depth--;
	if (m_handler)
		m_handler->TagEnd (el);
}								/* End of end handler */

void
XMLParser::Characters (wxString & chars)
{
	if (m_handler)
		m_handler->Characters (chars);
}								/* End of character handler */

int
XMLParser::CurrentLineNumber ()
{
	return m_lineNbr;
}

wxString XMLParser::ErrorString ()
{
	return wxString (wxConvertMB2WX (XML_ErrorString (m_errorNbr)));
}

int
XMLParser::ErrorCode ()
{
	return m_errorNbr;
}

bool XMLParser::Parse (wxString buffer, int &value)
{
	int
		retVal =
		XML_Parse (m_parser, wxConvertWX2MB (buffer.c_str ()),
				   buffer.length (),
				   0);
	if (retVal == 0)
		return false;
	return true;
}


#if defined(XMLParser_MAIN_NEEDED)

#include "wx/ffile.h"

#if defined(WIN32) && defined(_DEBUG)
#include <crtdbg.h>
#endif

int
main (int argc, char *argv[])
{
#if defined(WIN32) && defined(_DEBUG)
	// Set Breakpoint at memory allocation 
	//_CrtSetBreakAlloc(94);
#endif

	XMLParser *
		xp =
		new
		XMLParser ();
	int
		len;

	wxFFile *
		fp =
		new
		wxFFile (argv[1]);

	if (!fp->IsOpened ()) {
		std::
			cerr << "Could not open \"" << argv[1] << "\" for reading" <<
			std::endl;
		return 1;
	}

	wxString
		contents;

	char *
		buffer;

	buffer = new char[fp->Length () + 1];

	fp->Read (buffer, fp->Length ());
	buffer[fp->Length () - 1] = '\0';

	delete
		fp;

	contents = buffer;
/*
  contents = "<?xml version=\"1.0\"?>\n<outer type=\"classtag\">Outer"
	  " Tag\n <inner mytype=\"enclosed\">Enclosed tag</inner>\n</outer>\n";

  contents = "<?xml version=\"1.0\"?>\n\n<report>\n</report>\n";
*/

	//std::cerr << "Contents: " << contents.Mid(contents.Length()-80).c_str() << endl;
	//std::cerr << "file contents:" << endl << contents.c_str() << endl;

	bool
		retCode =
		xp->
		Parse (contents, len);
	if (retCode) {
		std::cout << "end of parsing" << std::endl;
	}
	else {
		std::cout << "parse error" << endl;
	}

	delete
		xp;
	delete[]buffer;
}

#endif
