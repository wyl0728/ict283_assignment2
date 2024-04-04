#ifndef Bst_H
#define Bst_H

#include <algorithm>
#include <functional>
#include <stdexcept>

/**
 * @brief A template class for an AVL tree (a self-balancing binary search tree).
 *
 * @tparam T The data type of the elements stored in the tree.
 */
template<typename T>
class Bst {
private:
    /**
     * @brief A nested structure to represent a node in the tree.
     */
    struct Node {
        T data;          ///< The data stored in the node.
        Node* left;      ///< Pointer to the left child.
        Node* right;     ///< Pointer to the right child.
        int height;      ///< The height of the node.

        /**
         * @brief Constructor for creating a new node.
         *
         * @param data The data to store in the node.
         */
        Node(const T& data) : data(data), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;// Root node of the binary search tree

    /**
     * @brief Get the height of a node.
     *
     * @param node The node whose height is to be determined.
     * @return int The height of the node.
     */
    int Height(Node* node) const {
        return node ? node->height : 0;
    }

    /**
     * @brief Get the balance factor of a node.
     *
     * @param node The node whose balance factor is to be determined.
     * @return int The balance factor of the node.
     */
    int GetBalance(Node* node) const {
        return node ? Height(node->left) - Height(node->right) : 0;
    }

    /**
     * @brief Perform a right rotation on the subtree rooted with y.
     *
     * @param y The root of the subtree.
     * @return Node* The new root after rotation.
     */
    Node* RightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(Height(y->left), Height(y->right)) + 1;
        x->height = std::max(Height(x->left), Height(x->right)) + 1;

        return x;
    }

    /**
     * @brief Perform a left rotation on the subtree rooted with x.
     *
     * @param x The root of the subtree.
     * @return Node* The new root after rotation.
     */
    Node* LeftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(Height(x->left), Height(x->right)) + 1;
        y->height = std::max(Height(y->left), Height(y->right)) + 1;

