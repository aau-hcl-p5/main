#!/usr/bin/env bash

cd /home/nxtosek/nxtOSEK/build/nxt
wineconsole ../../ecrobot/../toppers_osek/sg/sg ./nxt.oil -os=ECC2 -I../../ecrobot/../toppers_osek/sg/impl_oil -template=../../ecrobot/../toppers_osek/sg/lego_nxt.sgt &> /dev/null
make $1
