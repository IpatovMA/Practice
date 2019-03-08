#include "plant.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <iomanip>

using namespace std;

int enter (int &K, vector<int> &M, double &T, int &N)
{
    cerr<<"Number of sensor: ";
    cin>>K;
    M.resize(K);
    cerr<<"Numbers of sensors: ";
    for(size_t i = 0; i < K; i++)
    {
        cin>>M[i];
    }
    cerr<<"Pause time: ";
    cin>>T;
    cerr<<"Number of iteration: ";
    cin>>N;
}
double average(vector<double> A)
{
    double S = 0;
    for(double a: A)
    {
        S+=a;
    }
    S/= A.size()*1.0;
    return S;
}
double mediana(vector<double> M)
{
    size_t N = M.size();
    double Med;
    if (N%2)
    {
        Med = M[(N)/2];
    }
    else
    {
        Med = (M[N/2]+M[(N/2)-1])/2;
    }
    return Med;
}
int main(int argc, char* argv[])
{
    // Инициализация ОУ.
    Plant plant;
    plant_init(plant);

    int K,N;
    double T;
    vector<int> M;

    enter(K,M,T,N);
    M.resize(K);
    /**<     cout<<K<<'\n';
        for(int m:M)
        {
            cout<<m<<" ";
        }
        cout<<'\n'<<T<<"  "<<N<<'\n'; */
    vector<vector<double>> X(K);

    for (size_t j = 0; j < N; j++)
    {
        for (size_t i = 0; i < K; i++)
        {
            X[i].push_back(plant_measure(M[i], plant));
        }
        Sleep(T*1000);
       //s Sleep(T);
    }

    vector<vector<double>> Z(K);
    for(size_t i = 0; i < K; i++)
    {
        for(size_t k=0; k<N; k++)
        {
            size_t maxJ=0;
            for (size_t j = 0; j < (N-k); j++)
            {
                if (X[i][maxJ]>X[i][j])
                {
                    maxJ=j;
                }
            }
            Z[i].push_back(X[i][maxJ]);
            //     cout<<k<<" -- "<<maxJ<<"  "<<X[i][maxJ]<<'\n';
            X[i].erase(X[i].begin()+maxJ);
        }
    }

    vector<double> Aver(K), Med(K);

    for (size_t i = 0; i<K; i++)
    {
        Aver[i] = average(Z[i]);
        Med[i] = mediana(Z[i]);
    }
    cout<<'\n'<<'\t';

        for (size_t i = 0; i < K; i++)
    {
        // cout.unsetf(ios::showpos);
        cout<<"sens#"<<M[i]<<'\t';
    }
    cout<<'\n';
     for (size_t i = 0; i < N; i++)
    {
        // cout.unsetf(ios::showpos);
        cout<<"#"<<i+1<<'\t';
//       cout.setf(ios::showpos);
        for (size_t j = 0; j < K; j++)
        {
            cout<<Z[j][i]<<'\t';
        }
        cout<<'\n';
    }

    cout<<"Average"<<'\t';
                for (size_t i = 0; i < K; i++)
        {
            cout<<Aver[i]<<'\t';
        }
        cout<<'\n';
    cout<<"Median"<<'\t';
                for (size_t i = 0; i < K; i++)
        {
            cout<<Med[i]<<'\t';
        }
        cout<<'\n';

/**    cout.setf(ios::fixed);
    cout<<'\t';
    //cout<<"Sen./Iter.";
    for(size_t i = 1; i < N+1; i++)
    {
        cout.width(7);
        cout.setf(ios::right);
        cout<<"iter#"<<i<<'\t';
    }

    cout<<"  "<<"Average"<<"\t "<<"Mediana"<<'\n';

    for (size_t i = 0; i < K; i++)
    {
        // cout.unsetf(ios::showpos);
        cout<<"sens#"<<M[i]<<'\t';
//       cout.setf(ios::showpos);
        for (size_t j = 0; j < N; j++)
        {
            cout<<Z[i][j]<<'\t';
        }

        cout<<Aver[i]<<'\t'<<Med[i]<<'\n';
    }
 */



    /**<     for (vector<double> A: Z)
        {
            for(double B: A)
            {
                cout<<B<<"  ";
            }
            cout<<'\n';
        }
        cout<<'\n';
        cout<<'\n'; */

    // cout<<Z[1].size()<<"  "<<average(Z[1])<<"  "<<mediana(Z[1]);


    return 0;
}
