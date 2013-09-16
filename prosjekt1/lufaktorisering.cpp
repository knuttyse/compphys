#include <iostream>
#include <armadillo>
#include "time.h"

using namespace std;
using namespace arma;
int main(){

    double n=100;//antall punkter
    double h=1/(n+1);//steglengde
    //lager tridiagonal matrise:
    mat A= mat(n,n);
    A(0,0)= 2;
    for (int i=1; i<n ; i++){
        A(i,i-1)=-1;// a_i=-1
        A(i,i)= 2; //  b_i=2
        A(i-1,i)=-1;// c_i=-1
    }

    mat L, U, P;
    clock_t start, finish;
    start = clock();//starter å måle tid
    lu(L, U, P, A); // LU-faktoriserer den tri-diagonale matrisen
    vec x =zeros(n); // variabelen x
    vec v =zeros(n); // vektor med kjent verdi: Ax=v
    vec u= zeros(n); // eksakt loesning
    vec y = zeros(n);// Ly=v
    vec z = zeros(n);// Uz=y
    //genererer verdier for noen av de tomme arrayene over 
    for (int i=0;i<n;i++){
         x(i)=(i+1)*h;
         v(i)=100.0*exp(-10.0*x(i))*h*h;
         u(i)=1.0-(1.0-exp(-10.0))*x(i)-exp(-10.0*x(i));
    }
    //finn y:
    for (int i=0;i<n;i++){
        y(i)=v(i);
        for (int j=0;j<i;j++){
            y(i)-=L(i,j)*y(j);
        }
    }
    //finn z:
    for (int i=n-1;i>-1;i--){
        z(i)=y(i);
        for (int j=n-1;j>i-1;j--){
            z(i)-=U(i,j)*z(j);
        }
        z(i)/=U(i,i);
    }
    //Da har vi funnet løsningen z(x)
    finish = clock();
    cout.precision(5);
    cout <<( (finish - start)/CLOCKS_PER_SEC)<<endl<<endl;
    //skriv ut
    ofstream myfile;
    myfile.open ("ludata.txt");
    for (int i=0;i<n;i++){
        myfile << x(i)<<' '<<u(i)<<' ' <<z(i)<<endl;
    }
    myfile.close();
    return 0;
}
