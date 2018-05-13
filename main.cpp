#include "coordinate_Sys.h"
#pragma comment(lib,"winmm.lib")

int main() {
	//�뷡
	PlaySound(TEXT(SOUND_FILE_NAME),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	//ó�� �� ���� ��������
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


	//temperature = 28; //����
	//temperature = 18; //�ʰ���
	//temperature = 10;//�ʰ���
	//temperature = -4; //�Ѱܿ�

	//����Ÿ ���� ��  ����
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
	std::cout << "*���ϸ��� �ڵ������ �ý����� Ʈ����� ����� ��ȣ���� �������� �ڵ��մϴ�*\n" << std::endl;
	std::cout << "****���ϸ��� �ڵ�������� ��õ�� ���� �԰� �ڽ��ִ� �Ϸ縦 �����ϼ���****\n" << std::endl;

	while (1) {

		std::cout << "--------------MENU------------- " << std::endl;
		std::cout << "1.���� �������" << std::endl;
		std::cout << "2.���� �µ� Ȯ��" << std::endl;
		std::cout << "3.���ϸ��� �ڵ� ����" << std::endl;
		std::cout << "4.���ϸ��� �ڵ������ �ý��� ����" << std::endl;

		std::cin >> menuchoice;
		std::cout << std::endl;

		switch (menuchoice)
		{
		case 1://�������
			std::cout << "����� ������ �����մϴ�" << std::endl;
			std::cout << "1.�߰��ϱ� " << std::endl;
			std::cout << "2.�����ϱ� " << std::endl;
			std::cout << "3.����ȸ�ϱ�" << std::endl;
			std::cout << "4.������" << std::endl;
			std::cin >> managechoice;
			std::cout << std::endl;




			if (managechoice == 1) { //�߰�
				std::cout << "�߰��Ϸ��� ���� ������ �Է����ּ��� 1.�ƿ��� 2.�ѿ� 3.���� 4.���� 5.�Ź� 6.�Ǽ��縮" << std::endl;
				std::cin >> cate;

				if (cate == 1) {//outer

					std::cout << "�ƿ����� �̸��� �Է����ּ��� ex)outer# " << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "�ƿ����� ��Ÿ���� �Է����ּ��� " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "�ƿ����� ������ �Է����ּ��� " << std::endl;
					std::cin >> col;
					std::cout << std::endl;

					std::cout << "�ƿ����� ���̸� �Է����ּ��� " << std::endl;
					std::cin >> len;
					std::cout << std::endl;

					std::cout << "�ƿ����� ���¼��� �Է����ּ���(1~10) " << std::endl;
					std::cin >> insulation;
					std::cout << std::endl;

					std::cout << "�ƿ����� Ʈ���带 �Է����ּ���(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "�ƿ����� ����� ��ȣ���� �Է����ּ���(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;

					std::cout << "�ƿ����� �ʰ��� �Է����ּ���" << std::endl;
					std::cin >> texture;
					std::cout << std::endl;

					std::string t_str = pictureroot_outer;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Outer temp_outer(t_name, style, col, len, insulation, trend, priority, texture, pr);

					m.Add_outer(temp_outer);

					std::cout << "�ƿ��� �����Կ��� �ϰڽ��ϴ�.!!      �غ��Ͻð�~ ESC ���! " << std::endl;

					//Sleep(1.00);

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC ������ ����!

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
					std::cout << "�ѿ��� �̸��� �Է����ּ��� ex)overgarment#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "�ѿ��� ��Ÿ���� �Է����ּ��� " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "�ѿ��� ������ �Է����ּ��� " << std::endl;
					std::cin >> col;
					std::cout << std::endl;

					std::cout << "�ѿ��� ������ �Է����ּ��� " << std::endl;
					std::cin >> len;
					std::cout << std::endl;

					std::cout << "�ѿ��� ���¼��� �Է����ּ���(1~10) " << std::endl;
					std::cin >> insulation;
					std::cout << std::endl;

					std::cout << "�ѿ��� Ʈ���带 �Է����ּ���(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "�ѿ��� ����� ��ȣ���� �Է����ּ���(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;



					std::string t_str = pictureroot_overgarment;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Overgarment temp_over(t_name, style, col, len, insulation, trend, priority, pr);

					m.Add_overgarment(temp_over);

					std::cout << "�ѿ��� �����Կ��� �ϰڽ��ϴ�. �غ��Ͻð�~~~ ESC ���! " << std::endl;

					//Sleep(1.00);

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC ������ ����!

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
				else if (cate == 3) {//����
					std::cout << "������ �̸��� �Է����ּ��� ex)tops#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "������ ��Ÿ���� �Է����ּ��� " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "������ ������ �Է����ּ��� " << std::endl;
					std::cin >> col;
					std::cout << std::endl;

					std::cout << "������ ������ �Է����ּ��� " << std::endl;
					std::cin >> len;
					std::cout << std::endl;

					std::cout << "������ ���¼��� �Է����ּ���(1~10) " << std::endl;
					std::cin >> insulation;
					std::cout << std::endl;

					std::cout << "������ Ʈ���带 �Է����ּ���(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "������ ����� ��ȣ���� �Է����ּ���(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;

					std::cout << "������ �β��� �Է����ּ���(1~10) " << std::endl;
					std::cin >> thickness;
					std::cout << std::endl;

					std::string t_str = pictureroot_top;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Top temp_top(t_name, style, col, len, insulation, trend, priority, thickness, pr);

					m.Add_top(temp_top);

					std::cout << "���� �����Կ��� �ϰڽ��ϴ�. �غ��Ͻð�~~~~~~ ESC ���! " << std::endl;

					//Sleep(1.00);

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC ������ ����!

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
				else if (cate == 4) {//����
					//Pants(std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, bool belt, std::string& pictureroot);

					std::cout << "������ �̸��� �Է����ּ��� ex)pants#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "������ ��Ÿ���� �Է����ּ��� " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "������ ������ �Է����ּ��� " << std::endl;
					std::cin >> col;
					std::cout << std::endl;

					std::cout << "������ ������ �Է����ּ��� " << std::endl;
					std::cin >> len;
					std::cout << std::endl;

					std::cout << "������ ���¼��� �Է����ּ���(1~10) " << std::endl;
					std::cin >> insulation;
					std::cout << std::endl;

					std::cout << "������ Ʈ���带 �Է����ּ���(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "������ ����� ��ȣ���� �Է����ּ���(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;

					std::cout << "������ ��Ʈ�� �ʿ��ϸ� 1 �ƴϸ� 0�� �Է����ּ��� " << std::endl;
					std::cin >> belt;
					std::cout << std::endl;

					std::string t_str = pictureroot_pants;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Pants temp_pants(t_name, style, col, len, insulation, trend, priority, belt, pr);

					m.Add_pants(temp_pants);

					std::cout << "���� �����Կ��� �ϰڽ��ϴ�. �غ��Ͻð�~~~~ ESC ���! " << std::endl;

					//Sleep(1.00);

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC ������ ����!

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
				else if (cate == 5) {//�Ź� std::string& name, std::string& style, std::string& color, int trend, int priority, std::string& pictureroot);
					std::cout << "�Ź��� �̸��� �Է����ּ��� ex)shoes#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "�Ź��� ��Ÿ���� �Է����ּ��� " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "�Ź��� ������ �Է����ּ��� " << std::endl;
					std::cin >> col;
					std::cout << std::endl;


					std::cout << "�Ź��� Ʈ���带 �Է����ּ���(1~10) " << std::endl;
					std::cin >> trend;
					std::cout << std::endl;

					std::cout << "�Ź��� ����� ��ȣ���� �Է����ּ���(1~10) " << std::endl;
					std::cin >> priority;
					std::cout << std::endl;

					std::string t_str = pictureroot_shoes;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Shoes temp_shoes(t_name, style, col, trend, priority, pr);

					//m.Add_shoes(temp_shoes);

					std::cout << "�Ź� �����Կ��� �ϰڽ��ϴ�. �غ��Ͻð�~ ESC ���! " << std::endl;

					//sleep

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC ������ ����!

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
					std::cout << "�Ǽ��縮�� �̸��� �Է����ּ��� ex)accessory#" << std::endl;
					std::cin >> t_name;
					std::cout << std::endl;

					std::cout << "�Ǽ��縮�� ��Ÿ���� �Է����ּ��� " << std::endl;
					std::cin >> style;
					std::cout << std::endl;

					std::cout << "�Ǽ��縮�� ������ �Է����ּ��� " << std::endl;
					std::cin >> col;
					std::cout << std::endl;




					std::string t_str = pictureroot_shoes;
					char * pic_root = new char[t_str.size() + 50];

					strcpy(pic_root, t_str.c_str());

					pic_root[t_str.size()] = '\0'; // 



					std::string pr = t_str;
					Accessory temp_acc(t_name, style, col, pr);

					//m.Add_accessory(temp_acc);

					std::cout << "�Ǽ��縮�� �����Կ��� �ϰڽ��ϴ�. �غ��Ͻð�~ ESC ���! " << std::endl;

					//sleep

					while (Esc != 27 && cap.isOpened()) {
						bool Frame = cap.read(save_img);
						if (!Frame || save_img.empty()) {
							std::cout << "error: frame not read from webcam\n";
							break;
						}
						namedWindow("save_img", CV_WINDOW_NORMAL);
						imshow("imgOriginal", save_img);
						Esc = waitKey(1);//ESC ������ ����!

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

			else if (managechoice == 2) { /////����
				std::cout << "������ ���� ������ �Է��ϼ��� 1.�ƿ��� 2.�ѿ� 3.���� 4.���� 5.�Ź� 6.�Ǽ��縮" << std::endl;
				std::cin >> catego;
				std::cout << std::endl;

				if (catego == 1) {//outer 
					std::cout << "������ �ƿ����� �̸��� �Է��ϼ��� ex) outer1" << std::endl;
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
					std::cout << "������  �ѿ��� �̸��� �Է��ϼ��� ex) overgarment1" << std::endl;
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
					std::cout << "������ ������ �̸��� �Է��ϼ��� ex) tops1" << std::endl;
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
					std::cout << "������ ������ �̸��� �Է��ϼ��� ex) pants1" << std::endl;
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
					std::cout << "������ �Ź��� �̸��� �Է��ϼ��� ex) shoes1" << std::endl;
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
					std::cout << "������ �Ǽ��縮�� �̸��� �Է��ϼ��� ex) accessory1" << std::endl;
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
				else if (managechoice == 3) { //��ȸ
					std::cout << "���忡�� ��ȸ�� ����� ��ȣ�� �Է��ϼ��� 1.�ƿ��� 2.�ѿ� 3.���� 4.���� 5.�Ź� 6.�Ǽ��縮" << std::endl;
					std::cin >> checknum;
					std::cout << std::endl;

					if (checknum == 1) {//�ƿ���
						std::cout << "���忡�� �ƿ��͸� ��ȸ�մϴ�." << std::endl;
						
						std::cout << std::endl;
						m.print_clothes(1);
						std::cout << "������� �ƿ����� �̸��� �Է��� �ּ���." << std::endl;
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
					else if (checknum == 2) {//�ѿ�
						std::cout << "���忡�� �ѿ��� ��ȸ�մϴ�." << std::endl;

						std::cout << std::endl;
						m.print_clothes(6);

						std::cout << "������� �ѿ��� �̸��� �Է��� �ּ���." << std::endl;
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
					else if (checknum == 3) {//����
						std::cout << "���忡�� ���Ǹ� ��ȸ�մϴ�." << std::endl;

						std::cout << std::endl;
						m.print_clothes(2);
						std::cout << "������� ������ �̸��� �Է��� �ּ���." << std::endl;
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
					else if (checknum == 4) {//����
						std::cout << "���忡�� ���Ǹ� ��ȸ�մϴ�." << std::endl;

						std::cout << std::endl;
						m.print_clothes(3);
						std::cout << "������� ������ �̸��� �Է��� �ּ���." << std::endl;
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
					else if (checknum == 5) {//�Ź�
						std::cout << "���忡�� �Ź��� ��ȸ�մϴ�." << std::endl;

						std::cout << std::endl;
						m.print_clothes(5);

						std::cout << "������� �Ź��� �̸��� �Է��� �ּ���." << std::endl;
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
					else if (checknum == 6) {//�Ǽ��縮
						std::cout << "���忡�� �Ǽ��縮�� ��ȸ�մϴ�." << std::endl;

						std::cout << std::endl;
						m.print_clothes(4);
						std::cout << "������� �Ǽ��縮�� �̸��� �Է��� �ּ���." << std::endl;
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

		case 2://�µ�Ȯ��

			std::cout.setf(std::ios::fixed);
			std::cout.precision(1);
			std::cout << "���̿��� ���� ����� ����µ�: " << temperature << std::endl;
			break;

		case 3://�ڵ��ϱ�
			check = 0;
			std::cout << "���ϸ��� �ڵ�����Ͱ� �ڵ� �����մϴ�!" << std::endl;




			//result = cordi.cordinate("new_color.txt", temperature);

			//std::string& name, std::string& style, std::string& col, std::string& len, int insulation, int trend, int priority, std::string& texture, std::string&  pictureroot


			//�ʼ��׸� ��������, �ٽ� �ڵ�
			//���� �� �����ϰ�� �Ǵ��ؾ���.
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


			//�ڿ� set �� outer,overgarment,top,pants,shoes,accessory�� ������ ���� �����ռ� �ٸ���.
			
			while (check !=1)
			{
				check = 0;
				
				//////////////////////////�ƿ��� ������ �ѿ�,����,����,�Ź�,�Ǽ�

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

					//��ġ��
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
						std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
						return -1;
					}

					char savefilename[128];

					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					//sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
					//imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					hconcat(image_temp1, image_temp2, image_temp3);
					hconcat(image_temp3, image_5, image_result);
					resize(image_result, image_result, Size(600, 300), 0, 0, INTER_CUBIC);

					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img�� ���Ϸ� �����Ѵ�.


					imshow("resultimage.png", image_result);
					waitKey(0);




					std::cout << result.size() - 1 << "���� �ĺ��� ���ֽ��ϴ�" << "�� �ڵ� ������ ��ʴϱ�? (�� :1 �ƴϿ�:2) �ƴϿ��� ������ �ٸ��ĺ��� �������ϴ�." << std::endl;
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
				//�ƿ��� ���µ� �ѿʵ� ������ ����,����,�Ź�,�Ǽ��縮
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

					//��ġ��
					//�ΰ��� ���ϱ�
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty())
					{
						std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
						return -1;
					}

					char savefilename[128];        // �̹��� ���� �̸��� 200�� �̳��� �����ϱ� ���� char ���� ����



												   // �ΰ��� �̹����� �����ִ� ������ ��ɾ� :-)
					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																						 //imwrite(savefile, image_temp2);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_temp1, image_temp2, image_result);

					//resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img�� ���Ϸ� �����Ѵ�.


					imshow("resultimage.png", image_result);
					waitKey(0);

					std::cout << result.size() - 1 << "���� �ĺ��� ���ֽ��ϴ�" << "�� �ڵ� ������ ��ʴϱ�? (�� :1 �ƴϿ�:2) �ƴϿ��� ������ �ٸ��ĺ��� �������ϴ�." << std::endl;
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
				//�ƿ��� ���µ� �Ǽ��縮�� ������ �ѿ�,����,����,�Ź�
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

					//��ġ��

					//�ΰ��� ���ϱ�
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty())
					{
						std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
						return -1;
					}

					char savefilename[128];        // �̹��� ���� �̸��� 200�� �̳��� �����ϱ� ���� char ���� ����



												   // �ΰ��� �̹����� �����ִ� ������ ��ɾ� :-)
					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																						 //imwrite(savefile, image_temp2);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_temp1, image_temp2, image_result);

					resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img�� ���Ϸ� �����Ѵ�.


					imshow("resultimage.png", image_result);
					waitKey(0);

					std::cout << result.size() - 1 << "���� �ĺ��� ���ֽ��ϴ�" << "�� �ڵ� ������ ��ʴϱ�? (�� :1 �ƴϿ�:2) �ƴϿ��� ������ �ٸ��ĺ��� �������ϴ�." << std::endl;
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
				//�ƿ��� ���µ� �ѿ�,�Ǽ��縮�� ������ ����,����,�Ź�
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

					
					//��ġ��
					//�ΰ��� ���ϱ�
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty())
					{
						std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
						return -1;
					}

					char savefilename[128];        // �̹��� ���� �̸��� 200�� �̳��� �����ϱ� ���� char ���� ����



												   // �ΰ��� �̹����� �����ִ� ������ ��ɾ� :-)
					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_temp1, image_3, image_result);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																						 //imwrite(savefile, image_temp2);        // img�� ���Ϸ� �����Ѵ�.

					

					//resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img�� ���Ϸ� �����Ѵ�.


					imshow("resultimage.png", image_result);
					waitKey(0);

					std::cout << result.size() - 1 << "���� �ĺ��� ���ֽ��ϴ�" << "�� �ڵ� ������ ��ʴϱ�? (�� :1 �ƴϿ�:2) �ƴϿ��� ������ �ٸ��ĺ��� �������ϴ�." << std::endl;
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

				////////////////////////�ƿ��� ������ �ƿ���,�ѿ�,����,����,�Ź�,�Ǽ� ���ִ°�
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


					//��ġ��
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
						std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
						return -1;
					}

					char savefilename[128];

					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					//sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
					//imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					hconcat(image_5, image_6, image_temp3);
					hconcat(image_temp1, image_temp2, image_temp4);

					hconcat(image_temp3, image_temp4, image_result);

					resize(image_result, image_result, Size(600, 300), 0, 0, INTER_CUBIC);

					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img�� ���Ϸ� �����Ѵ�.


					imshow("resultimage.png", image_result);
					waitKey(0);




					std::cout << result.size() - 1 << "���� �ĺ��� ���ֽ��ϴ�" << "�� �ڵ� ������ ��ʴϱ�? (�� :1 �ƴϿ�:2) �ƴϿ��� ������ �ٸ��ĺ��� �������ϴ�." << std::endl;
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


				//�ƿ��� �ִµ�, �ѿ� ������ �ƿ���,����,����,�Ź�,�Ǽ��縮
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


					//��ġ��
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
						std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
						return -1;
					}

					char savefilename[128];

					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					//sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
					//imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					hconcat(image_temp1, image_temp2, image_temp3);
					hconcat(image_temp3, image_5, image_result);
					resize(image_result, image_result, Size(600, 300), 0, 0, INTER_CUBIC);

					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img�� ���Ϸ� �����Ѵ�.


					imshow("resultimage.png", image_result);
					waitKey(0);




					std::cout << result.size() - 1 << "���� �ĺ��� ���ֽ��ϴ�" << "�� �ڵ� ������ ��ʴϱ�? (�� :1 �ƴϿ�:2) �ƴϿ��� ������ �ٸ��ĺ��� �������ϴ�." << std::endl;
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
				//�ƿ��� �ִµ�,�Ǽ��縮������ �ƿ��� �ѿ� ���� ���� �Ź� 
				else if (result[0].get_outer().get_name() != "no"&&result[0].get_overgarment().get_name() != "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() == "no") {
					//������ ���Ӱ� ��Ʈ ���ϱ�
					//delete�ؾߵ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111

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
						std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
						return -1;
					}

					char savefilename[128];

					hconcat(image_1, image_2, image_temp1);

					//resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_3, image_4, image_temp2);

					//resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					hconcat(image_temp1, image_temp2, image_temp3);
					hconcat(image_temp3, image_5, image_result);
					resize(image_result, image_result, Size(600, 300), 0, 0, INTER_CUBIC); 

					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img�� ���Ϸ� �����Ѵ�.


					imshow("resultimage.png", image_result);
					waitKey(0);



					
					std::cout << result.size() - 1 << "���� �ĺ��� ���ֽ��ϴ�" << "�� �ڵ� ������ ��ʴϱ�? (�� :1 �ƴϿ�:2) �ƴϿ��� ������ �ٸ��ĺ��� �������ϴ�." << std::endl;
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
				//�ƿ��� �ִµ� ,�ѿ� ,�Ǽ��縮 ������ //�ƿ���,����,����,�Ź�
				else if (result[0].get_outer().get_name() != "no"&&result[0].get_overgarment().get_name() == "no"&&result[0].get_top().get_name() != "no"&&result[0].get_pants().get_name() != "no"&&result[0].get_shoes().get_name() != "no"&&result[0].get_accessory().get_name() == "no") {
					//������ ���Ӱ� ��Ʈ ���ϱ�


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



					//�ΰ��� ���ϱ�
					Mat image_1 = imread(pic_root1, IMREAD_COLOR);
					Mat image_2 = imread(pic_root2, IMREAD_COLOR);
					Mat image_3 = imread(pic_root3, IMREAD_COLOR);
					Mat image_4 = imread(pic_root4, IMREAD_COLOR);
					Mat image_temp1;
					Mat image_temp2;
					Mat image_result;

					if (image_1.empty() && image_2.empty() && image_3.empty() && image_4.empty())
					{
						std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
						return -1;
					}

					char savefilename[128];        // �̹��� ���� �̸��� 200�� �̳��� �����ϱ� ���� char ���� ����



											   // �ΰ��� �̹����� �����ִ� ������ ��ɾ� :-)
					hconcat(image_1, image_2, image_temp1);

					resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																						 //imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_3, image_4, image_temp2);

					resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																						 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																						 //imwrite(savefile, image_temp2);        // img�� ���Ϸ� �����Ѵ�.

					hconcat(image_temp1, image_temp2, image_result);

					resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
					sprintf_s(savefilename, "C:\\opencv\\image\\result\\resultiamge.jpg");
					imwrite(savefilename, image_result);        // img�� ���Ϸ� �����Ѵ�.


					imshow("resultimage.png", image_result);
					waitKey(0);

					std::cout <<result.size()-1 <<"���� �ĺ��� ���ֽ��ϴ�"<<"�� �ڵ� ������ ��ʴϱ�? (�� :1 �ƴϿ�:2) �ƴϿ��� ������ �ٸ��ĺ��� �������ϴ�." << std::endl;
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
			std::cout << "daily coordinator System �� �����մϴ�." << std::endl;
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
		//����
		Closetmanager m;

		//get
		m.Add_Outer(o);
		m.delete_Outer("top101");
		*/


		//use opencv;~~~~
		/*
		String filepath1("C:\\opencv\\image\\im1\\������1.png");
		String filepath2("C:\\opencv\\image\\im2\\������2.png");
		String filepath3("C:\\opencv\\image\\im3\\������3.png");
		String filepath4("C:\\opencv\\image\\im4\\������4.png");
		Mat image_1 = imread(filepath1, IMREAD_COLOR);
		Mat image_2 = imread(filepath2, IMREAD_COLOR);
		Mat image_3 = imread(filepath3, IMREAD_COLOR);
		Mat image_4 = imread(filepath4, IMREAD_COLOR);
		Mat image_temp1;
		Mat image_temp2;
		Mat image_result;

		if (image_1.empty() && image_2.empty())
		{
			std::cout << "�̹����� ���ų�, ��ȿ�� ���� ������ �ƴմϴ�." << std::endl;
			return -1;
		}

		//imshow("image", image_1);      // ���� ���
		//imshow("image2", image_2);




		char savefile[128];        // �̹��� ���� �̸��� 200�� �̳��� �����ϱ� ���� char ���� ����



								   // �ΰ��� �̹����� �����ִ� ������ ��ɾ� :-)
		hconcat(image_1, image_2, image_temp1);

		resize(image_temp1, image_temp1, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																			 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage1.png");
																			 //imwrite(savefile, image_temp1);        // img�� ���Ϸ� �����Ѵ�.

		hconcat(image_3, image_4, image_temp2);

		resize(image_temp2, image_temp2, Size(600, 300), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
																			 //sprintf_s(savefile, "C:\\opencv\\image\\tempimage2.png");
																			 //imwrite(savefile, image_temp2);        // img�� ���Ϸ� �����Ѵ�.

		hconcat(image_temp1, image_temp2, image_result);

		resize(image_result, image_result, Size(800, 400), 0, 0, INTER_CUBIC); // �������� ������ ���� ũ�⸦ downsizing�ؼ� �����Ѵ�
		sprintf_s(savefile, "C:\\opencv\\image\\result\\resultiamge.png");
		imwrite(savefile, image_result);        // img�� ���Ϸ� �����Ѵ�.


		imshow("resultimage.png", image_result);
		waitKey(0);

		*/

		return 0;
	}
