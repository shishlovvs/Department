#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
using std::cin;
using std::cout;

#define tab "\t"

class Human
{
protected:
	string last_name;
	string first_name;
	unsigned int age;
public:
	const string& get_last_name()const
	{
		return last_name;
	}
	const string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}
	//		Constructors:
	Human(const string& last_name, const string& first_name, unsigned int age)
	{
		set_last_name(last_name);//Инициализация в теле конструктора
		set_first_name(first_name);
		set_age(age);
#ifdef DEBUG
		cout << "HConstructor:\t" << this << endl;
#endif // DEBUG

	}
	virtual ~Human()
	{
#ifdef DEBUG
		cout << "HDestructor:\t" << this << endl;
#endif // DEBUG
	}
	//		Methods:
	virtual ostream& print(ostream& os)const
	{
		os.width(25);//Задает ширину поля, в которое будет выводиться следующее значение (в скобках указывается количество знакопозиций)
		os << left; os << typeid(*this).name();
		os.width(15); os << std::left; os << last_name;
		os.width(10); os << std::left; os << first_name;
		os.width(10); os << std::left; os << age;
		return os;
	}
	virtual ofstream& print(ofstream& os)const
	{
		os.width(25); os << left; os << typeid(*this).name() << "|";
		os.width(15); os << std::left; os << last_name << "|";
		os.width(10); os << std::left; os << first_name << "|";
		os.width(10); os << std::left; os << age << "|";
		/*os << std::to_string(age) + ",";*/
		return os;
	}
	virtual istream& input(istream& is)
	{
		return is >> last_name >> first_name >> age;
	}
	virtual ifstream& input(ifstream& is)
	{
		std::getline(is, last_name, '|');
		std::getline(is, first_name, '|');
		string age_buffer;
		std::getline(is, age_buffer, '|');
		this->age = std::stoi(age_buffer);	//stoi() - преобразует строку в int
		return is;
	}
};
//		Operators
ostream& operator<<(ostream& os, const Human& obj)
{
	return obj.print(os);
}
ofstream& operator<<(ofstream& os, const Human& obj)
{
	return obj.print(os);
}
istream& operator>>(istream& is, Human& obj)
{
	return obj.input(is);
}
ifstream& operator>>(ifstream& is, Human& obj)
{
	return obj.input(is);
}

