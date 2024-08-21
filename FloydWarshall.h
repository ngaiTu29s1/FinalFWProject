#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>

#define INF 666

struct Matrix {
    int vertex;
    std::vector<std::vector<int> > mat;
    std::vector<std::vector<int> > res_mat;
    std::vector<std::vector<int> > trace;
    std::vector<int> trace_path(int, int);
	std::vector<int> path;
    void init_trace();
    void create();
    void read(const std::string& filename);
    void print();
    void find(int, int);
    void FloydWarshall();
    std::vector<int> tp(int, int);
};  