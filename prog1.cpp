#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int N=10;

void matrix(int **A, int **B){


	
	cout<<"----------Initial Matices-----------"<<endl;

	// print A
	#pragma omp parallel for
	cout<<"A ="<<endl;
	for(int i= 0; i < N; i++){
		for(int j = 0; j< N; j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	// print B
	#pragma omp parallel for
	cout<<"B ="<<endl;
	for(int i= 0; i < N; i++){
		for(int j = 0; j< N; j++){
			cout<<B[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;


	// multiply
	int R[N][N];
	#pragma omp parallel for
	for(int i =0; i<N;i++){
		for(int j=0; j<N;j++){
			R[i][j] = 0;
			for (int k = 0; k< N; k++){
				R[i][j] += A[i][k]*B[k][j]; 
			}
		}
	}


	
	// result
	
	cout<<"A X B ="<<endl;
	#pragma omp parallel for
	for(int i= 0; i < N; i++){
		for(int j = 0; j< N; j++){
			cout<<R[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	
};




int main(){
	

	int **A, **B;
	A = new int*[N];
	for(int i = 0; i < N; i++){
		A[i] = new int[N];
	}

	B = new int*[N];
	for(int i = 0; i < N; i++){
		B[i] = new int[N];
		
	}

	//random values
	srand(time(0));
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			A[i][j] = rand() % 10;
		}
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			B[i][j] = rand() % 10;
		}
	}
	

	matrix(A, B);
	
	return 0;
}
