#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode* parentPtr;

    TreeNode(int val) {
        data = val;
        leftChild = NULL;
        rightChild = NULL;
        parentPtr = NULL;
    }
};

class BinarySearchTree {
private:
    TreeNode* rootNode;

    void printInorder(TreeNode* node) {
        if (node == NULL) return;
        printInorder(node->leftChild);
        cout << node->data << "\n";
        printInorder(node->rightChild);
    }

    void printPreorder(TreeNode* node) {
        if (node == NULL) return;
        cout << node->data << "\n";
        printPreorder(node->leftChild);
        printPreorder(node->rightChild);
    }

    void printPostorder(TreeNode* node) {
        if (node == NULL) return;
        printPostorder(node->leftChild);
        printPostorder(node->rightChild);
        cout << node->data << "\n";
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->leftChild != NULL)
            node = node->leftChild;
        return node;
    }

    void replaceSubtree(TreeNode* oldNode, TreeNode* newNode) {
        if (oldNode->parentPtr == NULL)
            rootNode = newNode;
        else if (oldNode == oldNode->parentPtr->leftChild)
            oldNode->parentPtr->leftChild = newNode;
        else
            oldNode->parentPtr->rightChild = newNode;
        if (newNode != NULL)
            newNode->parentPtr = oldNode->parentPtr;
    }

    TreeNode* findNode(TreeNode* node, int target) {
        while (node != NULL && node->data != target) {
            if (target < node->data)
                node = node->leftChild;
            else
                node = node->rightChild;
        }
        return node;
    }

public:
    BinarySearchTree() {
        rootNode = NULL;
    }

    void insertNode(int val) {
        TreeNode* parent = NULL;
        TreeNode* walker = rootNode;
        TreeNode* newNode = new TreeNode(val);

        while (walker != NULL) {
            parent = walker;
            if (val < walker->data)
                walker = walker->leftChild;
            else if (val > walker->data)
                walker = walker->rightChild;
            else {
                delete newNode; // Avoid duplicate
                return;
            }
        }

        newNode->parentPtr = parent;

        if (parent == NULL)
            rootNode = newNode;
        else if (val < parent->data)
            parent->leftChild = newNode;
        else
            parent->rightChild = newNode;
    }

    void removeNode(int val) {
        TreeNode* target = findNode(rootNode, val);
        if (target == NULL) return;

        if (target->leftChild == NULL)
            replaceSubtree(target, target->rightChild);
        else if (target->rightChild == NULL)
            replaceSubtree(target, target->leftChild);
        else {
            TreeNode* successor = findMin(target->rightChild);
            if (successor->parentPtr != target) {
                replaceSubtree(successor, successor->rightChild);
                successor->rightChild = target->rightChild;
                if (successor->rightChild != NULL)
                    successor->rightChild->parentPtr = successor;
            }
            replaceSubtree(target, successor);
            successor->leftChild = target->leftChild;
            if (successor->leftChild != NULL)
                successor->leftChild->parentPtr = successor;
        }

        delete target;
    }

    void traverse(const string& orderType) {
        if (orderType == "oin")
            printInorder(rootNode);
        else if (orderType == "opre")
            printPreorder(rootNode);
        else if (orderType == "opost")
            printPostorder(rootNode);
    }
};

int main() {
    BinarySearchTree bst;
    string command;

    while (cin >> command) {
        if (command == "e")
            break;

        if (command[0] == 'i')
            bst.insertNode(atoi(command.substr(1).c_str()));
        else if (command[0] == 'd')
            bst.removeNode(atoi(command.substr(1).c_str()));
        else if (command == "oin" || command == "opre" || command == "opost")
            bst.traverse(command);
    }

    return 0;
}
