#define MEM_SEGMENT_SIZE  128
#define MEM_SEGMENT_ALIGN 0x800

struct __attribute__((packed)) QueueNode {
    struct QueueNode *next;
    int val;
    uint8_t padding[4];
};

static_assert(MEM_SEGMENT_SIZE * sizeof(struct QueueNode) <= MEM_SEGMENT_ALIGN);

class MyQueue {
    int total_size;
    int current_size;
    vector<struct QueueNode*> mem_segments;
    vector<struct QueueNode*> free_segments;
    struct QueueNode *push_segment;
    struct QueueNode *pop_segment;
    struct QueueNode *head;
    struct QueueNode *tail;

    bool inline isLastNodeFromSegment(struct QueueNode *node) {
        return (((uint64_t)node + sizeof(struct QueueNode)) & (MEM_SEGMENT_ALIGN - 1)) == 0;
    }
public:
    /** Initialize your data structure here. */
    MyQueue() : total_size(MEM_SEGMENT_SIZE), current_size(0) {
        /* Allocate the inital memory */
        allocate_new_push_segment();
        pop_segment = push_segment;

        head = pop_segment;
        tail = push_segment;
    }

    void allocate_new_push_segment() {
        struct QueueNode *segment = (struct QueueNode *)aligned_alloc(MEM_SEGMENT_ALIGN, MEM_SEGMENT_SIZE * sizeof(struct QueueNode));
        assert(segment);
        assert(((uint64_t)segment & (MEM_SEGMENT_ALIGN - 1)) == 0);

        mem_segments.push_back(segment);
        push_segment = segment;
    }

    /** Push element x to the back of queue. */
    void push(int x) {
        current_size++;
        if (current_size > total_size) {
            if (free_segments.size()) {
                push_segment = free_segments.back();
                free_segments.pop_back();
                tail->next = push_segment;
            } allocate_new_push_segment();
        } else tail->next = (struct QueueNode*)((uint64_t)tail + sizeof(struct QueueNode));
        tail->val = x;
        tail = tail->next;
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        current_size--;
        int val = head->val;
        if (isLastNodeFromSegment(head)) {
            free_segments.push_back((struct QueueNode*)((uint64_t)head & (MEM_SEGMENT_ALIGN - 1)));
        }
        head = head->next;
        return val;
    }

    /** Get the front element. */
    int peek() {
        return head->val;
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return (head==tail);
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
