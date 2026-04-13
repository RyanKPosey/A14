#include <iostream>

struct nodeType {
    int data;
    nodeType *next;
};

void appendNode(nodeType *&head, nodeType *&tail, int value) {
    nodeType *newNode = new nodeType{value, nullptr};

    // First item becomes both the head and the tail.
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    // Otherwise, tack it on to the end of the list.
    tail->next = newNode;
    tail = newNode;
}

void printList(const nodeType *head) {
    const nodeType *current = head;
    bool firstValue = true;

    while (current != nullptr) {
        // Keep the output on one line with spaces between values.
        if (!firstValue) {
            std::cout << ' ';
        }
        std::cout << current->data;
        firstValue = false;
        current = current->next;
    }
    std::cout << '\n';
}

void deleteList(nodeType *&head) {
    // Walk the list and free each node one by one.
    while (head != nullptr) {
        nodeType *nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

int main() {
    nodeType *head = nullptr;
    nodeType *tail = nullptr;
    int value = 0;

    while (true) {
        // Stop when the sentinel shows up.
        std::cout << "Enter an integer (-999 to stop): ";
        if (!(std::cin >> value)) {
            break;
        }
        if (value == -999) {
            break;
        }
        appendNode(head, tail, value);
    }

    printList(head);
    deleteList(head);
    return 0;
}
