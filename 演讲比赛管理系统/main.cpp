#include"SpeechManager.h"
#include<iostream>
#include<random>
using namespace std;

int main() {
	srand(time(0));
	SpeechManager sm;
	int choice;
	//测试12名选手创建
	/*for (auto i = sm.m_Speaker.begin(); i!=sm.m_Speaker.end(); i++) {
			cout << i.first;
			cout << i.second.s_name;
			cout << i.second.s_score[0] << endl;
		}*/
	while (true) {	
		sm.show_Menu();
		cout << "请输入你的选择:";
		cin >> choice;
		switch (choice) {
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看往届记录
			sm.showRecord();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 4://退出
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;


		}
	}

	system("pause");
	return 0;
}