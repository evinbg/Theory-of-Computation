#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> readFile();
void longestIncreasingSubsequence(std::vector<int> seq);

int main() {

	std::vector<int> arr = readFile();
	std::cout << "Sequence: ";
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	longestIncreasingSubsequence(arr);

	return 0;
}

std::vector<int> readFile() {
	std::ifstream in_stream;
	in_stream.open("incseq.txt");

	if (in_stream.fail()) {
		std::cout << "\"incseq.txt\" not found";
		exit(1);
	}

	std::vector<int> arr;

	int number;
	while (in_stream >> number) {
		arr.push_back(number);
	}

	in_stream.close();

	return arr;
}

void longestIncreasingSubsequence(std::vector<int> seq) {
	int seq_len = seq.size();
	std::vector<int> L(seq_len, 1); // creating a vector of length of seq filled with all 1's

	for (int i = 1; i < seq_len; i++) { // iterating through the vectors starting at the second element
		for (int j = 0; j < i; j++) { // iterating through all elements up to i
			if (seq[i] > seq[j] && L[i] < L[j] + 1) { // if the value is increasing and has not yet been accounted for
				L[i] = L[j] + 1; // increase the length of the subsequence
			}
		}
	}

	// iterating through L to find the length of LIS
	int longest = 0;
	for (int k = 0; k < seq_len; k++) {
		if (L[k] > longest) {
			longest = L[k];
		}
	}

	// iterating through L and seq to find the LIS
	std::vector<int> S(longest, INT_MAX); // used to hold the LIS
	int current_longest = longest; // keep track of  what number we should be looking for in L
	int d = longest - 1; // keep track of  where to insert the number in S
	for (int l = seq_len - 1; l >= 0; l--) { // iterate through L backwards
		if (l == seq_len - 1) { // if the last number of LIS is at the end of the sequence
			if (L[l] == current_longest) {
				S[d] = seq[l]; // add the number to S
				d--;
				current_longest--;
			}
		}
		else { // if the last number of LIS is not at the end of the sequence
			if (d == longest - 1) { // for the largest (last) number in the LIS
				if (L[l] == current_longest && seq[l] < S[d]) { // if L[l] is the number we are looking for and seq[l] is less than the current number in S[d]
					S[d] = seq[l]; // add the number to the vector
					d--;
					current_longest--;
				}
			}
			else { // for all the other numbers in the LIS
				if (L[l] == current_longest && seq[l] < S[d + 1]) { // if L[l] is the number we are looking for and seq[l] is less than the current number in S[d + 1]
					S[d] = seq[l]; // add the number to the vector
					d--;
					current_longest--;
				}
			}
		}
		if (current_longest == 0) {
			break;
		}
	}

	// print the LIS
	std::cout << "LIS Length: " << longest << std::endl;
	std::cout << "LIS: ";
	for (int m = 0; m < longest; m++) {
		std::cout << S[m] << " ";
	}
}