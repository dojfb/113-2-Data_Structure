class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        //count+1
        int c = 1;
        //count+1
        int state = 0;  //0表示未知陣列，1表示單調遞增陣列，2表示單調遞減陣列
        //count+1
        if(nums.size()<3){  //長度3以下皆為單調陣列
            //count+1
            return true;
        }else{
            //count+1
            while(c<nums.size()){
                //count+3
                if(nums[c-1]==nums[c]){ //若前後兩個元素一樣跳過
                    //count+1
                    c++;
                    continue;
                    //count+3
                }else if(nums[c-1]<nums[c]){    //後一個元素較大則狀態設為1
                    //count+1
                    if(state != 2){
                        //count+1
                        state = 1;
                        //count+1
                        c++;
                        continue;
                    }else{
                        //count+1
                        return false;   //若已知他是單調遞減陣列，其中又有相鄰遞增元素則非單調陣列
                    }
                }else{
                    //count+1
                    if(state != 1){ //後一個元素較小則狀態設為2
                        //count+1
                        state = 2;
                        //count+1
                        c++;
                        continue;
                    }else{
                        //count+1
                        return false;   //若已知他是單調遞增陣列，其中又有相鄰遞減元素則非單調陣列
                    }
                }
            }
            //count+1
            return true;    //若一切跑完沒問題則他是單調陣列
        }
    }//最糟情況共: 7n+6 steps
};
