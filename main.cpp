#include <iostream>

struct nodeType {
    int data;
    nodeType *next;
};

void initializeList(nodeType *&head, nodeType *&tail, size_t &count) {
    // Start with an empty list.
    head = nullptr;
    tail = nullptr;
    count = 0;
}

bool isEmptyList(nodeType *head) {
    return head == nullptr;
}

void print(nodeType *head) {
    nodeType *current = head;
    bool firstValue = true;

    while (current != nullptr) {
        // Print the values in order, one space at a time.
        if (!firstValue) {
            std::cout << ' ';
        }
        std::cout << current->data;
        firstValue = false;
        current = current->next;
    }

    std::cout << '\n';
}

size_t length(size_t count) {
    return count;
}

void destroyList(nodeType *&head, nodeType *&tail, size_t &count) {
    // Free every node so we leave no heap memory behind.
    while (head != nullptr) {
        nodeType *nextNode = head->next;
        delete head;
        head = nextNode;
    }

    tail = nullptr;
    count = 0;
}

int front(nodeType *head) {
    return head != nullptr ? head->data : 0;
}

int back(nodeType *tail) {
    return tail != nullptr ? tail->data : 0;
}

bool search(nodeType *head, int target) {
    nodeType *current = head;

    while (current != nullptr) {
        // Keep walking until we either find the value or run out of list.
        if (current->data == target) {
            return true;
        }
        current = current->next;
    }

    return false;
}

void insertFirst(nodeType *&head, nodeType *&tail, size_t &count, int newItem) {
    nodeType *newNode = new nodeType{newItem, head};
    head = newNode;

    if (tail == nullptr) {
        tail = newNode;
    }

    ++count;
}

void insertLast(nodeType *&head, nodeType *&tail, size_t &count, int newItem) {
    nodeType *newNode = new nodeType{newItem, nullptr};

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    ++count;
}

void deleteNode(nodeType *&head, nodeType *&tail, size_t &count, int delItem) {
    if (head == nullptr) {
        return;
    }

    // Handle the front of the list first.
    if (head->data == delItem) {
        nodeType *nodeToDelete = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete nodeToDelete;
        --count;
        return;
    }

    nodeType *previous = head;
    nodeType *current = head->next;

    while (current != nullptr && current->data != delItem) {
        // Move both pointers forward together until we hit the match.
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    previous->next = current->next;
    if (current == tail) {
        tail = previous;
    }

    delete current;
    --count;
}

int main() {
    nodeType *head = nullptr;
    nodeType *tail = nullptr;
    size_t count = 0;
    int value = 0;

    initializeList(head, tail, count);

    // Keep reading numbers until the sentinel value shows up.
    while (true) {
        std::cout << "Enter an integer (-999 to stop): ";
        if (!(std::cin >> value)) {
            break;
        }

        if (value == -999) {
            break;
        }

        insertLast(head, tail, count, value);
    }

    // Show the list and a few basic facts about it.
    std::cout << "\nLinked list: ";
    if (isEmptyList(head)) {
        std::cout << "empty\n";
    } else {
        print(head);
        std::cout << "Length: " << length(count) << '\n';
        std::cout << "Front: " << front(head) << '\n';
        std::cout << "Back: " << back(tail) << '\n';
    }

    std::cout << "Search 59: " << (search(head, 59) ? "found" : "not found") << '\n';
    std::cout << "Search 1000: " << (search(head, 1000) ? "found" : "not found") << '\n';

    // Remove 59 so the delete function gets a real test run.
    std::cout << "Deleting 59...\n";
    deleteNode(head, tail, count, 59);
    std::cout << "Linked list after deleting 59: ";
    if (isEmptyList(head)) {
        std::cout << "empty\n";
    } else {
        print(head);
    }

    destroyList(head, tail, count);
    return 0;
}
