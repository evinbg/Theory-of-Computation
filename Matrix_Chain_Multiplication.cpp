#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

void matrixChainMultiplication(std::vector<int> M);
std::string parenthesizedOrdering(std::vector<std::vector<int>> K, int i, int j);
void printMatrix(std::vector<std::vector<int>> M, std::string s);

int main() {
	std::vector<int> sizes = { 24, 12, 19, 21, 7, 18, 16, 13 };

	matrixChainMultiplication(sizes);
	
	return 0;
}

void matrixChainMultiplication(std::vector<int> Matrix) {
	int dimension = Matrix.size() - 1;

	std::vector<std::vector<int>> M(dimension, std::vector<int>(dimension, 0));
	std::vector<std::vector<int>> K(dimension, std::vector<int>(dimension, 0));

	for (int d = 0; d < dimension; d++) {
		for (int i = 0; i < dimension - d - 1; i++) {
			int j = i + d + 1;
			M[i][j] = INT_MAX;
			for (int k = i; k < j; k++) {
				int cost = M[i][k] + M[k + 1][j] + Matrix[i] * Matrix[k + 1] * Matrix[j + 1];
				if (cost < M[i][j]) {
					M[i][j] = cost;
					K[i][j] = k + 1;
				}
			}
		}
	}

	printMatrix(M, "Matrix M:");
	std::cout << "Minimal Multiplications: " << M[0][dimension - 1] << std::endl << std::endl;

	printMatrix(K, "Matrix K:");
	std::string parenthesized = parenthesizedOrdering(K, 1, dimension);
	std::cout << "Parenthesized Ordering: " << parenthesized << std::endl;
}

std::string parenthesizedOrdering(std::vector<std::vector<int>> K, int i, int j) {
	if (i == j) {
		return ("A" + std::to_string(i));
	}
	else {
		int k = K[i - 1][j - 1];
		return ("(" + parenthesizedOrdering(K, i, k) + " X " + parenthesizedOrdering(K, k + 1, j) + ")");
	}

}

void printMatrix(std::vector<std::vector<int>> M, std::string s) {
	std::cout << s << std::endl;

	for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[i].size(); j++) {
			std::cout << std::setw(7) << M[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}