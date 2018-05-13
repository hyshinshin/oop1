#include "coordinate_Sys.h"

//closetmanager::Add_Outer();
void Closet::set_outer() {
	std::string name;	std::string style;
	std::string col;		std::string len;
	int insulation; int trend; int priority;
	std::string texture;
	std::string pictureroot = pictureroot_outer;

	std::fstream fin;
	fin.open("outer profile.txt", std::ios::in);
	if (fin.is_open()) {
		while (!fin.eof())
		{
			fin >> name;		fin >> style;
			fin >> col;			fin >> len;
			fin >> texture;		fin >> insulation;
			fin >> trend; 		fin >> priority;
			Outer_list.push_back(Outer::Outer(name, style, col, len, insulation, trend, priority, texture, pictureroot));
		}
	}
}

void Closet::set_top() {
	std::string name;	std::string style;
	std::string col;		    std::string len;
	int insulation; int trend; int priority;
	int thickness = 0;
	std::string pictureroot = pictureroot_outer;

	std::fstream fin;
	fin.open("top profile.txt", std::ios::in);
	if (fin.is_open()) {
		while (!fin.eof())
		{
			fin >> name;		fin >> style;
			fin >> col;			fin >> len;
			fin >> insulation;	fin >> thickness;
			fin >> trend; 		fin >> priority;
			top_list.push_back(Top::Top(name, style, col, len, insulation, trend, priority, thickness, pictureroot));
		}
	}
}

void Closet::set_pants() {
	std::string name;	std::string style;
	std::string col;	std::string len;
	int insulation; int trend; int priority;
	bool belt;
	std::string pictureroot = pictureroot_pants;

	std::fstream fin;
	fin.open("pants profile.txt", std::ios::in);
	if (fin.is_open()) {
		while (!fin.eof())
		{
			fin >> name;		fin >> style;
			fin >> col;			fin >> len;
			fin >> insulation;	fin >> belt;
			fin >> trend;		fin >> priority;
			pants_list.push_back(Pants::Pants(name, style, col, len, insulation, trend, priority, belt, pictureroot));
		}
	}
}

void Closet::set_shoes() {
	std::string name;	std::string style;
	std::string col;
	int trend; int priority;
	std::string pictureroot = pictureroot_shoes;

	std::fstream fin;
	fin.open("shoes profile.txt", std::ios::in);
	if (fin.is_open()) {
		while (!fin.eof())
		{
			fin >> name;		fin >> style;
			fin >> col;			
			fin >> trend; 		fin >> priority;
			shoes_list.push_back(Shoes::Shoes(name, style, col, trend, priority, pictureroot));
		}
	}
}

void Closet::set_accessory() {
	std::string name;	std::string style;
	std::string col;
	std::string pictureroot = pictureroot_accessory;

	std::fstream fin;
	fin.open("accessory profile.txt", std::ios::in);
	if (fin.is_open()) {
		while (!fin.eof())
		{
			fin >> name;		fin >> style;
			fin >> col;
			accessory_list.push_back(Accessory::Accessory(name, style, col, pictureroot));
		}
	}
}

void Closet::set_overgarment() {
	std::string name;	std::string style;
	std::string col;	std::string len;
	int insulation; int trend; int priority;
	std::string pictureroot = pictureroot_overgarment;

	std::fstream fin;
	fin.open("overgarment profile.txt", std::ios::in);
	if (fin.is_open()) {
		while (!fin.eof())
		{
			fin >> name;		fin >> style;
			fin >> col;			fin >> len;
			fin >> insulation;	fin >> trend;
			fin >> priority;
			overgarment_list.push_back(Overgarment::Overgarment(name, style, col, len, insulation, trend, priority, pictureroot));
		}
	}
}

std::vector<Outer> Closet::get_outer() {
	return Outer_list;
}

std::vector<Top> Closet::get_top() {
	return top_list;
}

std::vector<Pants> Closet::get_pants() {
	return pants_list;
}

std::vector<Shoes> Closet::get_shoes() {
	return shoes_list;
}

std::vector<Accessory> Closet::get_accessory() {
	return accessory_list;
}

std::vector<Overgarment> Closet::get_overgarment() {
	return overgarment_list;
}

