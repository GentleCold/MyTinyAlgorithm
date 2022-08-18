//
// Created by GentleCold on 2022/8/18.
//

#include "../chain.h"
#include <string>
#include <iostream>

struct StudentRecord {
    int score = 0;
    std::string *name = nullptr;

    operator int() const { return score; }
};

void binSort(myalm::Chain<StudentRecord>& v, int range) {
    myalm::Chain<StudentRecord> *bin;
    bin = new myalm::Chain<StudentRecord>[range + 1];

    int num = v.size();
    for (int i = 0; i < num; i++) {
        StudentRecord s = v.get(0);
        v.erase(0);
        bin[s.score].insert(0, s);
    }

    for (int i = range; i >= 0; i--) {
        while (!bin[i].empty()) {
            StudentRecord s = bin[i].get(0);
            bin[i].erase(0);
            v.insert(0, s);
        }
    }

    delete [] bin;
}

int main() {
    myalm::Chain<StudentRecord> v;
    for (int i = 0; i < 10; i++) {
        StudentRecord s;
        s.score = rand() % 10 + 1;
        v.insert(0, s);
    }
    binSort(v, 10);
    for (int i = 0; i < 10; i++) {
        std::cout << v[i].score << std::endl;
    }
}