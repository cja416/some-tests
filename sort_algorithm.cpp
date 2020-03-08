#include <iostream>
#include <vector>
#include <ctime>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

void swap(vector<int>& a, int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

/*****************************************/
void bubble_sort(vector<int>& a) {
	cout << "use bubble sort" << endl;
	int len = a.size();
	for (int i = len-1; i > 0; i--) {
		bool flag = true;
		for (int j = 0; j < i; j++) {
			if (a[j] >= a[j+1]) {
				swap(a, j+1, j);
				flag = false;
			}
		}
		if (flag == true)
			break;
	}
}

/********************************************/
void insert_sort(vector<int>& a) {		//基本有序的情况下适用
	cout << "use insert sort" << endl;
	int len = a.size();
	for (int i = 0; i < len; i++) {
		for (int j = i-1; j >= 0; j--) {
			if (a[j + 1] <= a[j]) {
				swap(a, j, j + 1);
			}
		}
	}
}

/*************************************/
int partition(vector<int>& a, int l, int r) {
	int pivot = a[l];
	while (l < r) {
		while (l < r && a[r] > pivot) r--;
		if (l < r) a[l++] = a[r];
		while (l < r && a[l] < pivot) l++;
		if (l < r) a[r--] = a[l];
	}
	a[l] = pivot;
	return l;
}

void quick_sort(vector<int>& a, int l, int r) {
	if (l < r) {
		int mid = partition(a, l, r);
		quick_sort(a, l, mid - 1);
		quick_sort(a, mid+1, r);
	}
}


/*************************************/
void merge_array(vector<int> &a, int l, int mid ,int r, vector<int>& tmp) {
	int i = l, j = mid + 1;
	int k = 0;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}
	while(i<=mid)
		tmp[k++] = a[i++];
	while(j<=r)
		tmp[k++] = a[j++];

	for (int q = 0; q < k; q++) {
		a[l + q] = tmp[q];
	}
}
void merge_sort(vector<int> &a, int l, int r, vector<int>& tmp) {
	if (l < r) {
		int mid = (l + r) >> 1;
		merge_sort(a, l, mid, tmp);
		merge_sort(a, mid + 1, r, tmp);	//若是传入mid，会在3个元素情况下的右边12121212死循环调用了。
		merge_array(a, l, mid, r, tmp);
	}	
}

/*************************************/
void heap_adjust(vector<int>& a, int root, int limit) {
	int lc = root * 2 + 1;
	int rc = root * 2 + 2;

	int large = root;
	if (lc < limit && a[large] < a[lc]) large = lc;
	if (rc < limit && a[large] < a[rc]) large = rc;

	if (large != root) {	//这三个元素发生了调整
		swap(a, large, root);
		heap_adjust(a, large, limit);
	}
}

void heap_sort(vector<int>& a) {
	int len = a.size();
	for (int i = len / 2 - 1; i >= 0; i--) {	//建堆
		heap_adjust(a, i, len-1);
	}

	for (int i = len - 1; i > 0; i--) {		//堆排序
		swap(a, i, 0);
		heap_adjust(a, 0, i);
	}
}


/*************************************/
void choose_sort(vector<int>& a) {
	int len = a.size();
	for (int i = 0; i < len; i++) {
		int pos = i;
		for (int j = i + 1; j < len; j++) {
			if (a[j] <= a[pos]) {
				pos = j;
			}
		}
		swap(a, i, pos);
	}
}




void sort_this_vector(vector<int>& a) {
	cout << "please input a number to choose a sort algorithm:" << endl;
	cout << "1.bubble_sort" << endl << "2.insert_sort" << endl << "3.quick_sort" << endl;
	cout << "4.merge_sort" << endl << "5.heap_sort" << endl << "6.choose_sort" << endl;
	char num;
	cin >> num;
	if (num<'0' || num>'9')
		cout << "please input a num abovemention" << endl;

	//DWORD time_start, time_end;
	int time_start=0,time_end=0;
	struct timeval tv;
	vector<int> tmp(a.size(), 0);
	//time_start = GetTickCount(); //从操作系统启动经过的毫秒数
	gettimeofday(&tv,NULL);
	time_start = tv.tv_usec;
	switch (num)
	{
	case '1':bubble_sort(a); break;
	case '2':insert_sort(a); break;
	case '3':quick_sort(a, 0, a.size() - 1); break;
	case '4':merge_sort(a, 0, a.size() - 1, tmp); break;
	case '5':heap_sort(a); break;
	case '6':choose_sort(a); break;
	default:
		cout << "please input a num abovemention" << endl;
		break;
	}
	//time_end = GetTickCount();
	gettimeofday(&tv,NULL);
	time_end = tv.tv_usec;
	cout << "used Time = " << (time_end - time_start) << "us\n";
}

int main() {

	vector<int> a;

	srand((unsigned int) time(NULL));
	int count = 200;
	while(count--){
		a.emplace_back(rand() % 500);
	}
	cout << "before sort: " << endl;
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << ", ";
	}
	cout << endl;

	sort_this_vector(a);

	cout << "after sort: " << endl;
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << ", ";
	}
	cout<<endl;

	//system("pause");
	return 0;
}