void Closetmanager::Add_outer(Outer x) {
	Closet open;
	open.set_outer();
	std::vector<Outer> outer_list = open.get_outer();
	outer_list.push_back(x);

	std::fstream fout;
	fout.open("outer profile.txt", std::ios::out);
	if (fout.is_open()) {
		for (unsigned int i = 0; i < outer_list.size(); i++) {
			if (i == outer_list.size() - 1) {
				fout << outer_list[i].get_name() << " " << outer_list[i].get_style() << " " << outer_list[i].get_color() << " " 
					<< outer_list[i].get_length() << " " << outer_list[i].get_texture() << " " << outer_list[i].get_insulation() << " " 
					<< outer_list[i].get_trend() << " " << outer_list[i].get_priority();
			}
			else {
				fout << outer_list[i].get_name() << " " << outer_list[i].get_style() << " " << outer_list[i].get_color() << " "
					<< outer_list[i].get_length() << " " << outer_list[i].get_texture() << " " << outer_list[i].get_insulation() << " "
					<< outer_list[i].get_trend() << " " << outer_list[i].get_priority() << std::endl;
			}
		}
	}
}

void Closetmanager::Add_top(Top x) {
	Closet open;
	open.set_top();
	std::vector<Top> top_list = open.get_top();
	top_list.push_back(x);

	std::fstream fout;
	fout.open("top profile.txt", std::ios::out);
	if (fout.is_open()) {
		for (unsigned int i = 0; i < top_list.size(); i++) {
			if (i == top_list.size() - 1) {
				fout << top_list[i].get_name() << " " << top_list[i].get_style() << " " << top_list[i].get_color() << " "
					<< top_list[i].get_length() << " " << top_list[i].get_insulation() << " "; fout << top_list[i].get_thickness() << " "
					<< top_list[i].get_trend() << " ";		fout << top_list[i].get_priority();
			}
			else {
				fout << top_list[i].get_name() << " " << top_list[i].get_style() << " " << top_list[i].get_color() << " "
					<< top_list[i].get_length() << " " << top_list[i].get_insulation() << " "; fout << top_list[i].get_thickness() << " "
					<< top_list[i].get_trend() << " ";		fout << top_list[i].get_priority() << std::endl;
			}
		}
	}
}

void Closetmanager::Add_pants(Pants x) {
	Closet open;
	open.set_pants();
	std::vector<Pants> pants_list = open.get_pants();
	pants_list.push_back(x);

	std::fstream fout;
	fout.open("pants profile.txt", std::ios::out);
	if (fout.is_open()) {
		for (unsigned int i = 0; i < pants_list.size(); i++) {
			if (i == pants_list.size() - 1) {
				fout << pants_list[i].get_name() << " " << pants_list[i].get_style() << " " << pants_list[i].get_color() << " "
					<< pants_list[i].get_length() << " " << pants_list[i].get_insulation() << " " << pants_list[i].get_belt() << " "
					<< pants_list[i].get_trend() << " " << pants_list[i].get_priority();
			}
			else {
				fout << pants_list[i].get_name() << " " << pants_list[i].get_style() << " " << pants_list[i].get_color() << " "
					<< pants_list[i].get_length() << " " << pants_list[i].get_insulation() << " " << pants_list[i].get_belt() << " "
					<< pants_list[i].get_trend() << " " << pants_list[i].get_priority() << std::endl;
			}
		}
	}
}

void Closetmanager::Add_shoes(Shoes x) {
	Closet open;
	open.set_shoes();
	std::vector<Shoes> shoes_list = open.get_shoes();
	shoes_list.push_back(x);

	std::fstream fout;
	fout.open("shoes profile.txt", std::ios::out);
	if (fout.is_open()) {
		for (unsigned int i = 0; i < shoes_list.size(); i++) {
			if (i == shoes_list.size() - 1) {
				fout << shoes_list[i].get_name() << " " << shoes_list[i].get_style() << " " << shoes_list[i].get_color() << " "
					<< shoes_list[i].get_trend() << " " << shoes_list[i].get_priority();
			}
			else {
				fout << shoes_list[i].get_name() << " " << shoes_list[i].get_style() << " " << shoes_list[i].get_color() << " "
					<< shoes_list[i].get_trend() << " " << shoes_list[i].get_priority() << std::endl;
			}
		}
	}
}

void Closetmanager::Add_accessory(Accessory x) {
	Closet open;
	open.set_accessory();
	std::vector<Accessory> accessory_list = open.get_accessory();
	accessory_list.push_back(x);

	std::fstream fout;
	fout.open("accessory profile.txt", std::ios::out);
	if (fout.is_open()) {
		for (unsigned int i = 0; i < accessory_list.size(); i++) {
			if (i == accessory_list.size() - 1) {
				fout << accessory_list[i].get_name() << " " << accessory_list[i].get_style() << " "
					<< accessory_list[i].get_color() << " ";
			}
			else {
				fout << accessory_list[i].get_name() << " " << accessory_list[i].get_style() << " "
					<< accessory_list[i].get_color() << " " << std::endl;
			}
		}
	}
}

