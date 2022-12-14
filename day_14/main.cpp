#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <queue>
#include <numeric>


#define NORMALIZE_CONST 0


using namespace std;


int main() {
  string line, cordinates, cordinate;
  int x = 0, y = 0, prev_x, prev_y, size_x = 0, num_of_grains = 0;
  bool first_pair = true;
  vector<vector<int>> map;

  ifstream input("../day_14/input.txt");
  stringstream s, ss;

  if (input.is_open()) {
    while (getline(input, line)) {

      s.str(line);
      while (getline(s, cordinates, ' ')) {
        if (cordinates == "->")
          continue;

        ss.str(cordinates);

        getline(ss, cordinate, ',');
        prev_x = x;
        x = stoi(cordinate) - NORMALIZE_CONST;

        getline(ss, cordinate, ',');
        prev_y = y;
        y = stoi(cordinate);

        if (!first_pair) {
          if (prev_x - x != 0) {
            if (map.size() < y)
              map.resize(y + 1);
            int max_x = max(prev_x, x);
            if (map.at(y).size() < max_x) {
              map.at(y).resize(max_x + 1);
              if (size_x < max_x + 1)
                size_x = max_x + 1;
            }
            for (int i = min(prev_x, x); i <= max_x; i++) {
              map.at(y).at(i) = 1;
            }
          } else {
            int max_y = max(prev_y, y);
            if (map.size() < max_y)
              map.resize(max_y + 1);
            for (int i = min(prev_y, y); i <= max_y; i++) {
              if (map.at(i).size() < x) {
                map.at(i).resize(x + 1);
                if (size_x < x + 1)
                  size_x = x + 1;
              }
              map.at(i).at(x) = 1;
            }
          }
        }
        first_pair = false;
        ss.clear();
      }
      first_pair = true;
      s.clear();
    }
    y = 0;
    x = 500 - NORMALIZE_CONST;
    num_of_grains++;
    while (true) {
      if (y + 1 >= map.size())
        break;

      if (map.at(y + 1).size() <= x || map.at(y + 1).at(x) == 0) {
        y++;
        continue;
      }
      if (map.at(y + 1).at(x - 1) == 0) {
        y++;
        x--;
        continue;
      }
      if (size_x <= x + 1) {
        break;
      }
      if (map.at(y + 1).size() <= x + 1 || map.at(y + 1).at(x + 1) == 0) {
        y++;
        x++;
        continue;
      }

      // Create new grain
      if(map.at(y).size() <= x)
        map.at(y).resize(x + 1);
      map.at(y).at(x) = 2;
      y = 0;
      x = 500 - NORMALIZE_CONST;
      num_of_grains++;

    }
    num_of_grains--;
  } else {
    cout << "Unable to open file";
    return -1;
  }

  cout << num_of_grains << endl;
  return 0;
}
