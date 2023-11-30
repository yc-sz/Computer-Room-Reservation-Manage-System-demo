#include"BookProcesser.h"

BookProcesser::BookProcesser()
{
	this->load_room_capacity();
	this->init_status();
	this->load_status();
	this->save_status();
}

BookProcesser::~BookProcesser()
{
	//释放教室预约状态数组
	for (int i = 0; i < this->room_num; i++)
	{
		for (int j = 0; j < this->day_num; j++)
		{
			delete[] this->room_status[i][j];
			this->room_status[i][j] = NULL;
		}
		delete[] this->room_status[i];
		this->room_status[i] = NULL;
	}
	delete[] this->room_status;
	this->room_status = NULL;
}

void BookProcesser::init_status()
{
	//初始化教室预约状态，全部赋空闲状态
	this->room_status = new int** [this->room_num];
	for (int i = 0; i < this->room_num; i++) 
	{
		this->room_status[i] = new int* [this->day_num];
		for (int j = 0; j < this->day_num; j++)
		{
			this->room_status[i][j] = new int[this->time_num];
			for (int k = 0; k < this->time_num; k++)
			{
				this->room_status[i][j][k] = 0;   //初始化为0，即空闲状态
			}
		}
	}
}

void BookProcesser::save_status()
{
	ofstream ofs(STATUSFILE, ios::out | ios::trunc);
	for (int room_num = 0; room_num < this->room_num; room_num++)
	{
		ofs << room_num << "," << endl;
		for (int time_num = 0; time_num < this->time_num; time_num++)
		{
			for (int day_num = 0; day_num < this->day_num; day_num++)
			{
				ofs << this->room_status[room_num][day_num][time_num] << ",";
			}
			ofs << endl;
		}
	}
	ofs.close();
}

void BookProcesser::load_status()
{
	ifstream ifs(STATUSFILE, ios::in);
	if (ifs.is_open())
	{
		char ch;
		ifs >> ch;
		if (!ifs.eof())
		{
			ifs.putback(ch);
			string buf = "";
			int line = 0;
			int room_index;
			while (ifs >> buf)
			{
				switch ((line % 3))
				{
				case 0:
				{
					int pos = -1;
					int start = 0;
					pos = buf.find(",", start);
					room_index = stoi(buf.substr(start, pos - start));
					break;
				}
				case 1:
				{	//上午时段
					int day = 0;
					int pos = -1;
					int start = 0;
					while (true)
					{
						pos = buf.find(",", start);
						if (pos == -1) {
							break;
						}
						int status = stoi(buf.substr(start, pos - start));
						this->room_status[room_index][day][0] = status;
						start = pos + 1;
						day++;
					}
					//this->day_num = day - 1;
					break;
				}
				case 2:
				{	//下午时段
					int day = 0;
					int pos = -1;
					int start = 0;
					while (true)
					{
						pos = buf.find(",", start);
						if (pos == -1) {
							break;
						}
						int status = stoi(buf.substr(start, pos - start));
						this->room_status[room_index][day][1] = status;
						start = pos + 1;
						day++;
					}
					break;
				}
				default:
					break;
				}
				line++;
			}
		}
		else
		{
			cout << STATUSFILE << "文件为空!" << endl;
		}
	}
	else
	{
		cout << STATUSFILE << "文件打开失败或不存在!" << endl;
	}
	ifs.close();
}

void BookProcesser::load_room_capacity()
{
	int room_count = 0;	//记录教室数量，默认0
	ifstream ifs(ROOMFILE, ios::in);

	//检测room.csv是否打开成功
	if (ifs.is_open()) 
	{
		char ch;
		ifs >> ch;
		if (!ifs.eof())		//若room.csv文件不为空
		{
			ifs.putback(ch);
			string buff;
			while (ifs >> buff)
			{
				int num = -1;
				int capacity = -1;
				int index = 0;
				int pos = -1;
				int start = 0;
				while (true)
				{
					if (index > 1)
					{
						break;
					}
					switch (index)
					{
					case 0:
						pos = buff.find(",", start);
						num = stoi(buff.substr(start, pos - start));
						start = pos + 1;
						break;
					case 1:
						pos = buff.find(",", start);
						capacity = stoi(buff.substr(start, pos - start));
						start = pos + 1;
						break;
					default:
						break;
					}
					index++;
				}
				this->room_num_capacity.insert(make_pair(num, capacity));
				room_count++;
			}
		}
		else
		{
			cout << ROOMFILE << "文件为空!" << endl;
		}
	}
	else
	{
		cout << ROOMFILE << "文件不存在或打开失败" << endl;
	}
	this->room_num = room_count;	//更新教室数量
	ifs.close();
}

