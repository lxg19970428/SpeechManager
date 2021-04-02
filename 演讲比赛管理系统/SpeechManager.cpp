#include"SpeechManager.h"

SpeechManager::SpeechManager() {
	//初始化容器和属性
	initSpeech();
	//创建12名选手
	createSpeaker();
	//获取记录
	loadScore();
}

void SpeechManager::show_Menu()
{
	cout << "**************** 欢迎参加演讲比赛 ****************" << endl;
	cout << "**************** 1、开始演讲比赛 *****************" << endl;
	cout << "**************** 2、观看往届比赛 *****************" << endl;
	cout << "**************** 3、清空比赛记录 *****************" << endl;
	cout << "**************** 4、退出比赛程序 *****************" << endl;
	cout << endl;

}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用!"<<endl;
	system("pause");
	exit(0);

}

void SpeechManager::initSpeech()
{
	//初始化容器
	v1.clear();
	v2.clear();
	victory.clear();
	m_Speaker.clear();
	//初始化比赛轮次
	Index = 1;
	m_Record.clear();
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];
		//创建具体选手
		Speaker sp;
		sp.s_name = name;
		for (int j = 0; j < 2; j++) {
			sp.s_score[j] = 0;
		}
		//将选手编号放入v1容器
		v1.push_back(i + 10001);
		//将选手编号和选手放入map容器
		m_Speaker.insert(pair<int,Speaker>(i+10001,sp));
	}
}

void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1.抽签
	speechDraw();
	//2.比赛
	speechContest();
	//3.显示晋级结果
	speechPromote();
	//第二轮比赛
	Index++;
	//1.抽签
	speechDraw();
	//2.比赛
	speechContest();
	//3.显示最终结果
	speechPromote();
	//4.保存分数
	saveScore();

	//重置比赛获取记录
	//初始化容器和属性
	initSpeech();
	//创建12名选手
	createSpeaker();
	//获取记录
	loadScore();

	
	
	cout << "本次比赛已结束" << endl;
	system("pause");
	system("cls");
	

}

void SpeechManager::speechDraw()
{
	cout << "第 "<<Index<<" 轮比赛正在抽签: " << endl;
	cout << "----------------------" << endl;
	cout << "抽签结果如下: " << endl;
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
	cout << "-----------第 " << Index << " 轮比赛正式开始------------" << endl;
	multimap<double, int, greater<double>> m;//排序选手比赛分数临时容器
	int num = 0;//选手计数
	vector<int> v_Src;//比赛选手容器
	deque<double> v_score;//选手分数容器
	if (Index == 1)
		v_Src = v1;
	else
		v_Src = v2;
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//评委打分
		//cout << "编号" << (*it) << "选手成绩如下: " << endl;
		for (int i = 0; i < 10; i++) {
			double sp_score = (rand() % 401 + 600) / 10.f;		
			//cout << sp_score << " ";
			v_score.push_back(sp_score);
		}
		//cout << endl;
		sort(v_score.begin(), v_score.end(), greater<double>());
		v_score.pop_back();//去除最低分
		v_score.pop_front();//去除最高分
		double sum = accumulate(v_score.begin(), v_score.end(), 0.0f);//总分
		double avg = sum / double(v_score.size());//平均分
		m_Speaker[*it].s_score[Index - 1] = avg;
		v_score.clear();
		m.insert(pair<double, int>(avg, *it));
		if (num % 6 == 0) {
			if (Index == 1) {
				cout << "第" << num / 6 << "组成绩如下:" << endl;
				for (multimap<double, int>::iterator it = m.begin(); it != m.end(); it++) {
					cout << "选手编号: " << (*it).second <<" 姓名: "<<m_Speaker[(*it).second].s_name <<" 成绩: " << (*it).first << endl;
				}
				int j = 0;
				for (auto it = m.begin(); j < 3; it++, j++) {
					v2.push_back((*it).second);
				}
				if (num / 6 == 2) {
					cout << "-------------第" << Index << "轮比赛结束---------------" << endl;
					system("pause");
				}	
				m.clear();
				
			}
			else {
				cout << "第" << Index<< "轮成绩如下:" << endl;
				for (multimap<double, int>::iterator it = m.begin(); it != m.end(); it++) {
					cout << "选手编号: " << (*it).second << " 姓名: " << m_Speaker[(*it).second].s_name << " 成绩: " << (*it).first << endl;	
				}
				int j = 0;
				for (auto it = m.begin(); j < 3; it++, j++) {
					victory.push_back((*it).second);
				}
				cout << "-------------第" << Index << "轮比赛结束---------------" << endl;
				system("pause");
			}
			
		}
	}
}

void SpeechManager::speechPromote()
{
	
	if (Index == 1) {
		cout << "第" << Index << "轮晋级结果如下" << endl;
		for (auto it = v2.begin(); it != v2.end(); it++) {
			cout << "选手编号: " << (*it) << " 姓名: " << m_Speaker[*it].s_name << " 成绩: " << m_Speaker[*it].s_score[Index - 1] << endl;
		}
		system("pause");
	}
	else {
		cout << "优胜者如下: " << endl;
		for (auto it = victory.begin(); it != victory.end(); it++) {
			cout << "选手编号: " << (*it) << " 姓名: " << m_Speaker[*it].s_name << " 成绩: " << m_Speaker[*it].s_score[Index - 1] << endl;
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
	cout << "记录已保存 " << endl;
	fileIsEmpty = false;
}

void SpeechManager::loadScore()
{
	ifstream fin;
	fin.open("speech.csv", ios_base::in);

	//打开文件失败
	if (!fin.is_open()) {
		fileIsEmpty = true;
		//cout << "打开文件失败" << endl;
		fin.close();
		return ;
	}

	//文件清空
	char ch;
	fin >> ch;
	if (fin.eof()) {
		//cout << "文件为空" << endl;
		fileIsEmpty = true;
		fin.close();
		return ;
	}

	//文件不为空
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
		cout << "文件为空或不存在" << endl;
		return;
	}
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		cout << "第" << (*it).first << "届成绩: " << endl << "冠军编号: " << (*it).second[0] << " 冠军成绩: " << (*it).second[2] << endl << "亚军编号: " << (*it).second[3] << " 亚军成绩: " << (*it).second[5] << endl << "季军编号: " << (*it).second[6] << " 季军成绩: " << (*it).second[8] << endl;
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "确定清空？" << "1、确定 " << " 2、返回 " << endl;
	int i;
	cin >> i;
	//清空往届记录
	if (i == 1) {
		ofstream fout;
		fout.open("speech.csv", ios_base::trunc);
		fout.close();
		cout << "清空成功!" << endl;
	}
	//初始化
	initSpeech();
	//创建12名选手
	createSpeaker();
	//获取记录
	loadScore();
		
	system("pause");
	system("cls");
		
}

SpeechManager::~SpeechManager() {


}