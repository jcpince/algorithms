/*
https://leetcode.com/problems/minimum-time-difference/

539. Minimum Time Difference
Medium
Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum minutes
difference between any two time points in the list.

Example 1:

Input: ["23:59","00:00"]
Output: 1

Note:

    The number of time points in the given list is at least 2 and won't exceed 20000.
    The input time is legal and ranges from 00:00 to 23:59.
*/
#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

const int HalfDayMinutes    = 12*60;
const int DayMinutes        = 2*HalfDayMinutes;

class Solution {
    int diff(int t0, int t1) {
        int mdiff = abs(t0 - t1);
        if (mdiff > HalfDayMinutes) mdiff = DayMinutes - mdiff;
        return mdiff;
    }
    int inline diffAdjusted(int t) {
        if (t > HalfDayMinutes) t = DayMinutes - t;
        return t;
    }
    int minDiff(vector<int>& timePoints, int start) {
        int mdiff = diff(timePoints[start], timePoints[start+1]);
        for (int idx = start+2 ; idx < timePoints.size() ; idx++)
            mdiff = min(mdiff, diff(timePoints[start], timePoints[idx]));
        return mdiff;
    }
    int time2int(string &_s) {
        size_t idx = 0;
        int hours = stoi(_s, &idx);
        int minutes = stoi(_s.substr(idx+1));
        return hours*60+minutes;
    }
public:
    int findMinDifference0(vector<string>& _timePoints) {

        vector<int> timePoints(_timePoints.size());
        int idx = 0;
        for (string tp : _timePoints)
            timePoints[idx++] = time2int(tp);

        int mdiff = INT_MAX;
        for (idx = 0 ; (idx+1) < timePoints.size() ; idx++)
            mdiff = min(mdiff, minDiff(timePoints, idx));
        return mdiff;
    }

        int findMinDifference(vector<string>& _timePoints) {

        vector<bool> timePoints(DayMinutes, false);
        int mintime = INT_MAX, maxtime = 0;
        for (string tp : _timePoints) {
            int t = time2int(tp);
            if (timePoints[t]) return 0;
            if (t < mintime) mintime = t;
            if (t > maxtime) maxtime = t;
            timePoints[t] = true;
        }

        int mdiff = INT_MAX, left = mintime, right = maxtime;
        while ((left < right) and (mdiff > 1)) {
            mdiff = min(mdiff, diffAdjusted(right - left));

            int new_left = left+1;
            while ((new_left < right) and !timePoints[new_left]) new_left++;
            if ((new_left == right) or !timePoints[new_left]) break; // no point between left and right
            mdiff = min(mdiff, diffAdjusted(new_left - left));
            left = new_left;

            int new_right = right-1;
            while ((new_right > left) and !timePoints[new_right]) new_right--;
            if (!timePoints[new_right]) {
                mdiff = min(mdiff, diffAdjusted(right - new_right));
                right = new_right;
            }
        }
        return mdiff;
    }
};
