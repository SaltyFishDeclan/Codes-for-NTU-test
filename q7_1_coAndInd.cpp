//7. Coordinates-to-index & Index-to-coordinates
//this is a code suitable for any given dimensionality, rather than solely solving 2-dimension or 6-dimension problems.


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdio.h>

using namespace std;

ifstream ind("input_index_7_1.txt");//input index
ifstream coo("input_coordinates_7_1.txt");//input coordinates, dimensionality d is got from here
ofstream outi("output_index_7_1.txt");
ofstream outc("output_coordinates_7_1.txt");

int getD(){// get dimensionality d by reading the first line of input coordinates file
	string str;
	int d=0;//the returned dimensionality
	getline(coo,str);
	
	for(int i=0; i<strlen(str.c_str()); i++){
		if(str[i]=='x')
			d++;
	}
	//cout<<d<<endl;
	getline(ind,str);
	
	return d;
}

// coordinate to index: given coordinates {x[i]}, find index I
void co2in(int d, int L[]){// input dimensionality d and L[]
	int x[20];
	int I=0;
	
	outi<<"index"<<endl;
	while(!coo.eof()){
		coo>>x[1];
		if(x[1]=='\n') continue;
		I = x[1];
		for(int i=2;i<=d;i++){
			coo>>x[i];
			int tmp = x[i];
			for(int j=1;j<i;j++){
				tmp*=L[j];
			}
			//tmp == L[1]*...*L[i-1]*x[i]
			I+=tmp;
		}
		outi<<I<<endl;	
	}
}

// index to coordinate: given index I, find coordinates {}
void in2co(int d, int L[]){// input dimension d and index I
	for(int i=1;i<=d;i++){
		outc<<"x"<<i<<'\t';
	}
	outc<<endl;
	//int ct = 0;
	while(!ind.eof()){
		int I;
		ind>>I;
		if(I=='\n') continue;
		//outc<<I%L[1];//x[1] = I%L[1]
		int tmp = 1;
		for(int i=1;i<=d;i++){
			int tmp1 = tmp; // tmp1 = L[1]*...*L[i-1] (if i==1, tmp=1)
			tmp*= L[i]; // tmp = L[1]*...*L[i]
			int xi = (I%tmp)/tmp1; // x[i] = {I%(L[1]*...*L[i])}/(L[1]*...*L[i-1])
			outc<<xi; 
			if(i==d){
				outc<<endl;
			}
			else{
				outc<<'\t';
			}
		}
		//ct++;
		//cout<<"processing - "<<ct<<endl;
	}
}

int main(){
	int d = getD();
	int L[20];
	cout<<"please input L1 to L"<<d<<":"<<endl;
	for (int i=1; i<=d; i++){
		cout<<"L"<<i<<" = "; 
		cin>>L[i];	
	}
	co2in(d,L);
	in2co(d,L);
	
	return 0;
}
