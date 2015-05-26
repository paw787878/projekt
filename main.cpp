#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;
double srednia (vector<double> v)
{
    double s=0;
    for(int i=0;i<v.size();i++)
        s+=v[i];
    s=(double)s/(double)v.size();
    return s;
}
double odchylenie (vector<double> v)
{
    double s=0;
    double sr=srednia(v);
    for(int i=0;i<v.size();i++)
        s+=(v[i]-sr)*(v[i]-sr);
        s=(double)s/(double)v.size();
        s=sqrt(s);
        return s;
}
class histogram
{
    double a,b;
    vector<int>bins;
public:
    histogram (double a,double b, int n, vector<double> dane); //od a do b n kubelkow,
    histogram (double o,int n, vector<double> dane); // o sigma od œredniej, n kubelkow
    int odczyt (int i); // odczytuje i ty kubelek
    void wyrzut (ostream& out); //wypisuje na output
};
void histogram::wyrzut (ostream& out)
{
    for(int i=0;i<bins.size();i++)
        out<<(double)a+(b-a)/(double)bins.size()*((double)i+0.5)<<" "<<bins[i]<<endl;
}

histogram::histogram (double o,int n, vector<double> dane)
{
    int k;
    a=srednia(dane)-o*odchylenie(dane);
    b=srednia(dane)+o*odchylenie(dane);
      for(int i=0;i<n;i++)
        bins.push_back(0);
    for(int i=0;i<dane.size();i++)
    {
        k=(int)((double)(((double)n*(dane[i]-a)/(b-a))));
       if(k<n&&k>=0)
        bins[k]++;
    }

}
int histogram::odczyt (int i)
{
    if(i>=0&&i<bins.size())
    return bins[i];
    else return -1;
}
histogram::histogram (double a,double b, int n, vector<double> dane): a(a), b(b)
{
    int k;
    for(int i=0;i<n;i++)
        bins.push_back(0);
    for(int i=0;i<dane.size();i++)
    {
    k=(int)(((double)((double)n*(dane[i]-a)/(b-a))));
       if(k<n&&k>=0)
        bins[k]++;
    }
}
class czytacz
{
    vector<vector<double> > vtekst;
    public:
    czytacz(string plik);
    int rozmiar();
    double komorka(int i, int j);
    vector<double> kolumna(int k);
};
vector<double> czytacz::kolumna(int k)
{
    vector<double> column;
    for(int i=0;i<vtekst.size();i++)
    column.push_back(vtekst[i][k]);
    return column;

}
double czytacz::komorka(int i, int j)
{
    return vtekst[i][j];
}
int czytacz::rozmiar()
{
    return vtekst.size();
}
czytacz::czytacz(string plik)
{
    string slinia;
    double liczba;
    ifstream we (plik);
    getline(we,slinia);
    getline(we,slinia);
    while(getline(we,slinia))
    {
        istringstream zrodlo(slinia);
        vector<double>vlinia;
        while(zrodlo>>liczba)
            vlinia.push_back(liczba);
        vtekst.push_back(vlinia);
    }
}

int main()
{
    czytacz dane("dane.txt");
    histogram wykres(3,100,dane.kolumna(2));
    ofstream wy("wynik.txt");
    wykres.wyrzut(wy);
    return 0;
}
