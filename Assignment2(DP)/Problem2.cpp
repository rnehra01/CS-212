#include <bits/stdc++.h>
#include <string>
#define ll long long int
using namespace std;

bool isBad(int x1, int y1, int x2, int y2, string *bad, int badLength){
	string possibleArr1 = to_string(x1)+" "+to_string(y1)+" "+to_string(x2)+" "+to_string(y2);
	string possibleArr2 = to_string(x2)+" "+to_string(y2)+" "+to_string(x1)+" "+to_string(y1);
	
	for (int i=0; i<badLength; i++){
		if (bad[i]==possibleArr1 || bad[i]==possibleArr2)
			return true;
	}
	return false;
}

ll numways(int width, int height, string *bad, int badLength){
	ll dp[height+1][width+1];
	
	for (int j=0; j<=width; j++)
		for (int i=0; i<=height; i++)
			dp[i][j] = 0;

	dp[0][0] = 1;

	for (int j=0; j<=width; j++)
		for (int i=0; i<=height; i++){
			if (i>0 && j>=0 && !isBad(i, j, i-1, j, bad, badLength))
				dp[i][j] +=  dp[i-1][j] ;
			if (i>=0 && j>0 && !isBad(i, j, i, j-1, bad, badLength))
				dp[i][j] += dp[i][j-1];
		}

	return dp[height][width];
}

int main(){
	string bad[] = {"0 0 0 1","6 6 5 6"};
	
	cout<<numways(6, 6, bad, sizeof(bad)/sizeof(bad[0]))<<endl;
	
	return 0;
}