        return y;
    }

    /**
     * @brief Recursively insert a new node with the given data in the AVL tree.
     *
     * @param node The root node of the subtree.
     * @param data The data to insert into the tree.
     * @return Node* The new root of the subtree.
     */
    Node* InsertNode(Node* node, const T& data) {
        if (!node) {
            return new Node(data);
        }
        if (data < node->data) {
            node->left = InsertNode(node->left, data);
        } else if (data > node->data) {
            node->right = InsertNode(node->right, data);
        }

        node->height = 1 + std::max(Height(node->left), Height(node->right));

        int balance = GetBalance(node);

        // Left Left Case
        if (balance > 1 && data < node->left->data) {
            return RightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && data > node->right->data) {
            return LeftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && data > node->left->data) {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->right->data) {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }

    /**
     * @brief Recursively remove a node with the given data from the AVL tree.
     *
     * @param node The root node of the subtree.
     * @param data The data to remove from the tree.
     * @return Node* The new root of the subtree.
     */
    Node* RemoveNode(Node* node, const T& data) {
        if (!node) {
            return node;
        }

        if (data < node->data) {
            node->left = RemoveNode(node->left, data);
        } else if (data > node->data) {
            node->right = RemoveNode(node->right, data);
        } else {
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
                Node* temp = node->right;
                while (temp->left) {
                    temp = temp->left;
                }

                node->data = temp->data;
                node->right = RemoveNode(node->right, temp->data);
            }
        }

        if (!node) {
            return node;
        }

        node->height = std::max(Height(node->left), Height(node->right)) + 1;

        int balance = GetBalance(node);

        // Left Left Case
        if (balance > 1 && GetBalance(node->left) >= 0) {
            return RightRotate(node);
        }

        // Left Right Case
        if (balance > 1 && GetBalance(node->left) < 0) {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && GetBalance(node->right) <= 0) {
            return LeftRotate(node);
        }

        // Right Left Case
        if (balance < -1 && GetBalance(node->right) > 0) {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }

    /**
     * @brief Delete all nodes in the subtree rooted with the given node.
     *
     * @param node The root node of the subtree to delete.
     */
    void DeleteSubtree(Node* node) {
        if (node) {
            DeleteSubtree(node->left);
            DeleteSubtree(node->right);
            delete node;
        }
    }

    /**
     * @brief Copy the entire tree rooted with source node.
     *
     * @param source The root node of the tree to copy.
     */
    void CopyTree(Node* source) {
        if (source) {
            Insert( source->data );
            CopyTree(source->left);
            CopyTree(source->right);
        }
    }

    /**
     * @brief In-order traversal of the tree, executing a function on each node's data.
     *
     * @param node The current node in the traversal.
     * @param func The function to execute on each node's data.
     */
    template<typename Func>
    void InOrderTraversal(Node* node, Func func) const {
        if (node != nullptr) {
            InOrderTraversal(node->left, func);
            func(node->data);
            InOrderTraversal(node->right, func);
        }
    }

    /**
     * @brief Pre-order traversal of the tree, executing a function on each node's data.
     *
     * @param node The current node in the traversal.
     * @param func The function to execute on each node's data.
     */
    template<typename Func>
    void PreOrderTraversal(Node* node, Func func) const {
        if (node != nullptr) {
            func(node->data);
            PreOrderTraversal(node->left, func);
            PreOrderTraversal(node->right, func);
        }
    }

    /**
     * @brief Post-order traversal of the tree, executing a function on each node's data.
     *
     * @param node The current node in the traversal.
     * @param func The function to execute on each node's data.
     */
    template<typename Func>
    void PostOrderTraversal(Node* node, Func func) const {
        if (node != nullptr) {
            PostOrderTraversal(node->left, func);
            PostOrderTraversal(node->right, func);
            func(node->data);
        }
    }

public:
    /**
     * @brief Construct a new Bst object.
     */
    Bst() : root(nullptr) {}

    /**
     * @brief Destroy the Bst object.
     */
    ~Bst() {
        Clear();
    }

    /**
     * @brief Copy constructor.
     *
     * @param other The tree to be copied.
     */
    Bst(const Bst& other) {
        root = nullptr;
        CopyTree(other.root);
    }

    /**
     * @brief Move constructor.
     *
     * @param other The tree to be moved.
     */
    Bst(Bst&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    /**
     * @brief Copy assignment operator.
     *
     * @param other The tree to be copied.
     * @return Bst& A reference to the copied tree.
     */
    Bst& operator=(const Bst& other) {
        if (this != &other) {
            Clear();
            CopyTree(other.root);
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     *
     * @param other The tree to be moved.
     * @return Bst& A reference to the moved tree.
     */
    Bst& operator=(Bst&& other) noexcept {
        if (this != &other) {
            Clear();
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    /**
     * @brief Insert a new element into the tree.
     *
     * @param data The data to insert.
     */
    void Insert(const T& data) {
        root = InsertNode(root, data);
    }

    /**
     * @brief Remove an element from the tree.
     *
     * @param data The data to remove.
     */
    void Remove(const T& data) {
        root = RemoveNode(root, data);
    }

    /**
     * @brief Clear the tree, removing all elements.
     */
    void Clear() {
        DeleteSubtree(root);
        root = nullptr;
    }

    /**
     * @brief Perform an in-order traversal of the tree.
     *
     * @param func A function to apply to each element.
     */
    void InOrderTraversal(std::function<void(const T&)> func) const {
        InOrderTraversal(root, func);
    }

    /**
     * @brief Perform a pre-order traversal of the tree.
     *
     * @param func A function to apply to each element.
     */
    void PreOrderTraversal(std::function<void(const T&)> func) const {
        PreOrderTraversal(root, func);
    }

    /**
     * @brief Perform a post-order traversal of the tree.
     *
     * @param func A function to apply to each element.
     */
    void PostOrderTraversal(std::function<void(const T&)> func) const {
        PostOrderTraversal(root, func);
    }
};

#endif
