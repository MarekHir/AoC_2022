#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <sstream>

using namespace std;

struct knot {
    int pos_x = 0, pos_y = 0;
};

void move_tail(const knot &head, knot &tail){
    if(head.pos_y == tail.pos_y && head.pos_x == tail.pos_x)
        return;
    if(head.pos_y != tail.pos_y && head.pos_x != tail.pos_x){
        if(abs(abs(head.pos_y) - abs(tail.pos_y)) == 1 && abs(abs(head.pos_x) - abs(tail.pos_x)) == 1)
            return;

        if(head.pos_y > tail.pos_y && head.pos_x > tail.pos_x){
            tail.pos_y++;
            tail.pos_x++;
        }
        else if(head.pos_y > tail.pos_y && head.pos_x < tail.pos_x){
            tail.pos_y++;
            tail.pos_x--;
        }
        else if(head.pos_y < tail.pos_y && head.pos_x > tail.pos_x){
            tail.pos_y--;
            tail.pos_x++;
        }
        else if(head.pos_y < tail.pos_y && head.pos_x < tail.pos_x){
            tail.pos_y--;
            tail.pos_x--;
        }
        return;
    }

    if(abs(abs(head.pos_y) - abs(tail.pos_y)) == 1 && head.pos_x == tail.pos_x ||
        abs(abs(head.pos_x) - abs(tail.pos_x)) == 1 && head.pos_y == tail.pos_y)
        return;
    else if(head.pos_y > tail.pos_y){
        tail.pos_y++;
    }
    else if(head.pos_y < tail.pos_y){
        tail.pos_y--;
    }
    else if(head.pos_x > tail.pos_x){
        tail.pos_x++;
    }
    else if(head.pos_x < tail.pos_x){
        tail.pos_x--;
    }
}

int main() {
    string line, direction, amount;
    ifstream input("../day_9/input.txt");
    stringstream ss;

    int tail_count = 9;
    set<string> visited;
    knot head, tail[tail_count];

    if (input.is_open()) {
        while (getline(input, line)) {
            ss.str(line);
            getline(ss, direction, ' ');
            getline(ss, amount, ' ');
            for(int i = 0; i < stoi(amount); i++){
                switch(direction[0]){
                    case 'R':
                        head.pos_x++;
                        break;
                    case 'D':
                        head.pos_y--;
                        break;
                    case 'L':
                        head.pos_x--;
                        break;
                    case 'U':
                        head.pos_y++;
                        break;
                }
                move_tail(head, tail[0]);
                for(int j = 1; j < tail_count; j++) {
                    move_tail(tail[j - 1], tail[j]);
                }

                visited.insert(to_string(tail[8].pos_x) + ':' + to_string(tail[8].pos_y));
            }
            ss.clear();
        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    cout << "Result: " << visited.size() << endl;
    return 0;
}