void BookProcesser::record_apply(string apply_acc, string apply_name, string audit_acc, string audit_name, string room, string day, string time, int result)
{
	//记录审核后的申请信息
	ifstream ifs(RECORDFILE, ios::in);
	if (ifs.is_open())
	{
		char ch;
		ifs >> ch;
		if (ifs.eof()) 
		{
			ofstream ofs(RECORDFILE, ios::out);
			ofs << "申请人账号,申请人姓名,审核人账号,审核人姓名,机房号,日期,时段,审核结果," << endl;
			ofs << apply_acc << "," << apply_name << "," << audit_acc << "," << audit_name << "," << room << "," << day << "," << time << "," << result << "," << endl;
			ofs.close();
		}
		else
		{
			ofstream ofs(RECORDFILE, ios::out | ios::app);
			ofs << apply_acc << "," << apply_name << "," << audit_acc << "," << audit_name << "," << room << "," << day << "," << time << "," << result << "," << endl;
			ofs.close();
		}
	}
	else
	{
		ofstream ofs(RECORDFILE, ios::out);
		ofs << "申请人账号,申请人姓名,审核人账号,审核人姓名,机房号,日期,时段,审核结果," << endl;
		ofs << apply_acc << "," << apply_name << "," << audit_acc << "," << audit_name << "," << room << "," << day << "," << time << "," << result << "," << endl;
		ofs.close();
	}
	ifs.close();
}

int*** BookProcesser::get_room_status()
{
	return this->room_status;
}

int BookProcesser::get_room_num()
{
	return this->room_num;
}

int BookProcesser::get_room_capacity(int room)
{
	return this->room_num_capacity[room];
}

void BookProcesser::apply_receive(string apply_acc, string apply_name, int room, int day, int time)
{
	ofstream ofs(AUDITFILE, ios::out | ios::app);
	ofs << apply_acc << "," << apply_name << "," << room << "," << day << "," << time << "," << "-1," << endl;	//最后加上-1代表是待审核文件
	ofs.close();
}

void BookProcesser::apply_audit(string tea_acc, string tea_name, int num, int result)
{
	this->record_apply(this->m_audit[num][0], this->m_audit[num][1], tea_acc, tea_name, this->m_audit[num][2], this->m_audit[num][3], this->m_audit[num][4], result);	//记录审核记录
	//若审核结果为通过，则修改对应教室状态
	if (result) {
		int room = stoi(this->m_audit[num][2]);
		int day = stoi(this->m_audit[num][3]);
		int time = stoi(this->m_audit[num][4]);
		this->room_status[room - 1][day - 1][time - 1] = 1;
		this->save_status();
	}
	this->m_audit.erase(num);		//删除map中key为num的元素
	//将删除审核后记录的map写回audit.csv
	ofstream ofs(AUDITFILE, ios::out | ios::trunc);
	for (map<int, vector<string>>::const_iterator it = this->m_audit.begin(); it != this->m_audit.end(); it++)
	{
		ofs << it->second[0] << "," << it->second[1] << "," << it->second[2] << "," << it->second[3] << "," << it->second[4] << "," << it->second[5] << endl;
	}
	ofs.close();
}

int BookProcesser::get_day_num()
{
	return this->day_num;
}

int BookProcesser::get_time_num()
{
	return this->time_num;
}

