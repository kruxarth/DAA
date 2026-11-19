# Experiment 9: Huffman Coding

## What problem does it solve?
**Compression.** Normally every character takes 8 bits (ASCII). Huffman gives **short codes to frequent characters** and **long codes to rare ones**, so the total number of bits is smaller.

Its codes are **prefix-free**: no code is the start of another code. So `0`, `100`, `101`... can be decoded without any separator.

## Steps (greedy)
1. Make a **leaf node** for each character with its frequency.
2. Put all nodes in a **min-priority queue** (smallest frequency on top).
3. While more than one node is left:
   - take out the **two smallest** (a and b),
   - make a new node with `freq = a + b`, left = a, right = b,
   - put it back.
4. The last node is the **root** of the Huffman tree.
5. Read the codes: going **left adds 0, right adds 1**. The path from the root to a leaf is that character's code.

## Dry run
| Char | a | b | c | d | e | f |
|---|---|---|---|---|---|---|
| Freq | 5 | 9 | 12 | 13 | 16 | 45 |

```
Pick 5(a) + 9(b)    = 14
Pick 12(c) + 13(d)  = 25
Pick 14 + 16(e)     = 30
Pick 25 + 30        = 55
Pick 45(f) + 55     = 100  <- root
```
Tree:
```
              100
            0/   \1
          f:45    55
                0/   \1
               25     30
             0/ \1   0/ \1
           c:12 d:13 14  e:16
                    0/ \1
                   a:5  b:9
```
| Char | Code | Bits used |
|---|---|---|
| f | 0 | 45 × 1 = 45 |
| c | 100 | 12 × 3 = 36 |
| d | 101 | 13 × 3 = 39 |
| a | 1100 | 5 × 4 = 20 |
| b | 1101 | 9 × 4 = 36 |
| e | 111 | 16 × 3 = 48 |
| **Total** | | **224 bits** |

Fixed-length codes would need 3 bits × 100 = 300 bits. **Huffman saves about 25%.**

## C++ code
File: [`cpp/09_huffman.cpp`](../cpp/09_huffman.cpp)

```cpp
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
```

## Sample run
```
Enter number of characters: 6
Enter character and frequency: a 5
Enter character and frequency: b 9
Enter character and frequency: c 12
Enter character and frequency: d 13
Enter character and frequency: e 16
Enter character and frequency: f 45
Huffman codes:
f : 0
c : 100
d : 101
a : 1100
b : 1101
e : 111
```
Your codes may differ slightly if two frequencies are equal (ties). That's fine, and the **total bits stay the same**.

## Complexity
- n−1 merges, each with heap operations costing O(log n), so **O(n log n)** in total.
- Space: O(n) for the tree.

## Viva questions
- **Which technique?** Greedy: always merge the two least frequent nodes.
- **What is a prefix code?** No code is a prefix of another, which makes decoding unambiguous.
- **Why min-heap / priority queue?** To get the two smallest frequencies quickly (O(log n)).
- **Fixed vs variable length coding?** Fixed gives every char the same number of bits. Variable (Huffman) gives fewer bits to frequent chars.
- **How do you decode?** Start at the root and read bits: 0 goes left, 1 goes right. At a leaf, output the char and go back to the root.
- **Where is it used?** ZIP, JPEG, MP3 (as one of the steps).
