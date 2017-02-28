#include <bits/stdc++.h>
using namespace std;

int lis(int *a, int n){
	int dp[n] = {1};

	int maxLength = 0;

	for (int i=0; i<n; i++){
		for (int j=0; j<i; j++){
			if (a[j] < a[i]) dp[i] = max(dp[i], dp[j]+1);
		}
		maxLength = max(maxLength, dp[i]);
	}
	return maxLength;
}

int main(){
	int t,n;
	cin>>t;
	while(t--){
		cin>>n;
		int a[2*n];
		for (int i=0; i<n; i++){
			cin>>a[i];
			a[n+i] = a[i];
		}
		int maxNumberOfGuests = 0;
		for (int i=0; i<n; i++){
			maxNumberOfGuests = max(maxNumberOfGuests, lis(a+i, n));
		}
		cout<<maxNumberOfGuests<<endl;
	}
	return 0;
}