void Closetmanager::Add_overgarment(Overgarment x) {
	Closet open;
	open.set_overgarment();
	std::vector<Overgarment> overgarment_list = open.get_overgarment();
	overgarment_list.push_back(x);

	std::fstream fout;
	fout.open("overgarment profile.txt", std::ios::out);
	if (fout.is_open()) {
		for (unsigned int i = 0; i < overgarment_list.size(); i++) {
			if (i == overgarment_list.size() - 1) {
				fout << overgarment_list[i].get_name() << " " << overgarment_list[i].get_style() << " " << overgarment_list[i].get_color() << " " << overgarment_list[i].get_length()
					<< " " << overgarment_list[i].get_insulation() << " " << overgarment_list[i].get_trend() << " " << overgarment_list[i].get_priority();
			}
			else {
				fout << overgarment_list[i].get_name() << " " << overgarment_list[i].get_style() << " " << overgarment_list[i].get_color() << " " << overgarment_list[i].get_length()
					<< " " << overgarment_list[i].get_insulation() << " " << overgarment_list[i].get_trend() << " " << overgarment_list[i].get_priority() << std::endl;
			}
		}
	}
}

void Closetmanager::delete_outer(std::string name) {
	Closet open;
	open.set_outer();
	std::vector<Outer> outer_list = open.get_outer();
	std::vector<Outer>::iterator p;
	p = find(outer_list.begin(), outer_list.end(), name);
	if (p != outer_list.end()) {
		p = outer_list.erase(p);

		std::fstream fout;
		fout.open("outer profile.txt", std::ios::out);
		if (fout.is_open()) {
			for (unsigned int i = 0; i < outer_list.size(); i++) {
				if (i == outer_list.size() - 1) {
					fout << outer_list[i].get_name() << " " << outer_list[i].get_style() << " " << outer_list[i].get_color() << " "
						<< outer_list[i].get_length() << " " << outer_list[i].get_texture() << " " << outer_list[i].get_insulation() << " "
						<< outer_list[i].get_trend() << " " << outer_list[i].get_priority();
				}
				else {
					fout << outer_list[i].get_name() << " " << outer_list[i].get_style() << " " << outer_list[i].get_color() << " "
						<< outer_list[i].get_length() << " " << outer_list[i].get_texture() << " " << outer_list[i].get_insulation() << " "
						<< outer_list[i].get_trend() << " " << outer_list[i].get_priority() << std::endl;
				}
			}
		}
	}
	else std::cout << name << " is not exsist in list!" << std::endl;
}

void Closetmanager::delete_top(std::string name) {
	Closet open;
	open.set_top();
	std::vector<Top> top_list = open.get_top();
	std::vector<Top>::iterator p;
	p = find(top_list.begin(), top_list.end(), name);
	if (p != top_list.end()) {
		//p = top_list.erase(p);

		std::fstream fout;
		fout.open("top profile.txt", std::ios::out);
		if (fout.is_open()) {
			for (unsigned int i = 0; i < top_list.size(); i++) {
				if (i == top_list.size() - 1) {
					fout << top_list[i].get_name() << " " << top_list[i].get_style() << " " << top_list[i].get_color() << " "
						<< top_list[i].get_length() << " " << top_list[i].get_insulation() << " "; fout << top_list[i].get_thickness() << " "
						<< top_list[i].get_trend() << " ";		fout << top_list[i].get_priority();
				}
				else {
					fout << top_list[i].get_name() << " " << top_list[i].get_style() << " " << top_list[i].get_color() << " "
						<< top_list[i].get_length() << " " << top_list[i].get_insulation() << " "; fout << top_list[i].get_thickness() << " "
						<< top_list[i].get_trend() << " ";		fout << top_list[i].get_priority() << std::endl;
				}
			}
		}
	}
	else std::cout << name << " is not exsist in list!" << std::endl;
}
void Closetmanager::delete_pants(std::string name) {
	Closet open;
	open.set_pants();
	std::vector<Pants> pants_list = open.get_pants();
	std::vector<Pants>::iterator p;
	p = find(pants_list.begin(), pants_list.end(), name);
	if (p != pants_list.end()) {
		//p = pants_list.erase(p);

		std::fstream fout;
		fout.open("pants profile.txt", std::ios::out);
		if (fout.is_open()) {
			for (unsigned int i = 0; i < pants_list.size(); i++) {
				if (i == pants_list.size() - 1) {
					fout << pants_list[i].get_name() << " " << pants_list[i].get_style() << " " << pants_list[i].get_color() << " "
						<< pants_list[i].get_length() << " " << pants_list[i].get_insulation() << " " << pants_list[i].get_belt() << " "
						<< pants_list[i].get_trend() << " " << pants_list[i].get_priority();
				}
				else {
					fout << pants_list[i].get_name() << " " << pants_list[i].get_style() << " " << pants_list[i].get_color() << " "
						<< pants_list[i].get_length() << " " << pants_list[i].get_insulation() << " " << pants_list[i].get_belt() << " "
						<< pants_list[i].get_trend() << " " << pants_list[i].get_priority() << std::endl;
				}
			}
		}
	}
	else std::cout << name << " is not exsist in list!" << std::endl;
}

