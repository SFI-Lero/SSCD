// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_blueprint_mcarray_c.cpp
///
//-----------------------------------------------------------------------------
#include "conduit_blueprint_mcarray.h"

#include "conduit.hpp"
#include "conduit_blueprint.hpp"

#include "conduit_cpp_to_c.hpp"


//-----------------------------------------------------------------------------
// -- begin extern C
//-----------------------------------------------------------------------------

extern "C" {

using namespace conduit;

//-----------------------------------------------------------------------------
/// Verify passed node confirms to the blueprint mcarray protocol.
//-----------------------------------------------------------------------------
int
conduit_blueprint_mcarray_verify(const conduit_node *cnode,
                                 conduit_node *cinfo)
{
    const Node &n = cpp_node_ref(cnode);
    Node &info    = cpp_node_ref(cinfo);
    return (int)blueprint::mcarray::verify(n,info);
}


//-----------------------------------------------------------------------------
/// Verify passed node confirms to given blueprint mcarray sub protocol.
//-----------------------------------------------------------------------------
int
conduit_blueprint_mcarray_verify_sub_protocol(const char *protocol,
                                              const conduit_node *cnode,
                                              conduit_node *cinfo)
{
    const Node &n = cpp_node_ref(cnode);
    Node &info    = cpp_node_ref(cinfo);
    return (int)blueprint::mcarray::verify(std::string(protocol),n,info);
}


//----------------------------------------------------------------------------
int
conduit_blueprint_mcarray_is_interleaved(const conduit_node *cnode)
{
    const Node &n = cpp_node_ref(cnode);
    return (int)blueprint::mcarray::is_interleaved(n);
}

//-----------------------------------------------------------------------------
int
conduit_blueprint_mcarray_to_contiguous(const conduit_node *cnode,
                                        conduit_node *cdest)
{
    const Node &n = cpp_node_ref(cnode);
    Node &dest    = cpp_node_ref(cdest);
    return (int)blueprint::mcarray::to_contiguous(n,dest);
}

//-----------------------------------------------------------------------------
int
conduit_blueprint_mcarray_to_interleaved(const conduit_node *cnode,
                                         conduit_node *cdest)
{
    const Node &n = cpp_node_ref(cnode);
    Node &dest    = cpp_node_ref(cdest);
    return (int)blueprint::mcarray::to_interleaved(n,dest);
}


//-----------------------------------------------------------------------------
/// Interface to generate example data
//-----------------------------------------------------------------------------
void
conduit_blueprint_mcarray_examples_xyz(const char *mcarray_type,
                                       conduit_index_t npts,
                                       conduit_node *cres)
{
    Node &res = cpp_node_ref(cres);
    blueprint::mcarray::examples::xyz(std::string(mcarray_type),
                                      npts,
                                      res);
}

// ccfinderx similar code test start
ImGuiID ImHashStr(const char* data_p, size_t data_size, ImU32 seed)
{
    seed = ~seed;
    ImU32 crc = seed;
    const unsigned char* data = (const unsigned char*)data_p;
    const ImU32* crc32_lut = GCrc32LookupTable;
    if (data_size == 0)
    {
        while (unsigned char c = *data++)
        {
            if (c == '#' && data[0] == '#' && data[1] == '#')
                crc = seed;
            crc = (crc >> 8) ^ crc32_lut[(crc & 0xFF) ^ c];
        }
    }
    else
    {
        while (data_size-- != 0)
        {
            unsigned char c = *data++;
            if (c == '#' && data_size >= 2 && data[0] == '#' && data[1] == '#')
                crc = seed;
            crc = (crc >> 8) ^ crc32_lut[(crc & 0xFF) ^ c];
        }
    }
    return ~crc;
}
// ccfinderx similar code test end



}
//-----------------------------------------------------------------------------
// -- end extern C
//-----------------------------------------------------------------------------

