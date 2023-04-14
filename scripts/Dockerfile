# Template variable is replaced with hash when build_docker.sh is run!
FROM idaholab/moose:{{MOOSE_HASH}}

WORKDIR /opt

RUN git clone -b master https://github.com/shannon-lab/zapdos.git ; \
cd zapdos ; \
git submodule update --init crane squirrel ; \
make -j $(grep -c ^processor /proc/cpuinfo)

WORKDIR /opt/zapdos
