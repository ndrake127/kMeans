// Macros to enable image reading/writing, thanks to stb team
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "RGB.h"
#include "means.h"

using namespace std;

struct Coordinate{
    int x, y;
};

void ReadImage(const char* path, vector<RGB>& image, int& x, int & y);

void WriteImage(const char* path, vector<RGB>& image, int& x, int& y);

int main(int argc, char** argv){
    int k = -1;
    string outfile = "output.png";
    
    if(argc != 3){
        cerr << "usage: ./means -means -filename\n";
        return 0;
    }else{
        k = stoi(string(argv[1]));
    }

    // getting image data with stb_image library
    // returns image, x, and y by reference
    vector<RGB> image;
    int x, y;
    ReadImage(argv[2], image, x, y);

    // there are k centroids
    // sets[i] is the index of the centroid closest to the ith node
    vector<RGB> centroids(k);
    InitializeCentroids(centroids, image);
    // PrintCentroids(centroids);

    bool IsDone = false;

    vector<int> sets(image.size());
    UpdateNodes(centroids, sets, image, IsDone);

    /*************************************************/

    for(int i = 0; i < 30; i++){
        // cout << i << '\n';
        UpdateCentroids(centroids, sets, image);
        PrintCentroids(centroids);
        cout << '\n';
        UpdateNodes(centroids, sets, image, IsDone);
    }

    UpdateImage(centroids, sets, image);

    /*************************************************/

    WriteImage(outfile.c_str(), image, x, y);
}

// reads image data into vector of RGB's which is passed by reference
// x is the width, y is the height
void ReadImage(const char* path, vector<RGB>& image, int& x, int& y){
    int n;
    unsigned char* data = stbi_load(path, &x, &y, &n, 3);

    image.resize(x*y);

    for(int i = 0; i < x*y; i++){
        for(int j = 0; j < 3; j++){
            image[i].SetChannel(j, data[3*i+j] & 255);
        }
    }

    stbi_image_free(data);
}

// writes image data by converting RGB vector into the original format loaded by stb
// and providing it back to stb_image_write library
void WriteImage(const char* path, vector<RGB>& image, int& x, int& y){
    unsigned char* data = new unsigned char[3 * image.size()];

    for(int i = 0; i < x*y; i++){
        for(int j = 0; j < 3; j++){
            data[3*i+j] = image[i].GetChannel(j);
        }
    }

    // last parameter is the number of bytes between the first byte of each row
    // each pixel is 3 bytes, x is the width of a row, and sizeof returns the size of a byte
    stbi_write_png(path, x, y, 3, data, x * 3 * sizeof(unsigned char));
    delete [] data;
}