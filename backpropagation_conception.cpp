#include <iostream>
#include <math.h>
using namespace std;

class MulLayer{
    public :
      float x;
      float y;
      float out;
      float dx;
      float dy;

      double sigmoid(double x);

      void forward(float neural_1, float neural_2);

      void backward(float dout);
};

void MulLayer::forward(float neural_1, float neural_2)
{
    x = neural_1;
    y = neural_2;
    out  = x * y;
}

void MulLayer::backward(float dout) {
    dx = dout * y;
    dy = dout * x;
}

int main()
{
    int orange_num = 2;      //橘子2顆
    int orange_price = 100;  //橘子價錢100元
    float tax = 1.1;        //稅金10%

    MulLayer orange_price_layer;
    MulLayer tax_layer;

    // Forward
    orange_price_layer.forward(orange_num, orange_price);
    tax_layer.forward(orange_price_layer.out, tax);

    cout << "Forward" << endl;
    cout << orange_price_layer.out << endl;
    cout << tax_layer.out << endl;

    // backward
    tax_layer.backward(1);
    cout << tax_layer.dx << endl;
    cout << tax_layer.dy << endl;
    orange_price_layer.backward(tax_layer.dx);

    cout << "Backward" << endl;
    cout << "Impact of one more apple for total price : " << orange_price_layer.dx << endl;
    cout << "Impact of one more dollar for total price : " << orange_price_layer.dy << endl;

    return 0;
}
