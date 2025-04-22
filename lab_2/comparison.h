#pragma once
#include "Sequences.h"

template<typename T>
bool cmp1(const T &a, const T &b) {
    return a <= b;
}

template<typename T>
bool cmp2(const T &a, const T &b) {
    return a < b;
}

template<typename T>
bool cmp3(const T &a, const T &b) {
    return a > b;
}