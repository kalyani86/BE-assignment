#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

class Compare {
public:
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

class HuffmanTree {
public:
    void build(const string& text) {
        unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        // Print character frequencies
        cout << "\nCharacter Frequencies:\n";
        for (auto pair : freq) {
            cout << pair.first << " : " << pair.second << endl;
        }

        priority_queue<Node*, vector<Node*>, Compare> pq;
        for (auto pair : freq) {
            pq.push(new Node(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();

            Node* newNode = new Node('\0', left->freq + right->freq);
            newNode->left = left;
            newNode->right = right;
            pq.push(newNode);
        }

        root = pq.top();
        encode(root, "");
    }

    void printCodes() const {
        cout << "\nHuffman Codes:\n";
        for (const auto& pair : huffmanCode) {
            cout << pair.first << " : " << pair.second << endl;
        }
    }

    ~HuffmanTree() {
        delete root;
    }

private:
    Node* root = nullptr;
    unordered_map<char, string> huffmanCode;

    void encode(Node* node, const string& str) {
        if (node == nullptr)
            return;

        if (!node->left && !node->right) {
            huffmanCode[node->ch] = str;
        }

        encode(node->left, str + "0");
        encode(node->right, str + "1");
    }
};

int main() {
    string text;
    cout << "Enter text to encode: ";
    getline(cin, text);

    HuffmanTree huffmanTree;
    huffmanTree.build(text);
    huffmanTree.printCodes();

    cout << "\nTime Complexity: O(n log n)\n";
    cout << "Space Complexity: O(n)\n";

    return 0;
}
