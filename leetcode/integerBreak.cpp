class Solution {
public:
    int integerBreak(int n) {
        switch (n) {
            case 2: return 1;
            case 3: return 2;
            case 4: return 4;
        }

        double pow3 = n / 3, part3 = pow3 * 3;
        if (part3 == n) return pow(3, pow3);
        else if ((part3 + 2) == n) return  pow(3, pow3) * 2;
        else return  pow(3, pow3-1) * 4;
    }
};
