#ifndef MEANS_H
#define MEANS_H

#include <vector>

using namespace std;

class RGB;

void InitializeCentroids(vector<RGB>& centroids, vector<RGB>& image);

void UpdateCentroids(vector<RGB>& centroids, vector<int>& sets, vector<RGB>& image);
void UpdateNodes(vector<RGB>& centroids, vector<int>& sets, vector<RGB>& image, bool& IsDone);
void UpdateImage(vector<RGB>& centroids, vector<int>& sets, vector<RGB>& image);

void PrintCentroids(vector<RGB>& centroids);

#endif