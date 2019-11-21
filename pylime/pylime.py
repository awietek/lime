#!/usr/bin/env python
import numpy as np
import h5py as h5
import tables as tb
import pandas as pd

filename="../dumpm.hdf5"

with h5.File(filename, 'r') as f:
    print(f.keys())
    print(list(f))
    # for i in range(9995,10000,1):
        
    #     print(f['s'][i])
    #     print(f['cs'][i])
    #     print(f['v'][i,:])
    #     print(f['cv'][i,:])
    #     print(f['m'][i,:,:])
    #     print(f['cm'][i,:,:])
    #     print("\n")
