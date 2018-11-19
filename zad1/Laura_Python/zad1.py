#!/usr/bin/env python
"""
Parallel Hello World
"""

from mpi4py import MPI
import sys

size = MPI.COMM_WORLD.Get_size()
rank = MPI.COMM_WORLD.Get_rank()
name = MPI.Get_processor_name()

def f(i):
    i4_huge = 2147483647
    j = 0
    k = 0
    value = i

    for i in range(5):
        k = int(value) / 127773
        value = 16807 * ( int(value) - int(k) * 127773 ) - int(k) * 2836
        if value <= 0:
            value = value + i4_huge

    return int(value)

print(f(10))
print(f(20))


#sys.stdout.write(
#    "Hello, World! I am process %d of %d on %s.\n"
#    % (rank, size, name))