vector<vector<string>> BookProcesser::get_personl_apply(string apply_acc)
{
	vector<vector<string>> records;

	ifstream ifs_audit(AUDITFILE, ios::in);
	if (ifs_audit.is_open())
	{
		char ch;
		ifs_audit >> ch;
		if (!ifs_audit.eof())
		{
			ifs_audit.putback(ch);
			string buf;
			while (ifs_audit >> buf)
			{
				vector<string> v_temp;
				int start = 0;
				int pos = buf.find(",", start);
				string acc = buf.substr(start, pos-start);
				//先对比账号是否一致
				if (acc.compare(apply_acc) == 0)
				{
					//一致，先将申请人账号读取进容器，然后开始将其他信息读取进容器
					v_temp.push_back(acc);
					start = pos + 1;
					while (true)
					{
						pos = buf.find(",", start);
						if (pos == -1)
						{
							break;
						}
						v_temp.push_back(buf.substr(start, pos - start));
						start = pos + 1;
					}
					//v_temp.push_back("-1");		//因为是待审核文件，所以赋-1代表待审核
					records.push_back(v_temp);
				}
			}
		}
		else
		{
			//cout << AUDITFILE << "文件为空!" << endl;
		}
	}
	else
	{
		//cout << AUDITFILE << "文件打开失败或不存在!" << endl;
	}
	ifs_audit.close();

	ifstream ifs_record(RECORDFILE, ios::in);
	if (ifs_record.is_open())
	{
		char ch;
		ifs_record >> ch;
		if (!ifs_record.eof())
		{
			ifs_record.putback(ch);
			string buf;
			while (ifs_record >> buf)
			{
				vector<string> v_temp;
				int start = 0;
				int pos = buf.find(",", start);
				string acc = buf.substr(start, pos - start);
				//先对比账号是否一致
				if (acc.compare(apply_acc) == 0)
				{
					//一致，先将申请人账号读取进容器，然后开始将其他信息读取进容器
					v_temp.push_back(acc);
					start = pos + 1;
					int index = 1;
					while (true)
					{
						pos = buf.find(",", start);
						if (pos == -1)
						{
							break;
						}
						if (index > 1 && index < 4)	//审核人账号和姓名不加入v_temp容器中
						{
							start = pos + 1;
							index++;
							continue;
						}
						v_temp.push_back(buf.substr(start, pos - start));
						start = pos + 1;
						index++;
					}
					records.push_back(v_temp);
				}
			}
		}
		else
		{
			//cout << RECORDFILE << "文件为空!" << endl;
		}
	}
	else
	{
		//cout << RECORDFILE << "文件打开失败或不存在!" << endl;
	}
	ifs_record.close();

	return records;
}

map<int, vector<string>> BookProcesser::get_all_audit()
{
	//读取待审核记录
	ifstream ifs(AUDITFILE, ios::in);
	if (ifs.is_open())
	{
		char ch;
		ifs >> ch;
		if (!ifs.eof())
		{
			ifs.putback(ch);
			int index = 0;
			string buf;
			while (ifs >> buf)
			{
				int pos = -1;
				int start = 0;
				vector<string> v_temp;
				while (true)
				{
					pos = buf.find(",", start);
					if (pos == -1)
					{
						break;
					}
					v_temp.push_back(buf.substr(start, pos - start));
					start = pos + 1;
				}
				v_temp.push_back("-1");		// -1表示待审核
				this->m_audit.insert(make_pair(index + 1, v_temp));
				index++;
			}
		}
		else
		{
			//cout << AUDITFILE << "文件为空!" << endl;
		}
	}
	else
	{
		//cout << AUDITFILE << "文件打开失败或不存在!" << endl;
	}
	ifs.close();

	return this->m_audit;
}

map<int, vector<string>> BookProcesser::get_all_record()
{
	map<int, vector<string>> m_temp;
	
	ifstream ifs(RECORDFILE, ios::in);
	if (ifs.is_open())
	{
		char ch;
		ifs >> ch;
		if (!ifs.eof())
		{
			ifs.putback(ch);
			int index = 0;
			string buf;
			while (ifs >> buf)
			{
				vector<string> v_temp;
				int pos = -1;
				int start = 0;
				if (index == 0)
				{
					index++;
					continue;
				}
				while (true)
				{
					pos = buf.find(",", start);
					if (pos == -1)
					{
						break;
					}
					v_temp.push_back(buf.substr(start, pos - start));
					start = pos + 1;
				}
				m_temp.insert(make_pair(index, v_temp));
				index++;
			}
		}
		else
		{
			cout << RECORDFILE << "文件为空!" << endl;
		}
	}
	else
	{
		cout << RECORDFILE << "文件打开失败或不存在!" << endl;
	}
	ifs.close();

	return m_temp;
}

