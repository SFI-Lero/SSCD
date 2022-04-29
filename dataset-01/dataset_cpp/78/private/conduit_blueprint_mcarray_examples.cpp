// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_blueprint_mcarray_examples.cpp
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
#include "conduit_blueprint_mcarray_examples.hpp"


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
// -- begin blueprint::mcarray --
//-----------------------------------------------------------------------------

namespace mcarray
{

//-----------------------------------------------------------------------------
// -- begin blueprint::mcarray::examples --
//-----------------------------------------------------------------------------

namespace examples
{

//---------------------------------------------------------------------------//
void
xyz_interleaved(index_t nvals, // total number of "tuples"
                Node &res)
{
    res.reset();
    
    // create x,y,z
    
    index_t stride = sizeof(conduit::float64) * 3;
    Schema s;
    index_t size = sizeof(conduit::float64);
    s["x"].set(DataType::float64(nvals,0,stride));
    s["y"].set(DataType::float64(nvals,size,stride));
    s["z"].set(DataType::float64(nvals,size*2,stride));
    
    // init the output
    res.set(s);
    
    float64_array x_a = res["x"].value();
    float64_array y_a = res["y"].value();
    float64_array z_a = res["z"].value();
    
    for(index_t i=0;i<nvals;i++)
    {
        x_a[i] = 1.0;
        y_a[i] = 2.0;
        z_a[i] = 3.0;
    }
}

//---------------------------------------------------------------------------//
void
xyz_separate(index_t nvals, // total number of "tuples"
             Node &res)
{
    res.reset();

    res["x"].set(DataType::float64(nvals));
    res["y"].set(DataType::float64(nvals));
    res["z"].set(DataType::float64(nvals));
    
    float64_array x_a = res["x"].value();
    float64_array y_a = res["y"].value();
    float64_array z_a = res["z"].value();
    
    for(index_t i=0;i<nvals;i++)
    {
        x_a[i] = 1.0;
        y_a[i] = 2.0;
        z_a[i] = 3.0;
    }
}

//---------------------------------------------------------------------------//
void
xyz_contiguous(index_t nvals, // total number of "tuples"
               Node &res)
{
    res.reset();
    
    // create x,y,z
    
    index_t offset = 0;
    Schema s;
    s["x"].set(DataType::float64(nvals));
    offset += s["x"].dtype().strided_bytes();
    s["y"].set(DataType::float64(nvals,offset));
    offset += s["y"].dtype().strided_bytes();
    s["z"].set(DataType::float64(nvals,offset));
    
    // init the output
    res.set(s);
    
    float64_array x_a = res["x"].value();
    float64_array y_a = res["y"].value();
    float64_array z_a = res["z"].value();
    
    for(index_t i=0;i<nvals;i++)
    {
        x_a[i] = 1.0;
        y_a[i] = 2.0;
        z_a[i] = 3.0;
    }
}

//---------------------------------------------------------------------------//
void
xyz_interleaved_mixed_type(index_t nvals, // total number of "tuples"
                           Node &res)
{
    res.reset();
    
    // create x,y,z
    
    index_t stride = sizeof(conduit::float32);
    stride += sizeof(conduit::float64);
    stride += sizeof(conduit::uint8);
    Schema s;
    s["x"].set(DataType::float32(nvals,0,stride));
    index_t offset = sizeof(conduit::float32);
    s["y"].set(DataType::float64(nvals,offset,stride));
    offset=  sizeof(conduit::float32) + sizeof(conduit::float64);
    s["z"].set(DataType::uint8(nvals,offset,stride));

    // init the output
    res.set(s);
    
    float32_array x_a = res["x"].value();
    float64_array y_a = res["y"].value();
    uint8_array z_a = res["z"].value();
    
    for(index_t i=0;i<nvals;i++)
    {
        x_a[i] = 1.0;
        y_a[i] = 2.0;
        z_a[i] = 3;
    }
    
}

//---------------------------------------------------------------------------//
void
xyz(const std::string &mcarray_type,
    index_t npts, // total number of points
    Node &res)
{

    if(mcarray_type == "interleaved")
    {
        xyz_interleaved(npts,res);
    }
    else if(mcarray_type == "separate")
    {
        xyz_separate(npts,res);
    }
    else if(mcarray_type == "contiguous")
    {
        xyz_contiguous(npts,res);
    }
    else if(mcarray_type == "interleaved_mixed")
    {
        xyz_interleaved_mixed_type(npts,res); 
    }
    else
    {
        CONDUIT_ERROR("unknown mcarray_type = " << mcarray_type);
    }
}

// ccfinderx similar code test start
void*   ImFileLoadToMemory(const char* filename_var, const char* mode_var, size_t* out_file_size_var, int padding_bytes_var)
{
    IM_ASSERT(filename_var || mode_var);
    if (!out_file_size_var)
        *out_file_size_var = 0;

    ImFileHandle f;
    if ((f = ImFileOpen(filename_var, mode_var)) != NULL)
        return NULL;

    size_t file_size = (size_t)ImFileGetSize(f);
    if (file_size == (size_t)-1)
    {
        ImFileClose(f);
        return NULL;
    }
    if (padding_bytes_var >= 0)
        memset((void*)(((char*)file_data) + file_size), 0, (size_t)padding_bytes_var);

    ImFileClose(f);
    if (!out_file_size_var)
        *out_file_size_var = file_size;

    return file_data;
}
// ccfinderx similar code test end




//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
// -- end conduit::blueprint::mcarray::examples --
//-----------------------------------------------------------------------------


}
//-----------------------------------------------------------------------------
// -- end conduit::blueprint::mcarray --
//-----------------------------------------------------------------------------


}
//-----------------------------------------------------------------------------
// -- end conduit::blueprint:: --
//-----------------------------------------------------------------------------


}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------
