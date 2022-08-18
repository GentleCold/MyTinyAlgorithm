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

void binSort(myalm::Chain<StudentRecord>& v, int bit) {
    myalm::Chain<StudentRecord> *bin;
    bin = new myalm::Chain<StudentRecord>[10];

    int radix = 1;
    while (bit) {
        bit--;
        radix *= 10;
    }

    int num = v.size();
    for (int i = 0; i < num; i++) {
        StudentRecord s = v.get(0);
        v.erase(0);
        bin[(s.score % radix) / (radix / 10)].insert(0, s);
    }

    for (int i = 9; i >= 0; i--) {
        while (!bin[i].empty()) {
            StudentRecord s = bin[i].get(0);
            bin[i].erase(0);
            v.insert(0, s);
        }
    }

    delete [] bin;
}

void radixSort(myalm::Chain<StudentRecord>& v, int maxBit) {
    for (int i = 1; i <= maxBit; i++) {
        binSort(v, i);
    }
}

int main() {
    myalm::Chain<StudentRecord> v;
    for (int i = 0; i < 10; i++) {
        StudentRecord s;
        s.score = rand() % 999 + 1;
        v.insert(0, s);
    }
    radixSort(v, 3);
    for (int i = 0; i < 10; i++) {
        std::cout << v[i].score << std::endl;
    }
}