#include <string>
#include "Set.h"
#include "Map.h"

using namespace std;
struct TreeNode {
	int v;
	int weight;//ignore this field!!
	TreeNode* left;
	TreeNode* right;
};

void pathSum(TreeNode* root, int s, Set<TreeNode*> &nodes);