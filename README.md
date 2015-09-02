	galaxyview - Graphical turn viewer for the PbEM game Galaxy



  Copyright (C) 2003 Quarterflash Design Group

  GalaxyView is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Comments are welcome.

	- Kenneth D. Weinert <madcoder42 @ users.sourceforge.net>





-----
Instructions for using the Visual C project/workspace files:
-----

These files include the information for compiling GalaxyView with VC6.
In order to build GV, you will also need to have downloaded and built 
wxWindows (www.wxwindows.org).  The current version is 2.4.1, however
both 2.4.0 and the CVS version work. 

In the 2.4.0 and 2.4.1 versions there is a bug (see below for the fix.)
This bug has been fixed in CVS.

You also need to build the xrc library that comes with wxWindows. 
It is in contrib/src/xrc.  Additionally, you will need sqlite 
(http://www.sqlite.org) and expat (http://expat.sourceforge.net.)

These project files do not specify any include/library folders - you
will need to set these yourself either in the project settings or in your
Visual C++ settings.  These were ommitted due to the fact that they will be
installed in different locations on different machines.

The bug you need to fix in one of the source files - src/common/fs_zip.cpp
Add the following code:

    if (right.Contains(wxT("./")))
    {
        if (right.GetChar(0) != wxT('/')) right = wxT('/') + right;
        wxFileName rightPart(right, wxPATH_UNIX);
        rightPart.Normalize(wxPATH_NORM_DOTS, wxT("/"), wxPATH_UNIX);
        right = rightPart.GetFullPath(wxPATH_UNIX);
    }

before this line, on line 90:

    if (right.GetChar(0) == wxT('/')) right = right.Mid(1);
    

That should be all you need to know about compiling with VC6, good luck! :o)
-----

