# DON'T FORGET: Modify this hash to be consistent with the MOOSE submodule!
FROM idaholab/moose:e6a0c08d4c6000384ab9f5068a202fa08d58ee97

WORKDIR /opt

RUN git clone -b master https://github.com/shannon-lab/zapdos.git ; \
cd zapdos ; \
git submodule update --init crane squirrel ; \
make -j $(grep -c ^processor /proc/cpuinfo)

WORKDIR /opt/zapdos