class Employee :public Human
{
protected:
	string position;//Занимаемая должность
public:
	const string& get_position()const
	{
		return position;
	}
	void set_posotion(const string& position)
	{
		this->position = position;
	}
	Employee(const string& last_name, const string& first_name, unsigned int age,
		const std::string& position)
		:Human(last_name, first_name, age)
	{
		set_posotion(position);//Инициализация в теле конструктора (1 вариант)
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Employee()
	{
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	ostream& print(ostream& os)const
	{
		Human::print(os);
		os.width(20); os << left; os << position;
		return os;
	}
	ofstream& print(ofstream& os)const
	{
		Human::print(os);
		os.width(20); os << left; os << position << "|";
		return os;
	}
	istream& input(istream& is)
	{
		Human::input(is);
		is >> position;
		return is;
	}
	ifstream& input(ifstream& is)
	{
		Human::input(is);
		std::getline(is, position, '|');
		return is;
	}
	virtual double count_monthly_salary()const = 0;
};

class ResidentEmployee :public Employee
{
	double const_salary;//Зарплата
public:
	double get_const_salary()const
	{
		return const_salary;
	}
	void set_const_salary(double salary)
	{
		this->const_salary = salary;
	}
	ResidentEmployee(const string& last_name, const string& first_name, unsigned int age,
		const std::string& position,
		double const_salary)
		:Employee(last_name, first_name, age, position)
	{
		set_const_salary(const_salary);//Инициализация в теле конструктора (2 вариант)
#ifdef DEBUG
		cout << "RConstructor;\t" << this << endl;
#endif // DEBUG
	}
	~ResidentEmployee()
	{
#ifdef DEBUG
		cout << "RDestructor:\t" << this << endl;
#endif // DEBUG
	}
	ostream& print(ostream& os)const
	{
		Employee::print(os);
		os.width(25); os << right; os << const_salary;
		return os;
	}
	ofstream& print(ofstream& os)const
	{
		Employee::print(os);
		os.width(25); os << right; os << const_salary << "RUB" << "|";
		return os;
	}
	istream& input(istream& is)
	{
		Employee::input(is);
		is >> const_salary;
		return is;
	}
	ifstream& input(ifstream& is)
	{
		Employee::input(is);
		string salary_buffer;
		std::getline(is, salary_buffer, '|');
		this->const_salary = std::stod(salary_buffer);	//stod() - преобразует строку в double
		return is;
	}
	double count_monthly_salary()const
	{
		return const_salary;
	}
};

class HourEmployee :public Employee
{
	double rate;//Ставка за час
	int complete_hour;//Количество отработанных часов
public:
	HourEmployee(const string& last_name, const string& first_name, unsigned int age,
		const std::string& position,
		double rate,
		int complete_hour)
		:Employee(last_name, first_name, age, position), rate(rate), complete_hour(complete_hour)//Инициализация в имени конструктора
	{
#ifdef DEBUG
		cout << "HEConstructor;\t" << this << endl;
#endif // DEBUG
	}
	~HourEmployee()
	{
#ifdef DEBUG
		cout << "HEDestructor;\t" << this << endl;
#endif // DEBUG
	}
	ostream& print(ostream& os)const
	{
		Employee::print(os);
		os.width(10);
		os << right;
		os << complete_hour;
		os.width(15);
		os << right;
		os << rate;
		return os;
	}
	ofstream& print(ofstream& os)const
	{
		Employee::print(os);
		os.width(10);
		os << right;
		os << complete_hour << "hour" << "|";
		os.width(10);
		os << right;
		os << rate << "RUB" << "|";
		return os;
	}
	istream& input(istream& is)
	{
		Employee::input(is);
		is >> rate;
		is >> complete_hour;
		return is;
	}
	ifstream& input(ifstream& is)
	{
		Employee::input(is);
		string complete_hour_buffer;
		std::getline(is, complete_hour_buffer, '|');
		this->complete_hour = std::stod(complete_hour_buffer);
		string rate_buffer;
		std::getline(is, rate_buffer, '|');
		this->rate = std::stod(rate_buffer);
		return is;
	}
	double count_monthly_salary()const
	{
		return rate * complete_hour;
	}
};

double total_money = 0;

void SaveToFile(Employee* department[], const int size, const string& filename);
void Print(Employee* department[], const int size);
Employee** LoadFromFile(const std::string& filename);
Employee* EmployeeFactory(const std::string& human_type);

void main()
{
	setlocale(LC_ALL, "");
	//Generalisation
	Employee* department[] =
	{
		new ResidentEmployee("Ivanov", "Ivan", 46, "Director", 50000),
		new ResidentEmployee("Bass", "Evgenyy", 35, "Chief spetsialist", 25000),
		new ResidentEmployee("Krivova", "Anastasiya", 21, "Spetsialist", 26000),
		new ResidentEmployee("Meretin", "Vikentii", 26, "Engineer", 35000),
		new HourEmployee("Kochubeev", "Denis", 26, "Consultant", 132, 192),
		new HourEmployee("Buryakov", "Aleksandr", 25, "Programmist", 150, 192),
		new HourEmployee("Klimakov", "Aleksei", 25, "Programmist", 148, 192)
	};

	//Specialisation
	cout << "\nЧтобы начать выполнение программы, нажмите Enter?";
	cin.get();
	cout << "\nФормируем зарплатную ведомость сотрудников департамента: " << endl;
	double total_money = 0;
	for (int i = 0; i < sizeof(department) / sizeof(department[0]); i++)
	{
		cout << *department[i] << tab << "salary: " << department[i]->count_monthly_salary() << endl;
		total_money += department[i]->count_monthly_salary();
	}
	cout << "\nTotal money: " << setprecision(15) << total_money << " RUB\n" << endl;	//setprecision(15) - определяет точность выведения 15 знаков
	system("PAUSE");
	system("CLS");

	cout << "\nЧтобы сохранить ведомость в файл \".txt\", нажмите Enter?";
	cin.get();
	string filename = "Department.txt";
	SaveToFile(department, sizeof(department) / sizeof(department[0]), "Department.txt");
	system((string("notepad ") + filename).c_str());

	for (int i = 0; i < sizeof(department) / sizeof(department[0]); i++)
	{
		delete department[i];
	}

	system("PAUSE");
	system("CLS");
	cout << "\nЧтобы загрузить ведомость из файла \".txt\" и вывести на экран, нажмите Enter?";
	cin.get();

	Employee** load_department = LoadFromFile("Department.txt");
	Print(load_department, 10);
}

void SaveToFile(Employee* department[], const int size, const string& filename)
{
	ofstream fout(filename);
	for (int i = 0; i < size; i++)
	{
		fout << *department[i];
		if (i < size - 1)fout << endl;
	}
	fout.close();
}
void Print(Employee* department[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << *department[i] << endl;
	}
}
Employee** LoadFromFile(const std::string& filename)
{
	ifstream fin(filename);
	if (fin.is_open())
	{
		std::string buffer;
		int n = 0;
		while (!fin.eof())
		{
			std::getline(fin, buffer);
			cout << fin.tellg() << endl;
			n++;
		}
		Employee** department = new Employee * [n] {};
		fin.clear();
		fin.seekg(ios::beg, 0);
		cout << fin.tellg() << endl;
		string human_type;
		for (int i = 0; i < n; i++)
		{
			std::getline(fin, human_type, '|');
			department[i] = EmployeeFactory(human_type);
			fin >> *department[i];
		}
		fin.close();
		return department;
	}
	else
	{
		cerr << "Error: File not found!" << endl;
	}
	return nullptr;
}
Employee* EmployeeFactory(const std::string& human_type)
{
	if (human_type.find("class ResidentEmployee") != string::npos) return new ResidentEmployee("last_name", "first_name", 0, "spec", 0);
	if (human_type.find("class HourEmployee") != string::npos) return new HourEmployee("last_name", "first_name", 0, "spec", 0, 0);
	return nullptr;
}