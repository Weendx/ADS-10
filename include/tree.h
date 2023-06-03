// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class Tree {
    struct Node {
        char data;
        std::vector<Node*> childrens;
        bool isEmpty() { return !data; }
    };

    Node* root;
    Node* createNode(char element, std::vector<char> elements);
    void storePerms(Node* root, std::vector<char> permutation);

    int maxPerm;
    std::vector<std::vector<char>> perms;
 public:
    explicit Tree(std::vector<char> elements);
    std::vector<char> getPerm(int n) const;
};

Tree::Node* Tree::createNode(char element, std::vector<char> elements) {
    Node* node = new Node();
    if (elements.empty())
        return node;
    node->data = element;
    std::vector<char> other;
    for (auto& e : elements) {
        if (e == element)
            continue;
        other.push_back(e);
    }
    for (auto& e : other) {
        Node* child = createNode(e, other);
        node->childrens.push_back(child);
    }
    return node;
}

void Tree::storePerms(Node* root, std::vector<char> permutation) {
    if (!root->isEmpty()) {
        permutation.push_back(root->data);
        for (Node* ch : root->childrens)
            storePerms(ch, permutation);
    }
    if (root->childrens.empty()) {
        perms.push_back(permutation);
        // permutation.clear();
    }
}

Tree::Tree(std::vector<char> elements) {
    if (!elements.empty()) {
        root = new Node();
        for (int i = 0; i < elements.size(); ++i) {
            auto ch = createNode(elements[i], elements);
            root->childrens.push_back(ch);
            storePerms(ch, std::vector<char>());
            maxPerm *= i + 1;
        }
    }
}

std::vector<char> Tree::getPerm(int n) const {
    if (n > perms.size())
        return std::vector<char>();
    return perms[n-1];
}

#endif  // INCLUDE_TREE_H_
