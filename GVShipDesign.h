#if !defined(GVSHIPDESIGN_H)
#define GVSHIPDESIGN_H

#include "wx/wxprec.h"

#if !defined(WX_PREC)
#include "wx/wx.h"
#endif

#include "wx/string.h"
#include "wx/gdicmn.h"

#include "GVdefines.h"

class GVShipDesign
{
  public:
	GVShipDesign ();
	~GVShipDesign ();


  private:
	wxString m_name;
	wxString m_owner;

	double m_drive;
	int m_attacks;
	double m_weapons;
	double m_shields;
	double m_cargo;

	wxString m_comments;		// for general comments, like which
	// planet it was developed for, etc
	wxString m_class;			// for grouping different designs

	priority m_carryCOL;		// priority is a value from 0-4
	priority m_carryCAP;		// 0 == never
	priority m_carryMAT;		// 4 == exclusive
};

// there are some added elements here from the original GV - elements
// added just to make manipulation easier
//
// comments: a place to put general comments; which planet it was
// developed to be built on, special job, etc
//
// class: a way of grouping different designs, this field should be
// used in orders. For example: 
// scout0 1 0 0 0 0 class: flak
// flak   1 0 0 1 0 class: flak
// now orders can be given such as "scan planets that don't have class
// flak", etc
//
// cargo priorities: this is meant to help the automatic planet
// development code. you can, for example, design a 73 0 0 0 26 cargo
// ship that you only want to haul CAP around. You'd then set
// m_carryCOL = 0, m_carryCAP = 4, m_carryMAT = 0. If you wanted it to
// carry CAP unless it wasn't available you'd set m_carryCOL = 1,
// m_carryCAP = 4, m_carryMAT = 0. BTW: I envision radio buttons on
// the ship design form, not the user typing in numbers:
//      NEVER               ONLY
// CAP    O    O    O    O    O
// COL    O    O    O    O    O
// MAT    O    O    O    O    O
//
// program logic will have to ensure that all NEVERs don't get checked
// and that !>1 ONLYs get checked. It should be OK that any of the
// other three can be checked as it implies that anything can be
// carried. (in fact, checking any ONLY should autocheck the other two
// NEVERs)

#endif
