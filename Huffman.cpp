#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>

class Node { // class for the nodes that create the huffman tree
public:
	int ascii;
	int freq;
	Node* left;
	Node* right;

	Node(int ascii, int freq) {
		this->ascii = ascii;
		this->freq = freq;
		left = nullptr;
		right = nullptr;
	}
};

class Compare { // custom comparator for the priority queue
public:
	bool operator()(Node* left, Node* right) {
		return left->freq > right->freq;
	}
};

void readFile(std::priority_queue<Node*, std::vector<Node*>, Compare>& q);
void buildHuffmanTree(std::priority_queue<Node*, std::vector<Node*>, Compare>& q);
void generateHuffmanCode(Node* node, std::string str, std::map<int, std::string>& huffmanCode);
void outputToFile(std::map<int, std::string>& huffmanCode);

int main() {
	std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap; // minHeap for generating huffman tree
	std::map<int, std::string> huffmanCodeTable; // map to hold the huffman code table
	readFile(minHeap);
	buildHuffmanTree(minHeap);
	generateHuffmanCode(minHeap.top(), "", huffmanCodeTable);
	outputToFile(huffmanCodeTable);

	return 0;
}

void readFile(std::priority_queue<Node*, std::vector<Node*>, Compare>& q) {
	std::ifstream in_stream;
	in_stream.open("freq.txt");

	if (in_stream.fail()) {
		std::cout << "\"freq.txt\" not found";
		exit(1);
	}

	std::string line;
	while (getline(in_stream, line)) { // reading line by line
		std::istringstream line_as_stream{ line };
		std::string key;
		std::string value;
		std::getline(line_as_stream, key, ' '); // getting string before ' ' delimiter
		std::getline(line_as_stream, value); // getting string after ' ' delimiter

		if (key == "") { // if key is space
			value = value.substr(1, value.length() - 1); // remove space from before the number
			key = " ";
		}
		int int_value = stoi(value);

		char c;
		int ascii;
		if (key == "LF") { // setting ascii value of LF
			ascii = 10;
		}
		else { // any value other than LF
			c = key[0];
			ascii = int(c);
		}

		q.push(new Node(ascii, int_value)); // creating and adding node to priority queue
	}

	in_stream.close();
}

void buildHuffmanTree(std::priority_queue<Node*, std::vector<Node*>, Compare>& q) {
	while (q.size() != 1) {
		// retrieving the two nodes with smallest frequencies currently
		Node* left = q.top();
		q.pop(); // remove first smallest node

		Node* right = q.top();
		q.pop(); // remove second smallest node

		// create a new node with the frequencies of the two smallest nodes
		Node* combo = new Node(-1, left->freq + right->freq); // -1 value indicates a non-leaf node
		combo->left = left;
		combo->right = right;

		q.push(combo); // push the new node back into the minHeap
	}
}

void generateHuffmanCode(Node* node, std::string str, std::map<int, std::string>& huffmanCode) {
	if (node == nullptr) {
		return;
	}

	if (node->ascii != -1) { // if the node is not a non-leaf node, put the current string in the map for the ascii value
		huffmanCode[node->ascii] = str;
	}

	generateHuffmanCode(node->left, str + "0", huffmanCode); // recursively generate huffman code for the left subtree
	generateHuffmanCode(node->right, str + "1", huffmanCode); // recursively generate huffman code for the right subtree
}

void outputToFile(std::map<int, std::string>& huffmanCode) {
	std::ofstream outputFile("codetable.txt");
	for (auto const& x : huffmanCode) { // looping through huffmanCode map
		if (x.first == 10) { // if ascii value is 10 (LF)
			outputFile << "LF"
				<< ": "
				<< x.second
				<< std::endl;
		}
		else {
			outputFile << char(x.first)
				<< ": "
				<< x.second
				<< std::endl;
		}
	}
}