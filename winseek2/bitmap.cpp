#include "bitmap.h"
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
typedef unsigned int uint;

void write_bmp(const string path, const uint width, const uint height, const int* const data) {
    const uint pad = (4 - (3 * width) % 4) % 4, filesize = 54 + (3 * width + pad) * height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
    char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
    for (uint i = 0; i < 4; i++) {
        header[2 + i] = (char)((filesize >> (8 * i)) & 255);
        header[18 + i] = (char)((width >> (8 * i)) & 255);
        header[22 + i] = (char)((height >> (8 * i)) & 255);
    }
    char* img = new char[filesize];
    for (uint i = 0; i < 54; i++) img[i] = header[i];
    for (uint y = 0; y < height; y++) {
        for (uint x = 0; x < width; x++) {
            const int color = data[x + (height - 1 - y) * width];
            const int i = 54 + 3 * x + y * (3 * width + pad);
            img[i] = (char)(color & 0xFF);
            img[i + 1] = (char)((color >> 8) & 0xFF);
            img[i + 2] = (char)((color >> 16) & 0xFF);
        }
        for (uint p = 0; p < pad; p++) img[54 + (3 * width + p) + y * (3 * width + pad)] = 0;
    }
    ofstream file(path, ios::out | ios::binary);
    file.write(img, filesize);
    file.close();
    delete[] img;
}

std::string createThermalBitmap(DWORD* frameBuffer) {
    auto p1 = std::chrono::system_clock::now();
    std::string filename = "WINSEEK_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(p1.time_since_epoch()).count()) + ".bmp";
    write_bmp(filename, 206, 156, (int*)frameBuffer);
    return filename;
}