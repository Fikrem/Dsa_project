#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    
    // Helper functions
    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }
    
    int getBalance(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    Node* balance(Node* node) {
        updateHeight(node);
        int balanceFactor = getBalance(node);
        
        // Left-Left case
        if (balanceFactor > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        
        // Left-Right case
        if (balanceFactor > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right-Right case
        if (balanceFactor < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        
        // Right-Left case
        if (balanceFactor < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    Node* insertNode(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        } else {
            // Duplicate - update the data
            node->data = value;
            return node;
        }
        
        return balance(node);
    }
    
    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    
    Node* removeNode(Node* node, const T& value) {
        if (!node) {
            return nullptr;
        }
        
        if (value < node->data) {
            node->left = removeNode(node->left, value);
        } else if (value > node->data) {
            node->right = removeNode(node->right, value);
        } else {
            // Node to be deleted found
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = removeNode(node->right, temp->data);
            }
        }
        
        if (!node) {
            return nullptr;
        }
        
        return balance(node);
    }
    
    Node* searchNode(Node* node, const T& value) const {
        if (!node || node->data == value) {
            return node;
        }
        
        if (value < node->data) {
            return searchNode(node->left, value);
        } else {
            return searchNode(node->right, value);
        }
    }
    
    void inorderTraversal(Node* node, vector<T>& result) const {
        if (node) {
            inorderTraversal(node->left, result);
            result.push_back(node->data);
            inorderTraversal(node->right, result);
        }
    }
    
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}
    
    ~AVLTree() {
        destroyTree(root);
    }
    
    void insert(const T& value) {
        root = insertNode(root, value);
    }
    
    void remove(const T& value) {
        root = removeNode(root, value);
    }
    
    bool search(const T& value) const {
        return searchNode(root, value) != nullptr;
    }
    
    T* find(const T& value) {
        Node* node = searchNode(root, value);
        return node ? &(node->data) : nullptr;
    }
    
    const T* find(const T& value) const {
        Node* node = searchNode(root, value);
        return node ? &(node->data) : nullptr;
    }
    
    vector<T> getAll() const {
        vector<T> result;
        inorderTraversal(root, result);
        return result;
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }
    
    int size() const {
        return getAll().size();
    }
};

#endif // AVLTREE_H
