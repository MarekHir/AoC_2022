#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct tree {
    int height = 0;
    int left = 0, right = 0, top = 0, bottom = 0;
    bool visible = false;
};

int main() {
    string line;
    bool first_line = true;
    ifstream input("../day_8/input.txt");
    getline(input, line);
    int row = 0, sum = 0, scenic_score = 0;
    size_t size = line.size();
    tree forrest[size][size];

    if (input.is_open()) {
        while (first_line || getline(input, line)) {
            first_line = false;
            for (int i = 0; i < size; i++) {
                forrest[row][i].height = line[i] - '0';
            }
            row++;
        }
        input.close();

        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                int highest[4] = {0, 0, 0, 0}, curr_scen_score = 0;

                for (int k = j - 1; k >= 0; k--) {
                    if (highest[0] < forrest[i][k].height) {
                        if (highest[0] < forrest[i][j].height && forrest[i][k].height >= forrest[i][j].height)
                            forrest[i][j].left++;
                        highest[0] = forrest[i][k].height;
                    }
                    if (highest[0] < forrest[i][j].height)
                        forrest[i][j].left++;
                }
                for (int k = j + 1; k < size; k++) {
                    if (highest[1] < forrest[i][k].height) {
                        if (highest[1] < forrest[i][j].height && forrest[i][k].height >= forrest[i][j].height)
                            forrest[i][j].right++;
                        highest[1] = forrest[i][k].height;
                    }
                    if (highest[1] < forrest[i][j].height)
                        forrest[i][j].right++;
                }
                for (int k = i - 1; k >= 0; k--) {
                    if (highest[2] < forrest[k][j].height) {
                        if (highest[2] < forrest[i][j].height && forrest[k][j].height >= forrest[i][j].height)
                            forrest[i][j].top++;
                        highest[2] = forrest[k][j].height;
                    }
                    if (highest[2] < forrest[i][j].height)
                        forrest[i][j].top++;

                }
                for (int k = i + 1; k < size; k++) {
                    if (highest[3] < forrest[k][j].height) {
                        if (highest[3] < forrest[i][j].height && forrest[k][j].height >= forrest[i][j].height)
                            forrest[i][j].bottom++;
                        highest[3] = forrest[k][j].height;
                    }
                    if (highest[3] < forrest[i][j].height)
                        forrest[i][j].bottom++;
                }
                for (int c: highest) {
                    if (c < forrest[i][j].height)
                        forrest[i][j].visible = true;
                }
                curr_scen_score = forrest[i][j].left * forrest[i][j].right * forrest[i][j].top * forrest[i][j].bottom;
                if (curr_scen_score > scenic_score)
                    scenic_score = curr_scen_score;
                if (forrest[i][j].visible)
                    sum++;
            }
        }
    } else {
        cout << "Unable to open file";
        return -1;
    }

    cout << sum + size * 4 - 4 << endl;
    cout << scenic_score << endl;

    return 0;
}
