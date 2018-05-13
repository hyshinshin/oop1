#include "coordinate_Sys.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Clothes::Clothes() {
	this->set_name("no");
}
Clothes::Clothes(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, std::string& pictureroot)
:name(name), style(style), color(col), length(len), insulation(insulation), trend(trend), priority(priority), pictureroot(pictureroot)
{}

//Clothes set
void Clothes::set_name(std::string name) {
	this->name = name;
}
void Clothes::set_style(std::string style) {
	this->style = style;
}
void Clothes::set_color(std::string col) {
	this->color = col;
}
void Clothes::set_length(std::string len) {
	this->length = len;
}
void Clothes::set_insulation(int insulation) {
	this->insulation = insulation;
}
void Clothes::set_trend(int trd) {
	trend = trd;
}
void Clothes::set_priority(int prior) {
	priority = prior;
}
void Clothes::set_pictureroot(std::string pictureroot) {
	this->pictureroot = pictureroot;
}
void Clothes::set_w_trend(float w_trend){
	this->w_trend = w_trend;
}
void Clothes::set_w_priority(float w_priority){
	this->w_priority = w_priority;
}

//Clothes get
std::string Clothes::get_name() {
	return name;
}
std::string Clothes::get_style() {
	return style;
}
std::string Clothes::get_pictureroot() {
	return pictureroot;
}
std::string Clothes::get_color() {
	return color;
}
std::string Clothes::get_length() {
	return length;
}
int Clothes::get_insulation() {
	return insulation;
}
int Clothes::get_trend() {
	return trend;
}
int Clothes::get_priority() {
	return priority;
}

