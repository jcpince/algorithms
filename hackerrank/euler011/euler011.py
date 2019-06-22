#!/usr/bin/python3
import time
import array
from math import sqrt

grid_size = 20
tuple_size = 4

hgrid = bytearray(grid_size*grid_size)

def xy2index(x, y):
    global grid_size
    return x + y * grid_size

def find_greatest_hproduct():
    global hgrid
    maxprod = 0
    for x in range(grid_size - tuple_size+1):
        for y in range(grid_size):
            index = xy2index(x, y)
            prod = 1
            for offset in range(tuple_size):
                prod *= hgrid[index+offset]
            # if prod > maxprod:
            #     print("(%d, %d) => %d -- %s" % (x, y, prod, [int(x) for x in hgrid[index:index+tuple_size]]))
            maxprod = max(maxprod, prod)
    return maxprod

def find_greatest_vproduct():
    global hgrid
    maxprod = 0
    for x in range(grid_size):
        for y in range(grid_size - tuple_size+1):
            prod = 1
            for offset in range(tuple_size):
                prod *= hgrid[xy2index(x, y+offset)]
            # if prod > maxprod:
            #     print("(%d, %d) => %d" % (x, y, prod))
            maxprod = max(maxprod, prod)
    return maxprod

def find_greatest_dproduct():
    global hgrid
    maxprod = 0
    for x in range(grid_size - tuple_size+1):
        for y in range(grid_size - tuple_size+1):
            prod = 1
            for offset in range(tuple_size):
                prod *= hgrid[xy2index(x+offset, y+offset)]
            # if prod > maxprod:
            #     print("(%d, %d) => %d" % (x, y, prod))
            maxprod = max(maxprod, prod)
    return maxprod

def find_greatest_cdproduct():
    global hgrid
    maxprod = 0
    for x in range(tuple_size-1, grid_size):
        for y in range(grid_size - tuple_size+1):
            prod = 1
            for offset in range(tuple_size):
                prod *= hgrid[xy2index(x-offset, y+offset)]
            # if prod > maxprod:
            #     print("(%d, %d) => %d" % (x, y, prod))
            maxprod = max(maxprod, prod)
    return maxprod


start = time.time()
vindex = 0
for grid_i in range(20):
   grid_t = [int(grid_temp) for grid_temp in input().strip().split(' ')]
   for hindex in range(grid_size):
       hgrid[hindex+vindex*grid_size] = grid_t[hindex]
   vindex += 1
maxprod = 0
maxprod = find_greatest_hproduct()
maxprod = max(maxprod, find_greatest_vproduct())
maxprod = max(maxprod, find_greatest_dproduct())
maxprod = max(maxprod, find_greatest_cdproduct())
print(maxprod)

#print("Computation time: %f seconds" % (time.time() - start))
