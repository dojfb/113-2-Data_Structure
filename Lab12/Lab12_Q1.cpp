class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        //用i遍歷nums1的陣列部分
                        //付值加計算
        int i = m-1;    //step+2
        //用j遍歷nums2
        int j = n-1;    //step+2
        //用k遍歷nums1來付值
        int k = m+n-1;  //step+2

        //因為兩個陣列都是單調的，當nums2完全放入nums1後，
        //表示資料都處理完了，所以用j當終止條件
        //每輪step+1
        while (j >= 0) {
            //若i>=0且當前比較的元素nums1的大於nums2的則優先放到nums1
            if (i >= 0 && nums1[i] > nums2[j]) {    //step+5取值加布林運算
                //放完後各自指標減一
                nums1[k--] = nums1[i--];            //step+5取值加--
            //若i<0表示nums1的陣列部分遍歷完了，將剩餘的nums2部分放入nums1
            //或者i>=0且nums2的元素比nums1的大則優先放到nums1
            } else {
                //放完後各自指標減一
                nums1[k--] = nums2[j--];            //step+5取值加--
            }
        }
        //最糟情況nums1元素皆大於nums2，要做完nums1才能做nums2，
        //while裡的程式做(m+n)次
        //total step=2+2+2+(m+n)(1+5+5)=6+11(m+n)
        //時間複雜度O(n)=O(m+n)
    }
};
