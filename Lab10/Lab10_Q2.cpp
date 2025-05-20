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

    //該方法回傳以傳入節點為根的樹的節點值和
    int sumtree(TreeNode* root) {
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue
        //levelsize儲存每層節點數
        int levelsize;
        //sum儲存節點總和
        int sum = 0;

        //如果還有子節點則繼續做
        while (!q.empty()) {
            //把當前層中的結點數給到levelsize
            levelsize = q.size();
            //遍歷該層並加總到sum
            for(int i=0; i<levelsize; ++i) {
                TreeNode* current = q.front();// 取出queue的第一個節點指標
                q.pop();// 將該節點從queue中刪除
                sum += current->value;
                if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
                if (current->right) q.push(current->right);// 將左子節點的指標加入queue
            }
        }
        return sum;
    }

    //該方法會回傳一輸入數值搜尋到的節點位址
    TreeNode* search_node(TreeNode* node, int target) {
        //若節點為空指標回傳空指標
        if (node == nullptr) return nullptr;
        
        //若節點值等於輸入數值回傳它的位址
        if (node->value == target) return node;
        //否則檢查左右子樹是否有目標節點
        else {
            //令l, r分別為欲搜尋的節點
            TreeNode *l = search_node(node->left, target), *r = search_node(node->right, target);

            //如果節點在左回傳它
            if (l) return l;
            //如果節點在右回傳它
            if (r) return r;
        }

        //如果都不在回傳空指標
        return nullptr;
    }
    
    //這個方法會印出使用者輸入節點的比較結果
    void compare_subtree(TreeNode* root) {
        //讓使用者輸入欲比較節點
        int target;
        cout << "輸入欲檢查的節點值: ";
        cin >> target;
        //利用search_node方法找到該節點位址
        TreeNode *node = search_node(root, target);
        //若該節點是空指標，印出該節點為空的訊息
        if (node == nullptr) {
            cout << "未找到指定節點" << endl;
        //若該節點沒有子樹，印出該節點為葉節點的訊息
        } else if (node->left == nullptr && node->right == nullptr) {
            cout << "該節點為葉節點，沒有子樹" << endl;
        //若該節點有子樹則比較並印出結果
        } else {
            //利用sumtree方法分別取得左右子樹的和
            int l = sumtree(node->left), r = sumtree(node->right);
            //印出左右子樹總和的值
            cout << "左子樹總和: " << l << endl;
            cout << "右子樹總和: " << r << endl;
            //印出左右子樹比較結果
            if (l > r) cout << "左子樹總和較大" << endl;                
            else if (r > l) cout << "右子樹總和較大" << endl;
            else cout << "兩子樹總和一樣大" << endl;            
        }
    }

};

int main() {
    int layer;
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    //cout << "DFS Result: ";
    //tree.Depth_first_search(tree.root);
    //cout << endl;

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;

    tree.compare_subtree(tree.root);

    system("pause");
    return 0;
}
