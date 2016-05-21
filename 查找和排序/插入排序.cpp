void insertSort1(int a[], int n)
{
    int i, j, k;
    for (i = 1; i < n; i++) {
        //为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
        for (j = i - 1; j >= 0; j--)
            if (a[j] < a[i]) {
                break;
            }
        if (j != i - 1) {		//如找到了一个合适的位置
            int temp = a[i];	//将比a[i]大的数据向后移
            for (k = i - 1; k > j; k--) {
                a[k + 1] = a[k];
            }
            a[k + 1] = temp;	//将a[i]放到正确位置上
        }
    }
}

void insertSort2(int a[], int n)
{
    int i, j;
    for (i = 1; i < n; i++)
        if (a[i] < a[i - 1]) {
            int temp = a[i];
            for (j = i - 1; j >= 0 && a[j] > temp; j--) {
                a[j + 1] = a[j];
            }
            a[j + 1] = temp;
        }
}

void insertSort3(int a[], int n)
{
    for (int i = 1; i < n; i++)
        for (int j = i - 1; j >= 0 && a[j] > a[j + 1]; j--) {
            Swap(a[j], a[j + 1]);
        }
}
