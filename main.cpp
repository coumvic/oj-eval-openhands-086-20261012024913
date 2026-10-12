#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Function to assign depths to all nodes using BFS
    void assignDepths(vector<TreeNode*>& nodes, vector<int>& depths, int n) {
        depths.assign(n + 1, 0);
        queue<int> q;
        q.push(1); // root is node 1
        depths[1] = 1;
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            // Add children to queue if they exist
            if (nodes[curr]->left != nullptr) {
                int leftChild = nodes[curr]->left->val;
                depths[leftChild] = depths[curr] + 1;
                q.push(leftChild);
            }
            if (nodes[curr]->right != nullptr) {
                int rightChild = nodes[curr]->right->val;
                depths[rightChild] = depths[curr] + 1;
                q.push(rightChild);
            }
        }
    }
    
    // Function to perform swap operation on nodes at depth that is multiple of k
    void swapNodes(vector<TreeNode*>& nodes, vector<int>& depths, int n, int k) {
        // Find all nodes at depths that are multiples of k
        for (int i = 1; i <= n; i++) {
            if (depths[i] % k == 0) {
                // Swap left and right children
                swap(nodes[i]->left, nodes[i]->right);
            }
        }
    }
    
    // Function to get inorder traversal of the tree
    void inorderTraversal(TreeNode* root, vector<int>& result) {
        if (root == nullptr) return;
        inorderTraversal(root->left, result);
        result.push_back(root->val);
        inorderTraversal(root->right, result);
    }
};

int main() {
    int n;
    cin >> n;
    
    // Create nodes
    vector<TreeNode*> nodes(n + 1);
    for (int i = 1; i <= n; i++) {
        nodes[i] = new TreeNode(i);
    }
    
    // Read children information
    for (int i = 1; i <= n; i++) {
        int left, right;
        cin >> left >> right;
        if (left != -1) {
            nodes[i]->left = nodes[left];
        }
        if (right != -1) {
            nodes[i]->right = nodes[right];
        }
    }
    
    int t;
    cin >> t;
    
    Solution solution;
    vector<int> depths;
    
    // Assign initial depths
    solution.assignDepths(nodes, depths, n);
    
    // Process each query
    for (int i = 0; i < t; i++) {
        int k;
        cin >> k;
        
        // Perform swap operation
        solution.swapNodes(nodes, depths, n, k);
        
        // Get and print inorder traversal
        vector<int> result;
        solution.inorderTraversal(nodes[1], result);
        
        for (int val : result) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // Clean up memory
    for (int i = 1; i <= n; i++) {
        delete nodes[i];
    }
    
    return 0;
}