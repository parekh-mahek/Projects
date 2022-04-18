#include <bits/stdc++.h>
using namespace std;

//recursive function which gives values of chromatic polynomial of the graph
void chropoly(vector<vector<int>> adjmat, vector<int>& coef)
{
    for(int i=0;i<adjmat.size();i++)
    {
        for(int j=0;j<i;j++)
        {
            if(adjmat[i][j]==0 && i!=j)
            {
                vector<vector<int>>n=adjmat;
                n[i][j]=1;
                n[j][i]=1;
                chropoly(n,coef);
                vector<vector<int>>nn=adjmat;
                for(int k=0;k<adjmat.size();k++)
                {
                    if(nn[i][k]!=1 && nn[j][k]==1)
                    {
                        nn[i][k]=1;
                        nn[k][i]=1;
                    }
                }
                nn.erase(nn.begin()+j);
                for(int i=0;i<nn.size();i++)
                {
                    nn[i].erase(nn[i].begin()+j);
                }
                chropoly(nn,coef);
                return;
            }
        }
    }
    coef[adjmat.size()]++;
}

int main()
{
    //taking inputs for 1st graph
    int n;
    cout<<"Enter number of vertices in 1st graph: ";
    cin>>n;
    vector<vector<int>> adjmat1(n, vector<int>(n,0));
    cout<<"Enter number of edges in 1st graph: ";
    int e;
    cin>>e;
    cout<<"Enter pair of vertices forming edges: \n";
    int x,y;
    for(int i=0;i<e;i++)
    {
        cin>>x>>y;
        adjmat1[x][y]=1;
        adjmat1[y][x]=1;
    }

    //taking inputs for 2nd graph
    int n2;
    cout<<"Enter number of vertices in 2nd graph: ";
    cin>>n2;
    vector<vector<int>> adjmat2(n2, vector<int>(n2,0));
    cout<<"Enter number of edges in 2nd graph: ";
    int e2;
    cin>>e2;
    cout<<"Enter pair of vertices forming edges: \n";
    for(int i=0;i<e2;i++)
    {
        cin>>x>>y;
        adjmat2[x][y]=1;
        adjmat2[y][x]=1;
    }

    //if number of vertices and edges are not same then declare not in same equivalent class
    if(n!=n2 || e!=e2)
    {
        cout<<"Two graphs are not in same chromatic equivalence class.\n";
        return 0;
    }

    vector<int> coef1(n+1,0);
    vector<int> coef2(n+1,0);

    //callinf function chropoly to find chromatic polynomial of the graphs
    chropoly(adjmat1,coef1);
    chropoly(adjmat2,coef2);

    //printing chromatic polynimial of graph 1
    cout<<"Chromatic Polynomial for 1st Graph = ";
    for(int i=n;i>2;i--)
    {
        cout<<coef1[i]<<"*lambda("<<i<<") + ";
    }
    cout<<coef1[2]<<"*lambda(2)";
    cout<<"\n";

    //printing chromatic polynomial of graph 2
    cout<<"Chromatic Polynomial for 2nd Graph = ";
    for(int i=n;i>2;i--)
    {
        cout<<coef2[i]<<"*lambda("<<i<<") + ";
    }
    cout<<coef2[2]<<"*lambda(2)";
    cout<<"\n";

    //declaring whether 2 graphs are in same equivalence class or not
    if(coef1==coef2)
    {
        cout<<"Two graphs are in same chromatic equivalence class.\n";
    }
    else
    {
        cout<<"Two graphs are not in same chromatic equivalence class.\n";
    }

    return 0;
}