ifeq ($(arch), flatiron_linux)
cc         = clang++
ccopt      = -O3 -mavx 
ccarch     = -std=c++11 -Wall -pedantic -m64 -Wno-return-type-c-linkage
libraries  = 
liladir    = /mnt/home/awietek/Research/Software/lila
includes   = -I. -I$(liladir)
endif

rm     := rm -f
mkdir  := mkdir -p
