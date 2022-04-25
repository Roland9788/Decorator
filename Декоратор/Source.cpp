#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Data
{
public:
	string FileName;

	Data()
	{
		FileName = "DataFile.txt";
	}

	virtual void WriteData(string data) = 0;

	virtual string ReadData() = 0;

};

class FileData :public  Data
{
	string FileName;
	string buff;
public:

	FileData()
	{
		FileName = "DataFile.txt";
	}

	FileData(string FileName)
	{
		this->FileName = FileName;
		ofstream file(FileName);
	}

	virtual void WriteData(string data)
	{
		setlocale(LC_ALL, "Rus");
		ofstream file(FileName);
		file << buff;
		
	}

	virtual string ReadData()
	{
		ifstream file(FileName);
		cout << "\nСчитывание информации из файла ... \n";

		while (!file.eof()) 
		{
			file >> buff;
		}
		return buff;
	}

};

class DataDecorator : public Data
{
protected:
	Data* decor;
public:

	DataDecorator()
	{
		decor = nullptr;
	}

	DataDecorator(Data* source)
	{
		decor = source;
	}

	virtual void WriteData(string data)
	{
		decor->WriteData(data);
	}

	virtual string ReadData()
	{
		return decor->ReadData();
	}


};

class DataEncryption:public DataDecorator
{

public:

	DataEncryption(){}

	virtual void WriteData(string data)
	{
		cout << "\nШифрование информации в файле ... \n";
		ofstream file(FileName);
		for (int i = 0; i < data.size(); i++)
			data[i] += 3;
		file << data;
	}

	virtual string ReadData()
	{
		string buff;
		ifstream file(FileName);
		cout << "\nРасшифровка информации из файла ... \n";

		while (!file.eof())
		{
			file >> buff;
		}
		for (int i = 0; i < buff.size(); i++)
			buff[i] -= 3;
		return buff;
	}

};




int main()
{
	setlocale(LC_ALL, "Rus");

	FileData data;
	DataEncryption dataEnc;
	string buff;
	cout << "\nВведите текст который необходимо поместить в файл \n";

	getline(cin, buff);
	dataEnc.WriteData(buff);
	cout << dataEnc.ReadData();

	return 0;
}