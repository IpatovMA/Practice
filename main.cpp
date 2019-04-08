#include "plant.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <iomanip>

using namespace std;

int enter (int &K, vector<int> &M, double &T, int &Nmin,int &Nmax,int &Nstep)
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
    cerr<<"Number of iteration: min, max, step ";
    cin>>Nmin>>Nmax>>Nstep;
    return 0;
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

    int K,Nmin,Nmax,Nstep;
    double T;
    vector<int> M;

    enter(K,M,T,Nmin,Nmax,Nstep);
    M.resize(K);

    cout<<"#"<<'\t'<<"Average"<<'\t'<<"Mediana"<<'\t'<<"|Aver-Med|"<<'\t';

    for (int N=Nmin;N<=Nmax;N+=Nstep){
    //заполенение массива показаний с датчиков
    vector<vector<double>> X(K);

    for (size_t j = 0; j < N; j++)
    {
        for (size_t i = 0; i < K; i++)
        {
            X[i].push_back(plant_measure(M[i], plant));
        }
        Sleep(T*1000);

    }
    //упорядочивание измерений, формированиме массива Z
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
    cout<<'\n';
    double diff = fabs(Aver[0]-Med[0]);
    cout<<N<<'\t'<<Aver[0]<<'\t'<<Med[0]<<'\t'<<diff<<'\t';

    }
    return 0;
}
