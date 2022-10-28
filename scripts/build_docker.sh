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


# Check for and set ZAPDOS_DIR
if [ -z "$ZAPDOS_DIR" ]; then
    echo "ERROR: ZAPDOS_DIR is not set for build_docker"
    exit 1
fi
if [ ! -d "$ZAPDOS_DIR" ]; then
  echo "ERROR: $ZAPDOS_DIR=ZAPDOS_DIR does not exist"
  exit 1
fi

# Enter Zapdos and get latest master branch git commit hash
cd $ZAPDOS_DIR
git checkout master
MASTER_HASH=$(git rev-parse master)

# Build docker container
docker build -t shannonlab/zapdos:"$MASTER_HASH" . || exit $?

# Retag newly built container with "latest"
docker tag shannonlab/zapdos:"$MASTER_HASH" shannonlab/zapdos:latest

# Push all containers to Docker Hub, if enabled
if [[ $PUSH == 1 ]]; then
  docker push shannonlab/zapdos:$MASTER_HASH
  docker push shannonlab/zapdos:latest
else
  echo ""
  echo "INFO: Push to Docker Hub disabled. If desired in the future, run this script"
  echo "      with PUSH=1 in your environment. To push now, run the following two"
  echo "      commands:"
  echo ""
  echo "      docker push shannonlab/zapdos:$MASTER_HASH"
  echo "      docker push shannonlab/zapdos:latest"
fi
