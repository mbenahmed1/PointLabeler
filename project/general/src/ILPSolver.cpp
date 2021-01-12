//
// Created by tim on 04.01.21.
//

#include "ILPSolver.hpp"
#include "GreedyAlgorithm.hpp"


class mycallback : public GRBCallback
{
public:
    int numvars;
    GRBVar *vars;
    vector<Point> &points;
    std::vector<std::vector<int>>& map;

    mycallback(int xnumvars, GRBVar *xvars, vector<Point>& points, vector<vector<int>>& map) :map(map), points(points)
    {
        numvars = xnumvars;
        vars = xvars;
    }

protected:
    void callback()
    {
        try
        {
            if (where == GRB_CB_MIPNODE)
            {
                // MIP node callback
                //cout << "**** New node ****" << endl;
                if (getIntInfo(GRB_CB_MIPNODE_STATUS) == GRB_OPTIMAL)
                {
                    double *x = getNodeRel(vars, numvars);


                    /*DEBUG VARIABLES
                    for (int i = 0; i < numvars; i += 4) {
                        cout << vars[i+0].get(GRB_StringAttr_VarName) << ": " << x[i+0];
                        cout << vars[i+1].get(GRB_StringAttr_VarName) << ": " << x[i+1];
                        cout << vars[i+2].get(GRB_StringAttr_VarName) << ": " << x[i+2];
                        cout << vars[i+3].get(GRB_StringAttr_VarName) << ": " << x[i+3] << endl;
                    }
                    */

                    for (int i = 0; i < numvars; i += 4)
                    {
                        points[i/4].clear();
                        double maxValue = 0.0;
                        int maxA = -1;

                        for (int a = 0; a < 4; a++)
                        {
                            if (x[i+a] > maxValue)
                            {
                                maxValue = x[i+a];
                                maxA = a;
                            }
                        }

                        int p_index = i/4;

                        // set points
                        if (maxValue == 1.0)
                        {
                            points[p_index].set_label_pos(maxA);
                            continue;
                        }
                        else
                        {
                            x[i + 0] = 0.0;
                            x[i + 1] = 0.0;
                            x[i + 2] = 0.0;
                            x[i + 3] = 0.0;
                            points[p_index].set_label_pos(maxA);
                            x[i + maxA] = 1.0;

                            if (Util::hasConflict(map, points, p_index))
                            {
                                points[p_index].clear();
                                x[i + maxA] = 0.0;
                            }
                        }

                        // clear solution
                        points[p_index].clear();
                    }

                    setSolution(vars, x, numvars);
                    delete[] x;
                }
            }
        } catch (GRBException e)
        {
            cout << "Error number: " << e.getErrorCode() << endl;
            cout << e.getMessage() << endl;
        } catch (...)
        {
            cout << "Error during callback" << endl;
        }
    }
};

ILPSolver::ILPSolver(vector<Point> &points) : m_points(points), util(points)
{}


int ILPSolver::solve()
{
    int NUM_POINTS = m_points.size();

    GreedyAlgorithm g(m_points);
    g.solve();

    try
    {
        // Create an environment
        GRBEnv env = GRBEnv(true);
        //env.set("LogFile", "mip1.log");
        env.set(GRB_IntParam_LogToConsole, 0);
        env.start();

        // Create an empty model
        GRBModel model = GRBModel(env);

        // Create variables
        GRBVar l[NUM_POINTS][4]; // l_ia

        for (int i = 0; i < NUM_POINTS; i++)
        {
            int pos = -1;
            if (m_points[i].get_is_labeled() == 1)
            {
                pos = m_points[i].get_label_enum() - 1;
            }
            for (int a = 0; a < 4; a++)
            {
                ostringstream vname;
                vname << "l_" << i << a;
                l[i][a] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, vname.str());
                if (pos == a)
                {
                    l[i][a].set(GRB_DoubleAttr_Start, 1.0);
                }
                else
                {
                    l[i][a].set(GRB_DoubleAttr_Start, 0.0);
                }
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
        // Create a callback object and associate it with the model
        int numvars = NUM_POINTS * 4;
        model.set(GRB_IntParam_BranchDir, -1);
        model.update();

        GRBVar* vars = model.getVars();
        //for (int i = 0; i < numvars; i++) {
        //    cout << vars[i].get(GRB_StringAttr_VarName);
        //}
        mycallback cb = mycallback(numvars, vars, m_points, g.m_conflicts);

        model.setCallback(&cb);

        // Optimize model
        model.optimize();

        /* PRINT SOLUTION
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
        */

        // Save solution

        for (int i = 0; i < NUM_POINTS; i++)
        {
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


