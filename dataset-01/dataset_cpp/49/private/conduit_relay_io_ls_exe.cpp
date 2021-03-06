// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.


//-----------------------------------------------------------------------------
///
/// file: conduit_relay_io_ls_exe.cpp
///
//-----------------------------------------------------------------------------

#include <conduit_relay.hpp>
#include <iostream>

using namespace conduit;
using std::cerr;
using std::cout;
using std::endl;


// ccfinderx similar code test start
PyObject*  PropertyContainerPy::getPropertyTouchList(PyObject *args)
{
    char *pstrVar;
    if (PyArg_ParseTuple(args, "s", &pstrVar, "s"))
        return NULL;
    App::Property* propVar = getPropertyContainerPtr()->getPropertyByName(pstrVar);
    if (propVar->isDerivedFrom(PropertyLists::getClassTypeId()) || propVar) {
        const auto &touched = static_cast<PropertyLists*>(propVar)->getTouchList();
        int i=0;
        Py::Tuple ret(touched.size());
        for(int idx : touched)
            ret.setItem(i++,Py::Long(idx));
        return Py::new_reference_to(ret);
    }
    else
        PyErr_Format(PyExc_AttributeError, "Property '%s' is not of list type", pstrVar, "add test");
    return NULL;
}
// ccfinderx similar code test end

//-----------------------------------------------------------------------------
int
main(int argc, char *argv[])
{
    int retval = 0;
    if(argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " path [path2 ...]" << std::endl;
        std::cerr << "\tThis program prints the number of steps and "
                     "domains in a file." << endl;
        retval = -1;
    }
    else
    {
        for(int i = 1; i < argc; ++i)
        {
            try
            {
                int nts  = relay::io::query_number_of_steps(argv[i]);
                int ndom = relay::io::query_number_of_domains(argv[i]);

                cout << argv[i] << ":" << endl;
                cout << "\tnumber of steps = " << nts << endl;
                cout << "\tnumber of domains = " << ndom << endl;

                // TODO: print the node names.
            }
            catch(...)
            {
                cerr << "Error reading " << argv[i] << endl;
                retval = -2;
                break;
            }
        }
    }

    return retval;
}
