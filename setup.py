from distutils.core import setup, Extension

module = Extension('elligator',
                    libraries = ['elligator'],
                    library_dirs = ['./libelligator'],
                    include_dirs = ['./libelligator/src'],
                    runtime_library_dirs = ['./libelligator'],
                    sources = ['src/pyelligator.c' ])

setup (name = 'elligator',
       version = '1.0',
       url = 'https://github.com/secYOUre/pyelligator',
       license = 'BSD',
       description = 'Python wrapper for libelligator',
       author = 'Alfonso De Gregorio',
       author_email = 'adg@secYOUre.com',
       ext_modules = [module])