void Closetmanager::delete_shoes(std::string name) {
	Closet open;
	open.set_shoes();
	std::vector<Shoes> shoes_list = open.get_shoes();
	std::vector<Shoes>::iterator p;
	p = find(shoes_list.begin(), shoes_list.end(), name);
	if (p != shoes_list.end()) {
		p = shoes_list.erase(p);

		std::fstream fout;
		fout.open("shoes profile.txt", std::ios::out);
		if (fout.is_open()) {
			for (unsigned int i = 0; i < shoes_list.size(); i++) {
				if (i == shoes_list.size() - 1) {
					fout << shoes_list[i].get_name() << " " << shoes_list[i].get_style() << " " << shoes_list[i].get_color() << " "
						<< shoes_list[i].get_trend() << " " << shoes_list[i].get_priority();
				}
				else {
					fout << shoes_list[i].get_name() << " " << shoes_list[i].get_style() << " " << shoes_list[i].get_color() << " "
						<< shoes_list[i].get_trend() << " " << shoes_list[i].get_priority() << std::endl;
				}
			}
		}
	}
	else std::cout << name << " is not exsist in list!" << std::endl;
}

void Closetmanager::delete_accessory(std::string name) {
	Closet open;
	open.set_accessory();
	std::vector<Accessory> accessory_list = open.get_accessory();
	std::vector<Accessory>::iterator p;
	p = find(accessory_list.begin(), accessory_list.end(), name);
	if (p != accessory_list.end()) {
		p = accessory_list.erase(p);

		std::fstream fout;
		fout.open("accessory profile.txt", std::ios::out);
		if (fout.is_open()) {
			for (unsigned int i = 0; i < accessory_list.size(); i++) {
				if (i == accessory_list.size() - 1) {
					fout << accessory_list[i].get_name() << " " << accessory_list[i].get_style() << " "
						<< accessory_list[i].get_color() << " ";
				}
				else {
					fout << accessory_list[i].get_name() << " " << accessory_list[i].get_style() << " "
						<< accessory_list[i].get_color() << " " << std::endl;
				}
			}
		}
	}
	else std::cout << name << " is not exsist in list!" << std::endl;
}

void Closetmanager::delete_overgarment(std::string name) {
	Closet open;
	open.set_overgarment();
	std::vector<Overgarment> overgarment_list = open.get_overgarment();
	std::vector<Overgarment>::iterator p;
	p = find(overgarment_list.begin(), overgarment_list.end(), name);
	if (p != overgarment_list.end()) {
		p = overgarment_list.erase(p);

		std::fstream fout;
		fout.open("overgarment profile.txt", std::ios::out);
		if (fout.is_open()) {
			for (unsigned int i = 0; i < overgarment_list.size(); i++) {
				if (i == overgarment_list.size() - 1) {
					fout << overgarment_list[i].get_name() << " " << overgarment_list[i].get_style() << " " << overgarment_list[i].get_color() << " " << overgarment_list[i].get_length()
						<< " " << overgarment_list[i].get_insulation() << " " << overgarment_list[i].get_trend() << " " << overgarment_list[i].get_priority();
				}
				else {
					fout << overgarment_list[i].get_name() << " " << overgarment_list[i].get_style() << " " << overgarment_list[i].get_color() << " " << overgarment_list[i].get_length()
						<< " " << overgarment_list[i].get_insulation() << " " << overgarment_list[i].get_trend() << " " << overgarment_list[i].get_priority() << std::endl;
				}
			}
		}
	}
	else std::cout << name << " is not exsist in list!" << std::endl;
}

