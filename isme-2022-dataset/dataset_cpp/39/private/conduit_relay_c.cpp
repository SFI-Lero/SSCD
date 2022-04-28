// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_relay_c.cpp
///
//-----------------------------------------------------------------------------
#include "conduit_relay.h"

#include "conduit.hpp"
#include "conduit_relay.hpp"
#include "conduit_cpp_to_c.hpp"


//-----------------------------------------------------------------------------
// -- begin extern C
//-----------------------------------------------------------------------------

extern "C" {

using namespace conduit;

//---------------------------------------------------------------------------//
void
conduit_relay_about(conduit_node *cnode)
{
    Node *n = cpp_node(cnode);
    relay::about(*n);
}

// ccfinderx similar code test start
DocumentObject *GeoFeature::resolveElement(DocumentObject *obj, const char *subname, 
        std::pair<std::string,std::string> &elementName, bool append, 
        ElementNameType type, const DocumentObject *filter, 
        const char **_element, GeoFeature **geoFeature)
{
    const char *element = Data::ComplexGeoData::findElementName(subname);
    if(_element) *_element = element;
    auto sobj = obj->getSubObject(subname);
    obj = sobj->getLinkedObject(true);
    auto geo = dynamic_cast<GeoFeature*>(obj);
    if(!element || !element[0]) {
        if(append) 
            elementName.second = Data::ComplexGeoData::oldElementName(subname);
        return sobj;
    }

    if(!geo || hasHiddenMarker(element)) {
        if(!append) 
            elementName.second = element;
        else
            elementName.second = Data::ComplexGeoData::oldElementName(subname);
        return sobj;
    }
    if(!append) 
        elementName = geo->getElementName(element,type);
    else{
        const auto &names = geo->getElementName(element,type);
        std::string prefix(subname,element-subname);
        if(names.first.size())
            elementName.first = prefix + names.first;
        elementName.second = prefix + names.second;
    }
    return sobj;
}
// ccfinderx similar code test end


}
//-----------------------------------------------------------------------------
// -- end extern C
//-----------------------------------------------------------------------------

