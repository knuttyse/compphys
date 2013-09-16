#include <iostream>
#include <cmath>
#include <armadillo>
#include "time.h"
using namespace std;
using namespace arma;


int main(){
    double n=100;//antall punkter
    double h=1/(n+1);//steglengde
    //deklarerer arrayer vi trenger
    vec a=zeros(n);
    vec b=zeros(n);
    vec c=zeros(n);
    vec v=zeros(n);//tilnerming
    vec u=zeros(n);//eksakt
    vec x=zeros(n);//variabel
    double k;

    //setter verdier inn i null-arrayene over:
    for (int i=0;i<n;i++){
         b(i)=2;
         c(i)=-1;// vi trenger vel strengt tatt ikke bruke vektorer her 
         a(i)=-1;// siden alle elementene er like og konstante

         x(i)=(i+1)*h;
         v(i)=100.0*exp(-10.0*x(i))*h*h;//v=f(x)*h^2
         u(i)=1.0-(1.0-exp(-10.0))*x(i)-exp(-10.0*x(i));
    }
    clock_t start, finish;
    start = clock();
    //foroversubstitusjon
    for (int i=1;i<n;i++){
        k=-a(i)/b(i-1);
        v(i)+=k*v(i-1);
        b(i)+=k*c(i-1);
    }
    //bakoversubstitusjon
    v(n-1)/=b(n-1);
    for (int i=n-2;i>=0;i--){
        v(i)-=c(i)/b(i+1)*v(i+1);
    }
    finish = clock();
    cout.precision(5);
    cout <<( (finish - start)/CLOCKS_PER_SEC)<<endl<<endl;
    //epsilon er log(relativ feil) i v sammenlignet med u
    vec epsilon =zeros(n);
    double epsilonmax=-1;// feilen bør være mer positiv enn dette tallet
    //loop for å finne epsilon for alle i. If test for å finne den største feilen.
    for (int i=0;i<n;i++){
        epsilon(i)= log10( abs( ( v(i) - u(i) )/u(i) ) );
        if (epsilon(i)>epsilonmax){
            epsilonmax=epsilon(i);
            }
    }


    ofstream myfile;
    myfile.open ("../../data/prosjekt1data.txt");
    for (int i=0;i<n;i++){
        myfile << x(i)<<' '<<u(i)<<' ' <<v(i)<<endl;
    }
    myfile.close();
    cout<<epsilonmax;
    return 0;
}
