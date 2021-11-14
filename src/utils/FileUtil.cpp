//
// Created by alex on 26/05/20.
//

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "FileUtil.h"

using namespace std;

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

pair<vector<pair<int, int>>, int> FileUtil::load_graph(const std::string &file_path) {

    vector<std::vector<int>> vertices;
    string line;
    ifstream file(file_path);
    vector<std::pair<int, int>> edges_vec;
    int n = -1;
    if (file.is_open()) {

        getline(file, line);
        std::string::iterator new_end = std::unique(line.begin(), line.end(), BothAreSpaces);
        line.erase(new_end, line.end());

        boost::trim_right(line);
        boost::trim_left(line);

        vector<std::string> line_vec;
        boost::split(line_vec, line, boost::is_any_of(" "));

        string ninfo = line_vec[0];
        string minfo = line_vec[1];

        line_vec.clear();
        boost::split(line_vec, ninfo, boost::is_any_of("="));
        n = stoi(line_vec[1]);

        line_vec.clear();
        boost::split(line_vec, minfo, boost::is_any_of("="));
        int m = stoi(line_vec[1]);
        edges_vec.reserve(m);

        while (getline(file, line)) {
            line_vec.clear();
            std::replace(std::begin(line),std::end(line),'\t',' ');
            boost::trim_right(line);
            boost::trim_left(line);
            std::string::iterator new_end = std::unique(line.begin(), line.end(), BothAreSpaces);
            line.erase(new_end, line.end());

            boost::split(line_vec, line, boost::is_any_of(" "));

           int i = stoi(line_vec[0])-1;
           int j = stoi(line_vec[1])-1;
           edges_vec.emplace_back(i,j);
        }
        file.close();
    } else {
        cerr << "Unable to open file" << std::endl;
    }
    return make_pair(edges_vec, n);
}

void FileUtil::floydWarshall(std::vector<std::vector<float>> &G) {
    int n = G.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int l = 0; l < n; ++l) {
                float cost = (G[i][j] == +INFINITY || G[i][l] == +INFINITY) ?
                             +INFINITY : G[i][j] + G[i][l];
                if (cost < G[j][l]) {
                    G[j][l] = cost;
                }
            }
        }
    }
}

float FileUtil::stdDev(std::vector<float> &items, float average) {
    float std = 0;
    for (float item : items) {
        std += pow(item - average, 2);
    }
    int n = items.size() > 2 ? items.size() - 1 : items.size();
    return sqrt(std / n);
}

bool FileUtil::save(std::string &output_path, std::string &content) {
    std::ofstream output_file(output_path);
//    output_file.write(&content, content.size());
    output_file << content;
    output_file.close();
    return true;
}
