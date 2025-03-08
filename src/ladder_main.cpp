#include "ladder.h"

int main() {
    verify_word_ladder();
    cout << is_adjacent("appl", "apple") << endl;
    cout << is_adjacent("appl", "appleeeeee") << endl;
    cout << is_adjacent("applb", "apple") << endl;
    return 0;
}