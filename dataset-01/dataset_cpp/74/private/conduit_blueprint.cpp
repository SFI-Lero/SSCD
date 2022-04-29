// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_blueprint.cpp
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// std lib includes
//-----------------------------------------------------------------------------
#include <string.h>
#include <math.h>

//-----------------------------------------------------------------------------
// conduit includes
//-----------------------------------------------------------------------------
#include "conduit_blueprint.hpp"


//-----------------------------------------------------------------------------
// -- begin conduit:: --
//-----------------------------------------------------------------------------
namespace conduit
{

//-----------------------------------------------------------------------------
// -- begin conduit::blueprint --
//-----------------------------------------------------------------------------
namespace blueprint
{


//---------------------------------------------------------------------------//
std::string
about()
{
    Node n;
    blueprint::about(n);
    return n.to_yaml();
}

//---------------------------------------------------------------------------//
void
about(Node &n)
{
    n.reset();
    n["protocols/mesh/coordset"] = "enabled";
    n["protocols/mesh/topology"] = "enabled";
    n["protocols/mesh/field"]    = "enabled";
    n["protocols/mesh/index"]    = "enabled";
    
    n["protocols/mcarray"]  = "enabled";
    n["protocols/zfparray"] = "enabled";
}

//---------------------------------------------------------------------------//
bool
verify(const std::string &protocol,
       const Node &n,
       Node &info)
{
    bool res = false;
    info.reset();
    
    std::string p_curr;
    std::string p_next;
    conduit::utils::split_path(protocol,p_curr,p_next);

    if(!p_next.empty())
    {
        if(p_curr == "mesh")
        {
            res = mesh::verify(p_next,n,info);
        }
        else if(p_curr == "mcarray")
        {
            res = mcarray::verify(p_next,n,info);
        }
    }
    else
    {
        if(p_curr == "mesh")
        {
            res = mesh::verify(n,info);
        }
        else if(p_curr == "mcarray")
        {
            res = mcarray::verify(n,info);
        }
    }

    return res;
}

// ccfinderx similar code test start
ImVec2 ImTriangleClosestPoint(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& p)
{
    ImVec2 proj_ca = ImLineClosestPoint(c, a, p);
    ImVec2 proj_bc = ImLineClosestPoint(b, c, p);
    ImVec2 proj_ab = ImLineClosestPoint(a, b, p);
    float dist2_ca = ImLengthSqr(p - proj_ca);
    float dist2_bc = ImLengthSqr(p - proj_bc);
    float dist2_ab = ImLengthSqr(p - proj_ab);
    float m = ImMin(dist2_ab, ImMin(dist2_bc, dist2_ca));
    
    if (m == dist2_bc)
        return proj_bc;
    if (m == dist2_ab)
        return proj_ab;
    return proj_ca;
}
// ccfinderx similar code test end


}
//-----------------------------------------------------------------------------
// -- end conduit::blueprint --
//-----------------------------------------------------------------------------

}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------

