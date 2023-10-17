#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <functional>

using namespace std;

typedef struct node
{
    int freq;
    char data;
    node *left;
    node *right;
} node;

class Deref
{
public:
    bool operator() (node *a, node *b)
    {
        return a->freq > b->freq;
    }
};

node * huffman_hidden(string s)
{

    priority_queue<node *, vector<node *>, Deref> pq;
    vector<int> count(256, 0);

    for (int i = 0; i < s.length(); i++)
    {
        count[s[i]]++;
    }

    for (int i = 0; i < 256; i++)
    {

        node *n_node = new node;
        n_node->left = NULL;
        n_node->right = NULL;
        n_node->data = (char)i;
        n_node->freq = count[i];

        if (count[i] != 0)
            pq.push(n_node);
    }

    while (pq.size() != 1)
    {

        node *left = pq.top();
        pq.pop();
        node *right = pq.top();
        pq.pop();
        node *comb = new node;
        comb->freq = left->freq + right->freq;
        comb->data = '\0';
        comb->left = left;
        comb->right = right;
        pq.push(comb);
    }

    return pq.top();
}

void print_codes_hidden(node *root, string code, map<char, string> &mp)
{

    if (root == NULL)
        return;
    if (root->data != '\0')
    {
        mp[root->data] = code;
    }

    print_codes_hidden(root->left, code + '0', mp);
    print_codes_hidden(root->right, code + '1', mp);
}

/*
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;

}node;

*/
void getNodes(node *root, string currentPath, map<string, char> &dictionary)
{
    if (root->data != '\0')
    {
        dictionary.insert({currentPath, root->data});
        cout << "[DICT] " << currentPath << " : " << root->data << endl;
    }
    if (root->left != nullptr)
    {
        getNodes(root->left, currentPath + "0", dictionary);
    }
    if (root->right != nullptr)
    {
        getNodes(root->right, currentPath + "1", dictionary);
    }
}

void decode_huff(node *root, string s)
{
    map<string, char> dictionary;
    cout << "S: " << s << endl;
    getNodes(root, "", dictionary);
    int index = 0;
    int len = 1;
    while (index + 1 < s.size())
    {
        cout << "*";
        while(!dictionary.contains(s.substr(index, len))) {
            ++len;
        }

        while (index + len < s.size() && dictionary.contains(s.substr(index, len)))
        {
            ++len;
        }
        if(index + len >= s.size()) {
            cout << "ALTO!!!!!" << endl;
            len = s.size() - index;
        } else if(len < 1) {
            len = 1;
        } else {
            --len;
        }
        cout << "[SEARCH] " << s.substr(index, len) << endl;
        cout << index << "," << len << " -> " << dictionary.at(s.substr(index, len)) << endl;
        index += len;
        len = 1;
    }
    if(index - s.size() > 0) {
        cout << dictionary.at(s.substr(index, index - s.size()));
    }
    cout << endl;
}

int main()
{

    string s;
    std::cin >> s;

    node *tree = huffman_hidden(s);
    string code = "";

    map<char, string> mp;
    print_codes_hidden(tree, code, mp);

    string coded;

    for (int i = 0; i < s.length(); i++)
    {
        coded += mp[s[i]];
    }

    decode_huff(tree, coded);

    return 0;
}