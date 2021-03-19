#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (int argc, char *argv[]) {

    int dim = atoi(argv[2]);
    cout << dim << "\n";

    int A[dim][dim];
    int B[dim][dim];
    int C[dim][dim];

    int count = 0;
    std::ifstream file("input.txt");
    std::string str;
    while (std::getline(file, str)) {
        // Print out line
        //std::cout << str << "\n";

        if (count < dim * dim) {
            A[count / dim][count % dim] = stoi(str);
        }

        else {
            B[(count - dim * dim) / dim][(count - dim * dim) % dim] = stoi(str);
        }

        count += 1;

         // std::cout << std::stoi(str) << "\n";
    }

    cout << "Printing Matrix A" << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Printing Matrix B" << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    // Multiply 2 matrices regularly
    int i, j, k;
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                C[i][j]=0;
                for (k = 0; k < dim; k++)
                    C[i][j] += A[i][k] * B[k][j];
            }
        }

    // Output regular product
    cout << endl << "Output Matrix: " << endl;
    for(i = 0; i < dim; ++i)
        for(j = 0; j < dim; ++j)
        {
            cout << " " << C[i][j];
            if(j == dim-1)
                cout << endl;
        }

    return 0;
}




// function to subtract 2 matrices

// function to split matrices

// function to join matrices
