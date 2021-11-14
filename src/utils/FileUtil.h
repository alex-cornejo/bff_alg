//
// Created by alex on 26/05/20.
//

#ifndef CKC_CPP_UTILS_H
#define CKC_CPP_UTILS_H

#include <vector>

class FileUtil {

public:
    static std::vector<std::vector<int>> loadGEucSpace(const std::string &file_path);

    static std::pair<std::vector<std::pair<int, int>>, int> load_graph(const std::string &file_path);

    static float stdDev(std::vector<float> &items, float average);

    static void floydWarshall(std::vector<std::vector<float>>& G);

    static std::vector<std::vector<float>> loadGMetricSpace(int n, const std::string &file_path);

    static bool save(std::string &output_path, std::string &content);
};


#endif //CKC_CPP_UTILS_H
