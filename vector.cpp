#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;
int crossover_pt = 2; 
int dim; 

// Print matrix
void print (vector< vector<int> > C, int dim) {
    cout << "Matrix:" << endl;
	for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << " " << C[i][j];
        }
        cout << endl;
    }
}

// Print matrix diagonal
void print_d (vector< vector<int> > C, int dim) {
    cout << "Diagonal:" << endl;
	for (int i = 0; i < dim; i++) {
		cout << C[i][i] << "\n";
	}
}

// Multiply 2 matrices regularly
void multiply (vector< vector<int> > &A, vector< vector<int> > &B, 
               vector< vector<int> > &C, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            C[i][j] = 0;
            for (int k = 0; k < dim; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Add 2 matrices
void sum (vector< vector<int> > &A, vector< vector<int> > &B, 
          vector< vector<int> > &C, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            C[i][j] = 0;
            C[i][j] += A[i][j] + B[i][j];
        }
    }
}

// Subtract 2 matrices
void subtract (vector< vector<int> > &A, vector< vector<int> > &B, 
               vector< vector<int> > &C, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            C[i][j] = 0;
            C[i][j] += A[i][j] - B[i][j];
        }
    }
}

// Strassen function
void strassen (vector< vector<int> > &A, vector< vector<int> > &B, 
               vector< vector<int> > &C, int dim) {

    // Check if dim is odd, if so pad with zeros
	if (dim%2 != 0) {
        dim = dim+1;
		A.resize(dim);
		B.resize(dim);
		C.resize(dim);
		// pad inner vector as well
		for (int i = 0; i < dim; i++) {
			A[i].resize(dim);
			B[i].resize(dim);
			C[i].resize(dim);
		}
    }

    if (dim <= crossover_pt) {
		multiply (A, B, C, dim);
		return;
	}
	else {

        // Debugging Print
        // cout << "Entered Strassen's" << endl;

        // Resize dim for submatrices
        int sub_dim = dim/2;

        // Create submatrices
        vector <int> content (sub_dim);
        vector< vector <int> > A11 (sub_dim, content), 
                            A12 (sub_dim, content),
                            A21 (sub_dim, content),
                            A22 (sub_dim, content),
                            B11 (sub_dim, content),
                            B12 (sub_dim, content),
                            B21 (sub_dim, content),
                            B22 (sub_dim, content),
                            C11 (sub_dim, content),
                            C12 (sub_dim, content),
                            C21 (sub_dim, content),
                            C22 (sub_dim, content),
                            P1 (sub_dim, content),
                            P2 (sub_dim, content),
                            P3 (sub_dim, content),
                            P4 (sub_dim, content),
                            P5 (sub_dim, content),
                            P6 (sub_dim, content),
                            P7 (sub_dim, content),
                            temp1 (sub_dim, content),
                            temp2 (sub_dim, content);
        

        // Split submatrices
        for (int i = 0; i < sub_dim; i++) {
            for (int j = 0; j < sub_dim; j++) {
                A11[i][j] = A[i][j];
                B11[i][j] = B[i][j];

                A12[i][j] = A[i][j+sub_dim];
                B12[i][j] = B[i][j+ sub_dim];
                
                A21[i][j] = A[i+sub_dim][j];
                B21[i][j] = B[i+sub_dim][j];

                A22[i][j] = A[i+sub_dim][j+sub_dim];
                B22[i][j] = B[i+sub_dim][j+sub_dim];
            }
        }

        // Debugging Prints
        // print (A11, sub_dim);
        // print (A12, sub_dim);
        // print (A21, sub_dim);
        // print (A22, sub_dim);

        // print (B11, sub_dim);
        // print (B12, sub_dim);
        // print (B21, sub_dim);
        // print (B22, sub_dim);

        // --------------------------
        // Calculate all P values
        // --------------------------
        // P1 = A11 (B12 - B22)
        subtract (B12, B22, temp1, sub_dim);
        strassen (A11, temp1, P1, sub_dim);
        
        // P2 = (A11 + A12) B22
        sum (A11, A12, temp1, sub_dim);
        strassen (temp1, B22, P2, sub_dim);

        // P3 = (A21 + A22) B11
        sum (A21, A22, temp1, sub_dim);
        strassen (temp1, B11, P3, sub_dim);

        // P4 = A22 (B21 - B11)
        subtract (B21, B11, temp1, sub_dim);
        strassen (A22, temp1, P4, sub_dim);

        // P5 = (A11 + A22)(B11 + B22)
        sum (A11, A22, temp1, sub_dim);
        sum (B11, B22, temp2, sub_dim);
        strassen (temp1, temp2, P5, sub_dim);

        // P6 = (A12 - A22)(B21 + B22)
        subtract (A12, A22, temp1, sub_dim);
        sum (B21, B22, temp2, sub_dim);
        strassen (temp1, temp2, P6, sub_dim);

        // P7 = (A11 - A21)(B11 + B12)
        subtract (A11, A21, temp1, sub_dim);
        sum (B11, B12, temp2, sub_dim);
        strassen (temp1, temp2, P7, sub_dim);

        // --------------------------
        // Calculate all C values
        // --------------------------
        // C11 = P5 + P4 - P2 + P6
        sum (P5, P4, temp1, sub_dim);
        subtract (temp1, P2, temp2, sub_dim);
        sum (temp2, P6, C11, sub_dim);

        // C12 = P1 + P2
        sum (P1, P2, C12, sub_dim);

        // C21 = P3 + P4
        sum (P3, P4, C21, sub_dim);

        // C22 = P5 + P1 - P3 - P7
        sum (P5, P1, temp1, sub_dim);
        subtract (temp1, P3, temp2, sub_dim);
        subtract (temp2, P7, C22, sub_dim);

        // Insert all computed values into the final matrix
        for (int i = 0; i < sub_dim ; i++) {
            for (int j = 0 ; j < sub_dim ; j++) {
                C[i][j] = C11[i][j];
                C[i][j+sub_dim] = C12[i][j];
                C[i+sub_dim][j] = C21[i][j];
                C[i+sub_dim][j+sub_dim] = C22[i][j];
            }
        }
    }  
}


int main (int argc, char *argv[])
{
    // Matrix dimensions
    int dim = atoi(argv[2]);
    // cout << dim << "\n";

	// Line size of the input file
	int file_size = 2*dim*dim;

    // Vector for content of the matrices
	vector<int> content (dim);

    // Initialize 3 matrices
	vector< vector<int> > A (dim, content),
                          B (dim, content),
	                      C (dim, content);

	// Read input file
	std::ifstream infile(argv[3]);

	// Each line in the file is a string
	string line;

	// Iterate over files lines to construct A and B
	for (int i = 0, j = 0; i < file_size; i++) {
		getline (infile, line);
		if (i < (dim*dim)) {
			A[i/dim][i%dim] = stoi(line);
		}
		else {
			B[j/dim][i%dim] = stoi(line);
			j++;
		}
	}

    print (A, dim);
    print (B, dim);
    multiply (A,B,C,dim);
    print (C, dim);

    // Run Strassen's Algorithm
    strassen (A,B,C,dim);

    // Print the resulting matrix
    print (C, dim);

    // Print the diagonal of the resulting matrix
    print_d (C, dim);

   	return 0;
}
