#include"SpeechManager.h"

SpeechManager::SpeechManager() {
	//��ʼ������������
	initSpeech();
	//����12��ѡ��
	createSpeaker();
	//��ȡ��¼
	loadScore();
}

void SpeechManager::show_Menu()
{
	cout << "**************** ��ӭ�μ��ݽ����� ****************" << endl;
	cout << "**************** 1����ʼ�ݽ����� *****************" << endl;
	cout << "**************** 2���ۿ�������� *****************" << endl;
	cout << "**************** 3����ձ�����¼ *****************" << endl;
	cout << "**************** 4���˳��������� *****************" << endl;
	cout << endl;

}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��!"<<endl;
	system("pause");
	exit(0);

}

void SpeechManager::initSpeech()
{
	//��ʼ������
	v1.clear();
	v2.clear();
	victory.clear();
	m_Speaker.clear();
	//��ʼ�������ִ�
	Index = 1;
	m_Record.clear();
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];
		//��������ѡ��
		Speaker sp;
		sp.s_name = name;
		for (int j = 0; j < 2; j++) {
			sp.s_score[j] = 0;
		}
		//��ѡ�ֱ�ŷ���v1����
		v1.push_back(i + 10001);
		//��ѡ�ֱ�ź�ѡ�ַ���map����
		m_Speaker.insert(pair<int,Speaker>(i+10001,sp));
	}
}

void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1.��ǩ
	speechDraw();
	//2.����
	speechContest();
	//3.��ʾ�������
	speechPromote();
	//�ڶ��ֱ���
	Index++;
	//1.��ǩ
	speechDraw();
	//2.����
	speechContest();
	//3.��ʾ���ս��
	speechPromote();
	//4.�������
	saveScore();

	//���ñ�����ȡ��¼
	//��ʼ������������
	initSpeech();
	//����12��ѡ��
	createSpeaker();
	//��ȡ��¼
	loadScore();

	
	
	cout << "���α����ѽ���" << endl;
	system("pause");
	system("cls");
	

}

void SpeechManager::speechDraw()
{
	cout << "�� "<<Index<<" �ֱ������ڳ�ǩ: " << endl;
	cout << "----------------------" << endl;
	cout << "��ǩ�������: " << endl;
	if (Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (auto i = v1.begin(); i != v1.end(); i++) {
			cout << *i <<" ";
		}
		cout << endl;	
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (auto i = v2.begin(); i != v2.end(); i++) {
			cout << *i << " ";
		}
		cout << endl;
	}
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest()
{
	cout << "-----------�� " << Index << " �ֱ�����ʽ��ʼ------------" << endl;
	multimap<double, int, greater<double>> m;//����ѡ�ֱ���������ʱ����
	int num = 0;//ѡ�ּ���
	vector<int> v_Src;//����ѡ������
	deque<double> v_score;//ѡ�ַ�������
	if (Index == 1)
		v_Src = v1;
	else
		v_Src = v2;
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//��ί���
		//cout << "���" << (*it) << "ѡ�ֳɼ�����: " << endl;
		for (int i = 0; i < 10; i++) {
			double sp_score = (rand() % 401 + 600) / 10.f;		
			//cout << sp_score << " ";
			v_score.push_back(sp_score);
		}
		//cout << endl;
		sort(v_score.begin(), v_score.end(), greater<double>());
		v_score.pop_back();//ȥ����ͷ�
		v_score.pop_front();//ȥ����߷�
		double sum = accumulate(v_score.begin(), v_score.end(), 0.0f);//�ܷ�
		double avg = sum / double(v_score.size());//ƽ����
		m_Speaker[*it].s_score[Index - 1] = avg;
		v_score.clear();
		m.insert(pair<double, int>(avg, *it));
		if (num % 6 == 0) {
			if (Index == 1) {
				cout << "��" << num / 6 << "��ɼ�����:" << endl;
				for (multimap<double, int>::iterator it = m.begin(); it != m.end(); it++) {
					cout << "ѡ�ֱ��: " << (*it).second <<" ����: "<<m_Speaker[(*it).second].s_name <<" �ɼ�: " << (*it).first << endl;
				}
				int j = 0;
				for (auto it = m.begin(); j < 3; it++, j++) {
					v2.push_back((*it).second);
				}
				if (num / 6 == 2) {
					cout << "-------------��" << Index << "�ֱ�������---------------" << endl;
					system("pause");
				}	
				m.clear();
				
			}
			else {
				cout << "��" << Index<< "�ֳɼ�����:" << endl;
				for (multimap<double, int>::iterator it = m.begin(); it != m.end(); it++) {
					cout << "ѡ�ֱ��: " << (*it).second << " ����: " << m_Speaker[(*it).second].s_name << " �ɼ�: " << (*it).first << endl;	
				}
				int j = 0;
				for (auto it = m.begin(); j < 3; it++, j++) {
					victory.push_back((*it).second);
				}
				cout << "-------------��" << Index << "�ֱ�������---------------" << endl;
				system("pause");
			}
			
		}
	}
}

