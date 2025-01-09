#include <unordered_map>

class DoublyLinkedListNode {
public:
    int key;
    int val;
    DoublyLinkedListNode* prev;
    DoublyLinkedListNode* next;
    DoublyLinkedListNode(int key, int val)
        : key(key), val(val), prev(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    int capacity;
    // A hash map that maps keys to nodes.
    std::unordered_map<int, DoublyLinkedListNode*> hashmap;
    // Initialize the head and tail dummy nodes and connect them to 
    // each other to establish a basic two-node doubly linked list.
    DoublyLinkedListNode* head;
    DoublyLinkedListNode* tail;
    LRUCache(int capacity) : capacity(capacity) {
        head = new DoublyLinkedListNode(-1, -1);
        tail = new DoublyLinkedListNode(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (hashmap.find(key) == hashmap.end()) {
            return -1;
        }
        // To make this key the most recently used, remove its node and 
        // re-add it to the tail of the linked list. 
        removeNode(hashmap[key]);
        addToTail(hashmap[key]);
        return hashmap[key]->val;
    }

    void put(int key, int val) {
        // If a node with this key already exists, remove it from the 
        // linked list.
        if (hashmap.find(key) != hashmap.end()) {
            removeNode(hashmap[key]);
        }
        DoublyLinkedListNode* node = new DoublyLinkedListNode(key, val);
        hashmap[key] = node;
        // Remove the least recently used node from the cache if adding 
        // this new node will result in an overflow.
        if (hashmap.size() > capacity) {
            hashmap.erase(head->next->key);
            removeNode(head->next);
        }
        addToTail(node);
    }

    void addToTail(DoublyLinkedListNode* node) {
        DoublyLinkedListNode* prevNode = tail->prev;
        node->prev = prevNode;
        node->next = tail;
        prevNode->next = node; 
        tail->prev = node; 
    }

    void removeNode(DoublyLinkedListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
};