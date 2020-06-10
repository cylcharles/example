#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

using namespace std;

const int LAYERS = 3;
const int INPUTS = 4;
const int HIDDEN = 2;
const int OUPUTS = 1;

//神經元
class Neural
{
    public :
    double Value;
    double *Weights;
    double *fixWeights;
    int PreLayerSize;

    public :

    Neural(int preLayerSize) {
        int s;
        PreLayerSize = preLayerSize;
        Weights = new double[PreLayerSize];     //初始權重
        fixWeights = new double[PreLayerSize];  //修正權重

        if (PreLayerSize > 0) {
            for ( s = 0; s < PreLayerSize; s++) {
                Weights[s] = ( (double)rand() / RAND_MAX ) * 2 - 1;
                printf("(double)rand() = %f\n", (double)rand());
                printf("RAND_MAX = %d\n", RAND_MAX);
                printf("%f\n", Weights[s]);
            }
        }
    }
};

class Network
{
    public:

    Neural ***Neurals;
    double *y_true;

    int Neurals_lengths[LAYERS];

    //回傳輸入和輸出
    Neural ** InputLayer;  // Neurals[0];
    Neural ** OutputLayer; // Neurals[2];

    Network(int Layer, int InputLayerSize, int HiddenLayerSize, int OutputLayerSize) {

        // 宣告每一層的大小
        Neurals = new Neural **[Layer];
        Neurals[0] = new Neural *[InputLayerSize];
        Neurals[1] = new Neural *[HiddenLayerSize];
        Neurals[2] = new Neural *[OutputLayerSize];

        OutputLayer = Neurals[2];
        InputLayer = Neurals[0];
        Neurals_lengths[0] = InputLayerSize;
        Neurals_lengths[1] = HiddenLayerSize;
        Neurals_lengths[2] = OutputLayerSize;

        y_true = new double[OutputLayerSize];

        int preLayerSize = 0; //第一層Input前面無輸入，所以為0
        for (int i = 0; i < LAYERS; i++) {
            for (int j = 0; j < Neurals_lengths[i]; j++) {
                Neurals[i][j] = new Neural(preLayerSize);
            }
            preLayerSize = Neurals_lengths[i];
        }
    }
};

int main()
{
    Network *networks;
    networks = new Network(LAYERS, INPUTS, HIDDEN, OUPUTS);
}
