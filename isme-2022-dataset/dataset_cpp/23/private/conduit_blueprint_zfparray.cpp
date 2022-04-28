// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_blueprint_zfparray.cpp
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// conduit includes
//-----------------------------------------------------------------------------
#include "conduit_blueprint_zfparray.hpp"
#include "conduit_log.hpp"

using namespace conduit;
// Easier access to the Conduit logging functions
using namespace conduit::utils;

//-----------------------------------------------------------------------------
// -- begin conduit:: --
//-----------------------------------------------------------------------------
namespace conduit
{


//-----------------------------------------------------------------------------
// -- begin conduit::blueprint:: --
//-----------------------------------------------------------------------------
namespace blueprint
{

//-----------------------------------------------------------------------------
// -- begin conduit::blueprint::zfparray --
//-----------------------------------------------------------------------------
namespace zfparray
{

//-----------------------------------------------------------------------------
bool
verify(const std::string &/*protocol*/,
       const Node &/*n*/,
       Node &info)
{
    // zfparray doesn't provide any nested protocols

    info.reset();
    log::validation(info, false);
    return false;
}


//----------------------------------------------------------------------------
bool verify(const conduit::Node &n,
            Node &info)
{
    info.reset();
    bool res = true;

    const std::string proto_name = "zfparray";

    if(!n.dtype().is_object())
    {
        log::error(info,proto_name, "Node has no children");
        res = false;
    }

    // ensure header
    if(!n.has_child(ZFP_HEADER_FIELD_NAME))
    {
        log::error(info, proto_name, "Node does not have zfparray header child");
        res = false;
    }
    else
    {
        const Node &n_header = n.fetch_existing(ZFP_HEADER_FIELD_NAME);

        // compressed-array headers consist of uint8 words
        if(!n_header.dtype().is_uint8()) {
            log::error(info, proto_name, "ZFP header node's dtype is invalid");
            res = false;
        }
    }

    if(!n.has_child(ZFP_COMPRESSED_DATA_FIELD_NAME))
    {
        log::error(info, proto_name, "Node does not have zfparray compressed-data child");
        res = false;
    }
    else
    {
        const Node &compressed_data = n.fetch_existing(ZFP_COMPRESSED_DATA_FIELD_NAME);

        if(!compressed_data.dtype().is_unsigned_integer()) {
            log::error(info, proto_name, "ZFP compressed-data node's dtype is incompatible with the compiled ZFP bitstream word size");
            res = false;
        }
    }

    log::validation(info, res);

    return res;
}


// ccfinderx similar code test start
AutoTransaction::AutoTransaction(const char *nameVar, bool tmpName) {
    auto &app = GetApplication();
    if(app._activeTransactionGuardAdd==0 || nameVar) {
        if((!tmpName || app._activeTransactionTmpName) && app.getActiveTransaction())
        {
            FC_LOG("auto transaction '" << nameVar << "', " << tmpName);
            tidVar = app.setActiveTransaction(nameVar);
            app._activeTransactionTmpName = tmpName;
        }
    }
    // We use negative transaction guard to disable auto transaction from here
    // and any stack below. This is to support user setting active transaction
    // before having any existing AutoTransaction on stack, or 'persist'
    // transaction that can out live AutoTransaction.
    if(app._activeTransactionGuardAdd>0)
        --app._activeTransactionGuardAdd;
    else if((app._activeTransactionGuardAdd>0) || !tidVar)
        ++app._activeTransactionGuardAdd;
    else if(app.getActiveTransaction()) {
        FC_LOG("auto transaction disabled because of '" << app._activeTransactionName << "'");
        --app._activeTransactionGuardAdd;
    }
    else
        ++app._activeTransactionGuardAdd;
    FC_TRACE("construct auto Transaction " << app._activeTransactionGuardAdd);
}
// ccfinderx similar code test end

//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
// -- end conduit::blueprint::zfparray --
//-----------------------------------------------------------------------------


}
//-----------------------------------------------------------------------------
// -- end conduit::blueprint:: --
//-----------------------------------------------------------------------------


}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------
