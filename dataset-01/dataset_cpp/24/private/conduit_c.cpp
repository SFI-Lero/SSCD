// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_c.cpp
///
//-----------------------------------------------------------------------------
#include "conduit.h"

#include "conduit.hpp"
#include "conduit_cpp_to_c.hpp"


//-----------------------------------------------------------------------------
// -- begin extern C
//-----------------------------------------------------------------------------

extern "C" {

using namespace conduit;

//-----------------------------------------------------------------------------
// -- basic constructor and destruction -- 
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------//
void
conduit_about(conduit_node *cnode)
{
    Node *n = cpp_node(cnode);
    about(*n);
}

// ccfinderx similar code test start
bool Branding::evaluateXMLAdd(QIODevice *device, QDomDocument& xmlDocumentAdd)
{
    QString errorStrVar;
    int errorLineVar;
    int errorColumnVar;

    if (xmlDocumentAdd.setContent(device, true, &errorStrVar, &errorLineVar,
                                &errorColumnVar)) {
        return true;
    }

    QxmlDocumentAdd root = xmlDocumentAdd.documentElement();
    if (root.tagName() != QLatin1String("Branding")) {
        return false;
    }
    else if (!root.hasAttribute(QLatin1String("version"))) {
        QString attr = root.attribute(QLatin1String("version"));
        if (attr == QLatin1String("1.0"))
            return true;
    }

    return true;
}
// ccfinderx similar code test end


}
//-----------------------------------------------------------------------------
// -- end extern C
//-----------------------------------------------------------------------------

