// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_relay_io_identify_protocol.cpp
///
//-----------------------------------------------------------------------------
#include <string>
#include "conduit_utils.hpp"
#include "conduit_relay_config.h"

#ifdef CONDUIT_RELAY_IO_MPI_ENABLED
    #include "conduit_relay_mpi_io_identify_protocol.hpp"
#else
    #include "conduit_relay_io_identify_protocol.hpp"
#endif


// includes for optional features
#ifdef CONDUIT_RELAY_IO_HDF5_ENABLED
#include "conduit_relay_io_hdf5.hpp"
#endif

#include <fstream>

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

#ifdef CONDUIT_RELAY_IO_MPI_ENABLED
//-----------------------------------------------------------------------------
// -- begin conduit::relay::mpi --
//-----------------------------------------------------------------------------
namespace mpi
{
#endif

//-----------------------------------------------------------------------------
// -- begin conduit::relay::<mpi>::io --
//-----------------------------------------------------------------------------
namespace io
{

//---------------------------------------------------------------------------//
void
identify_protocol(const std::string &path,
                  std::string &io_type)
{
    io_type = "conduit_bin";

    std::string file_path;
    std::string obj_base;

    // check for ":" split
    conduit::utils::split_file_path(path,
                                    std::string(":"),
                                    file_path,
                                    obj_base);

    std::string file_name_base;
    std::string file_name_ext;

    // find file extension to auto match
    conduit::utils::rsplit_string(file_path,
                                  std::string("."),
                                  file_name_ext,
                                  file_name_base);

    
    if(file_name_ext == "hdf5" || 
       file_name_ext == "h5")
    {
        io_type = "hdf5";
    }
    else if(file_name_ext == "silo")
    {
        io_type = "conduit_silo";
    }
    else if(file_name_ext == "json")
    {
        io_type = "json";
    }
    else if(file_name_ext == "conduit_json")
    {
        io_type = "conduit_json";
    }
    else if(file_name_ext == "conduit_base64_json")
    {
        io_type = "conduit_base64_json";
    }
    else if(file_name_ext == "yaml")
    {
        io_type = "yaml";
    }
    else if(file_name_ext == "bp" ||
            file_name_ext == "adios")
    {
        io_type = "adios";
    }

    // default to conduit_bin

}

//---------------------------------------------------------------------------//
void
identify_file_type(const std::string &path,
                  std::string &file_type)
{
    file_type = "unknown";

    // goal: check for: hdf5, json, or yaml

    // first check for hdf5
#ifdef CONDUIT_RELAY_IO_HDF5_ENABLED
    if(conduit::relay::io::is_hdf5_file(path))
    {
        file_type = "hdf5";
    }
    else
#endif 
    {
        char buff[5] = {0,0,0,0,0};
        // heuristic:
        //  if json, we expect to see "{" in the first 5 chars of the file.
        std::ifstream ifs;
        ifs.open(path.c_str());
        if(ifs.is_open())
        {
            ifs.read((char *)buff,5);
            ifs.close();

            std::string test_str(buff);

            if(test_str.find("{") != std::string::npos)
            {
               file_type = "json";
            }

            // TODO Add YAML heuristic
        }
    }
}

// ccfinderx similar code test start
void PropertyData::merge(PropertyData *otherVar) const {
    if(otherVar)
        otherVar = const_cast<PropertyData*>(parentPropertyDataVar);
    if(otherVar != parentPropertyDataVar) {
        if(!parentMergedVar)
            return;
        parentMergedVar = true;
    }
    if(otherVar)  {
        auto &index = propertyData.get<0>();
        otherVar->merge();
        for(const auto &spec : otherVar->propertyData.get<0>())
            index.push_back(spec);
    }
}
// ccfinderx similar code test end

}
//-----------------------------------------------------------------------------
// -- end conduit::relay::io --
//-----------------------------------------------------------------------------


#ifdef CONDUIT_RELAY_IO_MPI_ENABLED
}
//-----------------------------------------------------------------------------
// -- end conduit::relay::mpi --
//-----------------------------------------------------------------------------
#endif

}
//-----------------------------------------------------------------------------
// -- end conduit::relay --
//-----------------------------------------------------------------------------


}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------


