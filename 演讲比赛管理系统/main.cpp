#include"SpeechManager.h"
#include<iostream>
#include<random>
using namespace std;

int main() {
	srand(time(0));
	SpeechManager sm;
	int choice;
	//����12��ѡ�ִ���
	/*for (auto i = sm.m_Speaker.begin(); i!=sm.m_Speaker.end(); i++) {
			cout << i.first;
			cout << i.second.s_name;
			cout << i.second.s_score[0] << endl;
		}*/
	while (true) {	
		sm.show_Menu();
		cout << "���������ѡ��:";
		cin >> choice;
		switch (choice) {
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴�����¼
			sm.showRecord();
			break;
		case 3://��ձ�����¼
			sm.clearRecord();
			break;
		case 4://�˳�
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