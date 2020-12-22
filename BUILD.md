## Versions used:
GCC: 5.5.0
Boost: 1.64.0
Hwloc: 1.11.3
HPX: 1.1.0
YewPar: https://github.com/Varunvaruns9/YewPar/tree/new

### Boost
Source:
https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
Instructions:
http://stellar.cct.lsu.edu/files/hpx-1.1.0/html/hpx/manual/build_system/prerequisites/boost_installation.html

### Hwloc
Source:
https://download.open-mpi.org/release/hwloc/v1.11/hwloc-1.11.13.tar.gz
Instructions:
http://stellar.cct.lsu.edu/files/hpx-1.1.0/html/hpx/manual/build_system/prerequisites/hwloc_installation.html

### HPX
Source:
http://stellar.cct.lsu.edu/files/hpx_1.1.0.tar.gz
Instructions:
http://stellar.cct.lsu.edu/files/hpx-1.1.0/html/hpx/manual/build_system/building_hpx/build_recipes.html#hpx.manual.build_system.building_hpx.build_recipes.unix_installation
Commands used:
```
cd hpx_1.1.0
mkdir my_hpx_build
cd my_hpx_build

cmake -DCMAKE_INSTALL_PREFIX=~/hpx -DBOOST_ROOT=~/boost_dir -DHWLOC_ROOT=~/hwloc_dir -DHPX_WITH_MALLOC=system ..

make -j4
make install
```

### YewPar
Source:
https://github.com/Varunvaruns9/YewPar/tree/new
Install:
```
git clone https://github.com/Varunvaruns9/YewPar.git
cd YewPar
mkdir build
cd build

cmake \
 -DHPX_DIR=~/hpx/lib/cmake/HPX/ \
 -DCMAKE_BUILD_TYPE=Release \
 -DCMAKE_INSTALL_PREFIX=$(pwd)/install \
 ../
 
make -j4 && make install

# Add libraries to linker path
LD_LIBRARY_PATH=~/hpx/lib:~/YewPar/build/install/lib
export LD_LIBRARY_PATH
```
Running:
```
./install/bin/tsp --skeleton stacksteal --input-file ../test/<filename>.tsp --hpx:threads <num-threads>
```
