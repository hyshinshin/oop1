#pragma once
#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
#include <iostream>
#include <string>
#include <vector>

//
enum color{white,navy,pink,yellow,blue,green,darkblue,liteblue,beige,khaki,black};

using namespace std;
class clothes {
private:
	char name[100];
	char style[100];
	char color;
	int length; //반팔,긴팔,칠부?
	int insulation;//보온성
	int trend; //1~5
	
	string pictureroot; //filepath root를  저장

public:
	clothes(char* name, char col, int len, int thick);
	
	//set
	
	void Set_name(char* x);
	void Set_color(char x);
	void Set_length(int x);
	void Set_thick(int thick);
	// void Set_Picture?

	//get
	char* Get_name();
	char Get_color();
	int Get_length();
	int Get_thick();


};

class Outer :clothes {
private:
	int priority;
	int texture; 
	

	// style?? 막,,코트,라이더, 이런거 구분?
	string pricturename;

	// 속성 더 생각하기 
public:
	Outer(char* name, char col, int len, int thick);

	void Set_name(char* name);
		
	char* Get_name();
	
	


};

class top :clothes {
private:
	int thickness;//두께
	bool accessary;
	
	//속성더 생각하기
public:
	
	
};

class set {
private:
	clothes clothes;
	Outer outer;
	top top;
	pants pants;

public:
	set(clothes clo,Outer )

};

class pants :clothes {
private:
	bool belt;
	int priority;
public:

};

class shoes { //신발까지???
private:

public:
};

class accsseary{

};

class manager {//옷장 관리, 추가,삭제,

public:




};
class coordinator {
public:

	void weather(vector<top> &data1, vector<Outer> &data2, vector<pants> &data3) {
		
	}
	
	/****************************************/ //1set
	vector<set> color(vector<top> &data1, vector<Outer> &data2, vector<pants> &data3) {
		// define 1=black 2=white 3=blue 4=beige
		set exset;
		vector<set> set;

		if ((data2[1].Get_color == 2) {
			if (data3[1].Get_color == 4) {
				Set.set();
				Set.
				

			}
		}



	}
	//
	void trend(vector<set>) {// trend 점수의 합으로 

	}



	void Algorithm(vector<top> &data1, vector<Outer> &data2, vector<pants> &data3) {


	}


};





#endif // !__BINARY_TREE_H__
