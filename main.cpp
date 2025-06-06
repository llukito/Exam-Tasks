#include <iostream>
#include <string>
#include "simpio.h"
#include "foreach.h"
#include "console.h"
#include <time.h>
#include "circle.h"
#include "random.h"
#include "pathSum.h"


using namespace std;

void printTestResults(bool passed, int testNum, int& passedCounter) {
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	}
	else {
		cout << "test " << testNum << " failed" << endl;
	}
}

bool equalsCircle(string s, Circle *c) {
	if (s.length() != c->length()) {
		return false;
	}
	for (int i=0; i<c->length(); i++) {
		if (s[i]-'0' != c->get(i)) {
			return false;
		}
	}
	return true;
}

Circle* initCircle(string s) {
	Circle *c = new Circle;
	for (int i=0; i<s.length(); i++) {
		c->insert(i, s[i]-'0');
	}
	return c;
}

const int CircleTestsNum = 16;
const int PathSumTestsNum = 10;

bool runCircleSingleTest(int testNum) {
	bool passed = false;
	Circle *c = new Circle;
	Circle* tmp;
	switch (testNum) {
	case 1:
		passed = c->length() == 0;
		break;
	case 2:
		c->insert(0, 3);
		passed = c->length() == 1 && c->get(0) == 3 && c->get(5) == 3;
		break;
	case 3:
		c->insert(0, 2);
		c->insert(0, 1);
		c->insert(2, 3);
		passed = c->length() == 3 && equalsCircle("123", c) &&
				c->get(4) == 2 && c->get(8) == 3 && c->get(12) == 1;
				break;
	case 4:
		c->insert(0, 2);
		c->insert(0, 1);
		c->insert(2, 3);
		c->insert(1, 1);
		c->insert(2, 2);
		passed = c->length() == 5 && equalsCircle("11223", c) && 
			c->get(27) == c->get(47) && c->get(27) == 2;
			break;
	case 5:
		c->insert(0, 2);
		c->insert(0, 1);
		c->insert(2, 3);
		c->insert(1, 3);
		c->insert(2, 4);
		c->set(0, 9);
		passed = c->length() == 5 && equalsCircle("93423", c);
		break;
	case 6:
		c->insert(0, 1);
		c->insert(1, 3);
		c->insert(1, 3);
		c->insert(2, 4);
		c->set(c->length(), 9);
		c->set(7, 9);

		passed = c->length() == 4 && equalsCircle("9349", c);
		break;
	case 7:
		c->insert(0, 1);
		c->insert(1, 3);
		c->insert(1, 3);
		c->insert(2, 4);
		c->set(8, 9);
		c->insert(0, 1);
		c->set(19, 9);
		c->insert(c->length(), 8);
		passed = c->length() == 6 && equalsCircle("193498", c);
		break;
	case 8:
		c->insert(0, 1);
		tmp = c->subCircle(0, 1);
		c->set(0, 4);
		passed = equalsCircle("1", tmp) && equalsCircle("4", c);
		break;
	case 9:
		c->insert(0, 1);
		tmp = c->subCircle(0, 0);
		c->insert(1, 2);
		passed = equalsCircle("", tmp) && equalsCircle("12", c);
		break;
	case 10:
		c->insert(0, 1);
		c->insert(1, 2);
		c->insert(2, 3);
		c->insert(3, 4);
		c->insert(4, 5);
		c = c->subCircle(3, 5);
		passed = equalsCircle("45", c);
		break;
	case 11:
		c->insert(0, 1);
		c->insert(1, 2);
		c->insert(2, 3);
		c->insert(3, 4);
		c->insert(4, 5);
		c = c->subCircle(0, c->length());
		passed = equalsCircle("12345", c);
		break;
	case 12:
		c = initCircle("12345");
		c = c->subCircle(0, c->length());
		passed = equalsCircle("12345", c);
		break;
	case 13:
		c = initCircle("12345");
		passed = c->contains(initCircle("123456")) == -1 && c->contains(initCircle("34")) == 2 && c->contains(initCircle("2345")) == 1;
		break;
	case 14:
		c = initCircle("12345");
		passed = c->contains(initCircle("12345")) == 0 && c->contains(initCircle("01234")) == -1;
		break;
	case 15:
		c = initCircle("12345");
		passed = c->contains(initCircle("45")) == 3 && c->contains(initCircle("23")) == 1;
		break;
	case 16:
		c = initCircle("1");
		passed = c->contains(initCircle("1233")) == -1 && c->contains(initCircle("1")) == 0;
		break;
	}
	return passed;
}

void clearWeights(TreeNode * root) {
	if (root == NULL) {
		return;
	}
	root->weight = 0;
	clearWeights(root->left);
	clearWeights(root->right);
}

TreeNode* insertNode(TreeNode * &root, int value, int weight) {
	if (root == NULL) {
		root = new TreeNode;
		root->v = value;
		root->weight = weight;
		root->left = NULL;
		root->right = NULL;
		return root;
	}

	if (root->weight < weight) {
		return insertNode(root->right, value, weight);
	} else {
		return insertNode(root->left, value, weight);
	}
}

void readBinaryTree(TreeNode * &r, ifstream &input, int &k, Set<TreeNode*>&answ) {
	int n;
	input >> n >> k;
	int w, v;
	for (int i=0; i<n; i++) {
		input >> v >> w;
		TreeNode * node = insertNode(r, v, w);
		if (node->weight % 10 != 0) {
			answ += node;
		}
	}
}


bool runPathSumSingleTest(int testNum) {
	TreeNode *root = NULL;
	Set<TreeNode*> answ, res;
	
	string testFileName = string("pathsum\\test") + integerToString(testNum) + ".txt";
	ifstream input;
	input.open(testFileName.c_str());
	int k;
	readBinaryTree(root, input, k, answ);
	clearWeights(root);
	input.close();

	pathSum(root, k, res);

	return res == answ;
}


void runCircleAllTests() {
	cout << "### Run Circle tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum <= CircleTestsNum; testNum++) {
		bool passed = runCircleSingleTest(testNum);
		printTestResults(passed, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

void runPathSumAllTests() {
	cout << "### Run Path Sum tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum <= PathSumTestsNum; testNum++) {
		bool passed = runPathSumSingleTest(testNum);
		printTestResults(passed, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runCircleAllTests();
	//runPathSumAllTests();
	cout << "end" << endl;
	return 0;
}
