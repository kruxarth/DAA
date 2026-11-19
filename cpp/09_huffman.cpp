#include <bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};

Node* makeNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// left adds '0', right adds '1'
void printCodes(Node* root, string code) {
    if (root == NULL) return;

    // leaf node = an actual character
    if (root->left == NULL && root->right == NULL) {
        if (code == "") code = "0";      // only one character in input
        cout << root->ch << " : " << code << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    // min-heap of {frequency, node}: smallest frequency on top
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> pq;

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;
        cout << "Enter character and frequency: ";
        cin >> ch >> freq;
        pq.push({freq, makeNode(ch, freq, NULL, NULL)});
    }

    // keep joining the two smallest until one tree is left
    while (pq.size() > 1) {
        Node* first = pq.top().second;
        pq.pop();
        Node* second = pq.top().second;
        pq.pop();

        int sum = first->freq + second->freq;
        Node* parent = makeNode('$', sum, first, second);    // '$' = internal node
        pq.push({sum, parent});
    }

    Node* root = pq.top().second;

    cout << "Huffman codes:" << endl;
    printCodes(root, "");
    return 0;
}
