#include <iostream>
#include <cmath>


#define MAXLEN 10                           //設定最大係數陣列儲存長度

using namespace std;

class Polynomial{                           //建立多項式物件(Polynomial)，用以表示多項式p(x)=a0x^n + a1x^n-1 + ... + an
    private:
        int length;                         //係數陣列儲存長度
        float coef[MAXLEN][2];              //宣告係數陣列長度為最大儲存長度，coef[][0]儲存係數coef[][1]儲存次方

    public:
        Polynomial(){}                      //若沒有輸入則只規劃儲存空間

        Polynomial(int len, float c[][2]){  //可透過傳入係數陣列儲存長度(len)與二維陣列(c[][2])來初始化
            length = len;
            for(int i=0; i<length; i++){
                coef[i][0] = c[i][0];
                coef[i][1] = c[i][1];
            }
        }

        float eval(float x) const {         //函數值評估函數(eval)，可計算多項式輸入x值的輸出值p(x)
            float result = 0;

            for(int i=0; i<length; i++){
                result += coef[i][0]*pow(x, coef[i][1]);    //將各項係數(coef[i][0])乘以x的各項次方(coef[i][1])後加總到result
            }

            return result;                                  //回傳加總值result
        }

		void printPolynomial() const {                              //多項式列印函數，將多項式以a0x^n + a1x^n-1 + ... + an的格式列印
			for(int i=length-1; i>0; i--){
				cout << coef[i][0] << "x^" << coef[i][1] << " + ";  //循環將每一項以係數(coef[i][0])、x^、次方(coef[i][1])與加號印出
			}

            if(coef[0][1] != 0)                                     //如果最後一行是常數就只印係數。否則再加印次方項
			    cout << coef[0][0] << "x^" << coef[0][1] << endl;
            else
                cout << coef[0][0] << endl;
		}

		static Polynomial add(Polynomial &p1, Polynomial &p2){  //傳入兩個多項式物件(polynomial)回傳一個相加後的多項式物件
			float c[MAXLEN][2] = {0};                           //宣告儲存係數用陣列，儲存相加後的係數
            int i, count1, count2;                              //宣告計數器，i用於相加後物件，count1、count2分別用於物件一與物件二的計數

            i = count1 = count2 = 0;    //計數器歸零
            while(count1 < p1.length && count2 < p2.length){    //直到其中一個物件數完前持續處理，目的是建立冪次單調遞增的多項式係數陣列
                if(p1.coef[count1][1] < p2.coef[count2][1]){    //若比較目前物件項次冪數發現物件一冪次較低則將它儲存至目前相加後的係數陣列(c)的目前項
                    c[i][0] = p1.coef[count1][0];
                    c[i][1] = p1.coef[count1][1];
                    count1++;                                   //將物件一的計數器加一，下次迭帶一起進下一項
                }else if(p1.coef[count1][1] > p2.coef[count2][1]){  //跟上面的邏輯一樣，只是改成物件二
                    c[i][0] = p2.coef[count2][0];
                    c[i][1] = p2.coef[count2][1];
                    count2++;
                }else{
                    c[i][0] = p2.coef[count2][0] + p1.coef[count1][0];//若兩物件冪次同時一樣，則係數相加，冪次取其中一個
                    c[i][1] = p2.coef[count2][1];
                    count1++;                                         //兩物件的計數器同時加一，下次迭帶一起進下一項
                    count2++;
                }
                i++;                                                  //讓相加後的係數陣列(c)計數器加一指向下一項
            }   
                                                               //由於其中一個物件可能會先迭帶完，接下來處理餘項，若無餘項不須處理
            if(count2 < p2.length){                                 //若物件二有餘項，則將他們接續存到相加後的係數陣列(c)後，
                for(;count2<p2.length;count2++){                    //由於單調性質可保證他們的冪次都小於相加後的係數陣列(c)的最小項
                    c[i][0] = p2.coef[count2][0];
                    c[i][1] = p2.coef[count2][1];
                    i++;                                            //讓相加後的係數陣列(c)計數器加一指向下一項
                }
            }else if(count1 < p1.length){                           //跟上面的邏輯一樣，只是改成物件一
                for(;count1<p1.length;count1++){
                    c[i][0] = p1.coef[count1][0];
                    c[i][1] = p1.coef[count1][1];
                    i++;
                }
            }
			return Polynomial(i, c);                                //此時計數器i極為陣列長度，與相加後的係數陣列(c)一同建立多項式物件並回傳
        }

		static Polynomial mult(Polynomial &p1, Polynomial &p2){     //輸入兩多項式物件回傳他們相乘後的多項式物件
			float c[MAXLEN][2] = {0};                               //宣告暫存陣列(c)
            Polynomial result, temp;                                //宣告結果與暫存多項式物件
            bool flag = 0;    
                                                                    //判定是否為第一次迴圈的旗標
            for(int i=0; i<p1.length; i++){                         //概念是將物件一的每一項乘以物件二製造暫存多項式物件後、
                for(int j=0; j<p2.length; j++){                     //利用物件方法add將他們加總
                    c[j][0] = p1.coef[i][0] * p2.coef[j][0];        //這裡做逐項相乘的係數，並儲存在暫存陣列，
                    c[j][1] = p1.coef[i][1] + p2.coef[j][1];        
                }
                temp = Polynomial(p2.length, c);                    //將暫存陣列與物件二長度建維暫存多項式物件，來使用多項式的add方法
                if(flag == 0){                                      //若為第一次迴圈則將結果物件設為目前的暫存物件
                    result = temp;
                    flag = 1;
                }else{
                    result = add(temp, result);                     //否則使用add方法身與暫存物件相加
                }
            }

			return result;                                          //回傳結果多項式物件
		}
};

int main(){
    //設定脫像是參數
    float c1[][2] = {{1, 0}, {2, 1}, {3, 2}, {4, 3}}; //4x^3 + 3x^2 + 2x^1 + 1
	float c2[][2] = {{2, 2}, {3, 3}, {5, 5}};         //5x^5 + 3x^3 + 2x^2

    //傳入參數建立物件
    Polynomial p1(4, c1);
    Polynomial p2(3, c2);
    Polynomial p3 = Polynomial::add(p1, p2);    //測試物件方法add
    Polynomial p4 = Polynomial::mult(p1, p2);   //測試物件方法mult

	cout << "P1(5): " << p1.eval(5) << endl;    //列印物件的eval方法回傳值
    cout << "P1: ";
    p1.printPolynomial();                       //利用物件方法列印物件與結果展示
    cout << "P2: ";
    p2.printPolynomial();
    cout << "P1 + P2: ";
    p3.printPolynomial();
    cout << "P1 * P2: ";
    p4.printPolynomial();

    return 0;

}
