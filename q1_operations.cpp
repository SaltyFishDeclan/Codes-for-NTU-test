#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

#define ll long long

stack <char>solution;
ofstream outf("output_question_1.txt");

void op(long long sum, int m, int n){
	int s;
	int steps = m+n-2;
	outf<<sum<<" ";
	s = (1+m)*m/2 + n-1;
	sum -= s;
	for(int k=m-1;k>0;k--){
		int a = sum/k;
		sum = sum%k;
		for(int i=0;i<a;i++){
			solution.push('R');
		}
		solution.push('D');
	}
	//cout<<solution.size()<<endl;
	while(solution.size()<steps){
		solution.push('R');
	}
		
	while(!solution.empty()){
		outf<<solution.top();
		solution.pop();	
	}
	outf<<endl;
}

int main(){
	int sum1[5] = {65, 72, 90, 110};
	long long sum2[5] = {87127231192, 5994891682};
	int m[5] = {9,90000};
	int n[5] = {9,100000};
	for(int i=0; i<4; i++){
		op(sum1[i], m[0], n[0]);
	}
	outf<<endl;
	for(int i=0; i<2; i++){
		op(sum2[i], m[1], n[1]);
	}
	return 0; 
}


