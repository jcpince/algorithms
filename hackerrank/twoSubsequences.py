# Brute force solution

# https://www.geeksforgeeks.org/print-subsets-given-size-set/
def getAllSubsetsSize(arr, subset_size, subset_sum = None, curent_sum = 0, index = 0, data = None, i = 0):
    assert(subset_size != 0)
    if data is None: data = list(range(subset_size))

    if subset_sum is not None and (curent_sum > subset_sum):
        return None

    # Current combination is
    # ready to be printed,
    # print it
    if index == subset_size:
        if subset_sum is None or (curent_sum == subset_sum):
            return [data.copy()]
        else:
            return None

    # When no more elements
    # are there to put in data[]
    subsets = []
    if i < len(arr):
        # current is included, put next at next location
        data[index] = arr[i]
        res = getAllSubsetsSize(arr, subset_size, subset_sum, curent_sum + arr[i], index + 1, data, i + 1)
        if res != None:
            subsets += res

        # current is excluded, replace it with next (Note that i+1 is passed, but index is not changed)
        res = getAllSubsetsSize(arr, subset_size, subset_sum, curent_sum, index, data, i + 1)
        if res != None:
            subsets += res

    return subsets

def getSubsetsSizeCount(arr, target_size, target_sum, current_sum = 0, current_size = 0, current_index = 0):

    # print("target_size(%ld), target_sum(%d), current_sum(%d), current_size(%ld), current_index(%ld)" %
    #     (target_size, target_sum, current_sum, current_size, current_index));
    # stop conditions
    if current_sum > target_sum: return 0
    if current_size == target_size: return 1 if current_sum == target_sum else 0
    if current_index >= len(arr): return 0

    res = getSubsetsSizeCount(arr, target_size, target_sum, current_sum + arr[current_index],
        current_size + 1, current_index + 1)
    res += getSubsetsSizeCount(arr, target_size, target_sum, current_sum, current_size,
        current_index + 1)
    return res;

def getAllSubsetsAllSizes(arr):
    subsets = []
    for i in range(1, len(arr)):
        subsets += getAllSubsetsSize(arr, i)
    return subsets

def printSubsets(subsets):
    size = 0
    for subset in subsets:
        if len(subset) != size:
            size = len(subset)
            print("Subsets of size %d:" % size)
        print("Subset: %s" % subset)

def getAll2Subsets(arr, r, s):
    total = 0
    if ((r + s) % 2) != 0:
        print("r+s is odd, 2 Subset match: []")
    asum = (r + s) / 2
    bsum = (r - s) / 2
    # arr.sort()
    # arr = [a for a in arr if a <= asum ]
    for i in range(1, len(arr)):
        Bs = getAllSubsetsSize(arr, i, bsum)
        print(Bs)
        if len(Bs) == 0: continue
        As = getAllSubsetsSize(arr, i, asum)
        print(As)
        subtotal = len(As) * len(Bs)
        print("Subset match for size %d: %d" % (i, subtotal))
        total += subtotal
    print("Total subset matches: %d" % total)

def twoSubsequences(arr, r, s):
    total = 0
    if ((r + s) % 2) != 0:
        print("r+s is odd, 2 Subset match: []")
    asum = (r + s) / 2
    bsum = (r - s) / 2
    # arr.sort()
    # arr = [a for a in arr if a <= asum ]
    for i in range(1, len(arr)):
        Bs = getSubsetsSizeCount(arr, i, bsum)
        print("Found %d subsequences of size %ld with sum %d" % (Bs, i, bsum));
        if Bs == 0: continue
        As = getSubsetsSizeCount(arr, i, asum)
        print("Found %d subsequences of size %ld with sum %d" % (As, i, asum));
        subtotal = As * Bs
        # print("Subset match for size %d: %d" % (i, subtotal))
        total += subtotal
    print("Total subset matches: %d" % total)

# arr = [677,179,362,1628,1863,1495,1601,451,1801,1443,1810,111,638,258,1568,946,263,524,115,491,1787,925,1125,310,1290,1016,1262,1293,1998,236,1218,1315,1443,1237,1385,547,825,1030,1727,1556,984,1878,1981,272,1731,1753,56,165,1887,1969,169,1579,1222,276,1341,1623,1335,559,1022,1343,1617,203,1233,511,224,111,1857,1500,838,1814,300,1671,1614,835,1228,1445,909,1330,537,1148,1593,1505,173,1680,1631,47,1353,1615,1920,1523,1558,1785,44,1328,878,1972,1986,1159,891,1343]
# r,s = 2000, 1000
#arr = [1,1,4]; r = 5; s = 3
arr = [1,2,1,3,1,4,1,4]; r = 5; s = 3
#all_2subsets = twoSubsequences(arr, r, s)

arr = [677,179,362,1628,1863,1495,1601,451,1801,1443,1810,111,638,258,1568,946,263,524,115,491,1787,925,1125,310,1290,1016,1262,1293,1998,236,1218,1315,1443,1237,1385,547,825,1030,1727,1556,984,1878,1981,272,1731,1753,56,165,1887,1969,169,1579,1222,276,1341,1623,1335,559,1022,1343,1617,203,1233,511,224,111,1857,1500,838,1814,300,1671,1614,835,1228,1445,909,1330,537,1148,1593,1505,173,1680,1631,47,1353,1615,1920,1523,1558,1785,44,1328,878,1972,1986,1159,891,1343]
r,s = 2000, 1000
all_2subsets = getAll2Subsets(arr, r, s)
#all_subsets = getAllSubsetsAllSizes(arr)
# print("############### All subsets: ###############")
# printSubsets(all_subsets)
#print("############### All 2 subsets: ###############")
#printSubsets(all_2subsets)
