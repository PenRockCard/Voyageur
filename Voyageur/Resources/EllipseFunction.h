#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <math.h>
#include <numbers>
#include <vector>

struct EllipsePoint {
    double x;
    double y;
};

class EllipseFunction {

    std::vector<EllipsePoint> ellipsePoints;

    void NewList();

    /** The number of points the ellipse has*/
    int numberPoints;
    /** How far offset the ellipse is from the origin (x) */
    double offsetX;
    /** How far offset the ellipse is from the origin (y) */
    double offsetY;
    /** The angle of the ellipse (measured from quadrant I (x+,y+) going CCW) */
    double angle;

public:
    EllipseFunction(double aConstr, double bConstr, int numberPointsConstr, double offSetXConstr = 0, double offSetYConstr = 0,
            double angleConstr = 0);

    void UpdateNumberPoints(int newNumberPoints);

    double *GetXArray();

    double *GetYArray();

    int GetNumberPoints();

    //These are public because they're used elsewhere. Consider moving them to a getter.
    /** The a value for the ellipse (the long side) */
    double a;
    /** The b value for the ellipse (the short side) */
    double b;

};

#endif //ELLIPSE_H
