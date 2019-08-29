/*
https://leetcode.com/problems/print-zero-even-odd/

1116. Print Zero Even Odd
Medium

Suppose you are given the following code:

class ZeroEvenOdd {
  public ZeroEvenOdd(int n) { ... }      // constructor
  public void zero(printNumber) { ... }  // only output 0's
  public void even(printNumber) { ... }  // only output even numbers
  public void odd(printNumber) { ... }   // only output odd numbers
}

The same instance of ZeroEvenOdd will be passed to three different threads:

    Thread A will call zero() which should only output 0's.
    Thread B will call even() which should only ouput even numbers.
    Thread C will call odd() which should only output odd numbers.

Each of the threads is given a printNumber method to output an integer. Modify the given program to output the series 010203040506... where the length of the series must be 2n.



Example 1:

Input: n = 2
Output: "0102"
Explanation: There are three threads being fired asynchronously. One of them calls zero(), the other calls even(), and the last one calls odd(). "0102" is the correct output.

Example 2:

Input: n = 5
Output: "0102030405"
*/

enum { EStateZero, EStateOdd, EStateEven } eState_t;

class ZeroEvenOdd {
private:
    int n;
    atomic_int state;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        state = EStateZero;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        int count = 0;
        while (count++ < n) {
            while (state != EStateZero)
                this_thread::yield();
            printNumber(0);
            if (count % 2) state = EStateOdd;
            else state = EStateEven;
        }
    }

    void even(function<void(int)> printNumber) {
        int count = 0;
        while (count++ < n) {
            if (!count || count % 2) continue;
            while (state != EStateEven)
                this_thread::yield();
            printNumber(count);
            state = EStateZero;
        }
    }

    void odd(function<void(int)> printNumber) {
        int count = 0;
        while (count++ < n) {
            if (!(count % 2)) continue;
            while (state != EStateOdd)
                this_thread::yield();
            printNumber(count);
            state = EStateZero;
        }
    }
};
/*
class ZeroEvenOdd {
private:
    int n;
    int k;
    mutex mZ;
    mutex mE;
    mutex mO;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        this->k=0;
        mE.lock();
        mO.lock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while(true) {
          mZ.lock();
          if (k < n) {
            printNumber(0);
          }
          k++;
          if (k > n) {
            mZ.unlock();
            mO.unlock();
            mE.unlock();
            return;
          }
          if (k & 1 == 1) {
            mO.unlock();
          } else {
            mE.unlock();
          }
        }
    }

    void even(function<void(int)> printNumber) {
        while (true) {
          mE.lock();
          if (k>n) {
            return;
          }
          printNumber(k);
          mZ.unlock();
        }
    }

    void odd(function<void(int)> printNumber) {
        while(true) {
          mO.lock();
          if (k>n) {
            return;
          }
          printNumber(k);
          mZ.unlock();
        }
    }
};*/
