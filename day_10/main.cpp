#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <sstream>

using namespace std;

void check_cycle(int &cycle, int &x){
//    cout << cycle << " " << x ;
    if(x + 1 >= cycle % 40 && cycle % 40 >= x - 1){
        cout << '#';
    }else{
        cout << '.';
    }
    if((cycle + 1) % 40 == 0){
        cout << endl;
    }
}

void noop(int &cycle, int &x){
    check_cycle( cycle, x);
    cycle++;
}

void addx(int amount,  int &cycle, int &x){
    for(int i = 0; i < 2; i++){
        check_cycle(cycle, x);
        cycle++;
    }
    x += amount;
}

int main() {
    string line, line_part;
    int cycle_count = 0, x_register = 1;
    ifstream input("../day_10/input.txt");
    stringstream s;

    if (input.is_open()) {
        while (getline(input, line)) {
            s.str(line);
            getline(s,line_part, ' ');
            if(line_part == "noop"){
                noop(cycle_count, x_register);
            }else if(line_part == "addx"){
                getline(s,line_part);
                addx(stoi(line_part), cycle_count, x_register);
            }
            s.clear();
        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    return 0;
}
