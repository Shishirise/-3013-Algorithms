#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int x) {
    data = x;
    left = right = nullptr;
  }
};

class Bst {
private:
  Node *root;

  void _insert(Node *&sub_root, int x) {
    if (sub_root == nullptr) {
      sub_root = new Node(x);
    } else {
      if (x < sub_root->data) {
        _insert(sub_root->left, x);
      } else {
        _insert(sub_root->right, x);
      }
    }
  }

  void _print(Node *root) {
    if (!root) {
      return;
    }
    _print(root->right);
    cout << root->data << " ";
    _print(root->left);
  }

  bool _search(Node *root, int x) {
    if (root == nullptr) {
      return false;
    }
    if (root->data == x) {
      return true;
    } else if (x < root->data) {
      return _search(root->left, x);
    } else {
      return _search(root->right, x);
    }
  }

  Node* _delete(Node* root, int x) {
    if (root == nullptr) {
      return root;
    }

    // Find the node to delete
    if (x < root->data) {
      root->left = _delete(root->left, x);
    } else if (x > root->data) {
      root->right = _delete(root->right, x);
    } else { // Node to be deleted found
      // Case 1: Node has no children (leaf node)
      if (root->left == nullptr && root->right == nullptr) {
        delete root;
        return nullptr;
      }
      // Case 2: Node has one child
      else if (root->left == nullptr) {
        Node* temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        Node* temp = root->left;
        delete root;
        return temp;
      }
      // Case 3: Node has two children
      else {
        Node* temp = _minValueNode(root->right);
        root->data = temp->data;
        root->right = _delete(root->right, temp->data);
      }
    }
    return root;
  }

  Node* _minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

public:
  Bst() { root = nullptr; }

  void insert(int x) {
    _insert(root, x);
  }

  bool search(int x) {
    return _search(root, x);
  }

  void deleteNode(int x) {
    root = _delete(root, x);
  }

  void print() {
    _print(root);
  }
};

int main() {
  cout << "Hello World!\n";
  Bst tree;
  tree.insert(8);
  tree.insert(3);
  tree.insert(1);
  tree.insert(11);
  tree.insert(7);
  tree.insert(15);

  // Print the tree (in-order traversal)
  cout << "Tree before deletion: ";
  tree.print();
  cout << endl;

  // Ask user for the node to delete
  int deleteValue;
  cout << "\nEnter the node value to be deleted: ";
  cin >> deleteValue;

  // Delete the node
  tree.deleteNode(deleteValue);

  // Print the tree after deletion
  cout << "Tree after deletion: ";
  tree.print();
  cout << endl;

  return 0;
}