void SpeechManager::speechPromote()
{
	
	if (Index == 1) {
		cout << "��" << Index << "�ֽ����������" << endl;
		for (auto it = v2.begin(); it != v2.end(); it++) {
			cout << "ѡ�ֱ��: " << (*it) << " ����: " << m_Speaker[*it].s_name << " �ɼ�: " << m_Speaker[*it].s_score[Index - 1] << endl;
		}
		system("pause");
	}
	else {
		cout << "��ʤ������: " << endl;
		for (auto it = victory.begin(); it != victory.end(); it++) {
			cout << "ѡ�ֱ��: " << (*it) << " ����: " << m_Speaker[*it].s_name << " �ɼ�: " << m_Speaker[*it].s_score[Index - 1] << endl;
		}
		system("pause");
	}
	system("cls");
	show_Menu();
	
	
}

void SpeechManager::saveScore() {
	ofstream fout;
	fout.open("speech.csv", ios_base::out | ios_base::app);
	for (vector<int>::iterator it = victory.begin(); it != victory.end();it++) {
		fout << *it << "," << m_Speaker[*it].s_name << "," << m_Speaker[*it].s_score[1] << ",";
	}
	fout << endl;
	fout.close();
	cout << "��¼�ѱ��� " << endl;
	fileIsEmpty = false;
}

void SpeechManager::loadScore()
{
	ifstream fin;
	fin.open("speech.csv", ios_base::in);

	//���ļ�ʧ��
	if (!fin.is_open()) {
		fileIsEmpty = true;
		//cout << "���ļ�ʧ��" << endl;
		fin.close();
		return ;
	}

	//�ļ����
	char ch;
	fin >> ch;
	if (fin.eof()) {
		//cout << "�ļ�Ϊ��" << endl;
		fileIsEmpty = true;
		fin.close();
		return ;
	}

	//�ļ���Ϊ��
	fileIsEmpty = false;
	fin.putback(ch);
	
	string data;
	int i = 1;
	while (fin>>data) {
		
		int pos = -1;
		int start=0;
		vector<string> s1;
		while (true) {
			pos = data.find(",",start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, (pos-start));
			
			start = pos + 1;
			s1.push_back(temp);
		}
		m_Record.insert(pair<int, vector<string>>(i, s1));
		i++;
	}

	


	fin.close();

	
}


void SpeechManager::showRecord()
{
	if (fileIsEmpty) {
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
		return;
	}
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		cout << "��" << (*it).first << "��ɼ�: " << endl << "�ھ����: " << (*it).second[0] << " �ھ��ɼ�: " << (*it).second[2] << endl << "�Ǿ����: " << (*it).second[3] << " �Ǿ��ɼ�: " << (*it).second[5] << endl << "�������: " << (*it).second[6] << " �����ɼ�: " << (*it).second[8] << endl;
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << "1��ȷ�� " << " 2������ " << endl;
	int i;
	cin >> i;
	//��������¼
	if (i == 1) {
		ofstream fout;
		fout.open("speech.csv", ios_base::trunc);
		fout.close();
		cout << "��ճɹ�!" << endl;
	}
	//��ʼ��
	initSpeech();
	//����12��ѡ��
	createSpeaker();
	//��ȡ��¼
	loadScore();
		
	system("pause");
	system("cls");
		
}

SpeechManager::~SpeechManager() {


}