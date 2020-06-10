# Using C++ to do exercise.
## Simple Neural networks
建構簡單神經網路架構，各層神經元數量 : Input=4，Hidden Layer = 2，Output = 1。
* 指定層數、輸入、隱藏層、輸出層大小參數 :
```
const int LAYERS = 3;
const int INPUTS = 4;
const int HIDDEN = 2;
const int OUPUTS = 1;
```
* 定義神經元，用二維陣列儲存神經元，並初始隨機權重 :
```
class Neural
{
    ...

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
```
* 建構神經網路，宣告每一層大小 :
```
class Network
{
    ...

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
```
* 執行
```
$ g++ -o neural_network neural_network.cpp
$ neural_network
```
目前程式只有定義架構方面，其他細節計算部分未加入。

## Simple Backpropagation Conception
用簡單小範例幫助自己紀錄反向傳播的基本概念。
先假設一個很簡單的網路，進行前向傳播 :
* 假設輸入是a、b和c，計算單元將a和b進行相加
```
x = a + b
```
* 而另一個計算單元是將b和c進行乘積 :
```
y = a * b
```
* 最後一層的計算單元則是將剛剛計算好的x函式和y函式進乘積 :
```
f = x * y
```
* 再來進行反向傳播解函數微分，對每一個計算單元(神經元)偏微分，首先由最終輸出f反推回x函數時，是對x進行偏微 :
```
df/dx =  y
```
* 再來是由f反推回y函數時，對y進行偏微 :
```
df/dy =  x
```
接著以此類堆計算出所有函式的偏微分，有了這些值我們就可以計算a、b和c輸入變化時，對輸出f的影響，以一個神經網路來說，就可以調整權重，訓練網路讓輸出值越來越接近真實值，使網路找到最佳解，為了方便理解運作流程，我們用一個更實際的例子來演示計算。
* 完整示意圖如下 :
![image](https://github.com/cylcharles/Pytorch_exercise/blob/master/img/example1.png)

假設網路的輸入是購買橘子的數量和橘子單價，以及加上購物的稅金，則最後輸出是購買橘子的總金額。示意圖中，假設購買1顆橘子，1顆橘子單價100元，並且需加上10%的稅金，那最後總價就是220元。那我們就可以用反向傳播的概念來計算如果橘子數量不一樣，對最後金額有多少影響;如果橘子漲一元，對總金額有多少影響。
![image](https://github.com/cylcharles/Pytorch_exercise/blob/master/img/example2.png)

首先也是對每一個參數進行偏微，每條線偏微後的結果如紅字所示，接著就可以進行計算。
* 假設多買了1顆橘子，我們從最後輸出反向走回橘子數量輸入，將經過的值全部相乘，結果是110元，意思是多買1顆橘子總金額會多110元 :
```
1 x 1.1 x 100 = 110
```
* 又假設橘子漲1元，一樣從最後輸出反向走回橘子單價的輸入，將經過的值相乘，結果是2.2元，意思是1顆橘子漲1元總金額會多2.2元 :
```
1 x 1.1 x 2 = 2.2
```
* 執行
```
$ g++ -o backpropagation backpropagation_conception.cpp
$ backpropagation
```
總結來說，反向傳播顧名思義就是由最後答案往回推，根據輸出結果，不斷更新權重，使網路一步步最佳化，進而讓輸出值越來越接近真實值，這樣就是一個反向傳播最基本的概念，用一個簡單的程式碼實做。
