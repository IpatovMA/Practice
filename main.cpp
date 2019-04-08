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

void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg width='" << width << "' height='" << height << "' "
         << "viewBox='0 0 " << width << " " << height << "' "
         << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout<< "<text x= \" "<<left<<" \" y=\" " <<baseline<<" \">"<<text<<"</text>";
}

void
svg_rect(double x, double y, double width, double height, string stroke="#4F4F4F", string fill = "#636363")
{
    cout<< "<rect x= \" "<<x<<" \" y=\" " <<y
        <<" \" width = \" "<<width<<" \" height=\" " <<height
        <<" \" fill='"<<fill<<"' stroke='"<<stroke<<"'/>";
}

void
svg_line(double x1,double y1,double x2, double y2, string stroke="#4F4F4F")
{
    cout<< "<line x1= '"<<x1<<"' y1='"<<y1
        << "void<line x2= '"<<x2<<"' y2='"<<y2
        <<"' stroke='"<<stroke<<"'/>";
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

    int IMG_WIDTH = 800;
    int IMG_HEIGHT=400;
    svg_begin(IMG_WIDTH,IMG_HEIGHT);

 //   cout<<"#"<<'\t'<<"Average"<<'\t'<<"Mediana"<<'\t'<<"|Aver-Med|"<<'\t';

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
   // cout<<N<<'\t'<<Aver[0]<<'\t'<<Med[0]<<'\t'<<diff<<'\t';



    }
    svg_end();
    return 0;
}
