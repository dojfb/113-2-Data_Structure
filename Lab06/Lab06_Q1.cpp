#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;  // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top; // 指向堆疊頂端
public:
    Stack() { top = nullptr; } // 初始化堆疊

    // Push 操作：將元素放入堆疊
    void push(char ch) {
		Node* newNode = new Node(); // 建立新節點
		newNode->data = ch;      // 儲存資料
		newNode->next = top;        // 新節點指向原本的頂端
		top = newNode;              // 更新頂端為新節點
		//cout << ch << " 已推入堆疊\n";
    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
	    if (top == nullptr) {  // 如果堆疊是空的
	        cout << "堆疊為空，無法取出元素。\n";
	    }
	
	    char poppedValue = top->data; // 取得頂端元素的值
	    Node* temp = top;            // 用 temp 暫存目前頂端節點
	    top = top->next;             // 更新頂端為下一個節點
	    delete temp;                 // 釋放記憶體，刪除原頂端節點
	    //cout << "已取出元素: " << poppedValue << endl;
        return poppedValue;
    }

    // Peek 操作：取得頂端元素但不移除
    char peek() {
        if (top == nullptr) {  // 如果堆疊是空的
	        cout << "堆疊為空，無法查看元素。\n";
	    }
        return top->data;
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
      if(top == nullptr) return true;
      else return false;
    }
};

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
    if(op == '+' || op == '-') return 2;    //+-的優先順序低輸出2
    else return 1;                          //*/的優先順序高輸出1
}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
    //i為輸入陣列指標，j為輸出陣列指標，初始化為0
	int i=0, j=0;
    //建立用於處理的stack物件
	Stack stack;
    //持續處理輸入表達式直到表達式結束
	while(infix[i] != '\0'){    
        //如果當前字元是數字或字母則直接放到輸出表達式後面
		if((47<int(infix[i]) && int(infix[i])<58) || (64<int(infix[i]) && int(infix[i])<91)){
			postfix[j] = infix[i];  //將當前字元放到當前輸出陣列指標位置後，
			j++;                    //將指標指向下一個輸出陣列位置
        //如果當前字元式)則將它與(之間的運算子全部接續pop到輸出陣列
        }else if(infix[i] == ')'){  
            //如果還沒到stack的(則持續做
            while(stack.peek() != '('){
                postfix[j] = stack.pop();//pop stack中的運算子到輸出陣列搭前位址
                j++;                     //將指標指向下一個輸出陣列位置
            }
            stack.pop();                 //最後把(也pop掉
        //若當前運算子為(則直接push進stack
        }else if(infix[i] == '('){
            stack.push('(');
        //若都不是以上情況，比對上一個在stack的運算子依照優先權處理
		}else{
            //如果stack不空，則進行處理
            while(!stack.isEmpty()){
                //如果當前運算子優先級較前一個運算子小，則依序pop到輸出陣列
                if(precedence(infix[i]) >= precedence(stack.peek()) && stack.peek() != '('){
                    postfix[j] = stack.pop();
                    j++;
                //但如果前一個運算子是(則離開迴圈或前一個運算子優先級較大則退出迴圈
                }else{
                    break;
                }
            }
            //不管空不空都要將當前運算子push到stack
            stack.push(infix[i]);
		}
		i++;    //輸入陣列指標在迴圈結束後指向下一個位址
        //cout << i << " : " << postfix << endl;
	}
    //若輸入陣列已處理完畢則將stack中的運算子依序pop到輸出陣列
    while(!stack.isEmpty()){
        postfix[j] = stack.pop();
        j++;
    }
    //最後將輸出陣列末端補上終止字元
    postfix[j] = '\0';
}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式

    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式

    return 0;
}
