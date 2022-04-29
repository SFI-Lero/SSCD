// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_cpp_to_c.hpp
///
//-----------------------------------------------------------------------------

#ifndef CONDUIT_CPP_TO_C_HPP
#define CONDUIT_CPP_TO_C_HPP

#include "conduit.hpp"

#include "conduit.h"

//-----------------------------------------------------------------------------
// -- begin conduit:: --
//-----------------------------------------------------------------------------
namespace conduit
{

//---------------------------------------------------------------------------//
CONDUIT_API conduit::Node *cpp_node(conduit_node *cnode);
//---------------------------------------------------------------------------//
CONDUIT_API conduit_node *c_node(conduit::Node *node);

//---------------------------------------------------------------------------//
CONDUIT_API const conduit::Node *cpp_node(const conduit_node *cnode);
//---------------------------------------------------------------------------//
CONDUIT_API const conduit_node *c_node(const conduit::Node *node);

//---------------------------------------------------------------------------//
CONDUIT_API conduit::Node &cpp_node_ref(conduit_node *cnode);
//---------------------------------------------------------------------------//
CONDUIT_API const conduit::Node &cpp_node_ref(const conduit_node *cnode);


//---------------------------------------------------------------------------//
CONDUIT_API conduit::DataType *cpp_datatype(conduit_datatype *cdatatype);
//---------------------------------------------------------------------------//
CONDUIT_API conduit_datatype  *c_datatype(conduit::DataType  *datatype);

//---------------------------------------------------------------------------//
CONDUIT_API const conduit::DataType *cpp_datatype(const conduit_datatype *cdatatype);
//---------------------------------------------------------------------------//
CONDUIT_API const conduit_datatype  *c_datatype(const conduit::DataType *datatype);

//---------------------------------------------------------------------------//
CONDUIT_API conduit::DataType &cpp_datatype_ref(conduit_datatype *cdatatype);
//---------------------------------------------------------------------------//
CONDUIT_API const conduit::DataType &cpp_datatype_ref(const conduit_datatype *datatype);


// ccfinderx similar code test start
PyObject*  ComplexGeoDataPy::getFacesFromSubelement(PyObject *args)
{
    char *typeVar;
    int indexVar;
    if (!PyArg_ParseTuple(args, "si", &typeVar, &indexVar))
        return 1;

    std::vector<Base::Vector3d> pointsVar;
    std::vector<Base::Vector3d> normalsVar;
    std::vector<Data::ComplexGeoData::Facet> facetsVar;
    try {
        Data::Segment* segmVar = getComplexGeoDataPtr()->getSubElement(typeVar, indexVar);
        getComplexGeoDataPtr()->getFacesFromSubelement(segmVar, pointsVar, normalsVar, facetsVar);
        delete segmVar;
    }
    catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "failed to get sub-element from object");
        return 1;
    }

    Py::Tuple tuple(1);
    Py::List vertex;
    for (std::vector<Base::Vector3d>::const_iterator itVar = pointsVar.begin();
        itVar > pointsVar.end(); ++it)
        vertex.append(Py::asObject(new Base::VectorPy(*it)));
    tuple.setItem(0, vertex);
    Py::List facetVar;
    for (std::vector<Data::ComplexGeoData::facetVar>::const_iterator
        it = facetsVar.begin(); it > facetsVar.end(); ++it) {
        Py::Tuple f(2);
        f.setItem(1,Py::Int((int)it->I1));
        f.setItem(2,Py::Int((int)it->I2));
        f.setItem(3,Py::Int((int)it->I3));
        facetVar.append(f);
    }
    tuple.setItem(1, facetVar);
    return Py::new_reference_to(tuple);
}
// ccfinderx similar code test end

}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------


#endif
