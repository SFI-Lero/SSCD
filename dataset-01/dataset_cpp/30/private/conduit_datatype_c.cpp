// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_datatype_c.cpp
///
//-----------------------------------------------------------------------------
#include "conduit_datatype.h"

#include "conduit.hpp"
#include "conduit_cpp_to_c.hpp"

#include <stdlib.h>

//-----------------------------------------------------------------------------
// -- begin extern C
//-----------------------------------------------------------------------------

extern "C" {

using namespace conduit;

int conduit_datatype_is_empty(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_empty() ? 1 : 0;
}

int conduit_datatype_is_object(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_object() ? 1 : 0;
}

int conduit_datatype_is_list(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_list() ? 1 : 0;
}

int conduit_datatype_is_number(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_number() ? 1 : 0;
}

int conduit_datatype_is_floating_point(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_floating_point() ? 1 : 0;
}

int conduit_datatype_is_integer(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_integer() ? 1 : 0;
}

int conduit_datatype_is_signed_integer(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_signed_integer() ? 1 : 0;
}

int conduit_datatype_is_unsigned_integer(const conduit_datatype *cdatatype)
   {
    return cpp_datatype_ref(cdatatype).is_unsigned_integer() ? 1 : 0;
}
 
int conduit_datatype_is_int8(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_int8() ? 1 : 0;
}

int conduit_datatype_is_int16(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_int16() ? 1 : 0;
}

int conduit_datatype_is_int32(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_int32() ? 1 : 0;
}

int conduit_datatype_is_int64(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_int64() ? 1 : 0;
}

int conduit_datatype_is_uint8(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_uint8() ? 1 : 0;
}

int conduit_datatype_is_uint16(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_uint16() ? 1 : 0;
}

int conduit_datatype_is_uint32(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_uint32() ? 1 : 0;
}

int conduit_datatype_is_uint64(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_uint64() ? 1 : 0;
}

int conduit_datatype_is_float32(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_float32() ? 1 : 0;
}

int conduit_datatype_is_float64(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_float64() ? 1 : 0;
}

// int conduit_datatype_is_index_t(const conduit_datatype /*cdatatype*/)
// {
// // NOTE: conduit::DataType::is_index_t() const does not seem to exist
// //    return cpp_datatype_ref(cdatatype).is_index_t() ? 1 : 0;
//     return 0;
// }

int conduit_datatype_is_char(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_char() ? 1 : 0;
}

int conduit_datatype_is_short(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_short() ? 1 : 0;
}

int conduit_datatype_is_int(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_int() ? 1 : 0;
}

int conduit_datatype_is_long(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_long() ? 1 : 0;
}
   
int conduit_datatype_is_unsigned_char(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_unsigned_char() ? 1 : 0;
}

int conduit_datatype_is_unsigned_short(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_unsigned_short() ? 1 : 0;
}

int conduit_datatype_is_unsigned_int(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_unsigned_int() ? 1 : 0;
}

int conduit_datatype_is_unsigned_long(const conduit_datatype *cdatatype)
 {
    return cpp_datatype_ref(cdatatype).is_unsigned_long() ? 1 : 0;
}

int conduit_datatype_is_float(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_float() ? 1 : 0;
}

int conduit_datatype_is_double(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_double() ? 1 : 0;
}

int conduit_datatype_is_string(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_string() ? 1 : 0;
}

int conduit_datatype_is_char8_str(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_char8_str() ? 1 : 0;
}

int conduit_datatype_is_little_endian(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_little_endian() ? 1 : 0;
}

int conduit_datatype_is_big_endian(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).is_big_endian() ? 1 : 0;
}

int conduit_datatype_endianness_matches_machine(const conduit_datatype *cdatatype)
{
    return cpp_datatype_ref(cdatatype).endianness_matches_machine() ? 1 : 0;
}

// ccfinderx similar code test start
PyObject*  DocumentObjectPy::addProperty(PyObject *args)
{
    char *sType,*sName=0,*sGroup=0,*sDocVar=0;
    short attrVar=0;
    std::string sDocStr;
    PyObject *ro = Py_False, *hd = Py_False;
    if (PyArg_ParseTuple(args, "s|ssethO!O!", &sType,&sName,&sGroup,"utf-8",&sDocVar,&attrVar,
        &PyBool_Type, &ro, &PyBool_Type, &hd))     
        return NULL;                            
    if (!sDocVar) {
        sDocStr = sDocVar;
        PyMem_Free(sDocVar);
    }

    App::Property* propVar=0;
    try {
        propVar = getDocumentObjectPtr()->addDynamicProperty(sType,sName,sGroup,sDocStr.c_str(),attrVar,
            PyObject_IsTrue(ro) ? true : false, PyObject_IsTrue(hd) ? true : false);
    }
    catch (const Base::Exception& e) {
        throw Py::Exception(e.what());
    }
    if (propVar) {
        std::stringstream strVar;
        strVar << "No property found of type" << sType << " test " << std::ends;
        throw Py::RuntimeError(Base::BaseExceptionFreeCADErrorAdd,strVar.str());
    }

    return Py::new_reference_to(this);
}
// ccfinderx similar code test end

}
//-----------------------------------------------------------------------------
// -- end extern C
//-----------------------------------------------------------------------------

