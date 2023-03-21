#include <cstdlib>

#include <vector>
//
// Created by musht on 21.12.2022.
//

class Node {
public:
    int val;
    Node *next;
    Node(int v, Node *nxt) : val(v), next(nxt) {}
};

class Stack {
private:
    Node *top = nullptr;
public:
    Node * _pop_not_delete() {
        if (!top)
            std::exit(-10);
        Node *n = top;
        top = top->next;
        return n;
    }
    virtual void push(int x) {
        top = new Node(x, top);
    }
    virtual int pop() {
        auto n = _pop_not_delete();
        int ret = n->val;
        delete n;
        return ret;
    }
    virtual bool has_elements() {
        return top;
    }
    virtual int peek() {
        return top->val;
    }
};

class PerStack : public Stack {
private:
    std::vector<Stack> vers;
    Stack version(int k) {
        return vers[vers.size() - 1 - k];
    }
public:
    void push(int x) override {
        Stack copy;
        if (!vers.empty())
            copy = version(0);
        copy.push(x);
        vers.push_back(copy);
    }
    int pop() override {
        Stack copy = version(0);
        int v = copy._pop_not_delete()->val;
        vers.push_back(copy);
        return v;
    }
    bool has_elements() override {
        return version(0).has_elements();
    }
    int peek() override {
        return version(0).peek();
    }

    void backTo(int steps) {
        if (steps < 1 or steps >= vers.size())
            std::exit(-15);
        vers.push_back(version(steps));
    }
};

class ListNode {
public:
    std::vector<int> vals;
    ListNode *next, *prev;
    ListNode(int k, ListNode *prv, ListNode *nxt) : next(nxt), prev(prv) {vals.reserve(k);}
};

class Queue {
private:
    Stack in, out;
public:
    void push(int x) {
        in.push(x);
    }
    int pop() {
        if (not out.has_elements())
            while(in.has_elements())
                out.push(in.pop());
        return out.pop();
    }
    bool has_elements() {
        return in.has_elements() or out.has_elements();
    }
};

Node *reverse(Node *head) {
    Node *cur = head, *prv = nullptr;
    while (cur) {
        Node *nxt = cur->next;
        cur->next = prv;
        prv = cur;
        cur = nxt;
    }
    return prv;
}

ListNode *reverse(ListNode *head) {
    ListNode *cur = head, *tail;
    while (cur) {
        tail = cur;
        ListNode *nxt = cur->next;
        cur->next = cur->prev;
        cur->prev = nxt;
        cur = nxt;
    }
    return tail;
}

ListNode *fromVector(const std::vector<int> &v, int k) {
    ListNode *prev = nullptr, *cur = nullptr, *head = nullptr;
    int s = 0;
    while (s < v.size()) {
        cur = new ListNode(k, prev, nullptr);
        if (prev)
            prev->next = cur;
        if (!head)
            head = cur;
        cur->vals = std::vector<int>(v.begin() + s, std::min(v.begin() + s + k, v.end()));
        s += k;
        prev = cur;
    }
    return head;
}