#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <sstream>
#include <queue>
#include <set>

using namespace std;

struct directory {
    int size = 0;
    int total_size = -1;
    bool completed = false;
    set<string> indirect;
};

string append_path(const string &current_path, const string &append_path) {
    if (current_path == "/")
        return current_path + append_path;

    return current_path + "/" + append_path;
}

int get_size(map<string, directory> directories, const string &dir_name) {
    if (directories[dir_name].total_size != -1) {
        return directories[dir_name].total_size;
    }
    int size = directories[dir_name].size;
    for (const string &s: directories[dir_name].indirect) {
        cout << s << endl;
        size += get_size(directories, s);
    }

    directories[dir_name].total_size = size;

    return size;
}

int main() {
    string line, line_part, current_dir;
    size_t temp;
    bool line_set = false;
    map<string, directory> directories;
    ifstream input("../day_7/input.txt");
    stringstream s;

    if (input.is_open()) {
        while (line_set || getline(input, line)) {
            line_set = false;

            s.str(line.substr(2));
            getline(s, line_part, ' ');

            if (line_part == "cd") {
                if (!getline(s, line_part, ' ')) {
                    cout << "cd failed ";
                    exit(-1);
                }

                if (line_part == "..") {
                    if ((temp = current_dir.find_last_of('/')) == 0)
                        current_dir = "/";
                    else
                        current_dir = current_dir.substr(0, temp);
                } else if (line_part == "/") {
                    current_dir = "/";
                } else {
                    current_dir = append_path(current_dir, line_part);
                }

                cout << "cd " << current_dir << endl;

            } else if (line_part == "ls") {
                cout << "ls" << endl;
                s.clear();
                while (getline(input, line)) {
                    line_set = true;
                    cout << line << endl;
                    if (line[0] == '$') {
                        cout << "found command" << endl;
                        break;
                    }
                    if (directories[current_dir].completed)
                        continue;
                    s.str(line);
                    getline(s, line_part, ' ');

                    if (line_part == "dir") {
                        cout << "found dir" << endl;
                        getline(s, line_part, ' ');
                        directories[current_dir].indirect.insert(append_path(current_dir, line_part));
                    } else {
                        cout << "found file" << endl;
                        directories[current_dir].size += stoi(line_part);
                    }
                    s.clear();
                    line_set = false;
                }

                directories[current_dir].completed = true;
            } else {
                cout << "Unknown command: " << line_part << " Full line: " << line << endl;
            }

            s.clear();
        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }
    int sum = 0, temp_sum, closest = INT_MAX, req_size = 30000000 - (70000000 - get_size(directories, "/"));
    for (const auto &kv: directories) {
        if ((temp_sum = get_size(directories, kv.first)) <= 100000)
            sum += temp_sum;
        if (temp_sum >= req_size && temp_sum < closest)
            closest = temp_sum;
    }

    cout << sum << endl;
    cout << closest << endl;

    return 0;
}
