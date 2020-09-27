class RBTress {
public:
    RBTress() : root(nullptr), size(0) {}

    // add new element(key, value)
    void add(int key, int value) {
        root = add(root, key, value);
        root->color = BLACK;    // the final root is set BLACK
    }

private:
    static const bool RED = true;
    static const bool BLACK = false;

    class Node {
    public: 
        int key; 
        int value; 
        Node* left; 
        Node* right;
        bool color;
            
        Node(int key, int value) : key(key), value(value), left(nullptr), right(nullptr), color(RED) {}

    };

    Node* root;
    int size;

    bool isRed(Node* node) {
        if(node == nullptr) return BLACK;
        return node->color;
    }

    //    node                           x
    //   /    \     leftRotate          /  \
    //  T1     x  ---------------->   node  T3
    //        / \                    /    \
    //       T2 T3                  T1    T2
    Node* leftRotate(Node* node) {
        Node* x = node->right;

        //left rotate
        node->right = x->left;
        x->left = node;

        x->color = node->color;
        node->color = RED;

        return x;
    }

    //      node                            x
    //     /    \     rightRotate          /  \
    //    x     T2  ---------------->    y   node  
    //   / \                                /    \
    //  y   T1                             T1    T2
    Node* rightRotate(Node* node) {
        Node* x = node->left;

        //right rotate
        node->left = x->right;
        x->right = node;

        x->color = node->color;
        node->color = RED;

        return x;
    }

    void flipColors(Node* node) {
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
    }

    Node* add(Node* node, int key, int value) {

        if(node == nullptr) {
            size++;
            return new Node(key, value);
        }

        if(key < node->key) {
            node->left = add(node->left, key, value);
        }
        else if(key > node->key) {
            node->right = add(node->right, key, value);
        }
        else {
            node->value = value;
        }
        
        // the current node need checking the following three conditions 
        // the three conditions are not mutually exclusive; not if...else
        // if node need leftRotate
        if(isRed(node->right) && !isRed(node->left)) {
            node = leftRotate(node);
        }

        // if node need rightRotate
        if(isRed(node->left) && isRed(node->left->left)) {
            node = rightRotate(node);
        }

        // if need flipColor
        if(isRed(node->left) && isRed(node->right)) {
            flipColors(node);
        }

        return node;
    }
};