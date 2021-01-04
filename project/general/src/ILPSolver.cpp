//
// Created by tim on 04.01.21.
//

#include "ILPSolver.hpp"

ILPSolver::ILPSolver(vector<Point> &points) : m_points(points), util(points)
{}


int ILPSolver::solve()
{
    int NUM_POINTS = m_points.size();

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
                        model.addConstr(util.o(i, a, j, b) + l[i][a] + l[j][b] <= 2, cname.str());
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

        // Save solution

        for (int i = 0; i < NUM_POINTS; i++) {
            bool labeled = false;
            for (int a = 0; a < 4; a++)
            {
                if (l[i][a].get(GRB_DoubleAttr_X) == 1.0)
                {
                    m_points[i].set_label_pos(a + 1);
                    labeled = true;
                }
            }
            if (!labeled)
            {
                m_points[i].clear();
            }
        }

    } catch (GRBException e)
    {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch (...)
    {
        cout << "Exception during optimization" << endl;
    }

    return 0;
}


