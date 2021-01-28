/* Copyright 2020, Gurobi Optimization, LLC */

/* This example formulates and solves the following simple MIP model:

     maximize    x +   y + 2 z
     subject to  x + 2 y + 3 z <= 4
                 x +   y       >= 1
                 x, y, z binary
*/

#include "/opt/gurobi911/linux64/include/gurobi_c++.h"
#include <sstream>

using namespace std;

int solve()
{
    int o[2][4][2][4];
    int NUM_POINTS = 5;

    try
    {
        // Create an environment
        GRBEnv env = GRBEnv(true);
        env.set("LogFile", "mip1.log");
        env.start();

        // Create an empty model
        GRBModel model = GRBModel(env);

        // Create variables
        GRBVar l[NUM_POINTS][4]; // l_ia

        for (int i = 0; i < NUM_POINTS; i++)
        {
            for (int a = 0; a < 4; a++)
            {
                ostringstream vname;
                vname << "l_" << i << a;
                l[i][a] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, vname.str());
            }
        }

        // Set objective
        GRBLinExpr obj = 0.0;
        for (int i = 0; i < NUM_POINTS; i++)
        {
            for (int a = 0; a < 4; a++)
            {
                obj += l[i][a];
            }
        }
        model.setObjective(obj, GRB_MAXIMIZE);

        // Add constraint 1
        for (int i = 0; i < NUM_POINTS; i++)
        {
            GRBLinExpr sum = 0.0;
            ostringstream cname;
            cname << "c1_" << i;
            for (int a = 0; a < 4; a++)
            {
                sum += l[i][a];
            }
            model.addConstr(sum <= 1, cname.str());
        }

        // Add constraint 2
        for (int i = 0; i < NUM_POINTS - 1; i++)
        {
            for (int j = i + 1; j < NUM_POINTS; j++)
            {
                for (int a = 0; a < 4; a++)
                {
                    for (int b = 0; b < 4; b++)
                    {
                        ostringstream cname;
                        cname << "c2_" << i << a << j << b;
                        model.addConstr(l[i][a] + l[j][b] <= 2, cname.str());
                    }
                }
            }
        }

        // Optimize model
        model.optimize();

        cout << "L_ia VALUES FOR SOLUTION:" << endl;
        for (int i = 0; i < NUM_POINTS; i++)
        {
            for (int a = 0; a < 4; a++)
            {
                cout << l[i][a].get(GRB_StringAttr_VarName) << ": " << l[i][a].get(GRB_DoubleAttr_X) << ", ";
            }
            cout << endl;
        }

        cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
    }
    catch (GRBException e)
    {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    }
    catch (...)
    {
        cout << "Exception during optimization" << endl;
    }

    return 0;
}

int main_example()
{
    try
    {
        // Create an environment
        GRBEnv env = GRBEnv(true);
        env.set("LogFile", "mip1.log");
        env.start();

        // Create an empty model
        GRBModel model = GRBModel(env);

        // Create variables
        GRBVar x = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "x");
        GRBVar y = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "y");
        GRBVar z = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "z");

        // Set objective: maximize x + y + 2 z
        model.setObjective(x + y + 2 * z, GRB_MAXIMIZE);

        // Add constraint: x + 2 y + 3 z <= 4
        model.addConstr(x + 2 * y + 3 * z <= 4, "c0");

        // Add constraint: x + y >= 1
        model.addConstr(x + y >= 1, "c1");

        // Optimize model
        model.optimize();

        cout << x.get(GRB_StringAttr_VarName) << " "
             << x.get(GRB_DoubleAttr_X) << endl;
        cout << y.get(GRB_StringAttr_VarName) << " "
             << y.get(GRB_DoubleAttr_X) << endl;
        cout << z.get(GRB_StringAttr_VarName) << " "
             << z.get(GRB_DoubleAttr_X) << endl;

        cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
    }
    catch (GRBException e)
    {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    }
    catch (...)
    {
        cout << "Exception during optimization" << endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    return main_example();
}