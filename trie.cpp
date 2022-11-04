#include "trie.h"

using namespace std;

Trie::Trie(){
    shared_ptr<trie_node> (NULL);
}

Trie::~Trie(){
}

void Trie::set_root(){
        root_ptr_ = shared_ptr<trie_node> (new trie_node);
        root_ptr_->end_word = false;
}


shared_ptr<trie_node> Trie::InitNode(){
    shared_ptr<trie_node> ret (new trie_node);
    return ret;
}


vector<char> Trie::Print_trie(){
    vector<char> ret;
    shared_ptr<trie_node> cursor (root_ptr_);
    shared_ptr<trie_node> temp;
    while (cursor->end_word != true){
        ret.push_back(cursor->children.begin()->first);
        cursor = cursor->children.begin()->second;
    }
    return ret;
}


shared_ptr<trie_node> Trie::insert(string word){
    shared_ptr<trie_node> cursor(root_ptr_);
    for (int i = 0; i < word.length(); i++){
        if (cursor->children.find(word[i]) == cursor->children.end()){
            cursor->children.insert(std::pair<char, shared_ptr<trie_node> > (word[i], shared_ptr<trie_node> (new trie_node)));
            cursor = cursor->children.begin()->second;
            cursor->end_word = false;
        }
        else {
            cursor = cursor->children.find(word[i])->second;
        }
    }
    cursor->end_word = true;
    return root_ptr_;    
}


void Trie::remove(string word){
    shared_ptr<trie_node> cursor (root_ptr_);
    remove_help(cursor, word, 0);
}

bool Trie::remove_help(shared_ptr<trie_node> cursor, string word, int index){
    shared_ptr<trie_node> node;
    if (index == word.length()){
        if (cursor->end_word == false){
            return false;
        }
        cursor->end_word = false;
        if (cursor->children.size() == 0){
            return true;
        }
        else {
            return false;
        }
    }
    char ch = word[index];
    node = cursor->children.at(ch);
    if (node == nullptr){
        return false;
    }

    bool should_delete = remove_help(node, word, index + 1);
    if (should_delete){
        cursor->children.erase(ch);
        if (cursor->children.size() == 0){
            return true;
        }
        else {
            return false;
        }
    }
}


bool Trie::search(string word){
    shared_ptr<trie_node> cursor (root_ptr_);
    for (int i = 0; i < word.length(); i++){
        if (cursor->children.find(word[i]) != cursor->children.end()){
            cursor = cursor->children.find(word[i])->second;
            if (cursor->end_word == true){
                return true;
            }
        }
        else {
            return false;
        }
    }
}

vector<string> Trie::prefix_search(string prefix){
    vector<string> vec;
    string word;
    shared_ptr<trie_node> cursor (root_ptr_);
    for (int i = 0; i < prefix.length(); i++){
        cursor = cursor->children.at(prefix[i]);
    }
    vec = prefix_add(prefix, cursor, vec, word);
}

vector<string> Trie::prefix_add(string prefix, shared_ptr<trie_node> cursor, vector<string> vec, string word){
    if (cursor->end_word){
        vec.push_back(prefix + word);
        word = "";
        return vec;
    }
    
    for (auto it = cursor->children.begin(); it != cursor->children.end(); it++){
        char next = it->first;
        shared_ptr<trie_node> child = cursor->children.at(next);
        if (child != nullptr){
            word += next;
            prefix_add(prefix, child, vec, word);
        }
    }
}
