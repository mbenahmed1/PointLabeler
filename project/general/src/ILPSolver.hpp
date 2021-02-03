/**
 * ILPSolver.hpp
 *
 *  @date 31.10.2020
 *  @author Tim Adam (tadam@uos)
 *  @author Martin ben Ahmed (mbenahmed@uos)
 */
#ifndef POINTLABELER_ILPSOLVER_HPP
#define POINTLABELER_ILPSOLVER_HPP

#include "/opt/gurobi911/linux64/include/gurobi_c++.h"
#include "Point.hpp"
#include "Util.hpp"
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

class ILPSolver
{
public:
    explicit ILPSolver(vector<Point> &points);

    int solve();

private:
    vector<Point> &m_points;

    Util util;
};

#endif //POINTLABELER_ILPSOLVER_HPP
