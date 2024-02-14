#include <iostream>
#include <vector>
#include <cmath>

#if FL_VAL
    #define TYPE double
#else
    #define TYPE float
#endif

#define LEN 10000000
#define PI 3.141592653589793238462643383279502884

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    
    vector<TYPE> vec;

    TYPE sum = 0.0;

    for (int i = 0; i < LEN; i++) {
        TYPE value = (TYPE)sin(i * 2 * (TYPE)PI / LEN);
        vec.push_back(value);
        sum += value;
    }

    cout << "Сумма значений синуса: " << sum << endl;

    return 0;
}
