#include<iostream>
#include<memory>

class node {
    public:
        int data;
        std::shared_ptr<node> left;
        std::shared_ptr<node> right;
        node(int d) {
            data = d;
            left = nullptr;
            right = nullptr;
        }
};

class tree {
public:
    std::shared_ptr<node> insert(std::shared_ptr<node> root, int data) {
        if(root == nullptr) {
            return std::make_shared<node>(data);
        } else {
            if(data <= root->data) {
                root->left = this->insert(root->left, data);
            } else {
                root->right = this->insert(root->right, data);
            }

            return root;
        }
    }

    int height(std::shared_ptr<node> x) {
        if (x == nullptr) return 0;
        return std::max(height(x->left), height(x->right)) + 1;
    }

}; // End of tree

int main() {
    
    tree myTree;
    std::shared_ptr<node> root = nullptr;
    
    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
    int height = myTree.height(root);
    std::cout << height << std::endl;

    return 0;
}
