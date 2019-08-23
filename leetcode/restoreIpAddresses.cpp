class Solution {
    static inline bool isValid(string &group) {
        uint64_t tmp = stoul(group);
        if (tmp > 255) return false;
        if ((tmp == 0) and (group.size() > 1)) return false;
        if ((tmp != 0) and (group[0] == '0')) return false;
        return true;
    }
    static inline string splitAddress(string &s, int g1_size, int g2_size, int g3_size, int g4_size) {
        string g1 = s.substr(0, g1_size);
        //printf("s(%s): g1_size %d, g1 %s\n", s.c_str(), g1_size, g1.c_str());
        if (!isValid(g1)) return "";
        string g2 = s.substr(g1_size, g2_size);
        if (!isValid(g2)) return "";
        string g3 = s.substr(g1_size + g2_size, g3_size);
        if (!isValid(g3)) return "";
        string g4 = s.substr(g1_size + g2_size + g3_size, g4_size);
        if (!isValid(g4)) return "";
        return g1 + "." + g2 + "." + g3 + "." + g4;
    }
public:
    vector<string> restoreIpAddresses(string s) {
        if ((s.size() < 4) or (s.size() > 12)) return {};

        int ssz = (int)s.size();
        vector<string> ans;
        for (int g1_size = 1 ; g1_size < 4 ; g1_size++) {
            for (int g2_size = 1 ; g2_size < 4 ; g2_size++) {
                for (int g3_size = 1 ; g3_size < 4 ; g3_size++) {
                    int g4_size = ssz - g1_size - g2_size - g3_size;
                    if (g4_size < 1) continue;

                    string ip = splitAddress(s, g1_size, g2_size, g3_size, g4_size);
                    if (ip != "")
                        ans.push_back(ip);
                }
            }
        }
        return ans;
    }
    vector<string> restoreIpAddresses2(string s) {
        if ((s.size() < 4) or (s.size() > 12)) return {};

        vector<string> ans;
        uint64_t bignumber = stoul(s);
        if (bignumber == 0) return {"0.0.0.0"};
        uint64_t g1, g2, g3, g4, g4_mod, g3_mod, g2_mod;
        for (g4_mod = 10 ; g4_mod < 10000 ; g4_mod *= 10) {
            g4 = bignumber % g4_mod;
            //if (g4 == 0) continue;
            if (g4 > 255) break;
            //printf("g4: %ld\n", g4);
            for (g3_mod = 10 ; g3_mod < 10000 ; g3_mod *= 10) {
                g3 = ((bignumber - g4) / g4_mod) % g3_mod;
                //if (g3 == 0) continue;
                if (g3 > 255) break;
                //printf("g3: %ld\n", g3);
                if (((g3 * g3_mod) + g4) >= bignumber) break;
                for (g2_mod = 10; g2_mod < 10000 ; g2_mod *= 10) {
                    g2 = ((((bignumber - g4) / g4_mod) - g3) / g3_mod) % g2_mod;
                    g1 = bignumber / (g2_mod * g3_mod * g4_mod);
                    //printf("%ld.%ld.%ld.%ld\n", g1, g2, g3, g4);
                    //if (g2 == 0) continue;
                    if (g2 > 255) break;
                    if (g1 > 255) continue;
                    string ip = to_string(g1) + "." + to_string(g2) + "." + to_string(g3) +
                            "." + to_string(g4);
                    ans.push_back(ip);
                }
            }
        }
        //printf("Done\n");
        return ans;
    }
};
