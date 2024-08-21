#include "FloydWarshall.h"

void Matrix::create() {
    mat.resize(vertex, std::vector<int>(vertex, 0));
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < i; j++) {
            int temp = 1 + std::rand() % 20;
            if ((temp >= 10) && (i != j)) {
                mat[i][j] = INF;
                mat[j][i] = INF;
            } else if ((temp < 10) && (i != j)) {
                mat[i][j] = temp;
                mat[j][i] = temp;
            }
        }
    }
    res_mat = mat;
}

void Matrix::read(const std::string& filename) {
    mat.resize(vertex, std::vector<int>(vertex, 0));
    std::ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < vertex; i++) {
            for (int j = 0; j < vertex; j++) {
                file >> mat[i][j];
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
    res_mat = mat;
}

void Matrix::print() {
    std::cout << std::endl;
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            if (mat[i][j] == INF) std::cout << "INF" << "\t";
            else std::cout << mat[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void Matrix::init_trace() {
    trace.resize(vertex, std::vector<int>(vertex, -1));
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            if (i != j && mat[i][j] != INF) {
                trace[i][j] = i;
            }
        }
    }
}

void Matrix::FloydWarshall() {
    init_trace();
    for (int k = 0; k < vertex; k++) {
        for (int i = 0; i < vertex; i++) {
            for (int j = 0; j < vertex; j++) {
                if (res_mat[i][k] + res_mat[k][j] < res_mat[i][j]) {
                    res_mat[i][j] = res_mat[i][k] + res_mat[k][j];
                    trace[i][j] = trace[k][j];
                }
            }
        }
    }
}

std::vector<int> Matrix::trace_path(int i, int j) {
	std::vector <int> tempPath;

    if (res_mat[i][j] == INF || i == j)
    {
		return tempPath;
    }
    else 
    {
        while (j != i) {
            tempPath.push_back(j);
            j = trace[i][j];
        }
        tempPath.push_back(i);
        std::reverse(tempPath.begin(), tempPath.end());

        return tempPath;
    }
}



void Matrix::find(int start, int end) {
    FloydWarshall();

    path = trace_path(start, end);


    if (path.size() > 1)
    {
        if (res_mat[start][end] < INF && res_mat[start][end] != 0) {
            std::cout << "Shortest path from: " << start << " to " << end << " : ";
            for (size_t i = 0; i < path.size(); i++) {
                std::cout << path[i];
                if (i < (path.size() - 1)) std::cout << " -> ";
            }
            std::cout << "\n";
            std::cout << "Weight: " << res_mat[start][end] << std::endl;
        }
    }
    else {
        std::cout << "No shortest path exists\n";
    }
    }
