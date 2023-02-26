# DON'T FORGET: Modify this hash to be consistent with the MOOSE submodule!
FROM idaholab/moose:1a6bfe777e40c135a7ca1fa750e4d658a29e8970

WORKDIR /opt

RUN git clone -b master https://github.com/shannon-lab/zapdos.git ; \
cd zapdos ; \
git submodule update --init crane squirrel ; \
make -j $(grep -c ^processor /proc/cpuinfo)

WORKDIR /opt/zapdos
