import sys

def find_smallest(n):
    smallest = 1
    for number in range(1, n+1):
        if smallest % number == 0:
            #print(smallest, 'is immediately ok with', number)
            continue
        #print(smallest, 'is not immediately ok with', number)
        for i in range(2, number+1):
            candidate = smallest * i
            if candidate % number == 0:
                #print(candidate, 'is ok with', number)
                smallest = candidate
                break
            #else:
            #    print(candidate, 'is not ok with', number)
    return smallest

#print(find_smallest(int(sys.argv[1])))

t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    print(find_smallest(n))
