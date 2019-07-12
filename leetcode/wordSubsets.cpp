class Solution {
    int findSorted(const char *array, const char value, int start, int end) {
        int middle, start0 = start;
        if(start == end) return (array[start] == value ? start : -1);

        while(start < end)
        {
            middle = (start + end) / 2;
            if(array[middle] == value) {
                /* Rewind in case we didn't get the first one of the range */
                while ((middle > start0) and (array[middle - 1] == value)) middle--;
                return middle;
            }
            else if (array[middle] > value) end = middle - 1;
            else start = middle + 1;
        }
        if (array[start] == value) {
            while ((start > start0) and (array[start - 1] == value)) start--;
            return start;
        }
        return -1;
    }

    bool isUniversal(string wa, string wb) {
        int idx = 0, end = wa.length();
        const char *stra = wa.c_str(), *strb = wb.c_str();

        while (*stra && *strb) {
            idx = findSorted(stra, *strb++, 0, end);
            if (idx == -1) return false;
            stra += idx + 1;
            end -= idx + 1;
        }
        return !*strb;
    }

    bool isUniversal(const int *a, const int *b) {
        for (int idx = 0 ; idx < 26 ; idx++)
            if (*a++ < *b++) return false;
        return true;
    }
public:
    vector<string> wordSubsets0(vector<string>& A, vector<string>& B) {
        vector<string> orderedA, orderedB;
        for (string w : A) {
            sort(w.begin(), w.end());
            orderedA.push_back(w);
        }
        for (string w : B) {
            sort(w.begin(), w.end());
            orderedB.push_back(w);
        }

        int idx = 0;
        vector<string> result;
        for (string wa : orderedA) {
            bool isu = true;
            for (string wb : orderedB) {
                isu = isUniversal(wa, wb);
                if (!isu) break;
            }
            if (isu) result.push_back(A[idx]);
            idx++;
        }

        return result;
    }

    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        vector<int[26]> As(A.size());
        int idx = 0;
        for (string w : A) {
            memset(As[idx], 0, 26*sizeof(int));
            const char *a = w.c_str();
            while(*a) {As[idx][*a - 'a']++;a++;}
            idx++;
        }

        int allBs[26] = {0};
        for (string w : B) {
            sort(w.begin(), w.end());
            const char *b = w.c_str();
            while(*b) {
                int count = 1;
                char c = *b;
                while (c == *(b+1)) {b++;count++;}
                allBs[c - 'a'] = max(allBs[c - 'a'], count);
                b++;
            }
        }

        vector<string> result;
        idx = 0;
        for (auto a : As) {
            if (isUniversal(a, allBs)) result.push_back(A[idx]);
            idx++;
        }

        return result;
    }
};