void Closetmanager::print_clothes(int type) {
	
	
	Closet closet;
	if (type == 1){
		closet.set_outer();
		std::vector<Outer> outer_list = closet.get_outer();
		std::cout << std::left << std::setw(10) << "이름" << std::setw(16) << "스타일" << std::setw(10) << "색" << std::setw(10) << "길이" << std::setw(10) << "재질" << std::setw(14) << "보온성" << std::setw(10) << "트렌드" << std::setw(8) << "선호도" << std::endl;
		for (unsigned int i = 0; i < outer_list.size(); i++)
			std::cout << std::left << std::setw(10) << outer_list[i].get_name() << std::setw(16) << outer_list[i].get_style() << std::setw(10) << outer_list[i].get_color() << std::setw(10) << outer_list[i].get_length() << std::setw(10) << outer_list[i].get_texture() << std::setw(14) << outer_list[i].get_insulation() << std::setw(10) << outer_list[i].get_trend() << std::setw(8) << outer_list[i].get_priority() << std::endl;
	}
	else if (type == 2) {
		closet.set_top();
		std::vector<Top> top_list = closet.get_top();
		std::cout << std::left << std::setw(10) << "이름" << std::setw(16) << "스타일" << std::setw(10) << "색" << std::setw(10) << "길이" << std::setw(10) << "두께" << std::setw(14) << "보온성" << std::setw(10) << "트렌드" << std::setw(8) << "선호도" << std::endl;
		for (unsigned int i = 0; i < top_list.size(); i++)
			std::cout << std::left << std::setw(10) << top_list[i].get_name() << std::setw(16) << top_list[i].get_style() << std::setw(10) << top_list[i].get_color() << std::setw(10) << top_list[i].get_length() << std::setw(10) << top_list[i].get_thickness() << std::setw(14) << top_list[i].get_insulation() << std::setw(10) << top_list[i].get_trend() << std::setw(8) << top_list[i].get_priority() << std::endl;
	}
	else if (type == 3) {
		closet.set_pants();
		std::vector<Pants> pants_list = closet.get_pants();
		std::cout << std::left << std::setw(10) << "이름" << std::setw(16) << "스타일" << std::setw(10) << "색" << std::setw(10) << "길이" << std::setw(6) << "벨트" << std::setw(14) << "보온성" << std::setw(10) << "트렌드" << std::setw(8) << "선호도" << std::endl;
		for (unsigned int i = 0; i < pants_list.size(); i++)
			std::cout << std::left << std::setw(10) << pants_list[i].get_name() << std::setw(16) << pants_list[i].get_style() << std::setw(10) << pants_list[i].get_color() << std::setw(10) << pants_list[i].get_length() << std::setw(6) << pants_list[i].get_belt() << std::setw(14) << pants_list[i].get_insulation() << std::setw(10) << pants_list[i].get_trend() << std::setw(8) << pants_list[i].get_priority() << std::endl;
	}
	else if (type == 4) {
		closet.set_accessory();
		std::vector<Accessory> accessory_list = closet.get_accessory();
		std::cout << std::left << std::setw(14) << "이름" << std::setw(20) << "스타일" << std::setw(10) << "색" << std::endl;
		for (unsigned int i = 0; i < accessory_list.size(); i++)
			std::cout << std::left << std::setw(14) << accessory_list[i].get_name() << std::setw(20) << accessory_list[i].get_style() << std::setw(10) << accessory_list[i].get_color() << std::endl;
	}
	else if (type == 5) {
		closet.set_shoes();
		std::vector<Shoes> shoes_list = closet.get_shoes();
		std::cout << std::left << std::setw(12) << "이름" << std::setw(16) << "스타일" << std::setw(10) << "색" << std::setw(10) << "트렌드" << std::setw(8) << "선호도" << std::endl;
		for (unsigned int i = 0; i < shoes_list.size(); i++)
			std::cout << std::left << std::setw(12) << shoes_list[i].get_name() << std::setw(16) << shoes_list[i].get_style() << std::setw(10) << shoes_list[i].get_color() << std::setw(10) << shoes_list[i].get_trend() << std::setw(8) << shoes_list[i].get_priority() << std::endl;
	}
	else if (type == 6) {
		closet.set_overgarment();
		std::vector<Overgarment> overgarment_list = closet.get_overgarment();
		std::cout << std::left << std::setw(16) << "이름" << std::setw(16) << "스타일" << std::setw(10) << "색" << std::setw(14) << "보온성" << std::setw(10) << "트렌드" << std::setw(8) << "선호도" << std::endl;
		for (unsigned int i = 0; i < overgarment_list.size(); i++)
			std::cout << std::left << std::setw(16) << overgarment_list[i].get_name() << std::setw(16) << overgarment_list[i].get_style() << std::setw(10) << overgarment_list[i].get_color() << std::setw(14) << overgarment_list[i].get_insulation() << std::setw(10) << overgarment_list[i].get_trend() << std::setw(8) << overgarment_list[i].get_priority() << std::endl;
	}
	else std::cout << "일치하는 형태의 옷을 찾을 수 없습니다." << std::endl;
}