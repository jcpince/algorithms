#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#ifndef DEBUG
#define ddump_ll()
#define dprintf(...)
#define dassert(...)
#else
#define ddump_ll() dump_ll()
#define dprintf printf
#define dassert assert
#endif

class DoubleLinkedListNode {
public:
    DoubleLinkedListNode *prev;
    DoubleLinkedListNode *next;
    int key;
    int val;

    DoubleLinkedListNode() : key(-1), val(-1), prev(nullptr), next(nullptr) {}
    static DoubleLinkedListNode* getLinkedList(int nb_nodes) {
        DoubleLinkedListNode *root = new DoubleLinkedListNode[nb_nodes]();

        for (int idx = 0 ; idx < nb_nodes ; idx++) {
            if (idx) root[idx].prev = &root[idx - 1];
            if (idx < (nb_nodes - 1)) root[idx].next = &root[idx + 1];
        }
        return root;
    }
    static DoubleLinkedListNode* getCircularLinkedList(int nb_nodes) {
        DoubleLinkedListNode *root = getLinkedList(nb_nodes);

        root[0].prev = &root[nb_nodes-1];
        root[nb_nodes-1].next = root;

        for (DoubleLinkedListNode *node = root ; node < &root[nb_nodes] ; node++) {
            assert(node->prev->next == node);
            assert(node->next->prev == node);
        }
        return root;
    }

    void remove() {
        dassert(prev->next == this);
        dassert(next->prev == this);
        prev->next = next;
        next->prev = prev;
    }

    void insertAfter(DoubleLinkedListNode *node) {
        dassert(prev->next == this);
        dassert(next->prev == this);
        DoubleLinkedListNode *old_next = node->next;
        node->next = old_next;
        old_next->prev = node;
        node->prev = this;
        this->next = node;
    }

    void insertBefore(DoubleLinkedListNode *node) {
        dassert(prev->next == this);
        dassert(next->prev == this);
        DoubleLinkedListNode *old_prev = prev;
        node->prev = old_prev;
        old_prev->next = node;
        node->next = this;
        this->prev = node;
    }
};

class LRUCache {
    void inline set_newest_position(DoubleLinkedListNode *elem) {
        if (oldest->prev == elem) // already newest
            return;

        if (oldest == elem)
            oldest = oldest->next;
        else {
            elem->remove();
            oldest->insertBefore(elem);
        }
    }
#ifdef DEBUG
    void inline dump_ll() {
        dprintf("llist from oldest to newest: ");
        DoubleLinkedListNode *elem = oldest;
        dprintf("%d(%d) -> ", elem->key, elem->val);
        elem = elem->next;
        for (; elem != oldest ; elem = elem->next) {
            dprintf("%d(%d) -> ", elem->key, elem->val);
        }
        dprintf("\n");
    }
#endif

    map<int, DoubleLinkedListNode*> cache;
    DoubleLinkedListNode *root;

    DoubleLinkedListNode *oldest, *next_available;
    int capacity;
public:
    LRUCache(int capacity) : capacity(capacity) {
        root = DoubleLinkedListNode::getCircularLinkedList(capacity);
        next_available = oldest = root;
    }
    ~LRUCache() {
        cache.clear();
        delete[] root;
    }

    int get(int key) {
        map<int, DoubleLinkedListNode*>::iterator it = cache.find(key);
        if (it == cache.end()) {
            dprintf("get %d => not found\n", key);
            ddump_ll();
            return -1;
        }

        /* found it, move the element to the newest of the list */
        DoubleLinkedListNode *elem = it->second;
        set_newest_position(elem);
        dprintf("get %d => %d\n", key, elem->val);
        ddump_ll();
        return elem->val;
    }

