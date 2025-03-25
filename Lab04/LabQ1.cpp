#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

random_device rd;
mt19937 g(rd());

// 表示單張撲克牌的類別
class Card {
public:
    string colors; //儲存撲克牌的花色
    string rank; //儲存撲克牌的數值
    Card(string s, string r) : colors(s), rank(r) {} //建立constructor來初始化物件，當Card物件建立時，它會自動執行這個函式，並把s和r的值存入colors和rank
    void display() const { //顯示撲克牌的資訊
        cout << rank << " of " << colors << endl;
    }
};

// 實作Stack
class Stack {
private:
    vector<Card> stack; //表示stack是一個能存放Card類別物件的vector

public:
    void push(const Card& card) {   //在Stack中實作堆疊的push功能
    	stack.push_back(card);  //利用vector的push_back方法，將card堆到stack的最後面
    }

    Card pop() {    //在Stack中實作堆疊的pop功能，刪掉最後一個元素並回傳他
    	Card val = stack.back();    //將stack最後一個元素複製到val
    	stack.pop_back();           //利用vector的pop_back方法，將stack的最後一個元素刪除
    	return val;                 //回傳val
    }

    bool isEmpty() const {     //若Stack為空，回傳true，不然false 
    	return stack.empty();   //利用vector的empty方法達成
    }
};

// 代表一副撲克牌的類別
class Deck {
private:
    vector<Card> cards; // 存放未洗牌的撲克牌
    Stack shuffledDeck; // 存放洗過的牌，用實作的stack來管理
public:
    Deck() { //建立constructor來初始化物件
        string colors[] = { "Hearts", "Diamonds", "Clubs", "Spades" }; //儲存撲克牌的花色
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" }; //儲存撲克牌的數值

        //利用迴圈將52張牌加入cards這個vector裡面
        for (int i = 0; i < 4; i++) { // 四種花色
            for (int j = 0; j < 13; j++) { // 13 種點數
                cards.push_back(Card(colors[i], ranks[j]));
            }
        }
    }

    //洗牌(Hint:使用shuffle函數)
    void shuffleDeck() {
        shuffle(cards.begin(), cards.end(), g); //先把cards用shuffle打亂，本來想存到shuffledDeck在打亂，
                                                //但不同class所以無法，只好打亂cards在複製給shuffledDeck
        for(int i=0; i<cards.size(); i++)
        	shuffledDeck.push(cards[i]);        //把打亂的cards堆到shuffledDeck中
    }

    //發牌
    void drawAllCards() {                   //印出shuffledDeck中的每一張牌，由最後一個元素依序印
		while(!shuffledDeck.isEmpty()){     //當shuffledDeck不是空的就做
			shuffledDeck.pop().display();   //印出shuffledDeck最後一個元素並刪除
		}
    }
};

int main() {
    Deck deck; //建立deck產生52張撲克牌
    deck.shuffleDeck(); //進行洗牌並放入堆疊
    cout << "Shuffled deck:" << endl;
    deck.drawAllCards(); //依序取出堆疊內的牌並顯示
    return 0;
}
