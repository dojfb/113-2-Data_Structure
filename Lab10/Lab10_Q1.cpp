#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
const int EMPTY = NULL; // 用 NULL 代表沒有節點
class TreeNode {
public:
    int value;// 節點值
    TreeNode* left;// 左子節點
    TreeNode* right;// 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//初始化節點
};

class BinaryTree {
public:
    TreeNode* root;// 樹根節點

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) {// 建立樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q;//建立queue儲存待處理的節點指標
        root = new TreeNode(arr[0]);// 建立根節點 (陣列第一個元素)
        q.push(&root);// 將根節點的指標加入queue

        size_t i = 1;// 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]);// 添加左子節點
                    q.push(&((*nodePtr)->left));// 將左子節點的指標加入queue
                }
                i++;
            }
            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]);// 添加右子節點
                    q.push(&((*nodePtr)->right));// 將右子節點的指標加入queue
                }
                i++;
            }
        }
        return root;
    }

    void Depth_first_search(TreeNode* node) {//深度優先搜尋
        if (node == nullptr) return;
        cout << node->value << " ";// 訪問當前節點的值
        Depth_first_search(node->left);// 遞迴遍歷左子樹
        Depth_first_search(node->right);// 遞迴遍歷右子樹
    }

    void Breadth_first_search(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right);// 將左子節點的指標加入queue
        }
    }
   
    //該函數加總指定層的節點值，若指定層數超過樹高印出警告
    void level_sum(TreeNode* root) {
        //若傳入空指標不做事
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue
        //level儲存當前層數
        int level = 0;
        //levelsize儲存當前層中的節點數
        int levelsize;
        //levelsum儲存指定層的和
        int levelsum = 0;
        //讓使用者輸入欲檢查的層
        int layer;
        cout << "請輸入要查詢層數(從0開始): ";
        cin >> layer;

        //當下一層還有節點繼續做
        while (!q.empty()) {
            //把當前層節點數存到levelsize
            levelsize = q.size();
            //遍歷該層將下一層的節點存入q
            for(int i=0; i<levelsize; ++i) {
                TreeNode* current = q.front();// 取出queue的第一個節點指標
                q.pop();// 將該節點從queue中刪除
                //若層數達到指定層將節點值加總到levelsum 
                if (level == layer) {
                    levelsum += current->value;
                }
                if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
                if (current->right) q.push(current->right);// 將左子節點的指標加入queue
            }
            //處理完一層後層數加一
            level++;
        }
        //若輸入層數高於計算的層數印出警告
        if (layer > level-1) cout << "超過樹高" << endl;
        //不然印出輸入層節點值和
        else cout << "第" << layer << "層的總和: " << levelsum << endl;
    }

};

int main() {
    int layer;
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, NULL, NULL, 8, 9, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    //cout << "DFS Result: ";
    //tree.Depth_first_search(tree.root);
    //cout << endl;

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;

    tree.level_sum(tree.root);

    system("pause");
    return 0;
}
