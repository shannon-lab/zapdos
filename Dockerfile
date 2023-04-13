# DON'T FORGET: Modify this hash to be consistent with the MOOSE submodule!
FROM idaholab/moose:5e60aeb38c948f5db9e98b2080724b87188f5ee2

WORKDIR /opt

RUN git clone -b master https://github.com/shannon-lab/zapdos.git ; \
cd zapdos ; \
git submodule update --init crane squirrel ; \
make -j $(grep -c ^processor /proc/cpuinfo)

WORKDIR /opt/zapdos
