#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node * left;
    Node * right;
};

Node * getNode(char ch,int freq,Node * left,Node * right){
    Node * newnode = new Node();
    newnode->ch = ch;
    newnode->freq = freq;
    newnode->left = left;
    newnode->right = right;
    return newnode;
}

struct comp{
    bool operator()(Node *l,Node *r){
        return l->freq > r->freq;
    }
};

void encode(Node *root,string str,unordered_map<char,string>&huffmanCode){
    if(root == nullptr){
        return ;
    }
    if(!root->left && !root->right){
        huffmanCode[root->ch] = str;
    }

    encode(root->left,str+'0',huffmanCode);
    encode(root->right,str+'1',huffmanCode);
}

void decode(Node * root,int &index,string str){
    if(root == nullptr){
        return ;
    }

    if(!root->left && !root->right){
        cout<<root->ch;
        return ;
    }
    index++;
    if(str[index] == '0'){
        decode(root->left,index,str);
    }
    else {
        decode(root->right,index,str);
    }

}


void buildHuffmanTree(string str){
    unordered_map<char,int> freq;
    for(char ch : str){
        freq[ch]++;
    }
    priority_queue<Node *,vector<Node*>,comp> pq;
    for(auto pair : freq){
        pq.push(getNode(pair.first,pair.second,nullptr,nullptr));
    }

    while(pq.size() != 1){
        Node* left = pq.top();
        pq.pop();
        Node* right =pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        pq.push(getNode('\0',sum,left,right));

    }

    Node* root = pq.top();
    unordered_map<char,string>huffmanCode;

    encode(root,"",huffmanCode);
    for(auto pair : huffmanCode){
        cout<<pair.first<<" "<<pair.second<<endl;
    }
    string text="";
    for(char ch : str){
        text +=huffmanCode[ch];
    }
    cout<<"\n Encoded string is "<<text<<endl;

    int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)text.size() - 2) {
		decode(root, index, text);
	}

}

int main()
{
    string str;
    getline(cin,str);
    buildHuffmanTree(str);
    return 0;
}
