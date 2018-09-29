#!/usr/bin/env bash

cd /home/nxtosek/nxtOSEK/build/nxt
if [ $1 != "clean" ]
then
  echo "Generating implementation.oil..."
  Xvfb :1 -screen 0 1280x960x24 &> /dev/null &
  export WINEARCH=win32
  export DISPLAY=1
  wine ../../ecrobot/../toppers_osek/sg/sg ./nxt.oil -os=ECC2 -I../../ecrobot/../toppers_osek/sg/impl_oil -template=../../ecrobot/../toppers_osek/sg/lego_nxt.sgt &> /dev/null
fi
make $1