    void put(int key, int value) {
        dprintf("put %d with %d\n", key, value);
        map<int, DoubleLinkedListNode*>::iterator it = cache.find(key);
        if (it == cache.end()) {
            // not found, replace oldest with new value and move oldest forward
            if (oldest->key > 0) cache.erase(oldest->key);
            oldest->val = value;
            oldest->key = key;
            cache[key] = oldest;
            oldest = oldest->next;
        } else {
            // found it, move the element to the newest position
            DoubleLinkedListNode *elem = it->second;
            elem->val = value;
            set_newest_position(elem);
        }
        ddump_ll();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(int argc, char **argv) {
    LRUCache *cache;

    cache = new LRUCache( 2 ); // capacity
    cache->put(1, 1);
    cache->put(2, 2);
    assert(cache->get(1) == 1);       // returns 1
    cache->put(3, 3);    // evicts key 2
    assert(cache->get(2) == -1);       // returns -1 (not found)
    cache->put(4, 4);    // evicts key 1
    assert(cache->get(1) == -1);        // returns -1 (not found)
    assert(cache->get(3) == 3);        // returns 3
    assert(cache->get(4) == 4);        // returns 4
    free(cache);

    cache = new LRUCache( 2 );
    cache->put(2, 1);
    cache->put(2, 2);
    assert(cache->get(2) == 2);
    cache->put(1, 1);
    cache->put(4, 1);    // evicts key 2
    assert(cache->get(2) == -1);        // returns -1 (not found)
    free(cache);

    cache = new LRUCache( 2 );
    cache->put(2, 2);
    cache->put(3, 3);
    assert(cache->get(3) == 3);
    assert(cache->get(2) == 2);
    cache->put(4, 4);    // evicts key 3
    assert(cache->get(2) == 2);        // returns -1 (not found)
    assert(cache->get(3) == -1);        // returns -1 (not found)
    assert(cache->get(4) == 4);        // returns -1 (not found)
    free(cache);

    cache = new LRUCache( 10 );
    cache->put(10, 13);
    cache->put(3, 17);
    cache->put(6, 11);
    cache->put(10, 5);
    cache->put(9, 10);
    assert(cache->get(13) == -1);
    cache->put(2, 19);
    assert(cache->get(2) == 19);
    assert(cache->get(3) == 17);
    cache->put(5, 25);
    assert(cache->get(8) == -1);
    cache->put(9, 22);
    cache->put(5, 5);
    cache->put(1, 30);
    assert(cache->get(11) == -1);
    cache->put(9, 12);
    assert(cache->get(7) == -1);
    assert(cache->get(5) == 5);
    assert(cache->get(8) == -1);
    assert(cache->get(9) == 12);
    cache->put(4, 30);
    cache->put(9, 3);
    assert(cache->get(9) == 3);
    assert(cache->get(10) == 5);
    assert(cache->get(10) == 5);
    cache->put(6, 14);
    cache->put(3, 1);
    assert(cache->get(3) == 1);
    cache->put(10, 11);
    assert(cache->get(8) == -1);
    cache->put(2, 14);
    assert(cache->get(1) == 30);
    assert(cache->get(5) == 5);
    assert(cache->get(4) == 30);
    cache->put(11, 4);
    cache->put(12, 24);
    cache->put(5, 18);
    assert(cache->get(13) == -1);
    cache->put(7, 23);
    assert(cache->get(8) == -1);
    assert(cache->get(12) == 24);
    cache->put(3, 27);
    cache->put(2, 12);
    assert(cache->get(5) == 18);
    cache->put(2, 9);
    cache->put(13, 4);
    cache->put(8, 18);
    cache->put(1, 7);
    assert(cache->get(6) == -1);
    cache->put(9, 29);
    cache->put(8, 21);
    assert(cache->get(5) == 18);
    cache->put(6, 30);
    cache->put(1, 12);
    assert(cache->get(10) == -1);
    cache->put(4, 15);
    cache->put(7, 22);
    cache->put(11, 26);
    cache->put(8, 17);
    cache->put(9, 29);
    assert(cache->get(5) == 18);
    cache->put(3, 4);
    cache->put(11, 30);
    assert(cache->get(12) == -1);
    cache->put(4, 29);
    assert(cache->get(3) == 4);
    assert(cache->get(9) == 29);
    assert(cache->get(6) == 30);
    cache->put(3, 4);
    assert(cache->get(1) == 12);
    assert(cache->get(10) == -1);
    cache->put(3, 29);
    cache->put(10, 28);
    cache->put(1, 20);
    cache->put(11, 13);
    assert(cache->get(3) == 29);
    cache->put(3, 12);
    cache->put(3, 8);
    cache->put(10, 9);
    cache->put(3, 26);
    assert(cache->get(8) == 17);
    assert(cache->get(7) == 22);
    assert(cache->get(5) == 18);
    cache->put(3, 17);
    cache->put(2, 27);
    cache->put(11, 15);
    assert(cache->get(12) == -1);
    cache->put(9, 19);
    cache->put(2, 15);
    cache->put(3, 16);
    assert(cache->get(1) == 20);
    cache->put(12, 17);
    cache->put(9, 1);
    cache->put(6, 19);
    assert(cache->get(4) == -1);
    assert(cache->get(5) == 18);
    assert(cache->get(5) == 18);
    cache->put(8, 1);
    cache->put(11, 7);
    cache->put(5, 2);
    cache->put(9, 28);
    assert(cache->get(1) == 20);
    cache->put(2, 2);
    cache->put(7, 4);
    cache->put(4, 22);
    cache->put(7, 24);
    cache->put(9, 26);
    cache->put(13, 28);
    cache->put(11, 26);
    free(cache);

    return 0;
}
