#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

Node* newNode(char ch, int freq, Node* l, Node* r) {
    Node* t = new Node;
    t->ch = ch;
    t->freq = freq;
    t->left = l;
    t->right = r;
    return t;
}

// Makes priority_queue give the SMALLEST frequency first
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Walk the tree: left adds '0', right adds '1'
void printCodes(Node* root, string code) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {   // leaf = a character
        cout << root->ch << " : " << (code == "" ? "0" : code) << endl;
        return;
    }
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < n; i++) {
        char ch;
        int f;
        cout << "Enter character and frequency: ";
        cin >> ch >> f;
        pq.push(newNode(ch, f, NULL, NULL));
    }

    // Keep joining the two smallest until one tree is left
    while (pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        pq.push(newNode('$', a->freq + b->freq, a, b));   // '$' = internal node
    }

    cout << "Huffman codes:" << endl;
    printCodes(pq.top(), "");
    return 0;
}
