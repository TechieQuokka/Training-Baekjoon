//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <math.h>
//#include <stdlib.h>
//#include <algorithm>
//#include <vector>
//#include <queue>
//#include <iostream>
//#include <limits>
//#include <string>
//
//using namespace std;
//using lld = long long int;
//using sd = short int;
//
//struct verylld {
//
//	sd integer;
//	struct verylld* next_integer;
//	struct verylld* before_integer;
//	
//};
//
//void verylld_resize(struct verylld* number, int change);
//
//int main() {
//	
//	int count = 0;
//	struct verylld number;
//
//	while (true) {
//		string a;
//		cin >> a;
//		int sdsize = ceil(a.size() / 4);
//		if (sdsize > count) {
//			verylld_resize(&number, sdsize - count);
//		}
//	}
//}
//
//void verylld_resize(struct verylld* number, int change) {
//
//	if (change > 0) {
//		if (!number->next_integer) {
//			verylld_resize(number->next_integer, change);
//		}
//		else {
//			struct verylld* next = (struct verylld*)malloc(1 * (sizeof(struct verylld)));
//			if (next == NULL) return;
//
//			next->integer = 0;
//			number->next_integer = next;
//			next->next_integer = NULL;
//			next->before_integer = number;
//			verylld_resize(number->next_integer, change - 1);
//		}
//		return;
//	}
//
//	else if (change < 0) {
//		if (number->next_integer && !(number->next_integer->next_integer)) {
//				free(number->next_integer);
//				verylld_resize(number->before_integer, change + 1);
//				return;
//		}
//	}
//
//	return;
//}
#define START first
#define END second
#include <iostream>
#include <math.h>
using namespace std;

long long tree[4300000];

//long long init_tree(long long tree[], long long idx, long long start, long long end, long long tree_size)
//{
//
//	if (start == end) return tree[tree_size >> 1 + start];
//	
//	long long left_val = init_tree(tree, idx << 1, start, (start + end) >> 1, tree_size);
//	long long right_val = init_tree(tree, idx << 1 + 1, (start + end) >> 1 + 1, end, tree_size);
//
//	//cout << idx << ": " << tree[idx] << ' ';
//	return tree[idx] = left_val + right_val;
//}

long long find_sum(long long tree[], long long idx, pair<long long, long long> target, pair<long long, long long> present)
{
	if (present.START >= target.START && present.END <= target.END) return tree[idx];
	else if (present.END < target.START || present.START > target.END) return 0;

	long long left_val = find_sum(tree, (idx << 1), { target.START, target.END }, { present.START, ((present.START + present.END) >> 1) });
	long long right_val = find_sum(tree, (idx << 1) + 1, { target.START, target.END }, { ((present.START + present.END) >> 1) + 1, present.END });

	return left_val + right_val;

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	long long num_num, num_change, num_sum;

	cin >> num_num >> num_change >> num_sum;

	long long tree_size = ((1 << (long long)(ceil(log2(num_num)) + 1))) - 1;

	for (long long i = 1; i <= num_num; i++)
	{
		cin >> tree[(tree_size >> 1) + i];
	}

	for (long long i = (tree_size >> 1); i >= 1; i--)
	{
		tree[i] = tree[(i << 1)] + tree[(i << 1) + 1];
	}

	for (long long i = 0; i < num_change + num_sum; i++)
	{
		long long num1, num2, num3;
		long long present;
		cin >> num1 >> num2 >> num3;

		if (num1 == 1)
		{
			long long temp = (tree_size >> 1) + num2;
			tree[temp] = num3;
			present = temp;
			present >>= 1;
			while (present > 1)
			{
				tree[present] = tree[(present << 1)] + tree[(present << 1) + 1];
				present >>= 1;
			}
		}
		else
		{
			cout << find_sum(tree, 1, { num2, num3 }, { 1, (tree_size >> 1) + 1 }) << '\n';
		}
	}

	return 0;

}