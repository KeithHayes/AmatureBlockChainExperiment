[![Build Status](https://travis-ci.com/lammertb/libcrc.svg?branch=master)](https://travis-ci.com/lammertb/libcrc)

# An experiment in block signature.

A text block is constructed with an embedded 16 bit CRC (Cyclic Redundancy Check) and a data byte 'shine' that with the CRC makes a unique block signature.  The data byte and CRC selected to be lowest in magnitude by the mining operation.  This provides a unique signature because only the 'shiniest' block has value.

The CRC library [www.libcrc.org]. 
API documentation is available on this website.

## License

None by me.  Github added a license to the included CRC lib but none is required by the original author.


## Platform

A SDL (Simple DirectMedia Layer) window and linked to the static library (https://github.com/lammertb/libcrc.git) for CRC code.

## Goal

A text block is constructed with an embedded 16 bit CRC (Cyclic Redundancy Check) and a data byte 'shine' that with the CRC makes a unique block signature.  A data byte and valid CRC are selected to be lowest in magnitude by the mining operation results in a unique identifier.  Only the shiniest block(low shine and low CRC) has any value. This allows a block to be checked.

The project was built using Visual Studio Code with its C++, CMake, Plugins for a DEV environment running Linux Mint 20.

## Details

First the static CRC library was built in a directory.  Then in its examples folder 'example.cpp' was replaced by 'tstcrc.cpp' which contains the entry point.  the output file is found at:  /build/examples/blockminer.out after the project is built.

CMakeListsCMakeLists.txt files link in SDL libraries which must be present.

## Notes

This is not a practical example.  It is an experiment that creates a digital signature which identifies a text block as a valid member in a chain.

Adding a hash value '<@!7he0)bb&>' from the parent block establishes block pedigree.

A similar hash value '<!@#$k78PO*>' for future links is introduced in the block at the end.

In the mining operation the embedded CRC is computed over the entire block.

When a block is accepted and entered into the shared database changing the CRC becomes impossible.  Making forgery impossible as a forgery must have identical low shine and low CRC values.

I contend this is not possible.  Mining would have to be performed to detect the forgery.  The forgery might match for a while but a forgery should have at least one shine CRC pair with a lower value than the original.  Having a tail block in the cloud set to the CRC of the end block prevents it from being changed.