void BookProcesser::clear_record_audit()
{
	ofstream ofs_record(RECORDFILE, ios::out | ios::trunc);
	ofs_record.close();
	ofstream ofs_audit(AUDITFILE, ios::out | ios::trunc);
	ofs_audit.close();

	this->m_audit.clear();
	this->init_status();
	this->save_status();
}

bool BookProcesser::cancel_personal_book(vector<string> apply_info)
{
	if (apply_info[5].compare("-1") == 0)		//在待审核记录中
	{
		map<int, vector<string>> m_temp;
		m_temp = this->get_all_audit();

		for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
		{
			if (it->second[0].compare(apply_info[0]) == 0)				//对比学生账号
			{
				if (it->second[2].compare(apply_info[2]) == 0)			//对比机房编号
				{
					if (it->second[3].compare(apply_info[3]) == 0)		//对比申请日期
					{
						if (it->second[4].compare(apply_info[4]) == 0)	//对比申请时段
						{
							this->record_apply(it->second[0], it->second[1], "无", "无", it->second[2], it->second[3], it->second[4], -2);	//记录到record.csv文件并将状态设置为-2代表已取消
							this->m_audit.erase(it->first);				//删除m_audit对应记录
							//将删除取消后记录的map写回audit.csv
							ofstream ofs(AUDITFILE, ios::out | ios::trunc);
							for (map<int, vector<string>>::const_iterator c_it = this->m_audit.begin(); c_it != this->m_audit.end(); c_it++)
							{
								ofs << c_it->second[0] << "," << c_it->second[1] << "," << c_it->second[2] << "," << c_it->second[3] << "," << c_it->second[4] << "," << c_it->second[5] << "," << endl;
							}
							ofs.close();
							return true;	//返回取消成功
						}
					}
				}
			}
		}
	}
	else if(apply_info[5].compare("1") == 0 || apply_info[5].compare("0") == 0 || apply_info[5].compare("-2") == 0)	//在审核后或已取消记录中
	{
		if (apply_info[5].compare("-2") == 0)		//在已取消记录中
		{
			cout << "请勿重复取消!" << endl;
		}
		else if (apply_info[5].compare("0") == 0)	//未通过记录
		{
			cout << "申请未通过，无需取消!" << endl;
		}
		else if (apply_info[5].compare("1") == 0)	//已通过记录
		{
			map<int, vector<string>> m_temp;
			m_temp = this->get_all_record();

			for (map<int, vector<string>>::iterator it = m_temp.begin(); it != m_temp.end(); it++)
			{
				if (it->second[0].compare(apply_info[0]) == 0)				//对比学生账号
				{
					if (it->second[4].compare(apply_info[2]) == 0)			//对比机房编号
					{
						if (it->second[5].compare(apply_info[3]) == 0)		//对比申请日期
						{
							if (it->second[6].compare(apply_info[4]) == 0)	//对比申请时段
							{
								//将对应教室状态置为空闲
								this->load_status();
								this->room_status[stoi(it->second[4]) - 1][stoi(it->second[5]) - 1][stoi(it->second[6]) - 1] = 0;
								this->save_status();

								//将审核状态置为已取消
								it->second[7] = "-2";

								//将修改后的记录写回record.csv
								ofstream ofs(RECORDFILE, ios::out | ios::trunc);
								ofs << "申请人账号,申请人姓名,审核人账号,审核人姓名,机房号,日期,时段,审核结果," << endl;
								for (map<int, vector<string>>::const_iterator c_it = m_temp.begin(); c_it != m_temp.end(); c_it++)
								{
									ofs << c_it->second[0] << ","
										<< c_it->second[1] << ","
										<< c_it->second[2] << ","
										<< c_it->second[3] << ","
										<< c_it->second[4] << ","
										<< c_it->second[5] << ","
										<< c_it->second[6] << ","
										<< c_it->second[7] << ","
										<< endl;
								}

								return true;	//返回取消成功
							}
						}
					}
				}
			}
		}
	}

	return false;
}