#include <fftw3.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include "grid_3d_class.h"


void fourier_first( int L1, int L2, int L3, double* rau_r,fftw_complex* rau_k )
{
int N;
N=L1*L2*L3;
//fftw_complex *rau_k ;
//rau_k = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
fftw_plan p;
p= fftw_plan_dft_r2c_3d(L1,L2,L3,rau_r,rau_k,FFTW_ESTIMATE);
fftw_execute(p);
fftw_destroy_plan(p);
rau_k[0][0] = 0  ;
rau_k[0][1] = 0  ;
for (int i=1;i<N;i++){
 rau_k[i][0] = rau_k[i][0]/2/M_PI ;
 rau_k[i][1] = rau_k[i][1]/2/M_PI ;
 
}
//return rau_k ;
}

void fourier_second( int L1,int L2, int L3, fftw_complex* fai_k, double* fai_r)
{
int N;
N=L1*L2*L3;
//double* fai_r = new double [N];
fftw_plan p;
p=fftw_plan_dft_c2r_3d(L1,L2,L3,fai_k,fai_r,FFTW_ESTIMATE);
fftw_execute(p);
fftw_destroy_plan(p);
for (int i=0;i<N;i++)
  fai_r[i] = fai_r[i]/N ;
//return fai_r ;
}

int poisson_kspace_solver(double* rau_r,double* fai_r,phf::coulomb_grid::grid_3d *p_grid3d)
{
int L1,L2,L3;
L1=p_grid3d->num_x;
L2=p_grid3d->num_y;
L3=p_grid3d->num_z;
int N;
N=L1*L2*L3;
//double* rau_r = new double [N];
//double* fai_r;
//double* fai_r = new double [N];
//for (int i=0;i<N;i++)
//    rau_r[i]=sin(2*M_PI*0.2*i);
fftw_complex *fai_k;
fai_k = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
fourier_first( L1, L2, L3, rau_r,fai_k );
fourier_second( L1, L2, L3, fai_k,fai_r);
fftw_free(fai_k) ;
/*for (int i=0;i<N;i++)
{
std::cout << i <<"\t"<< rau_r[i]<<"\t"<<fai_r[i] <<std::endl;
}*/
//delete [] rau_r ;
//delete [] fai_r ;

return 0 ;
}
