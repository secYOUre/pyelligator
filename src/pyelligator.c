#include <Python.h>

#include "elligator/elligator.h"


#if PY_MAJOR_VERSION >= 3

#include <string.h>

// Usage: (valid, public, representative) = elligator.scalarbasemult(private) -> get valid flag, public key, representative value
static PyObject *elligator_scalarbasemult(PyObject *self, PyObject *args)
{
    Py_buffer private;

    if (PyArg_ParseTuple(args, "y*", &private))
    {
        uint8_t *pub_key = PyMem_Malloc(32); // public key
        uint8_t *representative = PyMem_Malloc(32); // representative value
	bool valid = ScalarBaseMult(pub_key, representative, private.buf);

	PyObject *rslt = PyTuple_New(3);
        PyObject *valid_flag = Py_BuildValue("O", valid ? Py_True: Py_False);
	PyTuple_SetItem(rslt, 0, valid_flag);
	PyTuple_SetItem(rslt, 1, Py_BuildValue("y#", pub_key, 32));
	PyTuple_SetItem(rslt, 2, Py_BuildValue("y#", representative, 32));
	return rslt;
    }

    return 0;
}

// Usage: public = elligator.representativetopublic(representativevalue)
static PyObject *elligator_representativetopublic(PyObject *self, PyObject *args)
{
    Py_buffer repr;

    if (PyArg_ParseTuple(args, "y*", &repr))
    {
        uint8_t *public = PyMem_Malloc(32); // public key
	RepresentativeToPublicKey(public, repr.buf);
        return Py_BuildValue("y#", public, 32);
    }

    return 0;
}


static PyMethodDef elligator_methods[] = 
{
    {"scalarbasemult",  elligator_scalarbasemult, METH_VARARGS,
     "Computes a public key and representative value from a private key"},
    {"representativetopublic",  elligator_representativetopublic, METH_VARARGS,
     "Generates a public key from the representative value"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef elligator_module = 
{
    PyModuleDef_HEAD_INIT,
    "elligator",
    "Python wrapper for libelligator.",
    -1,
    elligator_methods
};

PyMODINIT_FUNC PyInit_elligator(void)
{
    return PyModule_Create(&elligator_module);
}

int main(int argc, char *argv[])
{
    PyImport_AppendInittab("elligator", PyInit_elligator);
    wchar_t progname[FILENAME_MAX + 1];
    mbstowcs(progname, argv[0], strlen(argv[0]) + 1);
    Py_SetProgramName(progname);
    Py_Initialize();
    return 0;
}

#else


// Usage: (valid, public, representative) = elligator.scalarbasemult(private) -> get valid flag, public key and representative value
static PyObject *elligator_scalarbasemult(PyObject *self, PyObject *args)
{
    Py_buffer private;

    // (void) curl_version_info(0);

    if (PyArg_ParseTuple(args, "s*", &private))
    {
        uint8_t *pub_key = PyMem_Malloc(32); // public key
        uint8_t *representative = PyMem_Malloc(32); // representative value
	bool valid = ScalarBaseMult(pub_key, representative, private.buf);

	PyObject *rslt = PyTuple_New(3);
        PyObject *valid_flag = Py_BuildValue("O", valid ? Py_True: Py_False);
	PyTuple_SetItem(rslt, 0, valid_flag);
	PyTuple_SetItem(rslt, 1, Py_BuildValue("s#", pub_key, 32));
	PyTuple_SetItem(rslt, 2, Py_BuildValue("s#", representative, 32));
	return rslt;
    }

    return 0;
}

// Usage: public = elligator.representativetopublic(your representative value)
static PyObject *elligator_representativetopublic(PyObject *self, PyObject *args)
{
    Py_buffer repr;

    if (PyArg_ParseTuple(args, "s*", &repr))
    {
        uint8_t *public = PyMem_Malloc(32); // public key
	RepresentativeToPublicKey(public, repr.buf);
        return Py_BuildValue("s#", public, 32);
    }

    return 0;
}

static PyMethodDef elligator_methods[] = 
{
    {"scalarbasemult",  elligator_scalarbasemult, METH_VARARGS,
     "Computes a public key and representative value from a private key"},
    {"representativetopublic",  elligator_representativetopublic, METH_VARARGS,
     "Generates a public key from the representative value"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initelligator(void)
{
    (void)Py_InitModule("elligator", elligator_methods);
}

int main(int argc, char *argv[])
{
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    initelligator();
    return 0;
}

#endif
