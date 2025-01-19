# Team 12

Maxwell Bryson, Ruichen He, Christopher Miao, Hannah Nelson

### Running
To compile and run navigate to project 1 directory and then run
$ make
$ ./ElectionApp

### Testing: 

`g++ -std=c++17 -Iinclude testing/FileUtilsTest.cpp src/FileUtils.cpp -Llib -lgtest -lgtest_main -pthread -o ./FileUtilsTest && ./FileUtilsTest`

Notes: lib and include file for GoogleTest has been added in the folder here for easier testing purpose.

### Doxygen

open documentation/html/index.html on a local browser

Pull Project1 on 11/13 at 6:00pm