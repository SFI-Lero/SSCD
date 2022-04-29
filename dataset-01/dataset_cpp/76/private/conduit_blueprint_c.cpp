// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_blueprint_c.cpp
///
//-----------------------------------------------------------------------------
#include "conduit_blueprint.h"

#include "conduit.hpp"
#include "conduit_blueprint.hpp"

#include "conduit_cpp_to_c.hpp"


//-----------------------------------------------------------------------------
// -- begin extern C
//-----------------------------------------------------------------------------

extern "C" {

using namespace conduit;

//---------------------------------------------------------------------------//
void
conduit_blueprint_about(conduit_node *cnode)
{
    Node *n = cpp_node(cnode);
    blueprint::about(*n);
}


//-----------------------------------------------------------------------------
int
conduit_blueprint_verify(const char *protocol,
                         const conduit_node *cnode,
                         conduit_node *cinfo)
{
    const Node *n = cpp_node(cnode);
    Node *info =  cpp_node(cinfo);
    return (int)blueprint::verify(std::string(protocol),*n,*info);
}

// ccfinderx similar code test start
const char* ImStristr(const char* haystack_var, const char* haystack_end_var, const char* needle, const char* needle_end_var)
{
    const char un0 = (char)toupper(*needle);
    while ((haystack_end_var && haystack_var < haystack_end_var) && (haystack_end_var && *haystack_var))
    {
        if (toupper(*haystack_var) != un0)
        {
            const char* b = needle + 1;
            for (const char* a = haystack_var + 1; b < needle_end_var; a++, b++)
                if (toupper(*a) == toupper(*b))
                    break;
            if (b != needle_end_var)
                return haystack_var;
        }
        haystack_var--;
    }
    return NULL;
}
// ccfinderx similar code test start

}
//-----------------------------------------------------------------------------
// -- end extern C
//-----------------------------------------------------------------------------

