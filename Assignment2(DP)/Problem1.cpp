#include <bits/stdc++.h>
using namespace std;

 int zig_zag_length(int *a, int n){
 	int dp[2][n];
 	for (int i=0; i<n; i++)
 		dp[0][i]=dp[1][i]=1;

 	for (int i=0; i<n; i++)
 		for (int j=0; j<i; j++){
 			if (a[i] > a[j])
 				dp[1][i] = max(dp[1][i], dp[0][j]+1);
 			else if (a[i] < a[j])
 				dp[0][i] = max(dp[0][i], dp[1][j]+1);
 		}
 	int max1 = 0;
 	for (int i=0; i<n; i++)
 		max1 = max(max(dp[0][i], dp[1][i]), max1);
 	return max1;
 }

 int main(){
 	int input[] = { 374, 40, 854, 203, 203, 156, 362, 279, 812, 955, 
600, 947, 978, 46, 100, 953, 670, 862, 568, 188, 
67, 669, 810, 704, 52, 861, 49, 640, 370, 908, 
477, 245, 413, 109, 659, 401, 483, 308, 609, 120, 
249, 22, 176, 279, 23, 22, 617, 462, 459, 244 };
 	
 	cout<<zig_zag_length(input, sizeof(input)/sizeof(input[0]));
 	return 0;
 }