find . -name "*.cpp" -exec sh -c 'gcov {} -o "../obj/gcov/$(dirname {})"' \;
