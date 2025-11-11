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
        left = right = NULL;
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
    Node* root = nullptr;
    unordered_map<char, string> huffmanCode;
public:

    void build(string text) {
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
            Node* left = pq.top(); 
            pq.pop();
            Node* right = pq.top(); 
            pq.pop();

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
    
    void encode(Node* node,  string str) {
        if (node == nullptr)
            return;

        if (!node->left && !node->right) {
            huffmanCode[node->ch] = str;
        }

        encode(node->left, str + "0");
        encode(node->right, str + "1");
    }

    void printEncodedText(string text)
    {
        string Encodedtext;
        for(int i=0;i<text.size();i++)
        {
            Encodedtext+=huffmanCode[text[i]];
        }
        cout<<"\nencoded text:"<<Encodedtext<<endl;
    }
    ~HuffmanTree() {
        delete root;
    }


};

int main() {
   

    HuffmanTree huffmanTree;
     string text;
    cout << "Enter text to encode: ";
    getline(cin, text);
    huffmanTree.build(text);
    huffmanTree.printEncodedText(text);
    huffmanTree.printCodes();
    
    cout << "\nTime Complexity: O(n log n)\n";
    cout << "Space Complexity: O(n)\n";

    return 0;
}
