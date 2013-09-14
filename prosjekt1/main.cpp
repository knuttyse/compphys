#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;



int main(){
    double n=10;
    double h=1/(n+1);
    vec a=zeros(n);
    vec b=zeros(n);
    vec c=zeros(n);
    vec v=zeros(n);
    vec u=zeros(n);
    vec x=zeros(n);
    double k;
    for (int i=0;i<n;i++){
         b(i)=2;
         c(i)=-1;
         a(i)=-1;

         x(i)=(i+1)*h;
         v(i)=100.0*exp(-10.0*x(i))*h*h;
         u(i)=1.0-(1.0-exp(-10.0))*x(i)-exp(-10.0*x(i));
    }

    for (int i=1;i<n;i++){
        k=-a(i)/b(i-1);
        v(i)+=k*v(i-1);
        b(i)+=k*c(i-1);
    }

    v(n-1)/=b(n-1);
    for (int i=n-2;i>=0;i--){
        v(i)-=c(i)/b(i+1)*v(i+1);
    }
    vec epsilon =zeros(n);
    double epsilonmax=-1;
    for (int i=0;i<n;i++){
        epsilon(i)= log10(abs( (v(i)-u(i))/u(i)));
        if (epsilon(i)>epsilonmax){
            epsilonmax=epsilon(i);
            }
    }


    ofstream myfile;
    myfile.open ("prosjekt1u.txt");
    cout.precision(16);
    myfile << u;
    myfile.close();

    myfile.open ("prosjekt1v.txt");
    myfile << v;
    myfile.close();

    myfile.open ("prosjekt1x.txt");
    myfile << x;
    myfile.close();
    return 0;
}
