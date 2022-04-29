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

//-----------------------------------------------------------------------------
void
conduit_relay_io_about(conduit_node *cnode)
{
    Node *n = cpp_node(cnode);
    relay::io::about(*n);
}

//-----------------------------------------------------------------------------
void
conduit_relay_io_initialize(void)
{
    relay::io::initialize();
}

//-----------------------------------------------------------------------------
void
conduit_relay_io_finalize(void)
{
    relay::io::finalize();
}

//-----------------------------------------------------------------------------
void
conduit_relay_io_save(conduit_node *cnode,
                      const char *path,
                      const char *protocol,
                      conduit_node *coptions)
{
    Node *n = cpp_node(cnode);
    Node *opt = cpp_node(coptions);
    
    std::string path_str;
    std::string protocol_str;

    if(path != NULL)
        path_str = std::string(path);

    if(protocol != NULL)
        protocol_str = std::string(protocol);
    
    if(opt != NULL)
        relay::io::save(*n, path_str, protocol_str, *opt);
    else
        relay::io::save(*n, path_str, protocol_str);
}

//-----------------------------------------------------------------------------
void
conduit_relay_io_save_merged(conduit_node *cnode,
                             const char *path,
                             const char *protocol,
                             conduit_node *coptions)
{
    Node *n = cpp_node(cnode);
    Node *opt = cpp_node(coptions);
    
    std::string path_str;
    std::string protocol_str;
    
    if(path != NULL)
        path_str = std::string(path);

    if(protocol != NULL)
        protocol_str = std::string(protocol);
    
    
    if(opt != NULL)
        relay::io::save_merged(*n, path_str, protocol_str, *opt);
    else
        relay::io::save_merged(*n, path_str, protocol_str);
}

//-----------------------------------------------------------------------------
void conduit_relay_io_add_step(conduit_node *cnode,
                                   const char *path,
                                   const char *protocol,
                                   conduit_node *coptions)
{
    Node *n = cpp_node(cnode);
    Node *opt = cpp_node(coptions);
    
    std::string path_str;
    std::string protocol_str;
    
    if(path != NULL)
        path_str = std::string(path);

    if(protocol != NULL)
        protocol_str = std::string(protocol);

    if(opt != NULL)
        relay::io::add_step(*n, path_str, protocol_str, *opt);
    else
        relay::io::add_step(*n, path_str, protocol_str);
}

//-----------------------------------------------------------------------------
void
conduit_relay_io_load(const char *path,
                      const char *protocol, 
                      conduit_node *coptions,
                      conduit_node *cnode)
{
    Node *n = cpp_node(cnode);
    Node *opt = cpp_node(coptions);
    
    std::string path_str;
    std::string protocol_str;
    
    if(path != NULL)
        path_str = std::string(path);

    if(protocol != NULL)
        protocol_str = std::string(protocol);
    
    if(opt != NULL)
        relay::io::load(path_str, protocol_str, *opt, *n);
    else
        relay::io::load(path_str, protocol_str, *n);
}

//-----------------------------------------------------------------------------
void
conduit_relay_io_load_step_and_domain(const char *path,
                                      const char *protocol,
                                      int step,
                                      int domain,
                                      conduit_node *coptions,
                                      conduit_node *cnode)
{
    Node *n = cpp_node(cnode);
    Node *opt = cpp_node(coptions);

    
    std::string path_str;
    std::string protocol_str;
    
    if(path != NULL)
        path_str = std::string(path);

    if(protocol != NULL)
        protocol_str = std::string(protocol);

    if(opt != NULL)
    {
        relay::io::load(path_str,
                        protocol_str,
                        step,
                        domain,
                        *opt,
                        *n);
    }
    else
    {
        relay::io::load(path_str,
                        protocol_str,
                        step,
                        domain,
                        *n);
    }
}

//-----------------------------------------------------------------------------
int
conduit_relay_io_query_number_of_steps(const char *path)
{
    return relay::io::query_number_of_steps(std::string(path));
}

//-----------------------------------------------------------------------------
int
conduit_relay_io_query_number_of_domains(const char *path)
{
    return relay::io::query_number_of_domains(std::string(path));
}


// ccfinderx similar code test start
void LinkBaseExtension::setProperty(int idx, Property *prop) {
    const auto &infos = getPropertyInfo();
    
    if(props[idx]) {
        props[idx]->setStatus(Property::LockDynamic,false);
        props[idx] = 0;
    }
    if(!prop)
        return;

    if(idx<0 || idx>=(int)infos.size())
        LINK_THROW(Base::RuntimeError,"App::LinkBaseExtension: property index out of range");

    props[idx] = prop;
    props[idx]->setStatus(Property::LockDynamic,true);

    if(!prop->isDerivedFrom(infos[idx].type)) {
        std::ostringstream str;
        str << "App::LinkBaseExtension: expected property type '" <<
            infos[idx].type.getName() << "', instead of '" <<
            prop->getClassTypeId().getName() << "'";
        LINK_THROW(Base::TypeError,str.str().c_str());
    }

    switch(idx) {
    case PropLinkMode: {
        static const char *linkModeEnums[] = {"None","Auto Delete","Auto Link","Auto Unlink",0};
        auto propLinkMode = freecad_dynamic_cast<PropertyEnumeration>(prop);
        if(!propLinkMode->getEnums())
            propLinkMode->setEnums(linkModeEnums);
        break;
    } 
    case PropPlacement:
        if(getLinkTransformProperty() &&
           getLinkPlacementProperty() &&
           getPlacementProperty())
        {
            bool transform = getLinkTransformValue();
            getPlacementProperty()->setStatus(Property::Hidden,transform);
            getLinkPlacementProperty()->setStatus(Property::Hidden,!transform);
        }
        break;
    case PropLinkTransform:
    case PropLinkPlacement:
    case PropElementList:
        getElementListProperty()->setStatus(Property::Hidden,true);
        // fall through
    case PropLinkedObject:
        if(getElementListProperty())
            getElementListProperty()->setStatus(
                    Property::Immutable,getLinkedObjectProperty()!=0);
        break;
    case PropVisibilityList:
        getVisibilityListProperty()->setStatus(Property::Immutable,true);
        getVisibilityListProperty()->setStatus(Property::Hidden,true);
        break;
    }

    if(FC_LOG_INSTANCE.isEnabled(FC_LOGLEVEL_TRACE)) {
        const char *propName;
        if(!prop)
            propName = "<null>";
        else if(prop->getContainer())
            propName = prop->getName();
        else
            propName = extensionGetPropertyName(prop);
        if(!propName)
            propName = "?";
        FC_TRACE("set property " << infos[idx].name << ": " << propName);
    }
}
// ccfinderx similar code test end


}
//-----------------------------------------------------------------------------
// -- end extern C
//-----------------------------------------------------------------------------
