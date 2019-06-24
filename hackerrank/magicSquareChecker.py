# Python3 program to check whether a given
# matrix is magic matrix or not
N = 3

# Returns true if mat[][] is magic
# square, else returns false.
def isMagicSquare( mat) :

    # calculate the sum of
    # the prime diagonal
    s = 0

    for i in range(0, N) :
        s = s + mat[i][i]

    # the secondary diagonal
    s2 = 0
    for i in range(0, N) :
        s2 = s2 + mat[i][N-i-1]

    if(s!=s2) :
        print("Diagonals are different %d vs %d" % (s, s2))
        return False

    # For sums of Rows
    for i in range(0, N) :
        rowSum = 0;
        for j in range(0, N) :
            rowSum += mat[i][j]

        # check if every row sum is
        # equal to prime diagonal sum
        if (rowSum != s) :
            print("Row[%d] %s is different from %d" % (i, mat[i], s))
            return False

    # For sums of Columns
    for i in range(0, N):
        colSum = 0
        for j in range(0, N) :
            colSum += mat[j][i]

        # check if every column sum is
        # equal to prime diagonal sum
        if (s != colSum) :
            col = [mat[0][i], mat[1][i], mat[2][i]]
            print("Column[%d] %s is different from %d" % (i, col, s))
            return False

    return True

# Driver Code
# mat = [ [ 2, 7, 6 ],
# 		[ 9, 5, 1 ],
# 		[ 4, 3, 8 ] ]
mat = [ [ 4, 3, 8 ],
        [ 2, 6, 7 ],
        [ 1, 9, 5 ] ]

if (isMagicSquare(mat)) :
    print( "Magic Square")
else :
    print( "Not a magic Square")
# This code is contributed by Nikita Tiwari.
