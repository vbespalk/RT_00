#include <iostream>

using namespace std;

int main()
{
    bitset<32> x(726541);
    cout << x << endl;
    cout << ((726541 >> 8) % 256) << endl;
    return 0;
}