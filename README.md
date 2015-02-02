## pyelligator - Python binding for libelligator
#### Alfonso De Gregorio (adg at secYOUre dot com)

### What?

[pyelligator ](https://github.com/secYOUre/pyelligator) is a Python 
binding for [libelligator](https://github.com/Yawning/libelligator).
Based on the code authored by agl in the [ed25519/extra25519](https://github.com/agl/ed25519), libelligator is a C++ implementation of ["Elligator: Elliptic-curve points indistinguishable from uniform random strings"](http://elligator.cr.yp.to/elligator-20130828.pdf) for Curve25519.  

### Usage

    import elligator

    from os import urandom

    # Generate keys
    while True:
        private = urandom(32)
        (valid, public, representative) = elligator.scalarbasemult(private)
        if valid:
            break


    # Convert a uniform representative value for Curve25519 public key, 
    # as produced by scalarbasemult, to a Curve25519 public key
    public = elligator.representativetopublic(representative)


### Installation

    make
    make install
    make test
