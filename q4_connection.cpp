#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>

using namespace std;

//stack <int>tags;
//for (int i=15;i>0;i--){
//	tags.push(i);
//}
ifstream image("input_question_4.txt");
//ifstream image("test.txt");
ofstream outf4("output_question_4_c4.txt");//4-connectivity
ofstream outf8("output_question_4_c8.txt");//8-connectivity

int map[40][40];

bool tags[40];

void initTags(){
	for(int i=0;i<40;i++){
		tags[i] = 1;
	}
}

void initMap(){
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			map[i][j] = 0;	
		}
	}
}

void readMap(int m, int n){// numbers of rows and columns of the map
	//int map[20][20];
	for(int i=1;i<=m;i++){// map starts from map[1][1]
		for(int j=1;j<=n;j++){
			image>>map[i][j];
		}
	}
}

int min(int a, int b){
	if(a<b) return a;
	else return b;
}

int min3(int a, int b, int c){
	return(min(a,min(b,c)));
}

//4-connectivity: checkP4 and setP4
void checkP4(int m, int n){//when a pixel has already been tagged and needs to be checked
	if(map[m][n]<map[m-1][n]){
		tags[map[m-1][n]] = 1;
		map[m-1][n] = map[m][n];
		checkP4(m-1,n);
	}
	if(map[m][n]<map[m+1][n]){
		tags[map[m+1][n]] = 1;
		map[m+1][n] = map[m][n];
		checkP4(m+1,n);
	}
	if(map[m][n]<map[m][n-1]){
		tags[map[m][n-1]] = 1;
		map[m][n-1] = map[m][n];
		checkP4(m,n-1);
	}
	if(map[m][n]<map[m][n+1]){
		tags[map[m][n+1]] = 1;
		map[m][n+1] = map[m][n];
		checkP4(m,n+1);
	}
}

void setP4(int m, int n){ // when a pixel is visited for the first time
	if(map[m][n]!=0){
		if(map[m-1][n]==0 && map[m][n-1]==0){//if its left and up pixels are both 0, give it a new tag
			for(int i=1;i<30;i++){
				if(tags[i]==1){
					map[m][n] = i;
					tags[i] = 0;
					break;
				}
			}
		}
		else if(map[m-1][n]==0){//if its up pixel is 0 while left is not, its tag is the same as its left
			map[m][n] = map[m][n-1];
		}
		else if(map[m][n-1]==0){//if its left pixel is 0 while up is not, its tag is the same as its up
			map[m][n] = map[m-1][n];
		}
		else if(map[m][n-1] == map[m-1][n]){//if its left equals to up(and not 0)
			map[m][n] = map[m-1][n];
		}
		else if(map[m][n-1] != map[m-1][n]){//if its left differs from up(both not 0)
			map[m][n] = min(map[m-1][n], map[m][n-1]);
			checkP4(m, n);
		}
	}
}

//8-connectivity: checkP8 and setP8
void checkP8(int m, int n){//when a pixel has already been tagged and needs to be checked
	for(int i=m-1;i<=m+1;i++){
		for(int j=n-1;j<=n+1;j++){
			if(m==i && n ==j) continue;
			if(map[m][n]<map[i][j]){
				tags[map[i][j]] = 1;
				map[i][j] = map[m][n];
				checkP8(i,j);
			}
		}
	}
}

void setP8(int m, int n){ // when a pixel is visited for the first time
	if(map[m][n]!=0){//q,w,e,a respectively represents the left-up, up, right-up and left blocks
		//4/4 0s 
		int q = map[m-1][n-1];
		int w = map[m-1][n];
		int e = map[m-1][n+1];
		int a = map[m][n-1];
		if(q==0 && w==0 && e==0 && a==0){// q=w=e=a=0: new tag
			for(int i=1;i<30;i++){
				if(tags[i]==1){
					map[m][n] = i;
					tags[i] = 0;
					break;
				}
			}
		}
		//3/4 0s
		else if(q==0 && w==0 && e==0){ //qwe
			map[m][n] = a;
		}
		else if(q==0 && w==0 && a==0){ //qwa
			map[m][n] = e;
		}
		else if(q==0 && e==0 && a==0){ //qea
			map[m][n] = w;
		}
		else if(w==0 && e==0 && a==0){ //wea
			map[m][n] = q;
		}
		//2/4 0s
		else if(q==0 && w==0){//qw
			map[m][n] = min(e,a);
			checkP8(m,n);
		}
		else if(q==0 && e==0){//qe
			map[m][n] = min(w,a);
			checkP8(m,n);
		}
		else if(q==0 && a==0){//qa
			map[m][n] = min(w,e);
			checkP8(m,n);
		}
		else if(w==0 && e==0){//we
			map[m][n] = min(q,a);
			checkP8(m,n);
		}
		else if(w==0 && a==0){//wa
			map[m][n] = min(q,e);
			checkP8(m,n);
		}
		else if(e==0 && a==0){//ea
			map[m][n] = min(q,w);
			checkP8(m,n);
		}
		//1/4 0s
		else if(q==0){//q
			map[m][n] = min3(w,e,a);//wea
			checkP8(m,n);
		}
		else if(w==0){//w
			map[m][n] = min3(q,e,a);//qea
			checkP8(m,n);
		}
		else if(e==0){//e
			map[m][n] = min3(q,w,a);//qwa
			checkP8(m,n);
		}
		else if(a==0){//a
			map[m][n] = min3(q,w,e);//qwe
			checkP8(m,n);
		}
		else if(q==w && q==e && q==a){//q=w=e=a!=0
			map[m][n] = q;
		}
		else{
			map[m][n] = min(q,min3(w,e,a));
			checkP8(m,n);
		}
	}
}


int main(){
	initMap();
	initTags();
	int m, n;
	cout<<"input the number of rows:";
	cin>>m;
	cout<<"input the number of columns:";
	cin>>n;
	readMap(m,n);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			//setP4(i,j);
			setP8(i,j);
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			//outf4<<map[i][j];
			outf8<<map[i][j];
			if(j==n) 
				//outf4<<endl;
				outf8<<endl;
			else 
				//outf4<<" ";
				outf8<<" ";
		}
	}
	
	return 0;
}
