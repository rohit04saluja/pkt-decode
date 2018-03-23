/*
 * main.cpp
 *
 * Created by Rohit Saluja on 3/22/18.
 * Copyright © 2018 rohit04saluja. All rights reserved.
 */

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

GTEST_API_ int main (int argc, char *argv[]) {
    cout << "Running main() from gtest_main.cc" << endl;
    testing::InitGoogleTest(&argc, argv);
    if (argc == 2) {
        testing::GTEST_FLAG(filter) = argv[1];
    }
    return RUN_ALL_TESTS();
}
