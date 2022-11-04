#include "trie.h"
#include "trie.cpp"

using namespace std;

int main(){
    Trie mytrie;
    mytrie.set_root();  
    mytrie.insert("word");
    mytrie.insert("well");
    mytrie.insert("woah");
    mytrie.insert("tough");
    mytrie.prefix_search("wo");
    //vector<string> words = mytrie.prefix_search("w");
    return 0;
}