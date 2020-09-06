#include <iostream>
#include <string>
#include <fstream>
#include <atltime.h>
using namespace std;

class Database
{
private:

	const string connectionString = "database.txt";
	bool isConnected = false;

public:

	void Log(string file_path)
	{
		SYSTEMTIME st;
		GetSystemTime(&st);

		ofstream fout;

		string message;
		string data_and_time;

		fout.open(file_path, ios::app);
		
		cout << "Enter message" << endl;
		cout << "->";
		cin >> message;
		fout << message << "  ";
		fout << to_string(st.wHour) + ":" + to_string(st.wMinute) + " / " + to_string(st.wDay) + "." + to_string(st.wMonth) + "." + to_string(st.wYear) << endl;
	
		fout.close();
	}

	bool IsConnect(string str)
	{
		if (str == connectionString)
		{
			return (rand() % 10) < 6;
		}
		else return false;
	}

};

class DatabaseProxy
{
private:
	Database* _database = new Database();
	const string _connectionString = "localTempDatabase.txt";
public:
	void Log()
	{
		if (_database == nullptr)
		{
			_database = new Database();
		}

		if (_database->IsConnect("database.txt") == false)
		{
			_database->Log(_connectionString);
		}
		else
		{
			bool is_clear = false;
			ifstream f;
			f.open(_connectionString);
			if (f)
			{
				char sumbol;
				if (!(f.get(sumbol)))
				{
					f.close();
				}
				else
				{
					f.close();
					f.open(_connectionString);
					ofstream fout;
					fout.open("database.txt", ios::app);
					string a;
					while (!f.eof())
					{
						getline(f, a);
						fout << a;
					}
					fout << endl;
					fout.close();
				}
			}
			f.close();
			ofstream ofs;
			ofs.open(_connectionString);
			ofs.close();


			_database->Log("database.txt");

		}
	}
};

int main()
{
	srand(time(0));

	DatabaseProxy* proxy = new DatabaseProxy();

	proxy->Log();

	system("pause");
	return 0;
}