// Clothes other operatiors
bool Clothes::operator==(std::string name) {
	if (this->get_name() == name)
		return true;
	return false;
}
bool Clothes::operator<(const Clothes &other) {
	return ((this->w_priority + this->w_trend) > (other.w_priority + other.w_trend));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Outer::Outer(){
	this->set_name("no");
}
Outer::Outer(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, std::string& texture, std::string& pictureroot)
:Clothes(name, style, col, len, insulation, trend, priority, pictureroot), texture(texture)
{}

// Outer get
std::string Outer::get_texture() {
	return texture;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Top::Top(){
	this->set_name("no");
}
Top::Top(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, int thickness, std::string& pictureroot)
:Clothes(name, style, col, len, insulation, trend, priority, pictureroot), thickness(thickness)
{}

// Top get
int Top::get_thickness() {
	return thickness;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Pants::Pants(){
	this->set_name("no");
}
Pants::Pants(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, bool belt, std::string& pictureroot)
:Clothes(name, style, col, len, insulation, trend, priority, pictureroot), belt(belt)
{}

// Pants other operators
bool Pants::get_belt() {
	return belt;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Overgarment::Overgarment(){
	this->set_name("no");
}
Overgarment::Overgarment(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, std::string& pictureroot)
:Clothes(name, style, col, len, insulation, trend, priority, pictureroot)
{}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Shoes::Shoes(){
	this->set_name("no");
}
Shoes::Shoes(std::string& name, std::string& style, std::string& color, int trend, int priority, std::string& pictureroot)
:name(name), style(style), color(color), trend(trend), priority(priority), pictureroot(pictureroot)
{}

// Shoes set
void Shoes::set_trend(int x) {
	trend = x;
}
void Shoes::set_priority(int x) {
	priority = x;
}
void Shoes::set_name(std::string name){
	this->name = name;
}
void Shoes::set_w_trend(float w_trend){
	this->w_trend = w_trend;
}
void Shoes::set_w_priority(float w_priority){
	this->w_priority = w_priority;
}

// Shoes get
std::string Shoes::get_name(){
	return name;
}
std::string Shoes::get_style() {
	return style;
}
std::string Shoes::get_color() {
	return color;
}
int Shoes::get_trend(){
	return trend;
}
int Shoes::get_priority(){
	return priority;
}
std::string Shoes::get_pictureroot() {
	return pictureroot;
}

// Shoes other operators
bool Shoes::operator<(const Shoes &other) {
	return ((this->w_priority + this->w_trend) > (other.w_priority + other.w_trend));
}
bool Shoes::operator==(std::string name) {
	return (this->get_name() == name);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Accessory::Accessory() {
	this->set_name("no");
}
Accessory::Accessory(std::string& name, std::string& style, std::string& color, std::string& pictureroot)
:name(name), style(style), color(color), pictureroot(pictureroot)
{}

// Accessory get
std::string Accessory::get_name(){
	return name;
}
std::string Accessory::get_style() {
	return style;
}
std::string Accessory::get_color() {
	return color;
}
std::string Accessory::get_pictureroot() {
	return pictureroot;
}

// Accessory set
void Accessory::set_name(std::string name){
	this->name = name;
}

bool Accessory::operator==(std::string name) {
	return (this->get_name() == name);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Set::Set() {

}
Set::Set(Outer outer, Top top, Pants pants, Overgarment overgarment, Shoes shoes, Accessory accessory) {
	this->outer = outer;
	this->top = top;
	this->pants = pants;
	this->overgarment = overgarment;
	this->shoes = shoes;
	this->accessory = accessory;
}

// Set set
void Set::set_outer(Outer outer) {
	this->outer = outer;
}
void Set::set_top(Top top) {
	this->top = top;
}
void Set::set_pants(Pants pants) {
	this->pants = pants;
}
void Set::set_overgarment(Overgarment overgarment) {
	this->overgarment = overgarment;
}
void Set::set_shoes(Shoes shoes) {
	this->shoes = shoes;
}
void Set::set_accessory(Accessory accessory) {
	this->accessory = accessory;
}

// Set get
Outer Set::get_outer() {
	return this->outer;
}
Top Set::get_top() {
	return this->top;
}
Pants Set::get_pants() {
	return this->pants;
}
Overgarment Set::get_overgarment() {
	return this->overgarment;
}
Shoes Set::get_shoes() {
	return this->shoes;
}
Accessory Set::get_accessory() {
	return this->accessory;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Cordinator::colorSelect(std::string fileName) {
	srand(time(NULL));
	std::fstream colorFile;
	int random = rand() % 126;
	std::string buf1, buf2, buf3, buf4;

	colorFile.open("new_color.txt", std::ios::in);
	if (!colorFile.is_open()) {
		std::cout << "file open error!" << std::endl;
		exit(1);
	}

	for (int i = 0; i < random; i++){
		colorFile >> buf1;
		colorFile >> buf2;
		colorFile >> buf3;
		colorFile >> buf4;
	}

	colorSet[0] = color_stoi(buf1);
	colorSet[1] = color_stoi(buf2);
	colorSet[2] = color_stoi(buf3);
	colorSet[3] = color_stoi(buf4);

	colorFile.close();

}

template<class T>
void Cordinator::color(std::vector<T> &object, int mod){
	std::vector<T>::iterator p = object.begin();
	int i = mod;

	for (p; p != object.end();){
		if (this->colorSet[i] != color_stoi(p->get_color())){
			p = object.erase(p);
		}
		else{
			p++;
		}
	}

}

template<class T>
void Cordinator::weather(std::vector<T> &object, double temp) {
	// 겉옷, 상의 , 바지, 걸치는거 4개만 생각
	std::vector<T>::iterator p = object.begin();
	standard_insulation[0] = 0;
	standard_insulation[1] = 11;

	for (p; p != object.end();) {
		if (temp < 10) {
			standard_insulation[0] = 9;
			if ((p->get_insulation()) < 8) {
				p = object.erase(p);
			}
			else {
				p++;
			}
		}
		else if (temp >= 10 && temp < 15) {
			standard_insulation[0] = 5;
			standard_insulation[1] = 8;
			if ((p->get_insulation()) < 5 || (p->get_insulation()) > 8) {
				p = object.erase(p);
			}
			else {
				p++;
			}
		}
		else if (temp >= 15 && temp < 20) {
			standard_insulation[0] = 3;
			standard_insulation[1] = 6;
			if ((p->get_insulation()) > 6 || (p->get_insulation()) < 3) {
				p = object.erase(p);
			}
			else {
				p++;
			}
		}
		else if (temp >= 20) {
			standard_insulation[1] = 2;
			if ((p->get_insulation()) >= 3) {
				p = object.erase(p);
			}
			else {
				p++;
			}
		}
	}
}

void Cordinator::sortList() {
	sort(outer.begin(), outer.end());
	sort(top.begin(), top.end());
	sort(pants.begin(), pants.end());
	sort(overgarment.begin(), overgarment.end());
	sort(shoes.begin(), shoes.end());
}

void Cordinator::give_weight(int mod){
	if (mod == 1){
		set_weightP(this->outer);
		set_no_weightT(this->outer);
		set_weightP(this->top);
		set_no_weightT(this->top);
		set_weightP(this->pants);
		set_no_weightT(this->pants);
	}
	else if (mod == 2){
		set_weightT(this->outer);
		set_no_weightP(this->outer);
		set_weightT(this->top);
		set_no_weightP(this->top);
		set_weightT(this->pants);
		set_no_weightP(this->pants);
	}
	else{
		set_no_weightT(this->outer);
		set_no_weightP(this->outer);
		set_no_weightT(this->top);
		set_no_weightP(this->top);
		set_no_weightT(this->pants);
		set_no_weightP(this->pants);
	}
}

template<class T>
void Cordinator::set_weightP(std::vector<T> &object){
	weight = 1.4;
	std::vector<T>::iterator p = object.begin();
	for (p; p != object.end();){
		p->set_w_priority((float)(weight * (p->get_priority())));
		p++;
	}
}
template<class T>
void Cordinator::set_weightT(std::vector<T> &object){
	weight = 1.4;
	std::vector<T>::iterator p = object.begin();
	for (p; p != object.end();){
		p->set_w_trend((float)(weight * (p->get_trend())));
		p++;
	}
}

template<class T>
void Cordinator::set_no_weightP(std::vector<T> &object){
	weight = 1;
	std::vector<T>::iterator p = object.begin();
	for (p; p != object.end();){
		p->set_w_priority((float)(weight * (p->get_priority())));
		p++;
	}
}
template<class T>
void Cordinator::set_no_weightT(std::vector<T> &object){
	weight = 1;
	std::vector<T>::iterator p = object.begin();
	for (p; p != object.end();){
		p->set_w_trend((float)(weight * (p->get_trend())));
		p++;
	}
}

std::vector<Set> Cordinator::makeSet() {

	std::vector<Set> final_set;
	Set in;
	int top_thick;
	vec_size = std::min(std::min(top.size(), pants.size()), shoes.size());
	
	for (int i = 0; i < vec_size; i++) {
		if (outer.size() != 0){
			in.set_outer(outer.front());
			outer.erase(outer.begin());
		}
		if (top.size() != 0){
			in.set_top(top.front());
			top_thick = (in.get_top()).get_thickness();
			if (top_thick <= 4) {
				for (it_over = overgarment.begin(); it_over != overgarment.end(); it_over++){
					if ((overgarment.size() != 0) && (((*it_over).get_insulation() >= standard_insulation[0]) && ((*it_over).get_insulation() <= standard_insulation[1]))){
						in.set_overgarment(*it_over);
						overgarment.erase(it_over);
						break;
					}
				}				
			}
			top.erase(top.begin());
		}
		if (pants.size() != 0){
			in.set_pants(pants.front());
			if (in.get_pants().get_style() == "slacks" && (shoes.size() != 0)){
				for (it_shoes = shoes.begin(); it_shoes != shoes.end(); it_shoes++) {
					if ((*it_shoes).get_style() == "dress") {
						in.set_shoes(*it_shoes);
						shoes.erase(it_shoes);
						break;
					}
				}
			}
			else if (in.get_pants().get_length() == "short" && (shoes.size() != 0)){
				for (it_shoes = shoes.begin(); it_shoes != shoes.end(); it_shoes++) {
					if ((*it_shoes).get_style() == "sandal") {
						in.set_shoes(*it_shoes);
						shoes.erase(it_shoes);
						break;
					}
				}
			}
			else if ((shoes.size() != 0) && (shoes.front().get_style() != "sandal" || shoes.front().get_style() != "dress")) {
				in.set_shoes(shoes.front());
				shoes.erase(shoes.begin());
			}
				
			pants.erase(pants.begin());
		}

		if ((in.get_pants()).get_belt()) {
			if (in.get_outer().get_style() == "coat" || in.get_top().get_style() == "shirt"){
				for (it_accessory = accessory.begin(); it_accessory != accessory.end(); it_accessory++) {
					if ((*it_accessory).get_style() == "classic-belt") {
						in.set_accessory(*it_accessory);
						accessory.erase(it_accessory);
						break;
					}
				}
			}
			else{
				for (it_accessory = accessory.begin(); it_accessory != accessory.end(); it_accessory++) {
					if ((*it_accessory).get_style() == "casual-belt"){
						in.set_accessory(*it_accessory);
						accessory.erase(it_accessory);
						break;
					}
				}
			}
		}

		final_set.push_back(in);
	}
	
	return final_set;
	// 각 정렬된 벡터 별 상위 3개의 세트를 만들어서 리턴 

}

int Cordinator::get_vector_size(){
	return vec_size;
}

std::vector<Set> Cordinator::cordinate(std::string colorFileName, double temparature){
	
	std::vector<Set> final_cordi;
	int ctrl = 0;
	vec_initialize(ori_outer, outer);
	vec_initialize(ori_top, top);
	vec_initialize(ori_pants, pants);
	vec_initialize(ori_overgarment, overgarment);
	vec_initialize(ori_shoes, shoes);
	vec_initialize(ori_accessory, accessory);
	
	weather(outer, temparature);
	weather(top, temparature);
	weather(pants, temparature);
	colorSelect(colorFileName);
	color(outer, 0);
	color(top, 1);
	color(pants, 2);
	color(shoes, 3);
	sortList();
	final_cordi = makeSet();

	if (final_cordi.size() > 3){
		while (final_cordi.size() > 3){
			final_cordi.pop_back();
		}		
	}

	return final_cordi;

}
template<class T>
void Cordinator::vec_initialize(std::vector<T> &scr_obj, std::vector<T> &dst_obj){
	
	dst_obj.clear();
	dst_obj.assign(scr_obj.begin(), scr_obj.end());

}

void Cordinator::set_weight(){
	int mode;
	// weight 입력받는 부분
	std::cout << "어느 부분에 더 가중치를 두시겠어요?" << std::endl;
	std::cout << "1. 선호도 / 2. 트렌드 / 3. 안함" << std::endl;
	std::cin >> mode;
	give_weight(mode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void split_getpost(std::string& object_str, std::string delimiter) {
	size_t pos = 0;
	std::string token;
	while ((pos = object_str.find(delimiter)) != std::string::npos) {
		token = object_str.substr(0, pos);
		//std::cout << token << std::endl;
		object_str.erase(0, pos + delimiter.length());
	}

}

void split_getpre(std::string& object_str, std::string delimiter) {
	size_t pos = 0;
	std::string token;
	while ((pos = object_str.find(delimiter)) != std::string::npos) {
		token = object_str.substr(0, pos);
		//std::cout << token << std::endl;
		object_str.erase(pos, pos + object_str.length());
	}

}

int color_stoi(std::string colorName) {
	if (colorName == "white")
		return 0;
	else if (colorName == "navy")
		return 1;
	else if (colorName == "pink")
		return 2;
	else if (colorName == "yellow")
		return 3;
	else if (colorName == "blue")
		return 4;
	else if (colorName == "green")
		return 5;
	else if (colorName == "darkblue")
		return 6;
	else if (colorName == "lightblue")
		return 7;
	else if (colorName == "beige")
		return 8;
	else if (colorName == "khaki")
		return 9;
	else if (colorName == "black")
		return 10;
	else if (colorName == "gray")
		return 11;
	else if (colorName == "brown")
		return 12;
	else
		return -1;
}
