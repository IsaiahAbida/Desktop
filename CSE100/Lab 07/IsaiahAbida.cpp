#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

int main() {
    int m;
    cin >> m; 

    vector<list<int>> table(m); 

    char command;
    while (cin >> command) {
        if (command == 'e') { // exit
            break;
        }
        else if (command == 'i') { // insert
            int key;
            cin >> key;
            int index = key % m;
            table[index].push_front(key); // insert at beginning
        }
        else if (command == 's') { // search
            int key;
            cin >> key;
            int index = key % m;
            int pos = 0;
            bool found = false;

            for (int val : table[index]) {
                if (val == key) {
                    cout << key << ":FOUND_AT" << index << "," << pos << ";" << endl;
                    found = true;
                    break;
                }
                pos++;
            }
            if (!found)
                cout << key << ":NOT_FOUND;" << endl;
        }
        else if (command == 'd') { // delete
            int key;
            cin >> key;
            int index = key % m;
            bool deleted = false;

            for (auto it = table[index].begin(); it != table[index].end(); ++it) {
                if (*it == key) {
                    table[index].erase(it);
                    cout << key << ":DELETED;" << endl;
                    deleted = true;
                    break;
                }
            }
            if (!deleted)
                cout << key << ":DELETE_FAILED;" << endl;
        }
        else if (command == 'o') { // output table
            for (int i = 0; i < m; ++i) {
                cout << i << ":";
                for (int val : table[i])
                    cout << val << "->";
                cout << ";" << endl;
            }
        }
    }

    return 0;
}
