# DON'T FORGET: Modify this hash to be consistent with the MOOSE submodule!
FROM idaholab/moose:9721739139002a43f9493611866793b7c2bc234b

WORKDIR /opt

RUN git clone -b master https://github.com/shannon-lab/zapdos.git ; \
cd zapdos ; \
git submodule update --init crane squirrel ; \
make -j $(grep -c ^processor /proc/cpuinfo)

WORKDIR /opt/zapdos
