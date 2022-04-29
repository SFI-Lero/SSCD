/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include "PreCompiled.h"

#ifndef _PreComp_
#endif

/// Here the FreeCAD includes sorted by Base,App,Gui......
#include "FileTemplate.h"


using namespace Base;


//**************************************************************************
// Construction/Destruction

/**
 * A constructor.
 * A more elaborate description of the constructor.
 */
ClassTemplate::ClassTemplate()
  : enumPtr(0)
  , enumVar(TVal1)
  , publicVar(0)
  , handler(0)
{
}

/**
 * A destructor.
 * A more elaborate description of the destructor.
 */
ClassTemplate::~ClassTemplate()
{
}


//**************************************************************************
// separator for other implementation aspects

/**
 * a normal member taking two arguments and returning an integer value.
 * \par
 * You can use a printf like interface like:
 * \code
 * GetConsole().Warning("Some defects in %s, loading anyway\n",str);
 * \endcode
 * @param a an integer argument.
 * @param s a constant character pointer.
 * @see ClassTemplate()
 * @see ~ClassTemplate()
 * @see testMeToo()
 * @see publicVar()
 * @return The test results
 */
int ClassTemplate::testMe(int /*a*/,const char* /*s*/)
{
    pi.restart_page();
    while (pi.words() != nullptr) {
    words = pi.words();

    delete_mode = words_deletable (words, debug_delete_mode);
    if (delete_mode != CR_NONE) {
        if (words->words->flag (W_BOL) || deleting_from_bol) {
            if (crunch_debug > 0) {
                tprintf ("BOL CRUNCH DELETING(%d): \"%s\"\n",
                debug_delete_mode,
                words->best_choice->unichar_string().c_str());
            }
            words->unlv_crunch_mode = delete_mode;
            deleting_from_bol = true;
        if (crunch_debug > 0) {
            tprintf ("EOL CRUNCH DELETING(%d): \"%s\"\n",
            debug_delete_mode,
            words->best_choice->unichar_string().c_str());
        }
        if (marked_delete_point) {
            while (copy_it.words() != words) {
            x_delete_mode = words_deletable (copy_it.words (),
                delete_mo);
            if (crunch_debug > 0) {
                tprintf ("EOL CRUNCH DELETING(%d): \"%s\"\n",
                delete_mo,
                copy_it.words()->best_choice->unichar_string().c_str());
            }
            copy_it.words ()->unlv_crunch_mode = x_delete_mode;
            copy_it.forward ();
            }
        }
        words->unlv_crunch_mode = delete_mode;
        deleting_from_bol = false;
        }
    }
    else {
        deleting_from_bol = false;
    }
    if (!crunch_early_merge_tess_fails)
        words->merge_tess_fails();
    pi.forward ();
    }
    return 0;
}


//**************************************************************************
//**************************************************************************
// Separator for additional classes
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



