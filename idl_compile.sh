#!/bin/bash
omniidl -bcxx ./idl/object.idl
mv ./object.hh ./inc
mv ./objectSK.cc ./src