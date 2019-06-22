#! /usr/bin/python3

import sys
sys.setrecursionlimit(100000)

class Solution:
    def reachingPoints_natural_rec(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        #print("reachingPoints(%d, %d)" % (sx, sy))
        if sx == tx and sy == ty:
            return True
        if sx > tx or sy > ty: return False

        if not self.reachingPoints_natural_rec(sx + sy, sy, tx, ty):
            return self.reachingPoints_natural_rec(sx, sx + sy, tx, ty)
        return True

    def reachingPoints_fast_seq(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        if sx == tx and sy == ty:
            return True
        if tx == ty:
            return (sx == sy == tx)
        if sx > tx or sy > ty: return False

        while tx > sx or ty > sy:
            if tx > ty:
                tx -= ty
            elif tx < ty:
                ty -= tx
            else:
                return (sx == sy == tx)

        return (sx == tx) and (sy == ty)

    def reachingPoints_superfast_seq(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        if sx == tx and sy == ty:
            return True
        if tx == ty:
            return (sx == sy == tx)
        if sx > tx or sy > ty: return False

        while tx > sx or ty > sy:
            if tx > ty:
                coef = max(int((tx-sx)/ty)-1, 1)
                #print("Reduces tx(%d) with %d * ty(%d)" % (tx, coef, ty))
                tx -= coef * ty
            else:
                coef = max(int((ty-sy)/tx)-1, 1)
                #print("Reduces ty(%d) with %d * tx(%d)" % (ty, coef, tx))
                ty -= coef * tx

        return (sx == tx) and (sy == ty)

    def reachingPoints_fast_rec(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        if sx == tx and sy == ty:
            return True
        if tx == ty:
            return (sx == sy == tx)
        if sx > tx or sy > ty: return False

        if tx > ty:
            return self.reachingPoints_fast_rec(sx, sy, tx-ty, ty)
        return self.reachingPoints_fast_rec(sx, sy, tx, ty-tx)

    def reachingPoints_superfast_rec(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        if sx == tx and sy == ty:
            return True
        if tx == ty:
            return (sx == sy == tx)
        if sx > tx or sy > ty: return False

        if tx > ty:
            coef = max(int((tx-sx)/ty)-1, 1)
            return self.reachingPoints_superfast_rec(sx, sy, tx-coef*ty, ty)
        coef = max(int((ty-sy)/tx)-1, 1)
        return self.reachingPoints_superfast_rec(sx, sy, tx, ty-coef*tx)

    def reachingPoints_sol(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        if (tx == ty): return (sx == sy and sx == tx)

        while ((sx != tx) or (sy != ty)):
            print("tx = %d, ty = %d" % (tx, ty))
            if ((tx < sx) or (ty < sy)): return False;

            if (tx > ty): tx -= max(int((tx-sx)/ty), 1) * ty;
            else: ty -= max(int((ty-sy)/tx), 1) * tx;

        print("End: tx = %d, ty = %d" % (tx, ty))
        return True;

    def reachingPoints(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        return self.reachingPoints_superfast_rec(sx, sy, tx, ty)

def check_solution():
    s = Solution()
    X = (1, 1)
    T = (3, 5)
    result = s.reachingPoints(X[0], X[1], T[0], T[1])
    assert(result == True)

    X = (3, 2)
    T = (42, 2)
    result = s.reachingPoints(X[0], X[1], T[0], T[1])
    assert(result == False)

    X = (1, 1)
    T = (2, 2)
    result = s.reachingPoints(X[0], X[1], T[0], T[1])
    assert(result == False)

    X = (1, 1)
    T = (1, 1)
    result = s.reachingPoints(X[0], X[1], T[0], T[1])
    assert(result == True)

    X = (10, 5)
    T = (15, 5)
    result = s.reachingPoints(X[0], X[1], T[0], T[1])
    assert(result == True)

    X = (35, 13)
    T = (455955547, 420098887)
    result = s.reachingPoints(X[0], X[1], T[0], T[1])
    assert(result == False)

    X = (1, 1)
    T = (1000000000, 1)
    result = s.reachingPoints(X[0], X[1], T[0], T[1])
    assert(result == True)

    print("All tests passed successfully!!")

check_solution()
