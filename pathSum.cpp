#include "pathSum.h"


using namespace std;


void fill(TreeNode* root, Set<TreeNode*>& nodes, int s) {
	if (!root)return;
	if (!root->left && !root->right && s - root->v == 0) {
		nodes.insert(root);
		return;
	}
	fill(root->left, nodes, s - root->v);
	fill(root->right, nodes, s - root->v);
}

void pathSum(TreeNode* root, int s, Set<TreeNode*>& nodes) {
	fill(root, nodes, s);
}