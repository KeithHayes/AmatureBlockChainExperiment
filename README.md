[![Build Status](https://travis-ci.com/lammertb/libcrc.svg?branch=master)](https://travis-ci.com/lammertb/libcrc)

# An experiment in block signature.

A text block is constructed with an embedded 16 bit CRC (Cyclic Redundancy Check) and a data byte 'shine' that with the CRC makes a unique block signature.  The data byte and CRC selected to be lowest in magnitude by the mining operation.  This provides a unique signature because only the 'shiniest' block has value.

The CRC library with API reference also has a new home at [www.libcrc.org](http://libcrc.org). An
online version of the API documentation is available on this website.

## License

None by me.  Github added a license to the included CRC lib but none is required by the original author.


## Platforms

Built using an SDL (Simple DirectMedia Layer) window and linked to the static library (https://github.com/lammertb/libcrc.git) for CRC code.

## Goal

A text block is constructed with an embedded 16 bit CRC (Cyclic Redundancy Check) and a data byte 'shine' that with the CRC makes a unique block signature.  The data byte and CRC selected to be lowest in magnitude by the mining operation provides a unique identifier.  Only the shiniest coin has value.

The project was built using Visual Studio Code and C++, CMake Plugins for a dev environment in Mint 20.

First the static libcrc library was built in a directory.  Then in the examples folder an 'example.cpp' was replaced by 'tstcrc.cpp' which contains main().  the output file is found at:  /build/examples/blockminer.out when the project is built.

The CMakeListsCMakeLists.txt files link in SDL libraries which must be present.

This is not a practical example and is an experiment which creates a digital signature that identifies a text block as a valid member in a chain.

Adding a hash value '<@!7he0)bb&>' from the parent block helps establish block pedigree.

A similar hash value '<!@#$k78PO*>' for future links is created.

In the mining operation the CRC is computed over the entire block.


