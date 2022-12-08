#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

int main() {
//    'W' pre value a transitions
//                  Opponent    Player
//     Rock             A          X
//     Paper            B          Y
//     Scissors         C          Z

    string line;
    int sum = 0, i = 0;
    ifstream input("../day_2/input.txt");

    if (input.is_open()) {
        while (getline(input, line)) {
            cout << "line: " << ++i << " " << line << " " << sum << endl;
            if (line.length() == 0) {
                cout << "panic" << endl;
                continue;
            } else {
                sum += (line[2] - 'X') * 3 + 1;
                switch (line[0]) {
                    case 'A':
                        if (line[2] == 'X')
                            sum += 2;
                        if (line[2] == 'Z')
                            sum += 1;
                        break;
                    case 'B':
                        if (line[2] == 'Y')
                            sum += 1;
                        if (line[2] == 'Z')
                            sum += 2;
                        break;
                    case 'C':
                        if (line[2] == 'X')
                            sum += 1;
                        if (line[2] == 'Y')
                            sum += 2;
                        break;
                }
            }
        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    cout << sum << endl;

    return 0;
}
