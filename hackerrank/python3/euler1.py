#!/bin/python3
#
# Sum up the multiples of 3 or 5 from 0 to n
# Note that the sum from 0 to n2 with n2 > n1 is equal to the sum from 0 to n1
# plus the sum from n1 to n2
#

import sys
import threading
import time
import queue
import multiprocessing

SHOW_DBG = False
SHOW_INFO = False
MAX_THREADS = multiprocessing.cpu_count()
MAX_RANGE_PER_THREAD = 100000

t = int(input().strip())
ns = list()
for a0 in range(t):
   ns.append(int(input().strip()))

def dbg_print(*kargs):
    if SHOW_DBG:
        print(*kargs)

def info_print(*kargs):
    if SHOW_INFO:
        print(*kargs)

class EulerThread (threading.Thread):
    def __init__(self, threadID, name):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self._inqueue = queue.Queue()
        self._outqueue = queue.Queue()

    def enqueue_request(self, start, end):
        self._inqueue.put((start, end))

    def dequeue_result(self):
        if self._outqueue.empty():
            return None
        return self._outqueue.get()

    def run(self):
        while not self._inqueue.empty():
            (start, end) = self._inqueue.get()
            assert(start < end)
            start0 = start
            # adjust the start position
            start, result = self.find_30_start(start, end)
            while True:
                start += 3
                if start >= end:
                    break
                dbg_print('%s: run adds returns ' % self.name, start)
                result += start
                start += 2
                if start >= end:
                    break
                dbg_print('%s: run adds returns ' % self.name, start)
                result += start
                start += 1
                if start >= end:
                    break
                dbg_print('%s: run adds returns ' % self.name, start)
                result += start
                start += 3
                if start >= end:
                    break
                dbg_print('%s: run adds returns ' % self.name, start)
                result += start
                start += 1
                if start >= end:
                    break
                dbg_print('%s: run adds returns ' % self.name, start)
                result += start
                start += 2
                if start >= end:
                    break
                dbg_print('%s: run adds returns ' % self.name, start)
                result += start
                start += 3
                if start >= end:
                    break
                dbg_print('%s: run adds returns ' % self.name, start)
                result += start
            self._outqueue.put((start0, end, result))

    def find_30_start(self, start, end):
        mod = start % 30
        if mod == 0:
            dbg_print('%s: find_30_start returns (%d, %d)' % (self.name, start, start))
            return start, start
        # Sum the multiples of 3 or 5 between start and the next multiple of 10
        result = 0
        end = min(start + 30 - mod, end)
        for idx in range(start, end):
            if idx % 3 == 0 or idx % 5 == 0:
                result += idx
        dbg_print('%s: find_30_start returns (%d, %d) with start %d' % (self.name, end, result, start))
        return end, result


# Creates the pool of threads
threads = list()
for idx in range(MAX_THREADS):
    threads.append(EulerThread(idx, "euler_thread_%d" % idx))

# enqueue the requests
info_print('Enqueueing the requests')
sorted_ns = sorted(ns)
ordered_results = list()
start = 0
thread_idx = 0
nb_requests = 0
for end in sorted_ns:
    if end - start > MAX_RANGE_PER_THREAD:
        for tmp in range(start, end, MAX_RANGE_PER_THREAD):
            threads[thread_idx].enqueue_request(tmp, tmp+MAX_RANGE_PER_THREAD)
            thread_idx = (thread_idx + 1) % MAX_THREADS
            nb_requests += 1
        start = tmp
    if start < end:
        dbg_print('starting a thread for %d, %d' % (start, end))
        threads[thread_idx].enqueue_request(start, end)
        nb_requests += 1
        thread_idx = (thread_idx + 1) % MAX_THREADS
    start = end
info_print('Enqueued %d requests' % nb_requests)

# start the threads and wait for all to finish
info_print('Starting the %d threads' % MAX_THREADS)
for idx in range(MAX_THREADS):
    threads[idx].start()

info_print('Waiting the threads')
for idx in range(MAX_THREADS):
    threads[idx].join()

# dequeue the intermediary results
info_print('Dequeing the requests')
for idx in range(MAX_THREADS):
    while True:
        queueitem = threads[idx].dequeue_result()
        if queueitem is None:
            break
        ordered_results.append(list(queueitem))

# order them, rebuild the full results and publish a dictionnary
info_print('Ordering and consilidating the results')
results = dict()
ordered_results.sort()
result = 0
for idx, result_item in enumerate(ordered_results):
    start, end, intermidiate_result = result_item
    dbg_print('Result between %d and %d is %d' % (start, end, intermidiate_result))
    result += intermidiate_result
    results[end] = result

# now, output the results (pushed n -1)
info_print('Showing the results')
for n in ns:
    print(results[n])

def unit_tests():
    t = EulerThread(1, "unit_tests_1")
    start, result = t.find_30_start(0, 10)
    assert(start == 0 and result == 0)
    start, result = t.find_30_start(1, 10)
    assert(start == 10 and result == 3+5+6+9+10)
    start, result = t.find_30_start(2, 10)
    assert(start == 10 and result == 3+5+6+9+10)
    start, result = t.find_30_start(3, 10)
    assert(start == 10 and result == 3+5+6+9+10)
    start, result = t.find_30_start(4, 10)
    assert(start == 10 and result == 5+6+9+10)
    start, result = t.find_30_start(5, 10)
    assert(start == 10 and result == 5+6+9+10)
    start, result = t.find_30_start(6, 10)
    assert(start == 10 and result == 6+9+10)
    start, result = t.find_30_start(7, 10)
    assert(start == 10 and result == 9+10)
    start, result = t.find_30_start(8, 10)
    assert(start == 10 and result == 9+10)
    start, result = t.find_30_start(9, 10)
    assert(start == 10 and result == 10+9)
    start, result = t.find_30_start(10, 10)
    assert(start == 10 and result == 10)
    print('find_30_start unitary tests succeeded')

    t = EulerThread(1, "unit_tests_2")
    t.enqueue_request(0,9)
    t.start()
    t.join()
    (_, _, result) = t.dequeue_result()
    assert(result == 23)

    t = EulerThread(2, "unit_tests_3")
    t.enqueue_request(0,99)
    t.start()
    t.join()
    (_, _, result) = t.dequeue_result()
    assert(result == 2318)

    assert(t.dequeue_result() is None)
    print('Basic computation unitary tests succeeded')

# 1000000000 => 233333333166666668
