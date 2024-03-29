# counting-triangles

To run the source codes, you need to first have the temporal graph file, graph.txt and the query file, query.txt. You can generate them from gen.cpp and genq.cpp.

The compile command of gen.cpp and genq.cpp:

g++ gen.cpp -o gen -O3 -std=c++14

g++ genq.cpp -o genq -O3 -std=c++14

You may refer to the content of genq.cpp to generate some special types of query you want.

For each source file, there is a makefile for compiling the source codes and a run.sh for running.

The command of running the source codes customizedly (take LSC index as an example):

./main graph.txt query.txt output_LSC.txt LSC > log_LSC.txt

You may change the output file and log file as you want.

The default sampling factor of all index-based solution is 0.01.
