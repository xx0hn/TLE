#include <iostream>
#include <vector>
using namespace std;

void preorder(vector<int>& inorder, vector<int>& postorder, int in_left, int in_right, int post_left, int post_right)

{
	if(post_left<=post_right)
	{
		int root,inorder_root_index,left_subtree_node_cnt, right_subtree_node_cnt;
		root=postorder[post_right];
		cout<<root<<" ";
		for(inorder_root_index=in_left;inorder[inorder_root_index]!=root;inorder_root_index++);
		left_subtree_node_cnt=inorder_root_index-in_left;
		preorder(inorder,postorder,in_left, in_left+left_subtree_node_cnt-1, post_left, post_left+left_subtree_node_cnt-1);
		preorder(inorder, postorder, inorder_root_index+1, in_right, post_left+left_subtree_node_cnt, post_right-1);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	vector<int> inorder, postorder;
	int n;
	cin>>n;
	inorder.resize(n);
	postorder.resize(n);
	for(int i=0;i<n;i++)
	{
		cin>>inorder[i];
	}
	for(int i=0;i<n;i++)
	{
		cin>>postorder[i];
	}
	preorder(inorder,postorder,0,n-1,0,n-1);
	return 0;
}