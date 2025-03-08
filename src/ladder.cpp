#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << word1 << " " << msg << " " << word2 << endl;
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
    int distance = fabs(word1.size() - word2.size());
    return distance >= 2 ? false : edit_distance_within(word1, word2, distance);
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
    return {};
}
void load_words(set<string> & word_list, const string& file_name) {
    ifstream in("../src/" + file_name);
    string word;
    while (in >> word)
        word_list.insert(word);
}
void print_word_ladder(const vector<string>& ladder) {
    for (string s : ladder)
        cout << s << endl;
}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    vector<string> wl = generate_word_ladder("Cat", "dog", word_list);
    print_word_ladder(wl);
}