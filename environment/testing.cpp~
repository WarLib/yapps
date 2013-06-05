#ifdef TESTING_ENV
#include "world.hpp"
#include <iostream>

int main(void) {
    int n = 500;
    string seed = "MagicalTestingSeed1337";
    double col = 8.5;

    Galaxy & MyGalaxy(Galaxy::GetGalaxy(n, col));
    cout << "--expo--" << endl;
    for (int i = 0; i < 10; i++)
        cout << MyGalaxy.rand_gen.exponential() << endl;
    cout << "--gamma--" << endl;
    for (int i = 0; i < 10; i++)
        cout << MyGalaxy.rand_gen.gamma(10.0) << endl;
    cout << "--random--" << endl;
    for (int i = 0; i < 10; i++)
        cout << MyGalaxy.rand_gen.random(0, 2000) << endl;
    cout << "--normal--" << endl;
    for (int i = 0; i < 10; i++)
        cout << MyGalaxy.rand_gen.normal() << endl;
    cout << "--poisson--" << endl;
    for (int i = 0; i < 10; i++)
        cout << MyGalaxy.rand_gen.poisson(10) << endl;
    StellarObject** MyObjects = MyGalaxy.GetSystems(n)[0]->GetObjects(n);


}
#endif
