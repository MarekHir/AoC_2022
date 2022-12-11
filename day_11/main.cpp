#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <queue>
#include <numeric>


#define num_of_monkeys 8



using namespace std;

struct monkey{
    int index;
    int inspect_count = 0;
    queue<unsigned long long int> items;
};

struct group{
    monkey monkeys[num_of_monkeys];
};

void ini_monkeys(group &monkeys){
//    int starting[num_of_monkeys][num_of_monkeys] = {{79, 98}, {54, 65, 75, 74}, {79, 60, 97}, {74}};
    int starting[num_of_monkeys][num_of_monkeys] = {{89, 73, 66, 57, 64, 80},
                    {83, 78, 81, 55, 81, 59, 69},
                    {76, 91, 58, 85},
                    {71, 72, 74, 76, 68},
                    {98, 85, 84},
                    {78},
                    {86, 70, 60, 88, 88, 78, 74, 83},
                    {81, 58}};
    int i = 0;
    for(monkey &monk : monkeys.monkeys){
        monk.index = i;
        for(int j : starting[i]){
            if(j > 0)
                monk.items.push(j);
        }
        i++;
    }
}

//void monkey_check(const int &monkey_num, unsigned long long int &item){
//    switch(monkey_num){
//        case 0:
//            item *= 19;
//            break;
//        case 1:
//            item += 6;
//            break;
//        case 2:
//            item *= item;
//            break;
//        case 3:
//            item += 3;
//            break;
//        default:
//            cout << "Uncovered path in monkey_check switch" << endl;
//            exit(-1);
//    }
//}
//
//int monkey_throw(const int &monkey_num, unsigned long long int &item){
//    switch(monkey_num){
//        case 0:
//            if(item % 23 == 0)
//                return 2;
//            return 3;
//        case 1:
//            if(item % 19 == 0)
//                return 2;
//            return 0;
//        case 2:
//            if(item % 13 == 0)
//                return 1;
//            return 3;
//        case 3:
//            if(item % 17 == 0)
//                return 0;
//            return 1;
//        default:
//            cout << "Uncovered path in monkey_throw switch" << endl;
//            exit(-1);
//    }
//}

void monkey_check(const int &monkey_num, unsigned long long int &item){
    switch(monkey_num){
        case 0:
            item *= 3;
            break;
        case 1:
            item += 1;
            break;
        case 2:
            item *= 13;
            break;
        case 3:
            item *= item;
            break;
        case 4:
            item += 7;
            break;
        case 5:
            item += 8;
            break;
        case 6:
            item += 4;
            break;
        case 7:
            item += 5;
            break;
        default:
            cout << "Uncovered path in monkey_check switch" << endl;
            exit(-1);
    }
}

int monkey_throw(const int &monkey_num, const unsigned long long int &item){
    switch(monkey_num){
        case 0:
            if(item % 13 == 0)
                return 6;
            return 2;
        case 1:
            if(item % 3 == 0)
                return 7;
            return 4;
        case 2:
            if(item % 7 == 0)
                return 1;
            return 4;
        case 3:
            if(item % 2 == 0)
                return 6;
            return 0;
        case 4:
            if(item % 19 == 0)
                return 5;
            return 7;
        case 5:
            if(item % 5 == 0)
                return 3;
            return 0;
        case 6:
            if(item % 11 == 0)
                return 1;
            return 2;
        case 7:
            if(item % 17 == 0)
                return 3;
            return 5;
        default:
            cout << "Uncovered path in monkey_throw switch" << endl;
            exit(-1);
    }
}

int main() {
    group monkeys;
    ini_monkeys(monkeys);
    unsigned long long int lcm = 1;
//    int numbers[] {23, 19, 13, 17};
    int numbers[] {13, 3, 7, 2, 19, 5, 11, 17};
    // Today, I became a bit smarter
    for(int i : numbers){
        lcm *= i;
    }

    for(int i = 0; i < 10000;){
        for(monkey &monk : monkeys.monkeys){
            while(!monk.items.empty()){
                unsigned long long int item = monk.items.front();
                monk.items.pop();
                monkey_check(monk.index, item);
                item %= lcm;
                monk.inspect_count++;
                monkeys.monkeys[monkey_throw(monk.index, item)].items.push(item);
            }
        }
        i++;
        if(i == 1 || i == 20 || (i != 0 && i % 1000 == 0)) {
            cout << "Round: " << i << endl;
            for (monkey &monk: monkeys.monkeys) {
                cout << monk.inspect_count << " " << (monk.items.empty() ? 69 : monk.items.front()) << endl;
            }
        }
    }
    unsigned long long int first = 0, second = 0;
    for(monkey &monk : monkeys.monkeys){
        if(monk.inspect_count > second) {
            if (monk.inspect_count > first) {
                second = first;
                first = monk.inspect_count;
            } else {
                second = monk.inspect_count;
            }
        }
    }

    cout << "Result: " << first * second << endl;
    return 0;
}
