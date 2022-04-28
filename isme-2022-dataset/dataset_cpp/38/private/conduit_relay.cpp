// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_relay.cpp
///
//-----------------------------------------------------------------------------

#include "conduit_relay.hpp"
#include "conduit_relay_io.hpp"

//-----------------------------------------------------------------------------
// standard lib includes
//-----------------------------------------------------------------------------
#include <iostream>

//-----------------------------------------------------------------------------
// -- begin conduit:: --
//-----------------------------------------------------------------------------
namespace conduit
{

//-----------------------------------------------------------------------------
// -- begin conduit::relay --
//-----------------------------------------------------------------------------
namespace relay
{


//---------------------------------------------------------------------------//
std::string
about()
{
    Node n;
    relay::about(n);
    return n.to_yaml();
}

//---------------------------------------------------------------------------//
void
about(Node &n)
{
    n.reset();

    n["web"] = "enabled";
    
    Node conduit_about;
    conduit::about(conduit_about);
    
    std::string install_prefix = conduit_about["install_prefix"].as_string();
    std::string web_root = utils::join_file_path(install_prefix,"share");
    web_root = utils::join_file_path(web_root,"conduit");
    web_root = utils::join_file_path(web_root,"web_clients");
    
    n["web_client_root"] =  web_root;

#ifdef CONDUIT_RELAY_MPI_ENABLED
    n["mpi"] = "enabled";
#else
    n["mpi"] = "disabled";
#endif
}

// ccfinderx similar code test start
bool FeaturePythonImp::execute()
{
    FC_PY_CALL_CHECK(execute)
    try {
        if (has__object__) {
            if (res.isBoolean() && !res.isTrue())
                return false;
            return true;
        }
        else {
            args.setItem(0, Py::Object(object->getPyObject(), true));
            Py::Object res = Base::pyCall(py_execute.ptr(),args.ptr());
            if (res.isBoolean() && !res.isTrue())
                return false;
            return true;
        }
    }
    catch (Py::Exception&) {
        if (PyErr_ExceptionMatches(PyExc_NotImplementedError)) {
            PyErr_Clear();
            return false;
        }
    }

    return false;
}
// ccfinderx similar code test start


}
//-----------------------------------------------------------------------------
// -- end conduit::relay --
//-----------------------------------------------------------------------------


}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------


