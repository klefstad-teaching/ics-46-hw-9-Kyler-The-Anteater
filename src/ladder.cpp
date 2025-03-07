#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << word1 << " " << msg << " " << word2 << endl;
}
bool edit_distance_within(const string& str1, const string& str2, int d) {

}
bool is_adjacent(const string& word1, const string& word2) {
    int distance = abs(word1.size() - word2.size());
    return distance >= 2 ? false : edit_distance_within(word1, word2, distance);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
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
                    if (word == last_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name);
void print_word_ladder(const vector<string>& ladder);
void verify_word_ladder();