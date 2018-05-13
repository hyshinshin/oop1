#include "coordinate_Sys.h"
#pragma comment(lib,"winmm.lib")

int main() {
	//노래
	PlaySound(TEXT(SOUND_FILE_NAME),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	//처음 에 날씨 가져오고
	auto fileStream = std::make_shared<ostream>();

	// Open stream to output file.
	pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
	{
		*fileStream = outFile;

		// Create http_client to send the request.
		http_client client(U("http://www.kweather.co.kr/forecast/forecast_lifestyle.html"));

		// Build request URI and start the request.
		uri_builder builder(U("/search"));
		builder.append_query(U("q"), U("Casablanca CodePlex"));
		return client.request(methods::GET, builder.to_string());
	})

		// Handle response headers arriving.
		.then([=](http_response response)
	{
		//printf("Received response status code:%u\n", response.status_code());

		// Write response body into the file.
		return response.body().read_to_end(fileStream->streambuf());
	})

		// Close the file stream.
		.then([=](size_t)
	{
		return fileStream->close();
	});

	// Wait for all the outstanding I/O to complete and handle any exceptions
	try
	{
		requestTask.wait();
	}
	catch (const std::exception &e)
	{
		printf("Error exception:%s\n", e.what());
	}
	//file IO


	std::string line;


	std::fstream inputfile("results.html");

	std::string comp = "<li class=\"lifestyle_map_se\">";//se == seoul
	std::string object_str;
	if (inputfile.is_open()) {

		while (getline(inputfile, line)) {
			if (line.find(comp) != std::string::npos) {
				object_str = line;
				break;
			}
		}

		inputfile.close();
	}
	else {
		std::cout << "unable to open the file" << std::endl;
	}



	std::string delimiter = "<span>";

	split_getpost(object_str, delimiter);

	delimiter = "/span>";
	split_getpre(object_str, delimiter);

	object_str.erase(3, 5);
	//std::cout << object_str << std::endl;

	double temperature = stod(object_str);


	//temperature = 28; //여름
	//temperature = 18; //초가을
	//temperature = 10;//늦가을
	//temperature = -4; //한겨울

	//데이타 생성 및  메인
	int menuchoice = 0;
	int managechoice = 0;
	int cate = 0;
	Closet a;
	Closetmanager m;
	std::string c_name;
	a.set_outer();
	a.set_top();
	a.set_pants();
	a.set_overgarment();
	a.set_shoes();
	a.set_accessory();
	std::vector<Outer> vec_outer = a.get_outer();
	std::vector<Pants> vec_pants = a.get_pants();
	std::vector<Top>   vec_top = a.get_top();
	std::vector<Shoes> vec_shoes = a.get_shoes();
	std::vector<Overgarment> vec_overgarment = a.get_overgarment();
	std::vector<Accessory> vec_accessory = a.get_accessory();

	std::string t_name;
	std::string style;
	std::string col;
	std::string len;

	int insulation;
	int trend;
	int priority;
	int catego = 0;
	std::string texture;
	std::string pictureroot;
	int thickness;
	bool belt;
	char savefile[128];
	VideoCapture cap(0);
	char Esc = 0;
	Mat save_img;

	int checknum = 0;
	int count = 0;
	int check = 0;
	char* std_image = STANDARD_IMAGE;

	Mat std_img = imread(std_image);

	std::vector<Set> result;


	Cordinator cordi(vec_outer, vec_top, vec_pants, vec_overgarment, vec_shoes, vec_accessory);

	/*
	std::string sname = "outer1";
	std::string style2 = "coat";
	std::string len2 = "long";
	std::string col2 = "black";
	std::string texture2 = "coat";
	std::string sroot = pictureroot_outer;
	Outer Outer1(sname, style2, col2, len2, 6, 5, 4, texture2, sroot);

	sname = "tops1";
	sroot = pictureroot_top;
	Top top(sname, style2, col2, len2, 6, 5, 4, 4, sroot);
	sname = "pants1";
	sroot = pictureroot_pants;

	Pants pants(sname, style2, col2, len2, 6, 5, 4, 4, sroot);

	sname = "shoes1";
	sroot = pictureroot_shoes;

	Shoes shoes(sname, style2, col2, 4, 5, sroot);
	Set set1(Outer1, top, pants, shoes);
	*/
	//result = set1;

	//std::string tt = result.get_outer().get_name();
	std::string out_name;
	std::string ove_name;
	std::string top_name;
	std::string pants_name;
	std::string shoes_name;
	std::string acc_name;
	int coordicheck=0;

	std::cout << "**********Wellcome to Daily Look Coordinator System!**********\n" << std::endl;
	std::cout << "*데일리룩 코디네이터 시스템은 트렌드와 당신의 선호도를 바탕으로 코디합니다*\n" << std::endl;
	std::cout << "****데일리룩 코디네이터의 추천된 옷을 입고 자신있는 하루를 시작하세요****\n" << std::endl;

	while (1) {

		std::cout << "--------------MENU------------- " << std::endl;
		std::cout << "1.나의 옷장관리" << std::endl;
		std::cout << "2.현재 온도 확인" << std::endl;
		std::cout << "3.데일리룩 코디 보기" << std::endl;
		std::cout << "4.데일리룩 코디네이터 시스템 종료" << std::endl;

		std::cin >> menuchoice;
		std::cout << std::endl;

		switch (menuchoice)
		{
		case 1://옷장관리
			std::cout << "당신의 옷장을 관리합니다" << std::endl;
			std::cout << "1.추가하기 " << std::endl;
			std::cout << "2.삭제하기 " << std::endl;
			std::cout << "3.옷조회하기" << std::endl;
			std::cout << "4.나가기" << std::endl;
			std::cin >> managechoice;
			std::cout << std::endl;




			if (managechoice == 1) { //추가
				std::cout << "추가하려는 옷의 종류를 입력해주세요 1.아우터 2.겉옷 3.상의 4.하의 5.신발 6.악세사리" << std::endl;
				std::cin >> cate;

				if (cate == 1) {//outer

					std::cout << "아우터의 이름을 입력해주세요 ex)outer# " << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "아우터의 스타일을 입력해주세요 " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "아우터의 색상을 입력해주세요 " << std::endl;
					std::cin >> col;
					std::cout << std::endl;

					std::cout << "아우터의 길이를 입력해주세요 " << std::endl;
					std::cin >> len;
					std::cout << std::endl;

					std::cout << "아우터의 보온성을 입력해주세요(1~10) " << std::endl;
					std::cin >> insulation;
					std::cout << std::endl;

					std::cout << "아우터의 트렌드를 입력해주세요(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "아우터의 당신의 선호도를 입력해주세요(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;

					std::cout << "아우터의 옷감를 입력해주세요" << std::endl;
					std::cin >> texture;
					std::cout << std::endl;

					std::string t_str = pictureroot_outer;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Outer temp_outer(t_name, style, col, len, insulation, trend, priority, texture, pr);

					m.Add_outer(temp_outer);

					std::cout << "아우터 사진촬영을 하겠습니다.!!      준비하시고~ ESC 쏘세요! " << std::endl;

					//Sleep(1.00);

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC 누르면 저장!

					}
					;
					char *temp_name = new char[t_name.length() + 30];


					strcpy(temp_name, t_name.c_str());



					std::string format = ".jpg";
					strcat(temp_name, format.c_str());

					strcat(pic_root, temp_name);



					sprintf_s(savefile, pic_root);




					resize(save_img, save_img, std_img.size());


					imwrite(savefile, save_img);


					cvDestroyWindow("imgOriginal");

					delete[] pic_root;
					delete[] temp_name;

				}
				else if (cate == 2) {//overgarment
					//std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority
					std::cout << "겉옷의 이름을 입력해주세요 ex)overgarment#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "겉옷의 스타일을 입력해주세요 " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "겉옷의 색상을 입력해주세요 " << std::endl;
					std::cin >> col;
					std::cout << std::endl;

					std::cout << "겉옷의 길이을 입력해주세요 " << std::endl;
					std::cin >> len;
					std::cout << std::endl;

					std::cout << "겉옷의 보온성을 입력해주세요(1~10) " << std::endl;
					std::cin >> insulation;
					std::cout << std::endl;

					std::cout << "겉옷의 트렌드를 입력해주세요(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "겉옷의 당신의 선호도를 입력해주세요(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;



					std::string t_str = pictureroot_overgarment;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Overgarment temp_over(t_name, style, col, len, insulation, trend, priority, pr);

					m.Add_overgarment(temp_over);

					std::cout << "겉옷의 사진촬영을 하겠습니다. 준비하시고~~~ ESC 쏘세요! " << std::endl;

					//Sleep(1.00);

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC 누르면 저장!

					}
					;
					char *temp_name = new char[t_name.length() + 30];


					strcpy(temp_name, t_name.c_str());



					std::string format = ".jpg";
					strcat(temp_name, format.c_str());

					strcat(pic_root, temp_name);



					sprintf_s(savefile, pic_root);

					resize(save_img, save_img, std_img.size());
					imwrite(savefile, save_img);
					cvDestroyWindow("imgOriginal");

					delete[] pic_root;
					delete[] temp_name;
				}
				else if (cate == 3) {//상의
					std::cout << "상의의 이름을 입력해주세요 ex)tops#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "상의의 스타일을 입력해주세요 " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "상의의 색상을 입력해주세요 " << std::endl;
					std::cin >> col;
					std::cout << std::endl;

					std::cout << "상의의 길이을 입력해주세요 " << std::endl;
					std::cin >> len;
					std::cout << std::endl;

					std::cout << "상의의 보온성을 입력해주세요(1~10) " << std::endl;
					std::cin >> insulation;
					std::cout << std::endl;

					std::cout << "상의의 트렌드를 입력해주세요(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "상의의 당신의 선호도를 입력해주세요(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;

					std::cout << "상의의 두께를 입력해주세요(1~10) " << std::endl;
					std::cin >> thickness;
					std::cout << std::endl;

					std::string t_str = pictureroot_top;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Top temp_top(t_name, style, col, len, insulation, trend, priority, thickness, pr);

					m.Add_top(temp_top);

					std::cout << "상의 사진촬영을 하겠습니다. 준비하시고~~~~~~ ESC 쏘세요! " << std::endl;

					//Sleep(1.00);

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC 누르면 저장!

					}
					;
					char *temp_name = new char[t_name.length() + 30];


					strcpy(temp_name, t_name.c_str());



					std::string format = ".jpg";
					strcat(temp_name, format.c_str());

					strcat(pic_root, temp_name);



					sprintf_s(savefile, pic_root);
					resize(save_img, save_img, std_img.size());
					imwrite(savefile, save_img);
					cvDestroyWindow("imgOriginal");

					delete[] pic_root;
					delete[] temp_name;

				}
				else if (cate == 4) {//하의
					//Pants(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, bool belt, std::string& pictureroot);

					std::cout << "하의의 이름을 입력해주세요 ex)pants#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "하의의 스타일을 입력해주세요 " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "하의의 색상을 입력해주세요 " << std::endl;
					std::cin >> col;
					std::cout << std::endl;

					std::cout << "하의의 길이을 입력해주세요 " << std::endl;
					std::cin >> len;
					std::cout << std::endl;

					std::cout << "하의의 보온성을 입력해주세요(1~10) " << std::endl;
					std::cin >> insulation;
					std::cout << std::endl;

					std::cout << "하의의 트렌드를 입력해주세요(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "하의의 당신의 선호도를 입력해주세요(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;

					std::cout << "하의의 벨트가 필요하면 1 아니면 0을 입력해주세요 " << std::endl;
					std::cin >> belt;
					std::cout << std::endl;

					std::string t_str = pictureroot_pants;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Pants temp_pants(t_name, style, col, len, insulation, trend, priority, belt, pr);

					m.Add_pants(temp_pants);

					std::cout << "하의 사진촬영을 하겠습니다. 준비하시고~~~~ ESC 쏘세요! " << std::endl;

					//Sleep(1.00);

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC 누르면 저장!

					}
					;
					char *temp_name = new char[t_name.length() + 30];


					strcpy(temp_name, t_name.c_str());



					std::string format = ".jpg";
					strcat(temp_name, format.c_str());

					strcat(pic_root, temp_name);



					sprintf_s(savefile, pic_root);
					resize(save_img, save_img, std_img.size());
					imwrite(savefile, save_img);
					cvDestroyWindow("imgOriginal");

					delete[] pic_root;
					delete[] temp_name;

				}
				else if (cate == 5) {//신발 std::string& name, std::string& style, std::string& color, int trend, int priority, std::string& pictureroot);
					std::cout << "신발의 이름을 입력해주세요 ex)shoes#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "신발의 스타일을 입력해주세요 " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "신발의 색상을 입력해주세요 " << std::endl;
					std::cin >> col;
					std::cout << std::endl;


					std::cout << "신발의 트렌드를 입력해주세요(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "신발의 당신의 선호도를 입력해주세요(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;

					std::string t_str = pictureroot_shoes;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Shoes temp_shoes(t_name, style, col, trend, priority, pr);

					//m.Add_shoes(temp_shoes);

					std::cout << "신발 사진촬영을 하겠습니다. 준비하시고~ ESC 쏘세요! " << std::endl;

					//sleep

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC 누르면 저장!

					}
					;
					char *temp_name = new char[t_name.length() + 30];


					strcpy(temp_name, t_name.c_str());



					std::string format = ".jpg";
					strcat(temp_name, format.c_str());

					strcat(pic_root, temp_name);



					sprintf_s(savefile, pic_root);
					resize(save_img, save_img, std_img.size());
					imwrite(savefile, save_img);
					cvDestroyWindow("imgOriginal");

					delete[] pic_root;
					delete[] temp_name;
				}
				else if (cate == 6) {
					std::cout << "악세사리의 이름을 입력해주세요 ex)accessory#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "악세사리의 스타일을 입력해주세요 " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "악세사리의 색상을 입력해주세요 " << std::endl;
					std::cin >> col;
					std::cout << std::endl;




					std::string t_str = pictureroot_shoes;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Accessory temp_acc(t_name, style, col, pr);

					//m.Add_accessory(temp_acc);

					std::cout << "악세사리의 사진촬영을 하겠습니다. 준비하시고~ ESC 쏘세요! " << std::endl;

					//sleep

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC 누르면 저장!

					}
					;
					char *temp_name = new char[t_name.length() + 30];


					strcpy(temp_name, t_name.c_str());



					std::string format = ".jpg";
					strcat(temp_name, format.c_str());

					strcat(pic_root, temp_name);



					sprintf_s(savefile, pic_root);
					resize(save_img, save_img, std_img.size());
					imwrite(savefile, save_img);
					cvDestroyWindow("imgOriginal");

					delete[] pic_root;
					delete[] temp_name;
				}



			}

			else if (managechoice == 2) { /////삭제
				std::cout << "삭제할 옷의 종류을 입력하세요 1.아우터 2.겉옷 3.상의 4.하의 5.신발 6.악세사리" << std::endl;
				std::cin >> catego;
				std::cout << std::endl;

				if (catego == 1) {//outer 
					std::cout << "삭제할 아우터의 이름을 입력하세요 ex) outer1" << std::endl;
					std::cin >> out_name;
					std::cout << std::endl;
					m.delete_outer(out_name);
					
					std::string t_str = pictureroot_outer;
					char * pic_root= new char[t_str.size() + 1024];

					strcpy(pic_root, t_str.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name = new char[out_name.length() + 1024];


					strcpy(temp_name, out_name.c_str());


					std::string jpg = ".jpg";
					strcat(temp_name, jpg.c_str());

					strcat(pic_root, temp_name);
					remove(pic_root);
					delete[] pic_root;
					delete[] temp_name;
					
				}

				else if (catego == 2) {//overgarment 
					std::cout << "삭제할  겉옷의 이름을 입력하세요 ex) overgarment1" << std::endl;
					std::cin >> ove_name;
					std::cout << std::endl;
					m.delete_overgarment(ove_name);
					
					std::string t_str = pictureroot_overgarment;
					char * pic_root = new char[t_str.size() + 1024];

					strcpy(pic_root, t_str.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name = new char[ove_name.length() + 1024];


					strcpy(temp_name, ove_name.c_str());


					std::string jpg = ".jpg";
					strcat(temp_name, jpg.c_str());

					strcat(pic_root, temp_name);
					remove(pic_root);
					delete[] pic_root;
					delete[] temp_name;

				}
				else if (catego == 3) {//tops
					std::cout << "삭제할 상의의 이름을 입력하세요 ex) tops1" << std::endl;
					std::cin >> top_name;
					std::cout << std::endl;
					m.delete_top(top_name);
					std::string t_str = pictureroot_top;
					char * pic_root = new char[t_str.size() + 1024];

					strcpy(pic_root, t_str.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name = new char[top_name.length() + 1024];


					strcpy(temp_name, top_name.c_str());


					std::string jpg = ".jpg";
					strcat(temp_name, jpg.c_str());

					strcat(pic_root, temp_name);
					remove(pic_root);
					delete[] pic_root;
					delete[] temp_name;

				}
				else if (catego == 4) {//pants 
					std::cout << "삭제할 바지의 이름을 입력하세요 ex) pants1" << std::endl;
					std::cin >> pants_name;
					std::cout << std::endl;
					m.delete_pants(pants_name);
					
					std::string t_str = pictureroot_pants;
					char * pic_root = new char[t_str.size() + 1024];

					strcpy(pic_root, t_str.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name = new char[pants_name.length() + 1024];


					strcpy(temp_name, pants_name.c_str());


					std::string jpg = ".jpg";
					strcat(temp_name, jpg.c_str());

					strcat(pic_root, temp_name);
					remove(pic_root);

					delete[] pic_root;
					delete[] temp_name;
				}
				else if (catego == 5) {//shoes 
					std::cout << "삭제할 신발의 이름을 입력하세요 ex) shoes1" << std::endl;
					std::cin >> shoes_name;
					std::cout << std::endl;
					m.delete_shoes(shoes_name);
					
					std::string t_str = pictureroot_shoes;
					char * pic_root = new char[t_str.size() + 1024];

					strcpy(pic_root, t_str.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name = new char[shoes_name.length() + 1024];


					strcpy(temp_name, shoes_name.c_str());


					std::string jpg = ".jpg";
					strcat(temp_name, jpg.c_str());

					strcat(pic_root, temp_name);
					remove(pic_root);

					delete[] pic_root;
					delete[] temp_name;
				}
				else if (catego == 6) {//accessory
					std::cout << "삭제할 악세사리의 이름을 입력하세요 ex) accessory1" << std::endl;
					std::cin >> acc_name;
					std::cout << std::endl;
					m.delete_accessory(acc_name);
					std::string t_str = pictureroot_accessory;
					char * pic_root = new char[t_str.size() + 1024];

					strcpy(pic_root, t_str.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name = new char[acc_name.length() + 1024];


					strcpy(temp_name, acc_name.c_str());


					std::string jpg = ".jpg";
					strcat(temp_name, jpg.c_str());

					strcat(pic_root, temp_name);
					remove(pic_root);

					delete[] pic_root;
					delete[] temp_name;
				}
			}
				else if (managechoice == 3) { //조회
					std::cout << "옷장에서 조회할 대상의 번호를 입력하세요 1.아우터 2.겉옷 3.상의 4.하의 5.신발 6.악세사리" << std::endl;
					std::cin >> checknum;
					std::cout << std::endl;

					if (checknum == 1) {//아우터
						std::cout << "옷장에서 아우터를 조회합니다." << std::endl;
						
						std::cout << std::endl;
						m.print_clothes(1);
						std::cout << "보고싶은 아우터의 이름을 입력해 주세요." << std::endl;
						std::cin >> out_name;
						std::cout << std::endl;
						
						std::string t_str = pictureroot_outer;
						char * pic_root = new char[t_str.size() + 1024];

						strcpy(pic_root, t_str.c_str());

						//pic_root3[t_str3.size()] = '\0'; // 

						char *temp_name = new char[out_name.length() + 1024];


						strcpy(temp_name, out_name.c_str());


						std::string jpg = ".jpg";
						strcat(temp_name, jpg.c_str());

						strcat(pic_root, temp_name);
						
						Mat showimage = imread(pic_root, IMREAD_COLOR);

						imshow("inquiry", showimage);
						waitKey(0);
						cvDestroyWindow("inquiry");
						delete[] pic_root;
						delete[] temp_name;

					}
					else if (checknum == 2) {//겉옷
						std::cout << "옷장에서 겉옷을 조회합니다." << std::endl;

						std::cout << std::endl;
						m.print_clothes(6);

						std::cout << "보고싶은 겉옷의 이름을 입력해 주세요." << std::endl;
						std::cin >> ove_name;
						std::cout << std::endl;

						std::string t_str = pictureroot_overgarment;
						char * pic_root = new char[t_str.size() + 1024];

						strcpy(pic_root, t_str.c_str());

						//pic_root3[t_str3.size()] = '\0'; // 

						char *temp_name = new char[ove_name.length() + 1024];


						strcpy(temp_name, out_name.c_str());


						std::string jpg = ".jpg";
						strcat(temp_name, jpg.c_str());

						strcat(pic_root, temp_name);

						Mat showimage = imread(pic_root, IMREAD_COLOR);

						imshow("inquiry", showimage);
						waitKey(0);
						cvDestroyWindow("inquiry");

						delete[] pic_root;
						delete[] temp_name;
					}
					else if (checknum == 3) {//상의
						std::cout << "옷장에서 상의를 조회합니다." << std::endl;

						std::cout << std::endl;
						m.print_clothes(2);
						std::cout << "보고싶은 상의의 이름을 입력해 주세요." << std::endl;
						std::cin >> top_name;
						std::cout << std::endl;

						std::string t_str = pictureroot_top;
						char * pic_root = new char[t_str.size() + 1024];

						strcpy(pic_root, t_str.c_str());

						//pic_root3[t_str3.size()] = '\0'; // 

						char *temp_name = new char[top_name.length() + 1024];


						strcpy(temp_name, top_name.c_str());


						std::string jpg = ".jpg";
						strcat(temp_name, jpg.c_str());

						strcat(pic_root, temp_name);

						Mat showimage = imread(pic_root, IMREAD_COLOR);

						imshow("inquiry", showimage);
						waitKey(0);
						cvDestroyWindow("inquiry");
						delete[] pic_root;
						delete[] temp_name;
					}
					else if (checknum == 4) {//하의
						std::cout << "옷장에서 하의를 조회합니다." << std::endl;

						std::cout << std::endl;
						m.print_clothes(3);
						std::cout << "보고싶은 하의의 이름을 입력해 주세요." << std::endl;
						std::cin >> pants_name;
						std::cout << std::endl;

						std::string t_str = pictureroot_pants;
						char * pic_root = new char[t_str.size() + 1024];

						strcpy(pic_root, t_str.c_str());

						//pic_root3[t_str3.size()] = '\0'; // 

						char *temp_name = new char[top_name.length() + 1024];


						strcpy(temp_name, top_name.c_str());


						std::string jpg = ".jpg";
						strcat(temp_name, jpg.c_str());

						strcat(pic_root, temp_name);

						Mat showimage = imread(pic_root, IMREAD_COLOR);

						imshow("inquiry", showimage);
						waitKey(0);
						cvDestroyWindow("inquiry");
						delete[] pic_root;
						delete[] temp_name;

					}
					else if (checknum == 5) {//신발
						std::cout << "옷장에서 신발을 조회합니다." << std::endl;

						std::cout << std::endl;
						m.print_clothes(5);

						std::cout << "보고싶은 신발의 이름을 입력해 주세요." << std::endl;
						std::cin >> shoes_name;
						std::cout << std::endl;

						std::string t_str = pictureroot_shoes;
						char * pic_root = new char[t_str.size() + 1024];

						strcpy(pic_root, t_str.c_str());

						//pic_root3[t_str3.size()] = '\0'; // 

						char *temp_name = new char[top_name.length() + 1024];


						strcpy(temp_name, top_name.c_str());


						std::string jpg = ".jpg";
						strcat(temp_name, jpg.c_str());

						strcat(pic_root, temp_name);

						Mat showimage = imread(pic_root, IMREAD_COLOR);

						imshow("inquiry", showimage);
						waitKey(0);
						cvDestroyWindow("inquiry");

						delete[] pic_root;
						delete[] temp_name;

					}
					else if (checknum == 6) {//악세사리
						std::cout << "옷장에서 악세사리를 조회합니다." << std::endl;

						std::cout << std::endl;
						m.print_clothes(4);
						std::cout << "보고싶은 악세사리의 이름을 입력해 주세요." << std::endl;
						std::cin >> acc_name;
						std::cout << std::endl;

						std::string t_str = pictureroot_accessory;
						char * pic_root = new char[t_str.size() + 1024];

						strcpy(pic_root, t_str.c_str());

						//pic_root3[t_str3.size()] = '\0'; // 

						char *temp_name = new char[top_name.length() + 1024];


						strcpy(temp_name, top_name.c_str());


						std::string jpg = ".jpg";
						strcat(temp_name, jpg.c_str());

						strcat(pic_root, temp_name);

						Mat showimage = imread(pic_root, IMREAD_COLOR);

						imshow("inquiry", showimage);
						waitKey(0);
						cvDestroyWindow("inquiry");

						delete[] pic_root;
						delete[] temp_name;

					}


				


				}
				else  {
					
					continue;
				}



				break;

		case 2://온도확인

			std::cout.setf(std::ios::fixed);
			std::cout.precision(1);
			std::cout << "케이웨더 기준 서울시 현재온도: " << temperature << std::endl;
			break;

		case 3://코디하기
			check = 0;
			std::cout << "데일리룩 코디네이터가 코디를 진행합니다!" << std::endl;




			//result = cordi.cordinate("new_color.txt", temperature);

			//std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, std::string& texture, std::string&  pictureroot


			//필수항목 빠졌을때, 다시 코디
			//여기 다 투루일경우 판단해야함.
			coordicheck = 0;
			cordi.set_weight();
			while(coordicheck!=1)
			{
				result = cordi.cordinate("new_color.txt", temperature);
				if (cordi.get_vector_size() == 0)
				{
					coordicheck = 0;

				}
				else {
					coordicheck = 1;
				}
			}

			
			//Set(Outer outer, Top top, Pants pants, Shoes shoes);
			//out top pants shoes


			//뒤에 set 에 outer,overgarment,top,pants,shoes,accessory에 유무에 따라 사진합성 다르게.
			
			while (check !=1)
			{
				check = 0;
				
				//////////////////////////아우터 없을때 겉옷,상의,하의,신발,악세

				if (result[0].get_outer().get_name() == "no"&&result[0].get_overgarment().get_name() != "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() != "no") {
					std::string format = ".jpg";

					//pic_root1 == overgarment
					std::string t_str1 = pictureroot_overgarment;
					char * pic_root1 = new char[t_str1.size() + 1024];

					strcpy(pic_root1, t_str1.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name1 = new char[result[0].get_overgarment().get_name().length() + 1024];


					strcpy(temp_name1, result[0].get_overgarment().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name1, format.c_str());

					strcat(pic_root1, temp_name1);


					//pic_root2 == top

					std::string t_str2 = pictureroot_top;
					char * pic_root2 = new char[t_str2.size() + 1024];

					strcpy(pic_root2, t_str2.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name2 = new char[result[0].get_top().get_name().length() + 1024];


					strcpy(temp_name2, result[0].get_top().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name2, format.c_str());

					strcat(pic_root2, temp_name2);

					//pic_root3== pants

					std::string t_str3 = pictureroot_pants;
					char * pic_root3 = new char[t_str3.size() + 1024];

					strcpy(pic_root3, t_str3.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name3 = new char[result[0].get_pants().get_name().length() + 1024];


					strcpy(temp_name3, result[0].get_pants().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name3, format.c_str());

					strcat(pic_root3, temp_name3);


					//pic_root4 == shoes

					std::string t_str4 = pictureroot_shoes;
					char * pic_root4 = new char[t_str4.size() + 1024];

					strcpy(pic_root4, t_str4.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name4 = new char[result[0].get_shoes().get_name().length() + 1024];


					strcpy(temp_name4, result[0].get_shoes().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name4, format.c_str());

					strcat(pic_root4, temp_name4);

					//pic_root5 == accessory

					std::string t_str5 = pictureroot_accessory;
					char * pic_root5 = new char[t_str5.size() + 1024];

					strcpy(pic_root5, t_str5.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name5 = new char[result[0].get_accessory().get_name().length() + 1024];


					strcpy(temp_name5, result[0].get_accessory().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name5, format.c_str());

					strcat(pic_root5, temp_name5);

					//합치기
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_5 = imread(pic_root5, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_temp3;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty() && image_5.empty())
					{
						std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
						return -1;
					}

					char savefilename[128];

					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					//sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
					//imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					hconcat(image_temp1, image_temp2, image_temp3);
					hconcat(image_temp3, image_5, image_result);
					resize(image_result, image_result, Size(600, 300), 0, 0, INTER_CUBIC);

					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img를 파일로 저장한다.


					imshow("resultimage.png", image_result);
					waitKey(0);




					std::cout << result.size() - 1 << "개의 후보가 더있습니다" << "이 코디가 마음에 드십니까? (예 :1 아니오:2) 아니오를 누르면 다른후보가 보여집니다." << std::endl;
					std::cin >> check;
					std::cout << "\n";

					delete[] pic_root1;
					delete[] pic_root2;
					delete[] pic_root3;
					delete[] pic_root4;
					delete[] pic_root5;
					delete[] temp_name1;
					delete[] temp_name2;
					delete[] temp_name3;
					delete[] temp_name4;
					delete[] temp_name5;

					if (check == 1) {
						break;
					}
					if (result.size() == 1 && check == 2) {
						check = 1;
					}

					result.erase(result.begin());


					



				}
				//아우터 없는데 겉옷도 없을때 상의,하의,신발,악세사리
				else if (result[0].get_outer().get_name() == "no"&&result[0].get_overgarment().get_name() == "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() != "no") {

					//pic_root1 == top
					std::string format = ".jpg";
					std::string t_str1 = pictureroot_top;
					char * pic_root1 = new char[t_str1.size() + 1024];

					strcpy(pic_root1, t_str1.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name1 = new char[result[0].get_top().get_name().length() + 1024];


					strcpy(temp_name1, result[0].get_top().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name1, format.c_str());

					strcat(pic_root1, temp_name1);

					//pic_root2== pants

					std::string t_str2 = pictureroot_pants;
					char * pic_root2 = new char[t_str2.size() + 1024];

					strcpy(pic_root2, t_str2.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name2 = new char[result[0].get_pants().get_name().length() + 1024];


					strcpy(temp_name2, result[0].get_pants().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name2, format.c_str());

					strcat(pic_root2, temp_name2);


					//pic_root3 == shoes

					std::string t_str3 = pictureroot_shoes;
					char * pic_root3 = new char[t_str3.size() + 1024];

					strcpy(pic_root3, t_str3.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name3 = new char[result[0].get_shoes().get_name().length() + 1024];


					strcpy(temp_name3, result[0].get_shoes().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name3, format.c_str());

					strcat(pic_root3, temp_name3);

					//pic_root4 == accessory

					std::string t_str4 = pictureroot_accessory;
					char * pic_root4 = new char[t_str4.size() + 1024];

					strcpy(pic_root4, t_str4.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name4 = new char[result[0].get_accessory().get_name().length() + 1024];


					strcpy(temp_name4, result[0].get_accessory().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name4, format.c_str());

					strcat(pic_root4, temp_name4);

					//합치기
					//두개씩 합하기
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty())
					{
						std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
						return -1;
					}

					char savefilename[128];        // 이미지 파일 이름을 200자 이내로 제한하기 위한 char 변수 선언



												   // 두개의 이미지를 합쳐주는 마법의 명령어 :-)
					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																						 //imwrite(savefile, image_temp2);        // img를 파일로 저장한다.

					hconcat(image_temp1, image_temp2, image_result);

					//resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img를 파일로 저장한다.


					imshow("resultimage.png", image_result);
					waitKey(0);

					std::cout << result.size() - 1 << "개의 후보가 더있습니다" << "이 코디가 마음에 드십니까? (예 :1 아니오:2) 아니오를 누르면 다른후보가 보여집니다." << std::endl;
					std::cin >> check;
					std::cout << "\n";

					delete[] pic_root1;
					delete[] pic_root2;
					delete[] pic_root3;
					delete[] pic_root4;
					delete[] temp_name1;
					delete[] temp_name2;
					delete[] temp_name3;
					delete[] temp_name4;

					if (check == 1) {
						break;
					}
					if (result.size() == 1 && check == 2) {
						check = 1;
					}
					result.erase(result.begin());
					
				
				}
				//아우터 없는데 악세사리도 없을때 겉옷,상의,하의,신발
				else if (result[0].get_outer().get_name() == "no"&&result[0].get_overgarment().get_name() != "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() == "no") {
					std::string format = ".jpg";
					
					//pic_root1 == overgarment
					std::string t_str1 = pictureroot_overgarment;
					char * pic_root1 = new char[t_str1.size() + 1024];

					strcpy(pic_root1, t_str1.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name1 = new char[result[0].get_overgarment().get_name().length() + 1024];


					strcpy(temp_name1, result[0].get_overgarment().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name1, format.c_str());

					strcat(pic_root1, temp_name1);

					
					//pic_root2 == top
					
					std::string t_str2 = pictureroot_top;
					char * pic_root2 = new char[t_str2.size() + 1024];

					strcpy(pic_root2, t_str2.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name2 = new char[result[0].get_top().get_name().length() + 1024];


					strcpy(temp_name2, result[0].get_top().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name2, format.c_str());

					strcat(pic_root2, temp_name2);

					//pic_root3== pants

					std::string t_str3 = pictureroot_pants;
					char * pic_root3 = new char[t_str3.size() + 1024];

					strcpy(pic_root3, t_str3.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name3 = new char[result[0].get_pants().get_name().length() + 1024];


					strcpy(temp_name3, result[0].get_pants().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name3, format.c_str());

					strcat(pic_root3, temp_name3);


					//pic_root4 == shoes

					std::string t_str4 = pictureroot_shoes;
					char * pic_root4 = new char[t_str4.size() + 1024];

					strcpy(pic_root4, t_str4.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name4 = new char[result[0].get_shoes().get_name().length() + 1024];


					strcpy(temp_name4, result[0].get_shoes().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name4, format.c_str());

					strcat(pic_root4, temp_name4);

					//합치기

					//두개씩 합하기
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty())
					{
						std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
						return -1;
					}

					char savefilename[128];        // 이미지 파일 이름을 200자 이내로 제한하기 위한 char 변수 선언



												   // 두개의 이미지를 합쳐주는 마법의 명령어 :-)
					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																						 //imwrite(savefile, image_temp2);        // img를 파일로 저장한다.

					hconcat(image_temp1, image_temp2, image_result);

					resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img를 파일로 저장한다.


					imshow("resultimage.png", image_result);
					waitKey(0);

					std::cout << result.size() - 1 << "개의 후보가 더있습니다" << "이 코디가 마음에 드십니까? (예 :1 아니오:2) 아니오를 누르면 다른후보가 보여집니다." << std::endl;
					std::cin >> check;
					std::cout << "\n";

					delete[] pic_root1;
					delete[] pic_root2;
					delete[] pic_root3;
					delete[] pic_root4;
					delete[] temp_name1;
					delete[] temp_name2;
					delete[] temp_name3;
					delete[] temp_name4;

					if (check == 1) {
						break;
					}
					if (result.size() == 1 && check == 2) {
						check = 1;
					}
					result.erase(result.begin());
				}
				//아우터 없는데 겉옷,악세사리도 없을때 상의,하의,신발
				else if (result[0].get_outer().get_name() == "no"&&result[0].get_overgarment().get_name() == "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() == "no") {
					

					//pic_root1 == top
					std::string format = ".jpg";
					std::string t_str1 = pictureroot_top;
					char * pic_root1 = new char[t_str1.size() + 1024];

					strcpy(pic_root1, t_str1.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name1 = new char[result[0].get_top().get_name().length() + 1024];


					strcpy(temp_name1, result[0].get_top().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name1, format.c_str());

					strcat(pic_root1, temp_name1);

					//pic_root2== pants

					std::string t_str2 = pictureroot_pants;
					char * pic_root2 = new char[t_str2.size() + 1024];

					strcpy(pic_root2, t_str2.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name2 = new char[result[0].get_pants().get_name().length() + 1024];


					strcpy(temp_name2, result[0].get_pants().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name2, format.c_str());

					strcat(pic_root2, temp_name2);


					//pic_root3 == shoes

					std::string t_str3 = pictureroot_shoes;
					char * pic_root3 = new char[t_str3.size() + 1024];

					strcpy(pic_root3, t_str3.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name3 = new char[result[0].get_shoes().get_name().length() + 1024];


					strcpy(temp_name3, result[0].get_shoes().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name3, format.c_str());

					strcat(pic_root3, temp_name3);

					
					//합치기
					//두개씩 합하기
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty())
					{
						std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
						return -1;
					}

					char savefilename[128];        // 이미지 파일 이름을 200자 이내로 제한하기 위한 char 변수 선언



												   // 두개의 이미지를 합쳐주는 마법의 명령어 :-)
					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

					hconcat(image_temp1, image_3, image_result);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																						 //imwrite(savefile, image_temp2);        // img를 파일로 저장한다.

					

					//resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img를 파일로 저장한다.


					imshow("resultimage.png", image_result);
					waitKey(0);

					std::cout << result.size() - 1 << "개의 후보가 더있습니다" << "이 코디가 마음에 드십니까? (예 :1 아니오:2) 아니오를 누르면 다른후보가 보여집니다." << std::endl;
					std::cin >> check;
					std::cout << "\n";

					delete[] pic_root1;
					delete[] pic_root2;
					delete[] pic_root3;
					
					delete[] temp_name1;
					delete[] temp_name2;
					delete[] temp_name3;
					

					if (check == 1) {
						break;
					}
					if (result.size() == 1 && check == 2) {
						check = 1;
					}
					result.erase(result.begin());
					


				}

				////////////////////////아우터 있을때 아우터,겉옷,상의,하의,신발,악세 다있는거
				else if (result[0].get_outer().get_name() != "no"&&result[0].get_overgarment().get_name() != "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() != "no") {
					
					//pic_root1 == outer
					std::string t_str1 = pictureroot_outer;
					char * pic_root1 = new char[t_str1.size() + 1024];

					strcpy(pic_root1, t_str1.c_str());

					//pic_root1[t_str1.size()] = '\0'; // 

					char *temp_name1 = new char[result[0].get_outer().get_name().length() + 1024];


					strcpy(temp_name1, result[0].get_outer().get_name().c_str());


					std::string format = ".jpg";
					strcat(temp_name1, format.c_str());

					strcat(pic_root1, temp_name1);


					//pic_root2 == overgarment
					std::string t_str2 = pictureroot_overgarment;
					char * pic_root2 = new char[t_str2.size() + 1024];

					strcpy(pic_root2, t_str2.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name2 = new char[result[0].get_overgarment().get_name().length() + 1024];


					strcpy(temp_name2, result[0].get_overgarment().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name2, format.c_str());

					strcat(pic_root2, temp_name2);

					//pic_root3 == top

					std::string t_str3 = pictureroot_top;
					char * pic_root3 = new char[t_str3.size() + 1024];

					strcpy(pic_root3, t_str3.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name3 = new char[result[0].get_top().get_name().length() + 1024];


					strcpy(temp_name3, result[0].get_top().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name3, format.c_str());

					strcat(pic_root3, temp_name3);

					//pic_root4== pants

					std::string t_str4 = pictureroot_pants;
					char * pic_root4 = new char[t_str4.size() + 1024];

					strcpy(pic_root4, t_str4.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name4 = new char[result[0].get_pants().get_name().length() + 1024];


					strcpy(temp_name4, result[0].get_pants().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name4, format.c_str());

					strcat(pic_root4, temp_name4);


					//pic_root5 == shoes

					std::string t_str5 = pictureroot_shoes;
					char * pic_root5 = new char[t_str5.size() + 1024];

					strcpy(pic_root5, t_str5.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name5 = new char[result[0].get_shoes().get_name().length() + 1024];


					strcpy(temp_name5, result[0].get_shoes().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name5, format.c_str());

					strcat(pic_root5, temp_name5);

					//pic_root6 == accessory

					std::string t_str6 = pictureroot_accessory;
					char * pic_root6 = new char[t_str6.size() + 1024];

					strcpy(pic_root6, t_str6.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name6 = new char[result[0].get_accessory().get_name().length() + 1024];


					strcpy(temp_name6, result[0].get_accessory().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name6, format.c_str());

					strcat(pic_root6, temp_name6);


					//합치기
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_5 = imread(pic_root5, IMREAD_COLOR);
					Mat image_6 = imread(pic_root6, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_temp3;
					Mat image_temp4;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty() && image_5.empty())
					{
						std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
						return -1;
					}

					char savefilename[128];

					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					//sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
					//imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					hconcat(image_5, image_6, image_temp3);
					hconcat(image_temp1, image_temp2, image_temp4);

					hconcat(image_temp3, image_temp4, image_result);

					resize(image_result, image_result, Size(600, 300), 0, 0, INTER_CUBIC);

					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img를 파일로 저장한다.


					imshow("resultimage.png", image_result);
					waitKey(0);




					std::cout << result.size() - 1 << "개의 후보가 더있습니다" << "이 코디가 마음에 드십니까? (예 :1 아니오:2) 아니오를 누르면 다른후보가 보여집니다." << std::endl;
					std::cin >> check;
					std::cout << "\n";

					delete[] pic_root1;
					delete[] pic_root2;
					delete[] pic_root3;
					delete[] pic_root4;
					delete[] pic_root5;
					delete[] pic_root6;
					delete[] temp_name1;
					delete[] temp_name2;
					delete[] temp_name3;
					delete[] temp_name4;
					delete[] temp_name5;
					delete[] temp_name6;

					if (check == 1) {
						break;
					}
					if (result.size() == 1 && check == 2) {
						check = 1;
					}

					result.erase(result.begin());


					
				}


				//아우터 있는데, 겉옷 없을때 아우터,상의,하의,신발,악세사리
				else if (result[0].get_outer().get_name() != "no"&&result[0].get_overgarment().get_name() == "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() != "no") {

					//pic_root1 == outer
					std::string t_str1 = pictureroot_outer;
					char * pic_root1 = new char[t_str1.size() + 1024];

					strcpy(pic_root1, t_str1.c_str());

					//pic_root1[t_str1.size()] = '\0'; // 

					char *temp_name1 = new char[result[0].get_outer().get_name().length() + 1024];


					strcpy(temp_name1, result[0].get_outer().get_name().c_str());


					std::string format = ".jpg";
					strcat(temp_name1, format.c_str());

					strcat(pic_root1, temp_name1);

					


					//pic_root2 == top

					std::string t_str2 = pictureroot_top;
					char * pic_root2 = new char[t_str2.size() + 1024];

					strcpy(pic_root2, t_str2.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name2 = new char[result[0].get_top().get_name().length() + 1024];


					strcpy(temp_name2, result[0].get_top().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name2, format.c_str());

					strcat(pic_root2, temp_name2);

					//pic_root3== pants

					std::string t_str3 = pictureroot_pants;
					char * pic_root3 = new char[t_str3.size() + 1024];

					strcpy(pic_root3, t_str3.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name3 = new char[result[0].get_pants().get_name().length() + 1024];


					strcpy(temp_name3, result[0].get_pants().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name3, format.c_str());

					strcat(pic_root3, temp_name3);


					//pic_root4 == shoes

					std::string t_str4 = pictureroot_shoes;
					char * pic_root4 = new char[t_str4.size() + 1024];

					strcpy(pic_root4, t_str4.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name4 = new char[result[0].get_shoes().get_name().length() + 1024];


					strcpy(temp_name4, result[0].get_shoes().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name4, format.c_str());

					strcat(pic_root4, temp_name4);

					//pic_root5 == accessory

					std::string t_str5 = pictureroot_accessory;
					char * pic_root5 = new char[t_str5.size() + 1024];

					strcpy(pic_root5, t_str5.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name5= new char[result[0].get_accessory().get_name().length() + 1024];


					strcpy(temp_name5, result[0].get_accessory().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name5, format.c_str());

					strcat(pic_root5, temp_name5);


					//합치기
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_5 = imread(pic_root5, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_temp3;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty() && image_5.empty())
					{
						std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
						return -1;
					}

					char savefilename[128];

					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					//sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
					//imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					hconcat(image_temp1, image_temp2, image_temp3);
					hconcat(image_temp3, image_5, image_result);
					resize(image_result, image_result, Size(600, 300), 0, 0, INTER_CUBIC);

					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img를 파일로 저장한다.


					imshow("resultimage.png", image_result);
					waitKey(0);




					std::cout << result.size() - 1 << "개의 후보가 더있습니다" << "이 코디가 마음에 드십니까? (예 :1 아니오:2) 아니오를 누르면 다른후보가 보여집니다." << std::endl;
					std::cin >> check;
					std::cout << "\n";

					delete[] pic_root1;
					delete[] pic_root2;
					delete[] pic_root3;
					delete[] pic_root4;
					delete[] pic_root5;
					delete[] temp_name1;
					delete[] temp_name2;
					delete[] temp_name3;
					delete[] temp_name4;
					delete[] temp_name5;

					if (check == 1) {
						break;
					}
					if (result.size() == 1 && check == 2) {
						check = 1;
					}

					result.erase(result.begin());



					

				}
				//아우터 있는데,악세사리없을떄 아우터 겉옷 상의 하의 신발 
				else if (result[0].get_outer().get_name() != "no"&&result[0].get_overgarment().get_name() != "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() == "no") {
					//각각의 네임과 루트 더하기
					//delete해야돼!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111

					//pic_root1 == outer
					std::string t_str1 = pictureroot_outer;
					char * pic_root1 = new char[t_str1.size() + 1024];

					strcpy(pic_root1, t_str1.c_str());

					//pic_root1[t_str1.size()] = '\0'; // 

					char *temp_name1 = new char[result[0].get_outer().get_name().length() + 1024];


					strcpy(temp_name1, result[0].get_outer().get_name().c_str());


					std::string format = ".jpg";
					strcat(temp_name1, format.c_str());

					strcat(pic_root1, temp_name1);

					//pic_root2 ==  overgarment
					std::string t_str2 = pictureroot_overgarment;
					char * pic_root2 = new char[t_str2.size() + 1024];

					strcpy(pic_root2, t_str2.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name2 = new char[result[0].get_overgarment().get_name().length() + 1024];


					strcpy(temp_name2, result[0].get_overgarment().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name2, format.c_str());

					strcat(pic_root2, temp_name2);
					
					
					
					
					
					//pic_root3 == top

					std::string t_str3 = pictureroot_top;
					char * pic_root3 = new char[t_str3.size() + 1024];

					strcpy(pic_root3, t_str3.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name3 = new char[result[0].get_top().get_name().length() + 1024];


					strcpy(temp_name3, result[0].get_top().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name3, format.c_str());

					strcat(pic_root3, temp_name3);

					//pic_root4== pants

					std::string t_str4 = pictureroot_pants;
					char * pic_root4 = new char[t_str4.size() + 1024];

					strcpy(pic_root4, t_str4.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name4 = new char[result[0].get_pants().get_name().length() + 1024];


					strcpy(temp_name4, result[0].get_pants().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name4, format.c_str());

					strcat(pic_root4, temp_name4);

					
					//pic_root5 == shoes

					std::string t_str5 = pictureroot_shoes;
					char * pic_root5 = new char[t_str5.size() + 1024];

					strcpy(pic_root5, t_str5.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name5 = new char[result[0].get_shoes().get_name().length() + 1024];


					strcpy(temp_name5, result[0].get_shoes().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name5, format.c_str());

					strcat(pic_root5, temp_name5);

					
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_5 = imread(pic_root5, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_temp3;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty()&&image_5.empty())
					{
						std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
						return -1;
					}

					char savefilename[128];

					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					hconcat(image_temp1, image_temp2, image_temp3);
					hconcat(image_temp3, image_5, image_result);
					resize(image_result, image_result, Size(600, 300), 0, 0, INTER_CUBIC); 

					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img를 파일로 저장한다.


					imshow("resultimage.png", image_result);
					waitKey(0);



					
					std::cout << result.size() - 1 << "개의 후보가 더있습니다" << "이 코디가 마음에 드십니까? (예 :1 아니오:2) 아니오를 누르면 다른후보가 보여집니다." << std::endl;
					std::cin >> check;
					std::cout << "\n";

					delete[] pic_root1;
					delete[] pic_root2;
					delete[] pic_root3;
					delete[] pic_root4;
					delete[] pic_root5;
					delete[] temp_name1;
					delete[] temp_name2;
					delete[] temp_name3;
					delete[] temp_name4;
					delete[] temp_name5;

					if (check == 1) {
						break;
					}
					if (result.size() == 1 && check == 2) {
						check = 1;
					}
					
					result.erase(result.begin());

				}
				//아우터 있는데 ,겉옷 ,악세사리 없을때 //아우터,상의,하의,신발
				else if (result[0].get_outer().get_name() != "no"&&result[0].get_overgarment().get_name() == "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() == "no") {
					//각각의 네임과 루트 더하기


					//pic_root1 == outer
					std::string t_str1 = pictureroot_outer;
					char * pic_root1 = new char[t_str1.size() + 1024];

					strcpy(pic_root1, t_str1.c_str());

					//pic_root1[t_str1.size()] = '\0'; // 

					char *temp_name1 = new char[result[0].get_outer().get_name().length() + 1024];


					strcpy(temp_name1, result[0].get_outer().get_name().c_str());


					std::string format = ".jpg";
					strcat(temp_name1, format.c_str());

					strcat(pic_root1, temp_name1);


					//pic_root2 == top

					std::string t_str2 = pictureroot_top;
					char * pic_root2 = new char[t_str1.size() + 1024];

					strcpy(pic_root2, t_str2.c_str());

					//pic_root2[t_str2.size()] = '\0'; // 

					char *temp_name2 = new char[result[0].get_top().get_name().length() + 1024];


					strcpy(temp_name2, result[0].get_top().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name2, format.c_str());

					strcat(pic_root2, temp_name2);

					//pic_root3 == pants

					std::string t_str3 = pictureroot_pants;
					char * pic_root3 = new char[t_str1.size() + 1024];

					strcpy(pic_root3, t_str3.c_str());

					//pic_root3[t_str3.size()] = '\0'; // 

					char *temp_name3 = new char[result[0].get_pants().get_name().length() + 1024];


					strcpy(temp_name3, result[0].get_pants().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name3, format.c_str());

					strcat(pic_root3, temp_name3);

					//pic_root4 == shoes

					std::string t_str4 = pictureroot_shoes;
					char * pic_root4 = new char[t_str4.size() + 1024];

					strcpy(pic_root4, t_str4.c_str());

					//pic_root4[t_str4.size()] = '\0'; // 

					char *temp_name4 = new char[result[0].get_shoes().get_name().length() + 1024];


					strcpy(temp_name4, result[0].get_shoes().get_name().c_str());


					//std::string format = ".jpg";
					strcat(temp_name4, format.c_str());

					strcat(pic_root4, temp_name4);



					//두개씩 합하기
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty())
					{
						std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
						return -1;
					}

					char savefilename[128];        // 이미지 파일 이름을 200자 이내로 제한하기 위한 char 변수 선언



											   // 두개의 이미지를 합쳐주는 마법의 명령어 :-)
					hconcat(image_1, image_2, image_temp1);

					resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

					hconcat(image_3, image_4, image_temp2);

					resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																						 //imwrite(savefile, image_temp2);        // img를 파일로 저장한다.

					hconcat(image_temp1, image_temp2, image_result);

					resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img를 파일로 저장한다.


					imshow("resultimage.png", image_result);
					waitKey(0);

					std::cout <<result.size()-1 <<"개의 후보가 더있습니다"<<"이 코디가 마음에 드십니까? (예 :1 아니오:2) 아니오를 누르면 다른후보가 보여집니다." << std::endl;
					std::cin >> check;
					std::cout << "\n";
					
					delete[] pic_root1;
					delete[] pic_root2;
					delete[] pic_root3;
					delete[] pic_root4;
					delete[] temp_name1;
					delete[] temp_name2;
					delete[] temp_name3;
					delete[] temp_name4;

					if (check == 1) {
						break;
					}
					if (result.size() == 1 && check == 2){
						check = 1;
					}
					result.erase(result.begin());
				}
			}



			break;

		case 4://EXIT
			std::cout << "daily coordinator System 을 종료합니다." << std::endl;
			return 0;

			break;
		
			}

		}

		/*
		int i = black;
		Closet a;
		Outer o("top101", "coat", "black", "long", 10, 10, 10, "daffd", pictureroot_top);


		//set

		std::vector<Top> TOP = a.get_top();
		TOP;
		//현재
		Closetmanager m;

		//get
		m.Add_Outer(o);
		m.delete_Outer("top101");
		*/


		//use opencv;~~~~
		/*
		String filepath1("C:\\opencv\\image\\im1\\날두형1.png");
		String filepath2("C:\\opencv\\image\\im2\\날두형2.png");
		String filepath3("C:\\opencv\\image\\im3\\날두형3.png");
		String filepath4("C:\\opencv\\image\\im4\\날두형4.png");
		Mat image_1 = imread(filepath1, IMREAD_COLOR);
		Mat image_2 = imread(filepath2, IMREAD_COLOR);
		Mat image_3 = imread(filepath3, IMREAD_COLOR);
		Mat image_4 = imread(filepath4, IMREAD_COLOR);
		Mat image_temp1;
		Mat image_temp2;
		Mat image_result;

		if (image_1.empty() && image_2.empty())
		{
			std::cout << "이미지가 없거나, 유효한 파일 형식이 아닙니다." << std::endl;
			return -1;
		}

		//imshow("image", image_1);      // 영상 출력
		//imshow("image2", image_2);




		char savefile[128];        // 이미지 파일 이름을 200자 이내로 제한하기 위한 char 변수 선언



								   // 두개의 이미지를 합쳐주는 마법의 명령어 :-)
		hconcat(image_1, image_2, image_temp1);

		resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																			 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																			 //imwrite(savefile, image_temp1);        // img를 파일로 저장한다.

		hconcat(image_3, image_4, image_temp2);

		resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
																			 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																			 //imwrite(savefile, image_temp2);        // img를 파일로 저장한다.

		hconcat(image_temp1, image_temp2, image_result);

		resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
		sprintf_s(savefile, "C:\\opencv\\image\\result\\resultiamge.png");
		imwrite(savefile, image_result);        // img를 파일로 저장한다.


		imshow("resultimage.png", image_result);
		waitKey(0);

		*/

		return 0;
	}
