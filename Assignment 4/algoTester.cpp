#include <iostream>
#include "cohen.h"
using namespace std;

int main () {
    LineClipping lc (0,1,0,1);

    double x0,y0,x1,y1;
    while (1) {
        cin >> x0 >> y0 >> x1 >> y1;
        if (lc.lineClip (x0,y0,x1,y1)) {
            cout << "YES" << endl;
            cout << "(" << x0 << "," << y0 << "), (" << x1 << ","  << y1 << ")"<< endl;
        }
        else cout << "NO" << endl;
    }

    return 0;
}

