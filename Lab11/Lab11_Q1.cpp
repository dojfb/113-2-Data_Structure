#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

//建立商品結構，儲存商品資料
struct Product {
    string name;
    int date;
    int hotness;
};

//建立分類類別，儲存並排序商品列表
class Sort {
    public:
    //宣告商品列表儲存商品
    vector<Product> list;
    //宣告商品數量
    int n;

    //這個方法將讀取到的檔案儲存為商品列表並取得商品數量
    void readFromFile(const string& filename) {
        //宣告檔案物件，讀取檔案
        ifstream file(filename);
        //若檔案為空則報錯
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        //設定暫存字串
        string line;
        //利用暫存字串讀檔案第一行
        getline(file, line); 
        //因為第一行是商品數，轉為整束後存在n
        n = stoi(line);

        //迴圈裡一行一行的讀，並把品名，日期與熱銷度分別存到個別商品物件後，存到商品列表list
        while (getline(file, line)) {
            if (line.empty()) continue; // 忽略空行
            //宣告字串處理物件用於迭代，把當前行用空白分隔製成迭代器
            stringstream ss(line);
            //把分割後的字串存到token方便迭代
            vector<string> tokens;
            //用word作為遍歷當前行的暫存字串
            string word;
            //迴圈裡將分隔後的字串依序儲存到token中
            while(ss >> word) {
                tokens.push_back(word);
            }
            //宣告這存商品物件
            Product p;
            //將暫存商品物件的熱銷度設為token最後一個元素
            p.hotness = stoi(tokens.back());
            //然後把token最後的元素pop掉
            tokens.pop_back();
            //如法炮製設定暫存商品物件的日期
            p.date = stoi(tokens.back());
            tokens.pop_back();
            
            //則最後token剩下的東西就是商品名稱
            //將他們用空格連起來後存到暫存商品物件的商品名
            p.name = tokens[0];
            for (int i = 1; i < tokens.size(); ++i) {
                p.name += " " + tokens[i];
            }

            //最後把暫存商品物件push到商品列表
            list.push_back(p);
        }
        //處理完後關閉檔案
        file.close();
    }

    //這個函數判斷排序優先順序，先照 date 小的優先，若 date 相同則照 hotness 大的優先
    bool compare(const Product& a, const Product& b) {
        //日期不相等比較日期
        if (a.date != b.date)
            return a.date > b.date;
        //否則比較熱銷度
        else
            return a.hotness < b.hotness;
    }

    // 這個函數用 selection sort 把商品列表排序
    void sortProducts() {
        //遍歷 0 到 n-1 號的商品
        for (int i = 0; i < n - 1; ++i) {
            //宣告變數儲存當前優先級最高的編號
            int minIndex = i;
            //遍歷未排序的剩餘商品列表
            for (int j = i + 1; j < n; ++j) {
                //如果j號商品日期較小或較熱門則將最優先編號設為j
                if (compare(list[minIndex], list[j])) {
                    minIndex = j;
                }
            }
            //找到剩餘列表中最優先元素後交換到第i號位置，如果i商品已經最優先則不做動
            if (minIndex != i) {
                swap(list[i], list[minIndex]);
            }
        }
    }
    //這個函數把當前商品列表的品名依序打印
    void printresult() {
        for (int i = 0; i < n; i++) {
            cout << list[i].name << endl;
        }
    }
};




int main() {
    //宣告分類器物件
    Sort sort;
    //宣告檔案位址宣告檔案位址
    string filename = "C:\\Users\\Dan\\Desktop\\mycode\\data_structure\\input1\\input3.txt";//請貼上input檔案的正確路徑
    
    //利用內建方法把檔案儲存到商品列表中
    sort.readFromFile(filename);
    //利用內建方法排序商品列表
    sort.sortProducts();
    //利用內建方法印出當前商品列表品名
    sort.printresult();

    return 0;
}
