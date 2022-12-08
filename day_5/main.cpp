#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <sstream>

using namespace std;

int main() {
    string line, line_part;
    int stack_size = 9;
    stack<char> stacks[stack_size];
    stack<char> stackie;
//    char inicial[3][3] = {{'Z', 'N'}, {'M', 'C', 'D'}, {'P'}};
    char inicial[9][8] = {{'B', 'L', 'D', 'T', 'W', 'C', 'F', 'M'},
                          {'N', 'B', 'L'},
                          {'J', 'C', 'H', 'T', 'L', 'V'},
                          {'S', 'P', 'J', 'W'},
                          {'Z', 'S', 'C', 'F', 'T', 'L', 'R'},
                          {'W', 'D', 'G', 'B', 'H', 'N', 'Z'},
                          {'F', 'M', 'S', 'P', 'V', 'G', 'C', 'N'},
                          {'W', 'Q', 'R', 'J', 'F', 'V', 'C', 'Z'},
                          {'R', 'P', 'M', 'L', 'H'}};
    for (int i = 0; i < stack_size; i++) {
        for (char c: inicial[i]) {
            if (isalpha(c))
                stacks[i].push(c);
        }
    }

    ifstream input("../day_5/input_test.txt");
    stringstream ss;

    if (input.is_open()) {
        while (getline(input, line)) {
            ss.str(line);
            int i = 0, from, to, amount;
            while (getline(ss, line_part, ' ')) {
                switch (i) {
                    case 1:
                        amount = stoi(line_part);
                        break;
                    case 3:
                        from = stoi(line_part) - 1;
                        break;
                    case 5:
                        to = stoi(line_part) - 1;
                        break;
                }
                i++;
            }
            while (amount) {
//              stacks[to].push(stacks[from].top());
//              Second part
                stackie.push(stacks[from].top());
//              end Second part
                stacks[from].pop();
                amount--;
            }
//          Second part
            while (!stackie.empty()) {
                stacks[to].push(stackie.top());
                stackie.pop();
            }
//          End Second part
            ss.clear();
        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    for (stack<char> c: stacks)
        cout << c.top();
    return 0;
}
