#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << word1 << " " << msg << " " << word2 << endl;
}
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > d) return false;

    int diff = 0;

    if (len1 == len2) {
        for (int i = 0; i < len1; ++i)
            if (str1[i] != str2[i] && (++diff) > 1)
                return false;
        return diff == 1;
    }

    int i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff > 1) return false;
            len1 > len2 ? ++i : ++j;
        } else {++i; ++j;}
    }
    return true;
}
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, abs((int)word1.size() - (int)word2.size()));
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    set<string> wordSet(word_list);
    if (begin_word == end_word || wordSet.find(end_word) == wordSet.end()) return {};

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        int level = ladder_queue.size();
        set<string> remove;
        for (int i = 0; i < level; ++i) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();

            for (const string& word : wordSet)
                if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                    remove.insert(word);
                }
        }
        for (const string& word : remove)
            visited.insert(word);
    }  
    return {};
}
void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while (in >> word)
        word_list.insert(word);
}
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty())
        cout << "No word ladder found.\n";
    else {
        cout << "Word ladder found: ";
        for (string s : ladder)
            cout << s << " ";
        cout << endl;
    }
    
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}