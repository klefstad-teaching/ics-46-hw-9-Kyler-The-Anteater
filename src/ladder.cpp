#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << word1 << " " << msg << " " << word2 << endl;
}

string lowercase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
bool edit_distance_within(const string& str1, const string& str2, int d) {
    // differing by 1 (add/remove)
    if (d == 1) {
        //Remove
        string larger, smaller;
        if (str1.size() > str2.size()) {larger = str1; smaller = str2;}
        else {larger = str2; smaller = str1;}
        for (int i = 0; i < larger.size(); ++i) {
            string rem = larger;
            rem.erase(i, 1);
            if (rem == smaller) return true;
        }
    }
    else if (d == 0) {
        //differing by 0 (change a letter)
        int s = str1.size();
        for (int i = 0; i < s; ++i) {
            string without1 = str1;
            string without2 = str2;
            without1.erase(i, 1);
            without2.erase(i, 1);
            if (without1 == without2) return true; //FIXME - make all lowercase
        }
    }
    return false;
}
bool is_adjacent(const string& word1, const string& word2) {
    size_t len1 = word1.size(), len2 = word2.size();
    int dist;
    if (len1 > len2) dist = len1 - len2;
    else dist = len2 - len1;
    return dist >= 2 ? false : edit_distance_within(word1, word2, dist);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        cout << "No word ladder found.\n";
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (string word : word_list)
            if (is_adjacent(last_word, word))
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
    }
    cout << "No word ladder found.\n";
    return {};
}
void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while (in >> word)
        word_list.insert(word);
}
void print_word_ladder(const vector<string>& ladder) {
    for (string s : ladder)
        cout << s << " ";
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