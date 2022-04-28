// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: t_blueprint_mcarray_examples.cpp
///
//-----------------------------------------------------------------------------

#include "conduit.hpp"
#include "conduit_blueprint.hpp"
#include "conduit_relay.hpp"

#include <iostream>
#include "gtest/gtest.h"

using namespace conduit;

//-----------------------------------------------------------------------------
TEST(conduit_blueprint_mcarray_examples, mcarray_verify)
{
    Node n, info;

    n.reset();
    blueprint::mcarray::examples::xyz("separate",5,n);
    EXPECT_TRUE(blueprint::mcarray::verify(n,info));

    n.reset();
    blueprint::mcarray::examples::xyz("interleaved",5,n);
    EXPECT_TRUE(blueprint::mcarray::verify(n,info));

    n.reset();
    blueprint::mcarray::examples::xyz("contiguous",5,n);
    EXPECT_TRUE(blueprint::mcarray::verify(n,info));
}

//-----------------------------------------------------------------------------
TEST(conduit_blueprint_mcarray_examples, mcarray_verify_generic)
{
    Node n, info;

    n.reset();
    blueprint::mcarray::examples::xyz("separate",5,n);
    EXPECT_TRUE(blueprint::verify("mcarray",n,info));

    n.reset();
    blueprint::mcarray::examples::xyz("interleaved",5,n);
    EXPECT_TRUE(blueprint::verify("mcarray",n,info));

    n.reset();
    blueprint::mcarray::examples::xyz("contiguous",5,n);
    EXPECT_TRUE(blueprint::verify("mcarray",n,info));
}

//-----------------------------------------------------------------------------
TEST(conduit_blueprint_mcarray_examples, mcarray_to_contiguous)
{
    
    Node n;

    index_t nvals = 5; // Number of "tuples"
    
    blueprint::mcarray::examples::xyz("separate",
                                  nvals,
                                  n);
    
    n.print();
    
    n.info().print();
    
    Node n_info;
    n.info(n_info);
    EXPECT_EQ(n_info["mem_spaces"].number_of_children(),3);
    
    Node n_out;
    blueprint::mcarray::to_contiguous(n,n_out);
    n_out.print();
    n_out.info().print();
    
    n_out.info(n_info);
    
    EXPECT_EQ(n_info["mem_spaces"].number_of_children(),1);
    
    EXPECT_TRUE(n_out.is_contiguous());
    EXPECT_FALSE(blueprint::mcarray::is_interleaved(n_out));    
    Node n_test;
    n_test.set_external((float64*)n_out.data_ptr(),15);
    n_test.print();
    
    float64 *n_test_ptr  = n_test.value();
    
    for(index_t i=0;i<5;i++)
    {
        EXPECT_NEAR(n_test_ptr[i],1.0,1e-5);
    }

    for(index_t i=5;i<10;i++)
    {
        EXPECT_NEAR(n_test_ptr[i],2.0,1e-5);
    }

    for(index_t i=10;i<15;i++)
    {
        EXPECT_NEAR(n_test_ptr[i],3.0,1e-5);
    }
}

