# DON'T FORGET: Modify this hash to be consistent with the MOOSE submodule!
FROM idaholab/moose:20d4a080193f0b0ee38d6210341a933c0ba544dc

WORKDIR /opt

RUN git clone -b master https://github.com/shannon-lab/zapdos.git ; \
cd zapdos ; \
git submodule update --init crane squirrel ; \
make -j $(grep -c ^processor /proc/cpuinfo)

WORKDIR /opt/zapdos
