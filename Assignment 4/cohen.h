#include <iostream>
using namespace std;

typedef int OutCode;
const int INSIDE = 0;   // 0000
const int LEFT   = 1;   // 0001
const int RIGHT  = 2;   // 0010
const int BOTTOM = 4;   // 0100
const int TOP    = 8;   // 1000

class LineClipping {
    OutCode ComputeOutCode(double x, double y);

    // Defines the clipping rectangle
    double xmin, xmax, ymin, ymax;

    public:
        LineClipping (double XMIN, double XMAX, double YMIN, double YMAX) {
            xmin = XMIN; xmax=XMAX; ymin=YMIN; ymax=YMAX;
        }

        // Returns TRUE, if (x0,y0) -> (x1,y1) inside the clipping area
        // Otherwise returns FALSE,
        // NOTE: References to the points are passed
        bool lineClip(double& x0, double& y0, double& x1, double& y1);
};
