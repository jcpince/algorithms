from itertools import permutations

class Solution:
    def numTilePossibilities(self, tiles: str) -> int:
        res = set()
        for i in range(1, len(tiles)+1):
            res = res.union(set(permutations(tiles, i)))
        return len(res)

s = Solution()
assert(s.numTilePossibilities("AAB") == 8)
assert(s.numTilePossibilities("AAABBC") == 188)
