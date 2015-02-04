.PHONY: deps

LIBELLIGATOR = "libelligator"

all: deps build

build: pyelligator

pyelligator:
	python setup.py build

deps: distclean
	git clone --branch master --depth=1 --quiet https://github.com/Yawning/libelligator.git
	patch -p0 < ./patches/00.patch
	$(MAKE) -C libelligator

install: build
	sudo python setup.py install

test: build
	python tests/test_elligator.py

clean:
	python setup.py clean

distclean:
	rm -rf ./libelligator
