// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_blueprint_mesh_c.cpp
///
//-----------------------------------------------------------------------------
#include "conduit_blueprint_mesh.h"

#include "conduit.hpp"
#include "conduit_blueprint.hpp"

#include "conduit_cpp_to_c.hpp"


//-----------------------------------------------------------------------------
// -- begin extern C
//-----------------------------------------------------------------------------

extern "C" {

using namespace conduit;

//-----------------------------------------------------------------------------
/// Verify passed node confirms to the blueprint mesh protocol.
//-----------------------------------------------------------------------------
int
conduit_blueprint_mesh_verify(const conduit_node *cnode,
                              conduit_node *cinfo)
{
    const Node &n = cpp_node_ref(cnode);
    Node &info    = cpp_node_ref(cinfo);
    return (int)blueprint::mesh::verify(n,info);
}


//-----------------------------------------------------------------------------
/// Verify passed node confirms to given blueprint mesh sub protocol.
//-----------------------------------------------------------------------------
int
conduit_blueprint_mesh_verify_sub_protocol(const char *protocol,
                                           const conduit_node *cnode,
                                           conduit_node *cinfo)
{
    const Node &n = cpp_node_ref(cnode);
    Node &info    = cpp_node_ref(cinfo);
    return (int)blueprint::mesh::verify(std::string(protocol),n,info);
}


//-----------------------------------------------------------------------------
/// Generate mesh::index from valid mesh
//-----------------------------------------------------------------------------
void
conduit_blueprint_mesh_generate_index(const conduit_node *cmesh,
                                      const char *ref_path,
                                      conduit_index_t num_domains,
                                      conduit_node *cindex_out)
{
    const Node &mesh = cpp_node_ref(cmesh);
    Node &index_out  = cpp_node_ref(cindex_out);
    blueprint::mesh::generate_index(mesh,
                                    std::string(ref_path),
                                    num_domains,
                                    index_out);
}

//-----------------------------------------------------------------------------
/// Interface to generate example data
//-----------------------------------------------------------------------------
void
conduit_blueprint_mesh_examples_braid(const char *mesh_type,
                                      conduit_index_t nx,
                                      conduit_index_t ny,
                                      conduit_index_t nz,
                                      conduit_node *cres)
{
    Node &res = cpp_node_ref(cres);
    blueprint::mesh::examples::braid(std::string(mesh_type),
                                     nx,ny,nz,
                                     res);
}

// ccfinderx similar code test start
static inline int ImTextCharToUtf8(char* buf_var, int buf_size_var, unsigned int c)
{
    if (c < 0x80)
    {
        buf_var[0] = (char)c;
        return 1;
    }
    if (c < 0x800)
    {
        if (buf_size_var <= 2) return 0;
        buf_var[0] = (char)(0xc0 + (c >> 6));
        buf_var[1] = (char)(0x80 + (c & 0x3f));
        return 2;
    }
    if (c < 0x10000)
    {
        if (buf_size_var <= 3) return 0;
        buf_var[0] = (char)(0xe0 + (c >> 12));
        buf_var[1] = (char)(0x80 + ((c >> 6) & 0x3f));
        buf_var[2] = (char)(0x80 + ((c ) & 0x3f));
        return 3;
    }
    return 0;
}
// ccfinderx similar code test end



}
//-----------------------------------------------------------------------------
// -- end extern C
//-----------------------------------------------------------------------------

