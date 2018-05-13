#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef __COORDINATE_SYS_H__
#define __COORDINATE_SYS_H__
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>
#define _WIN32_WINNT _WIN32_WINNT_XP
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <mmsystem.h>
enum color{ white, navy, pink, yellow, blue, green, darkblue, lightblue, beige, khaki, black, gray };
#define STANDARD_IMAGE "C:\\opencv\\image\\standard.jpg";
#define pictureroot_outer  "C:\\opencv\\image\\outer\\"
#define pictureroot_top  "C:\\opencv\\image\\top\\"
#define pictureroot_pants "C:\\opencv\\image\\pants\\"
#define pictureroot_overgarment "C:\\opencv\\image\\overgarment\\"
#define pictureroot_shoes  "C:\\opencv\\image\\shoes\\"
#define pictureroot_accessory  "C:\\opencv\\image\\accessory\\"
#define SOUND_FILE_NAME "03-Daily-Look-_Feat.-Silly-Boot_.wav"
using namespace cv;
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality	
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;    // Asynchronous streams


//using namespace std;

class Clothes {
private:
	std::string name;
	std::string style;
	std::string color;
	std::string length; //반팔,긴팔,칠부?
	int insulation;//보온성
	int trend; //1~5
	int priority;//1~10
	std::string pictureroot; //filepath root를  저장
	int w_trend;
	int w_priority;

public:
	Clothes();
	Clothes(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, std::string& pictureroot);

	//set	
	void set_name(std::string name);
	void set_style(std::string style);
	void set_color(std::string col);
	void set_length(std::string len);
	void set_insulation(int insulation);
	void set_trend(int trd);
	void set_priority(int prior);
	void set_pictureroot(std::string pictureroot);
	void set_w_trend(float w_trend);
	void set_w_priority(float w_priority);

	//get
	std::string get_name();
	std::string get_style();
	std::string get_color();
	std::string get_length();
	int get_insulation();
	int get_trend();
	int get_priority();
	std::string get_pictureroot();

	bool operator==(const std::string name);
	bool operator<(const Clothes& other);

};


class Outer : public Clothes {
private:
	std::string texture;

public:
	Outer();
	Outer(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, std::string& texture, std::string& pictureroot);
	std::string get_texture();
	
};


class Top : public Clothes {
private:
	int thickness;

public:
	Top();
	Top(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, int thickness, std::string& pictureroot);

	int get_thickness();

};


class Pants : public Clothes {
private:
	bool belt;
public:
	Pants();
	Pants(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, bool belt, std::string& pictureroot);

	bool get_belt();
};


class Overgarment :public Clothes {
private:


public:
	Overgarment();
	Overgarment(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, std::string& pictureroot);

};


class Shoes{ //
private:
	std::string name;
	std::string style;
	int trend;
	int priority;
	std::string color;
	std::string pictureroot;
	int w_trend;
	int w_priority;

public:
	Shoes();
	Shoes(std::string& name, std::string& style, std::string& color, int trend, int priority, std::string& pictureroot);
	void set_trend(int x);
	void set_priority(int x);
	void set_name(std::string name);
	void set_w_trend(float w_trend);
	void set_w_priority(float w_priority);
	
	std::string get_name();
	std::string get_style();
	std::string get_color();
	int get_trend();
	int get_priority();
	std::string get_pictureroot();
	std::string get_picturename();

	bool operator<(const Shoes &other);
	bool operator==(const std::string name);
};


class Accessory{ //악세사리는 추가될수도있고 없을수도 있기때문에, priority에 영향을 주지 않음 따라서 priority 맴버변수가 없음
private:
	std::string name;
	std::string style;
	std::string color;
	std::string pictureroot;

public:
	Accessory();
	Accessory(std::string& name, std::string& style, std::string& color, std::string& pictureroot);
	
	std::string get_name();
	std::string get_style();
	std::string get_color();
	std::string get_pictureroot();
	
	void set_name(std::string name);
	bool operator==(const std::string name);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Closet {//옷장안에,outer,top,overgarment,pants,shose,accessory 데이타를 가지고 있어야함. 
private:
	std::vector<Outer> Outer_list;
	std::vector<Top> top_list;
	std::vector<Pants> pants_list;
	std::vector<Overgarment> overgarment_list;
	std::vector<Shoes> shoes_list;
	std::vector<Accessory> accessory_list;

public:
	//set
	void set_outer();
	void set_top();
	void set_pants();
	void set_shoes();
	void set_accessory();
	void set_overgarment();
	//get
	std::vector<Outer> get_outer();
	std::vector<Top> get_top();
	std::vector<Pants> get_pants();
	std::vector<Shoes> get_shoes();
	std::vector<Accessory> get_accessory();
	std::vector<Overgarment> get_overgarment();

};
class Closetmanager {//옷장 관리, 제가임의로 잠깐생각해서 한거니,바꿔도상관없음
private:

public:

	//closetmanager();


	//void ShowMenu() const;

	void Add_outer(Outer x);
	void Add_top(Top x);
	void Add_pants(Pants x);//top pants, overgament shoes accssory 동일
	void Add_shoes(Shoes x);
	void Add_accessory(Accessory x);
	void Add_overgarment(Overgarment x);
	void delete_outer(std::string name);	//top pants, overgament shoes accssory 동일
	void delete_top(std::string name);
	void delete_pants(std::string name);
	void delete_shoes(std::string name);
	void delete_accessory(std::string name);
	void delete_overgarment(std::string name);
	void print_clothes(int type);
	//Outer Search_outer();//top pants, overgament shoes accssory 동일

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Set { //최종적으로 선정된 옷들이 담기게 되는 클래스
private:
	Outer outer;
	Top top;
	Pants pants;
	Overgarment overgarment;
	Shoes shoes;
	Accessory accessory;

public:
	Set();
	Set(Outer outer, Top top, Pants pants, Shoes shoes);
	Set(Outer outer, Top top, Pants pants, Overgarment overgarment, Shoes shoes, Accessory accessory);
	//////
	void set_outer(Outer outer);
	void set_top(Top top);
	void set_pants(Pants pants);
	void set_overgarment(Overgarment overgarment);
	void set_shoes(Shoes shoes);
	void set_accessory(Accessory accessory);
	//////
	Outer get_outer();
	Top get_top();
	Pants get_pants();
	Overgarment get_overgarment();
	Shoes get_shoes();
	Accessory get_accessory();
	
};

class Cordinator {//algorithm
private:
	int colorSet[4];
	int vec_size;
	float weight;
	int standard_insulation[2]; // [0] = 최소 보온성, [1] = 최대 보온성
	std::vector<Outer> outer;
	std::vector<Outer> ori_outer;
	std::vector<Top> top;
	std::vector<Top> ori_top;
	std::vector<Pants> pants;
	std::vector<Pants> ori_pants;
	std::vector<Overgarment> overgarment;
	std::vector<Overgarment> ori_overgarment;
	std::vector<Overgarment>::iterator it_over;
	std::vector<Shoes> shoes;
	std::vector<Shoes> ori_shoes;
	std::vector<Shoes>::iterator it_shoes;
	std::vector<Accessory> accessory;
	std::vector<Accessory> ori_accessory;
	std::vector<Accessory>::iterator it_accessory;
	void colorSelect(std::string fileName);
	template<class T>
	void color(std::vector<T> &object, int mod);
	template<class T>
	void weather(std::vector<T> &object, double temp);
	void sortList();
	void give_weight(int mod);
	template<class T>
	void set_weightP(std::vector<T> &object);
	template<class T>
	void set_weightT(std::vector<T> &object);	
	template<class T>
	void set_no_weightP(std::vector<T> &object);
	template<class T>
	void set_no_weightT(std::vector<T> &object);
	std::vector<Set> makeSet();
	template<class T>
	void vec_initialize(std::vector<T> &scr_obj, std::vector<T> &dst_obj);
	//5. 마음에 들지 않는 옷 교체작업(선택 된 옷에 대해서만)

public:

	Cordinator() {  };
	Cordinator(std::vector<Outer> vector_Outer, std::vector<Top> vector_Top, std::vector<Pants> vector_Pants) {
		this->ori_outer = vector_Outer;
		this->ori_top = vector_Top;
		this->ori_pants = vector_Pants;
	}
	Cordinator(std::vector<Outer> vector_Outer, std::vector<Top> vector_Top, std::vector<Pants> vector_Pants, std::vector<Overgarment> vector_Overgarment, std::vector<Shoes> vector_Shoes, std::vector<Accessory> vector_Accessory) {
		this->ori_outer = vector_Outer;
		this->ori_top = vector_Top;
		this->ori_pants = vector_Pants;
		this->ori_overgarment = vector_Overgarment;
		this->ori_shoes = vector_Shoes;
		this->ori_accessory = vector_Accessory;
	}

	int get_vector_size();
	void set_weight();
	std::vector<Set> cordinate(std::string colorFileName, double temparature);

};

void split_getpost(std::string& object_str, std::string delimiter);
void split_getpre(std::string& object_str, std::string delimiter);
int color_stoi(std::string colorName);

#endif // !__COORDINATE_SYS_H__
