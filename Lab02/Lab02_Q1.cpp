class Solution {
	public:
		int findLucky(vector<int>& arr) {
			int luck_num=-1;    //設luck_nums初值為-1//step+1: 給值1次
			int counter=0;      //設counter初值為0//step+1: 給值1次
	
			//step*n: 迴圈做n次
			for(int i: arr){        //step+1: 陣列取值1次
				//依序取出arr的值，並存在i//step*n: 迴圈做n次
				for(int j: arr){    //step+1: 陣列取值1次
					//依序取出arr的值，並存在j
					if(i == j){     //step+1: 比較1次
						//若i等於j則counter加1
						counter++;  //step+1: ++一次
					}
				}
				//此時counter值為i在arr中的出現次數
				if(i == counter && i > luck_num){//step+3: 比較3次
					luck_num = i;                //step+1: 給值1次
				}
				//若i與counter數值一樣且大於目前的luck_num，則設i為新的luck_num
				counter = 0;                     //計數器歸零//step+1: 給值1次
			}
			return luck_num;                     //回傳luck_num//step+1: 回傳
		}
	};      //total step: 3 + n(6 + 3n) = 3n^2 + 6n + 3
			//time complexity: O(n^2)
