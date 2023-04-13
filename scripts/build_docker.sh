#!/bin/bash

#* This file is part of Zapdos, an open-source
#* application for the simulation of plasmas
#* https://github.com/shannon-lab/zapdos
#*
#* Zapdos is powered by the MOOSE Framework
#* https://www.mooseframework.org
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html


# This script builds a Zapdos docker container based on the current master branch
# for upload to Docker Hub

# Set optional push parameter (defaults to NO / 0 if not set by the user)
if [ -z "$PUSH" ]; then
  PUSH=0
fi

# Check for ZAPDOS_DIR and if it exists; throw errors if either is false
if [ -z "$ZAPDOS_DIR" ]; then
    echo "ERROR: ZAPDOS_DIR is not set for build_docker"
    exit 1
fi
if [ ! -d "$ZAPDOS_DIR" ]; then
  echo "ERROR: $ZAPDOS_DIR=ZAPDOS_DIR does not exist"
  exit 1
fi

# Enter Zapdos source location, checkout master branch, and save latest git commit hash
cd $ZAPDOS_DIR
git checkout master
ZAPDOS_MASTER_HASH=$(git rev-parse master)

# Get MOOSE submodule hash and compare to Dockerfile to make sure it has been updated
git submodule update --init moose
cd moose
MOOSE_HASH=$(git rev-parse HEAD)

cd $ZAPDOS_DIR/scripts

# Use sed to find and replace MOOSE submodule hash into Dockerfile
sed -i '' "s/{{MOOSE_HASH}}/$MOOSE_HASH/g" Dockerfile

# Build docker container and tag it with master git hash
docker build -t shannonlab/zapdos:"$ZAPDOS_MASTER_HASH" . || exit $?

# Retag newly built container to make a second one with the tag "latest"
docker tag shannonlab/zapdos:"$ZAPDOS_MASTER_HASH" shannonlab/zapdos:latest

# Restore Dockerfile to un-modified state so that branch is clean
git restore Dockerfile

# Push both containers to Docker Hub, if enabled. If not, display a notice to the screen with more info
if [[ $PUSH == 1 ]]; then
  docker push shannonlab/zapdos:$ZAPDOS_MASTER_HASH
  docker push shannonlab/zapdos:latest
else
  echo ""
  echo "INFO: Push to Docker Hub disabled. If desired in the future, run this script"
  echo "      with PUSH=1 in your environment. To push now, run the following two"
  echo "      commands:"
  echo ""
  echo "      docker push shannonlab/zapdos:$ZAPDOS_MASTER_HASH"
  echo "      docker push shannonlab/zapdos:latest"
fi
