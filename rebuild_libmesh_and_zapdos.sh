#!/bin/bash

PROJECTDIR=/home/lindsayad/projects

cd $PROJECTDIR/zapdos
make clobber
METHOD=dbg make clobber

cd ../moose
git pull origin master
git clean -fxd
./scripts/update_and_rebuild_libmesh.sh --disable-timestamps

cd ../zapdos
make -j4
