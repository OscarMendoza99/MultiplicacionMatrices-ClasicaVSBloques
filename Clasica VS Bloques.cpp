#include <iostream>
#include <vector>
#include <chrono>

#define SIZE 600

using namespace std;

std::chrono::time_point<std::chrono::high_resolution_clock> inicio, fin;
int64_t duracion;

vector<vector<int> > A(SIZE,vector<int>(SIZE,0));
vector<vector<int> > B(SIZE,vector<int>(SIZE,0));
vector<vector<int> > C(SIZE,vector<int>(SIZE,0));

void llenarMatriz(){
	double a = 0, b = 0;
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			a = (double)rand() / RAND_MAX;
			A[i][j] = 0 + a * (10);
			for(int k = 0; k < SIZE; k++){
				b = (double)rand() / RAND_MAX;
				B[j][k] = 0 + b * (10);
				C[i][k] = 0;
			}
		}
	}
}

void limpiarC(){
	for(int i = 0; i < SIZE; i++){
		for(int k = 0; k < SIZE; k++){
			C[i][k] = 0;
		}
	}
}
	
void multiClasica(){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			for(int k = 0; k < SIZE; k++){
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}
	
void multiBlock(){
	int b = SIZE / 2;
	for(int ii = 0; ii < SIZE; ii += b){
		for(int jj = 0; jj < SIZE; jj += b){
			for(int kk = 0; kk < SIZE; kk += b){
				for(int i = ii; i < ii + b; i++){
					for(int j = jj; j < jj + b; j++){
						for(int k = kk; k < kk + b; k++){
							C[i][j] += A[i][k] * B[k][j];
						}
					}
				}
			}
		}
	}
}
	
void printAB(){
	//Print A
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			cout << A[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	//Print B
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			cout << B[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
	
void printC(){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	double a = 0, b = 0;
	llenarMatriz();
	//printAB();
	
	//Multiplicacion Clasica
	inicio = std::chrono::high_resolution_clock::now();
	multiClasica();
	fin = std::chrono::high_resolution_clock::now();
	duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio) .count();
	std::cout << "Execution Time (Classic Multiplication): " << duracion << endl;
	
	//printC();
	limpiarC();
	
	//Multiplicacion por bloques
	inicio = std::chrono::high_resolution_clock::now();
	multiBlock();
	fin = std::chrono::high_resolution_clock::now();
	duracion = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio) .count();
	std::cout << "Execution Time (Block Multiplication): " << duracion << endl;
	
	//printC();
	return 0;
}

