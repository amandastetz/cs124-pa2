#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (int argc, char *argv[]) {

    int dim = atoi(argv[2]);
    cout << dim << "\n";

    int A[dim][dim];
    int B[dim][dim];

    int count = 0;
    std::ifstream file("input.txt");
    std::string str;
    while (std::getline(file, str)) {
        // Print out line
        //std::cout << str << "\n";

        if (count < dim * dim) {
            A[count / dim][count % dim] = stoi(str);
        }

        count += 1;

         // std::cout << std::stoi(str) << "\n";
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

// function to multiply 2 matrices

// function to add 2 matrices

// function to subtract 2 matrices

// function to split matrices

// function to join matrices
