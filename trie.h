#ifndef Trie__
#define Trie__

#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>

using namespace std;

struct trie_node {
    map <char, shared_ptr<trie_node> > children;
    bool end_word;
};

class Trie {
public:
    Trie();

    ~Trie();

    vector<char> Print_trie();

    void set_root();

    shared_ptr<trie_node> InitNode();

    bool search(string word);

    vector<string> prefix_search(string prefix);

    vector<string> prefix_add(string prefix, shared_ptr<trie_node> cursor, vector<string> words, string word);

    void remove(string word);

    bool remove_help(shared_ptr<trie_node> current, string word, int index);

    shared_ptr<trie_node> get_parent(shared_ptr<trie_node> root, shared_ptr<trie_node> current, string word);

    shared_ptr<trie_node> insert(string word);

private:
    shared_ptr<trie_node> root_ptr_;
};

#endif 
