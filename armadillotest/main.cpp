#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;
int main(int argc, char** argv)
{
    int n=5;
    mat A = mat(2,2);
    A(0,0)=1;
    A(1,0)=2;
    A(0,1)=3;
    A(1,1)=4;
    cout << A<<endl;

    mat L, U, P;
    lu(L, U, P, A);
    mat B = P.t()*L*U;
    cout << B;
#if 0
    double x = A(1,2);

    mat B = A + A;
    mat C = A * B;
    mat D = A % B;

    cx_mat X(A,B);

    B.zeros();
    B.set_size(10,10);
    B.zeros(5,6);

    //
    // fixed size matrices:

    mat::fixed<5,6> F;
    F.ones();

    mat44 G;
    G.randn();

    cout << mat22().randu() << endl;

    //
    // constructing matrices from
    // auxiliary (external) memory:

    double aux_mem[24];
    mat H(aux_mem, 4, 6, false);
# endif
#if 0

    mat A = randu<mat>(5,5);
    //n=length(A);
    vec a =zeros<vec>;
    vec c =zeros<vec>;
    for (i=2;i<=n;i++){
    a[i]=-1;
    c[i]=-1;
    }
#endif
    vec btilde=zeros(n);// antar at armatillo gir Matlab-indeksering
#if 0
    for (int i=1; i<=n; i++)
    {
        a[i]=0;
        btilde[i]=b[i]-a[i]/b[i]*b[2];
        f[i]=
        c[]
    }
    for (i=n;i>0; i--){
        c[i]=
    }
#endif
    return 0;
    }
