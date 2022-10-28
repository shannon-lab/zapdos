FROM idaholab/moose:d73fc06368c8b33549cd1ec86f8863920789a878

WORKDIR /opt

RUN git clone -b master https://github.com/shannon-lab/zapdos.git ; \
cd zapdos ; \
git submodule update --init ; \
make -j $(grep -c ^processor /proc/cpuinfo)

WORKDIR /opt/zapdos
