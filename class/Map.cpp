#include "Map.hpp"

Map::Map(int width, int height) {}
Map::~Map() {}
void Map::Update() {
    std::vector<std::vector<double>> buffer;
    static const int dirs[9][2] = {
        {-1,-1}, {-1,0}, {-1,1},
        { 0,-1}, { 0,0}, { 0,1},
        { 1,-1}, { 1,0}, { 1,1}
    };
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++){
            pixels[i][j].ExpandCalculate();
            buffer[i][j] = 0.0;
        }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            const auto &exp = pixels[i][j].Expand();

            for (int k = 0; k < 9; k++) {
                int ni = i + dirs[k][0];
                int nj = j + dirs[k][1];

                if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    buffer[ni][nj] += exp[k];
            }
        }
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            pixels[i][j].ApplyBuffer(buffer[i][j]);
}



double Map::GetTotalAmount() {
    double sum = 0.0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            sum += pixels[i][j].GetAmount();
        }
    }
    return sum;
}
