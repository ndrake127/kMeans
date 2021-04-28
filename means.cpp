#include <algorithm>
#include <iostream>
#include <iomanip>

#include "means.h"
#include "RGB.h"

// randomly assigns centroids by permuting a list of integers 0, 1, ..., up to the number of pixels
// and using the first k elements of the list to choose an RGB from image
void InitializeCentroids(vector<RGB>& centroids, vector<RGB>& image){
    vector<int> range(image.size());
    for(unsigned int i = 0; i < range.size(); i++){
        range[i] = i;
    }
    random_shuffle(range.begin(), range.end());

    for(unsigned int i = 0; i < centroids.size(); i++){
        centroids[i] = image[range[i]];
    }
}

// updates centroids by finding the mean RGB of the pixels currently assigned to the
// respective centroid
void UpdateCentroids(vector<RGB>& centroids, vector<int>& sets, vector<RGB>& image){
    // channels keeps track of the sum of the R, G, and B channels of the nodes in a centroid
    // count keeps track of the total number of nodes in the range of a centroid
    unsigned int channels[3] = { 0, 0, 0 };
    unsigned int count = 0;
    
    for(unsigned int i = 0; i < centroids.size(); i++){
        // resets temp variables for new centroid to use
        for(unsigned int k = 0; k < 3; k++){
            channels[k] = 0;
        } 
        count = 0;
        
        for(unsigned int j = 0; j < sets.size(); j++){
            // if this if is true, then the working node j is within range of the working centroid i
            // after this for loop is finished then the sums of the channels is stored and the count is stored
            if(i == sets[j]){
                for(unsigned int k = 0; k < 3; k++){
                    channels[k] += image[j].GetChannel(k);
                }
                count++;
            }
        }

        // just in case a divide-by-zero tries to happen, not sure why this would happen
        // and if it does it probably means the program has failed anyways
        if(count == 0)
            continue;

        for(unsigned int k = 0; k < 3; k++){
            centroids[i].SetChannel(k, (float)channels[k]/count);
        }
    }
}

// the distance from each node is found to each centroid
// the minimum distance is found and then the node is associated
// to the centroid to which it is closest
void UpdateNodes(vector<RGB>& centroids, vector<int>& sets, vector<RGB>& image, bool& IsDone){    
    float MinimumDistance = 0;
    float CurrentDistance = 0;
    
    // assumes that the algorithm is done, and if any assignment occurs this is changed back to false
    // when the function returns and this is true, then k-means has converged.
    IsDone = true;

    // i stores the index of the working node
    // image[i] stores the working node itself
    // centroids[j] stores the working centroid

    // sets[i] stores the index of the closest centroid, which is the purpose of this function
    for(unsigned int i = 0; i < sets.size(); i++){
        MinimumDistance = image[i].GetDistanceTo(centroids[0]);
        sets[i] = 0;

        // j stores the working centroid
        for(unsigned int j = 1; j < centroids.size(); j++){
            CurrentDistance = image[i].GetDistanceTo(centroids[j]);
            
            if(CurrentDistance < MinimumDistance){
                MinimumDistance = CurrentDistance;
                sets[i] = j;
            }
        }
    }
}

void UpdateImage(vector<RGB>& centroids, vector<int>& sets, vector<RGB>& image){
    for(unsigned int i = 0; i < image.size(); i++){
        for(unsigned int j = 0; j < 3; j++){
            image[i].SetChannel(j, centroids[sets[i]].GetChannel(j));
        }
    }
}

void PrintCentroids(vector<RGB>& centroids){
    for(unsigned int i = 0; i < centroids.size(); i++){
        for(unsigned int j = 0; j < 3; j++){
            cout << setw(3) << (int)centroids[i].GetChannel(j) << ' ';
        }
        cout << '\n';
    }
}