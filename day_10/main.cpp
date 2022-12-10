#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <sstream>

using namespace std;

void check_cycle(int &strength, int &cycle, int &x){
    if((cycle == 20 || (cycle - 20) % 40 == 0) && cycle <= 220){
        strength += cycle * x;
    }
}

void noop(int &strength, int &cycle, int &x){
    cycle++;
    check_cycle(strength, cycle, x);
}

void addx(int amount, int &strength, int &cycle, int &x){
    for(int i = 0; i < 2; i++){
        cycle++;
        check_cycle(strength, cycle, x);
    }
    x += amount;
}

int main() {
    string line, line_part;
    int strength_total = 0, cycle_count = 0, x_register = 1;
    ifstream input("../day_10/input.txt");
    stringstream s;

    if (input.is_open()) {
        while (getline(input, line)) {
            s.str(line);
            getline(s,line_part, ' ');
            if(line_part == "noop"){
                noop(strength_total, cycle_count, x_register);
            }else if(line_part == "addx"){
                getline(s,line_part);
                addx(stoi(line_part), strength_total, cycle_count, x_register);
            }
            s.clear();
        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    cout << "Result: " << strength_total << endl;

    return 0;
}
