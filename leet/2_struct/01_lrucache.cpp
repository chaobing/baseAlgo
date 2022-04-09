#include "../leetcommon.hpp"

class LRUCache {
    struct DNode{
        int key;
        int val;
        DNode* prev;
        DNode* next;
        DNode(int x): val(x), prev(nullptr), next(nullptr){}
    };
private:
    DNode* head;
    DNode* tail;
    unordered_map<int, DNode*> cache;
    int cap;
    int size;
    void moveToHead(DNode* node){
        removeNode(node);
        addToHead(node);
    }
    void addToHead(DNode* node){
        node->next = head->next;
        head->next = node;
        node->next->prev = node;
        node->prev = head;
    }
    void removeNode(DNode* node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = nullptr;
        node->next = nullptr;
    }
    DNode* removeTail(){
        DNode* last = tail->prev;
        removeNode(last);
        return last;
    }
public:
    LRUCache(int capacity): cap(capacity) {
        head = new DNode(0);
        tail = new DNode(0);
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    
    int get(int key) {
        if(cache.find(key) == cache.end()) return -1;
        else{
            DNode* node = cache[key];
            moveToHead(node);
            return node->val;
        }
    }
    
    void put(int key, int value) {
        if(cache.find(key) != cache.end()){
            DNode* node = cache[key];
            node->val = value;
            moveToHead(node);
        }else{
            DNode* node = new DNode(value);
            node->key = key;
            addToHead(node);
            cache[key] = node;
            size++;
            if(size > cap){
                DNode* last = removeTail();
                cache.erase(last->key);
                size--;
                delete last;
            }
        }
    }
};

TEST(fun, lrucache) {
  LRUCache *obj = new LRUCache(2);
  obj->put(1, 1);
  obj->put(2, 2);
  EXPECT_EQ(1, obj->get(1));
  obj->put(3, 3);
  EXPECT_EQ(-1, obj->get(2));
  obj->put(4, 4);
  EXPECT_EQ(-1, obj->get(1));
  EXPECT_EQ(3, obj->get(3));
  EXPECT_EQ(4, obj->get(4));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
