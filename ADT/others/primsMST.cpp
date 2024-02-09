#include <bits/stdc++.h>
using namespace std;

#define I INT_MAX

int n = 7;
int cost[][8] = {
    {I, I, I, I, I, I, I, I},
    {I, I, 25, I, I, I, 5, I},
    {I, 25, I, 12, I, I, I, 10},
    {I, I, 12, I, 8, I, I, I},
    {I, I, I, 8, I, 16, I, 14},
    {I, I, I, I, 16, I, 20, 18},
    {I, 5, I, I, I, 20, I, I},
    {I, I, 10, I, 14, 18, I, I},
};
int near[8] = {I, I, I, I, I, I, I, I};
int mst[2][7];

int main()
{
    int i, j, k, u, v, min = I;
    int minCost = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (cost[i][j] < min)
            {
                min = cost[i][j];
                u = i;
                v = j;
            }
        }
    }
    mst[0][0] = u;
    mst[1][0] = v;
    near[u] = near[v] = 0;
    for (i = 0; i <= n; i++)
    {
        if (near[i] != 0)
        {

            if (cost[i][u] < cost[i][v])
                near[i] = u;
            else
                near[i] = v;
        }
    }
    for (i = 1; i <= n - 1; i++)
    {
        min = I;
        for (j = 1; j <= n; j++)
        {
            if (near[j] != 0 && cost[j][near[j]] < min)
            {
                k = j;
                min = cost[j][near[j]];
            }
        }
        mst[0][i] = k;
        mst[1][i] = near[k];
        near[k] = 0;
        for (j = 1; j <= n; j++)
        {
            if (near[j] != 0 && cost[j][k] < cost[j][near[k]])
                near[j] = k;
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        cout << "(" << mst[0][i] << ", " << mst[1][i] << ")  ";
        minCost += cost[mst[0][i]][mst[1][i]];
    }
    cout << endl
         << minCost << endl;
    return 0;
}