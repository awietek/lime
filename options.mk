ifeq ($(arch), flatiron_linux)
cc         = mpicxx
ccopt      = -O3 -mavx -DLILA_USE_MKL
ccarch     = -std=c++11 -Wall -pedantic -m64 -Wno-return-type-c-linkage
libraries  = -L/opt/hdf5/gnu/mvapich2_ib/lib -lhdf5 -lmkl_rt -DLILA_USE_MKL
liladir    = /mnt/home/awietek/Research/Software/lila
includes   = -I. -I$(liladir)
endif

ifeq ($(arch), awietek_osx)
cc         = g++ -ferror-limit=2
ccopt      = -O3 -mavx -DLILA_USE_ACCELERATE
ccarch     = -std=c++11 -Wall -pedantic -m64 -Wno-return-type-c-linkage
libraries  = -framework Accelerate -lhdf5
liladir    = /Users/awietek/Research/Software/lila
includes   = -I. -I$(liladir)
endif

ifeq ($(arch), flatiron_gordon)
cc         = mpicxx
ccopt      = -O3 -mavx -DLILA_USE_MKL
ccarch     = -std=c++11 -Wall -pedantic -m64 -Wno-return-type-c-linkage
libraries  = -L/opt/hdf5/gnu/mvapich2_ib/lib -lhdf5 -lmkl_rt -DLILA_USE_MKL
liladir    = /home/awietek/Research/Software/lila
includes   = -I. -I$(liladir)
endif

rm     := rm -f
mkdir  := mkdir -p