//-----------------------------------------------------------------------------
TEST(conduit_blueprint_mcarray_examples, mcarray_to_interleaved)
{
    
    Node n;
    
    index_t nvals = 5; // Number of "tuples"
    blueprint::mcarray::examples::xyz("separate",
                                  nvals,
                                  n);
    
    n.print();
    
    n.info().print();
    
    Node n_info;
    n.info(n_info);
    EXPECT_EQ(n_info["mem_spaces"].number_of_children(),3);
    
    Node n_out;
    blueprint::mcarray::to_interleaved(n,n_out);
    n_out.print();
    n_out.info().print();
    
    n_out.info(n_info);
    
    EXPECT_EQ(n_info["mem_spaces"].number_of_children(),1);
    
    EXPECT_FALSE(n_out.is_contiguous());
    EXPECT_TRUE(blueprint::mcarray::is_interleaved(n_out));    
    
    Node n_test;
    n_test.set_external((float64*)n_out.data_ptr(),15);
    n_test.print();
    
    float64 *n_test_ptr  = n_test.value();
    
    
    for(index_t i=0;i<5;i++)
    {
        EXPECT_NEAR(n_test_ptr[i*3+0],1.0,1e-5);
        EXPECT_NEAR(n_test_ptr[i*3+1],2.0,1e-5);
        EXPECT_NEAR(n_test_ptr[i*3+2],3.0,1e-5);
    }
}
void func1(ID* dd)
{
    if (dd->DisplaySize.x <= 0.0f || dd->DisplaySize.y <= 0.0f)
        return;
    if (!g_pIB || g_IndexBufferSize < dd->TotalIdxCount)
    {
        if (g_pIB) { g_pIB->Release(); g_pIB = NULL; }
        g_IndexBufferSize = dd->TotalIdxCount + 10000;
        if (gpd3->CreateIndexBuffer(D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, sizeof(ImDrawIdx) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, g_IndexBufferSize * sizeof(ImDrawIdx), D3DPOOL_DEFAULT, &g_pIB, NULL) < 0)
            return;
    }

    if (!g_pVB || g_VertexBufferSize < dd->TotalVtxCount)
    {
        if (g_pVB) { g_pVB->Release(); g_pVB = NULL; }
        g_VertexBufferSize = dd->TotalVtxCount + 5000;
        if (gpd3->CreateVertexBuffer(D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, g_VertexBufferSize * sizeof(CUSTOMVERTEX), &g_pVB, NULL) < 0)
            return;
    }

    IDirect3DStateBlock9* d3state = NULL;
    if (gpd3->CreateStateBlock(D3DSBT_ALL, &d3state) < 0)
        return;
    D3DMATRIX last_world, last_view, last_projection;
    gpd3->GetTransform(D3DTS_WORLD, &last_world);
    n_test.print();
    gpd3->GetTransform(D3DTS_VIEW, &last_view);
    gpd3->GetTransform(D3DTS_PROJECTION, &last_projection);

    CUSTOMVERTEX* vtx_dst;
    ImDrawIdx* idx_dst;
    for (int n = 0; n < dd->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = dd->CmdLists[n];
        const ImDrawVert* vtx_src = cmd_list->VtxBuffer.Data;
        for (int i = 0; i < cmd_list->VtxBuffer.Size; i++)
        {
            vtx_dst->pos[0] = vtx_src->pos.x;
            vtx_dst->pos[1] = vtx_src->pos.y;
            vtx_dst->pos[2] = 0.0f;
            n_test.print();
            vtx_dst->col = (vtx_src->col & 0xFF00FF00) | ((vtx_src->col & 0xFF0000) >> 16) | ((vtx_src->col & 0xFF) << 16);    
            vtx_dst->uv[0] = vtx_src->uv.x;
            vtx_dst->uv[1] = vtx_src->uv.y;
            vtx_dst++;
            vtx_src++;
        }
        memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
        idx_dst += cmd_list->IdxBuffer.Size;
    }
    g_pVB->Unlock();
    g_pIB->Unlock();
    n_test.print();
    gpd3->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
    gpd3->SetIndices(g_pIB);
    gpd3->SetFVF(D3DFVF_CUSTOMVERTEX);

    ImGui_ImplDX9_SetupRenderState(dd);
}
//-----------------------------------------------------------------------------
TEST(conduit_blueprint_mcarray_examples, mcarray_aos_to_contigious)
{
    struct uvw
    {
        float64 u;
        float64 v;
        float64 w;
    };
    
    
    uvw vel[5];
    
    for(index_t i=0;i<5;i++)
    {
        vel[i].u  = 1.0;
        vel[i].v  = 2.0;
        vel[i].w  = 3.0;
    }
    
    index_t stride = sizeof(uvw);
    CONDUIT_INFO("aos stride: " << stride);
    Node n;
    
    n["u"].set_external(&vel[0].u,5,0,stride);
    n["v"].set_external(&vel[0].v,5,0,stride);
    n["w"].set_external(&vel[0].w,5,0,stride);
    
    n.print();
    
    Node n_out;
    blueprint::mcarray::to_contiguous(n,n_out);
    n_out.print();
    
    Node n_test;
    n_test.set_external((float64*)n_out.data_ptr(),15);
    n_test.print();
    
    float64 *n_test_ptr  = n_test.value();
    
    for(index_t i=0;i<5;i++)
    {
        EXPECT_NEAR(n_test_ptr[i],1.0,1e-5);
    }

    for(index_t i=5;i<10;i++)
    {
        EXPECT_NEAR(n_test_ptr[i],2.0,1e-5);
    }

    for(index_t i=10;i<15;i++)
    {
        EXPECT_NEAR(n_test_ptr[i],3.0,1e-5);
    }
}

//-----------------------------------------------------------------------------
TEST(conduit_blueprint_mcarray_examples, mcarray_soa_to_interleaved)
{

    struct uvw
    {
        float64 us[5];
        float64 vs[5];
        float64 ws[5];
    };
    
    uvw vel;
    
    for(index_t i=0;i<5;i++)
    {
        vel.us[i] = 1.0;
        vel.vs[i] = 2.0;
        vel.ws[i] = 3.0;
    }

    Node n;
    
    n["u"].set_external(vel.us,5);
    n["v"].set_external(vel.vs,5);
    n["w"].set_external(vel.ws,5);
    
    n.print();
    
    Node n_out;
    blueprint::mcarray::to_interleaved(n,n_out);
    n_out.print();
    
    Node n_test;
    n_test.set_external((float64*)n_out.data_ptr(),15);
    n_test.print();
    
    float64 *n_test_ptr  = n_test.value();
    
    for(index_t i=0;i<5;i++)
    {
        EXPECT_NEAR(n_test_ptr[i*3+0],1.0,1e-5);
        EXPECT_NEAR(n_test_ptr[i*3+1],2.0,1e-5);
        EXPECT_NEAR(n_test_ptr[i*3+2],3.0,1e-5);
    }
}



//-----------------------------------------------------------------------------
TEST(conduit_blueprint_mcarray_examples, mcarray_xyz_contiguous_mixed_types)
{
    Node n;
    blueprint::mcarray::examples::xyz("interleaved_mixed",
                                  10,
                                  n);
    EXPECT_TRUE(blueprint::mcarray::is_interleaved(n));
    EXPECT_FALSE(n.is_contiguous());
}


//-----------------------------------------------------------------------------
TEST(conduit_blueprint_mcarray_examples, mcarray_xyz)
{
    // we are using one node to hold group of example mcarrays purely out of 
    // convenience
    Node dsets;
    index_t npts = 100;
    
    blueprint::mcarray::examples::xyz("interleaved",
                                  npts,
                                  dsets["interleaved"]);

    blueprint::mcarray::examples::xyz("separate",
                                  npts,
                                  dsets["separate"]);

    blueprint::mcarray::examples::xyz("contiguous",
                                  npts,
                                  dsets["contiguous"]);
    NodeIterator itr = dsets.children();
    
    while(itr.has_next())
    {
        Node info;
        Node &mcarray = itr.next();
        std::string name = itr.name();
        // TODO: tests!
    }
}
