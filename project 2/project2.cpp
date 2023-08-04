#include <iostream>
#include <unordered_set>

struct Node {
    int data;
    struct Node* next;
};

struct Node* findCycleStart(struct Node* head) {
    std::unordered_set<struct Node*> visited;

    while (head != nullptr) {
        if (visited.count(head) > 0) {
            return head;
        }

        visited.insert(head);
        head = head->next;
    }

    return nullptr;
}

struct Node* createNode(int data) {
    struct Node* newNode = new struct Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = head->next;

    struct Node* cycleStart = findCycleStart(head);

    if (cycleStart != nullptr) {
        std::cout << "Cycle found. Starting node data: " << cycleStart->data << std::endl;
    }
    else {
        std::cout << "No cycle found" << std::endl;
    }

    return 0;
}