#include <iostream>
#include<fstream>
#include <list>
#include<algorithm>
#include <cstring>
#include <iterator>
#include <string>
using namespace std;
#define MODE_RANGE 0
#define MODE_DURABILITY 1
#define MODE_FREQUENCY 2
#define MODE_NAME 3

////////////////////////////////////////


template<class T, class K>
class Quick_sort {
public:
    Quick_sort(std::vector<T> &vector, K &comparator);
    Quick_sort() = delete;
    ~Quick_sort() {};
private:
    int get_pivot(std::vector<T> &vector, int start_seq, int end_seq);
    int partition(std::vector<T> &vector, int start_seq, int end_seq, K &comparator);
    void quick_sort(std::vector<T> &vector, int start_seq, int end_seq, K &comparator);
};


template<class T, class K>
Quick_sort<T, K>::Quick_sort(std::vector<T> &vector, K &comparator) {
    quick_sort(vector, 0, vector.size() - 1, comparator);
};


template<class T, class K>
void Quick_sort<T, K>::quick_sort(std::vector<T> &vector, int start_seq, int end_seq, K &comparator) {
    int part_idx = partition(vector, start_seq, end_seq, comparator);
    if (end_seq - start_seq <= 1)
        return;
    quick_sort(vector, start_seq, part_idx - 1, comparator);
    quick_sort(vector, part_idx + 1, end_seq, comparator);
    return;
};


template<class T, class K>
int Quick_sort<T, K>::partition(std::vector<T> &vector, int start_seq, int end_seq, K &comparator) {
    if (start_seq >= end_seq)
        return 0;
    int pivot = get_pivot(vector, start_seq, end_seq);
    int i = start_seq;
    int j = end_seq - 1;
    while (i < j) {
        while (comparator(vector[i], vector[pivot]))
            i++;
        while (!comparator(vector[j], vector[pivot]) && j >= 0)
            j--;
        if (i < j) {
            std::swap(vector[i], vector[j]);
            i++;
            j--;
        }
    }
    if (comparator(vector[end_seq], vector[i]))
        std::swap(vector[i], vector[end_seq]);
    return i;
}


template<class T, class K>
int Quick_sort<T, K>::get_pivot(std::vector<T> &vector, int start_seq, int end_seq) {
    return end_seq;
}



//Класс гармонический сигнал
class harmonic_signal {
	double range;
	double durability;
	double frequency;
	std::string name;
	int search_mode;//по идее надо бы вынести в класс наследник и расширить его чтобы не портить текущий ксласс...
public:
	//конструктор без параметров
	harmonic_signal() {}

	//конструктор с параметрами
	harmonic_signal(double ph, double amp, double freq, std::string signal_name) {
		range = ph;
		durability = amp;
		frequency = freq;
		name = signal_name;
	}
	harmonic_signal(double ph, double amp, double freq, std::string signal_name, int mode) {
		range = ph;
		durability = amp;
		frequency = freq;
		name = signal_name;
		search_mode = mode;
	}

	double getrange()
	{
		return range;
	}
	double getdurability()
	{
		return durability;
	}
	double getfrequency()
	{
		return frequency;
	}
	std::string getname()
	{
		return name;
	}
	int get_search_mode()
	{
		return search_mode;
	}
	//перегруженные функции помещения в поток
	//и извлечения из потока
	friend ostream& operator<<(ostream &stream,
		harmonic_signal ob);
	friend istream& operator >> (istream &stream,
		harmonic_signal &ob);
};

ostream& operator<<(ostream &stream,
	harmonic_signal ob)
{
	stream << ob.range << "\t";
	stream << ob.durability << "\t";
	stream << ob.frequency << "\t";
	stream << ob.name << "\n";
	return stream;
}

istream& operator >> (istream &stream,
	harmonic_signal &ob)
{
	stream >> ob.range;
	stream >> ob.durability;
	stream >> ob.frequency;
	stream >> ob.name;
	return stream;
}


//функциональный класс
//с перегруженными операциями вызова функции
class funct
{
	int mode;
	double range;
	double durability;
	double frequency;
	std::string name;
public:
	//конструктор c умолчанием
	funct(int a)//0-range,1-durability,2-frequency,3-name
	{
		mode = a;
	}

	//конструктор с параметрами
	funct(harmonic_signal sig)
	{
		range = sig.getrange();
		durability = sig.getdurability();
		frequency = sig.getfrequency();
		name = sig.getname();
		mode = sig.get_search_mode();
	}

	//унарный предикат
	//критерий поиска
	//по параметру(?) для класса harmonic_signal
	bool operator()(harmonic_signal sig)
	{
		switch (mode)
		{
		case MODE_RANGE:
			if (range == sig.getrange())
				return true;
			return false;
			break;
		case MODE_DURABILITY:
			if (durability == sig.getdurability())
				return true;
			return false;
			break;
		case MODE_FREQUENCY:
			if (frequency == sig.getfrequency())
				return true;
			return false;
			break;
		case MODE_NAME:
			if (name == sig.getname())
				return true;
			return false;
			break;
		}
		return false;
	}

	//бинарный предикат
	//с разными критериями сортировки
	//для класса harmonic_signal
	bool operator()(harmonic_signal &a, harmonic_signal &b)
	{
		//по фазе
		if (mode == MODE_RANGE) {
			if (a.getrange()< b.getrange())
				return true;
			return false;
		}
		//по амплитуде
		if (mode == MODE_DURABILITY) {
			if (a.getdurability()< b.getdurability())
				return true;
			return false;
		}
		if (mode == MODE_FREQUENCY) {
			if (a.getfrequency()<b.getfrequency())
				return true;
			return false;
		}
		if (mode == MODE_NAME) {
			if (a.getname()<b.getname())
				return true;
			return false;
		}
		return false;
	}

};

//класс список гармонических сигналов
class harmonic_signal_list {
	//в качестве поля используем
	//контейнер двунаправленный список
	std::vector<harmonic_signal> l;
public:

	//добавление объекта класса
	//студент в конец списка
	void dobav(harmonic_signal sig)
	{
		l.push_back(sig);
	}

	//сортировка  по фазе
	void sortphase()
	{
		funct sravn(MODE_RANGE);
		//Сортирует все элементы по критерию sravn
		//при mode=MODE_RANGE
        Quick_sort<harmonic_signal, funct> quick_sort(l, sravn);
	}

	//сортировка по амплитуде
	void sortamp()
	{
		funct sravn(MODE_DURABILITY);
		//Сортирует все элементы по критерию sravn
		// при mode=MODE_DURABILITY
        Quick_sort<harmonic_signal, funct> quick_sort(l, sravn);
    }

	//сортировка по частоте
	void sortfreq()
	{
		funct sravn(MODE_FREQUENCY);
		//Сортирует все элементы по критерию sravn
		// при mode=MODE_FREQUENCY
        Quick_sort<harmonic_signal, funct> quick_sort(l, sravn);
    }

	void sortname()
	{
		funct sravn(MODE_NAME);
		//Сортирует все элементы по критерию sravn
		// при mode=MODE_FREQUENCY
        Quick_sort<harmonic_signal, funct> quick_sort(l, sravn);
    }

	string get_modename(int mode)
	{
		switch (mode)
		{
		case MODE_RANGE: return "диапазоном"; break;
		case MODE_DURABILITY: return "длительностью"; break;
		case MODE_FREQUENCY: return "частотой"; break;
		case MODE_NAME: return "именем"; break;
		}
		return "";
	}
	//поиск и вывод на экран
	//сигналов с параметром
	void findParam(double param, int mode)
	{
		string modename = get_modename(mode);
		//создаем итераторы для работы со списком
		std::vector<harmonic_signal>::iterator ptr, p;

		harmonic_signal hs;

		switch (mode)
		{
		case MODE_RANGE: hs = harmonic_signal(param, -1, -1, "", MODE_RANGE); break;
		case MODE_DURABILITY: hs = harmonic_signal(-1, param, -1, "", MODE_DURABILITY); break;
		case MODE_FREQUENCY: hs = harmonic_signal(-1, -1, param, "", MODE_FREQUENCY); break;
		}

		funct poisk(hs);
		//определяем сколько сигналов
		//имеют данный параметр
		int n = count_if(l.begin(),
			l.end(), poisk);
		if (n>0) {
			p = l.begin();
			for (int i = 1; i <= n; i++)
			{
				ptr = find_if(p, l.end(), poisk);
				cout << *ptr;
				ptr++;
				p = ptr;
			}
		}
		else
			cout << "Сигналов с " << modename.c_str() << " " << param << " нет!" << endl;
	}


	void findParam(std::string param)
	{
		string modename = get_modename(MODE_NAME);
		//создаем итераторы для работы со списком
		std::vector<harmonic_signal>::iterator ptr, p;

		harmonic_signal hs;
		hs = harmonic_signal(-1, -1, -1, param, MODE_NAME);

		funct poisk(hs);
		//определяем сколько сигналов
		//имеют данный параметр
		int n = count_if(l.begin(),
			l.end(), poisk);
		if (n>0) {
			p = l.begin();
			for (int i = 1; i <= n; i++)
			{
				ptr = find_if(p, l.end(), poisk);
				cout << *ptr;
				ptr++;
				p = ptr;
			}
		}
		else
			cout << "Сигналов с " << modename.c_str() << " " << param << " нет!" << endl;
	}

	//удаление из списка всех сигналов
	//с параметром
	void del(double param, int mode)
	{
		string modename = get_modename(mode);
		//создаем итераторы для работы со списком
		std::vector<harmonic_signal>::iterator ptr, p;

		harmonic_signal hs;
		switch (mode)
		{
		case MODE_RANGE: hs = harmonic_signal(param, -1, -1, "", MODE_RANGE); break;
		case MODE_DURABILITY: hs = harmonic_signal(-1, param, -1, "", MODE_DURABILITY); break;
		case MODE_FREQUENCY: hs = harmonic_signal(-1, -1, param, "", MODE_FREQUENCY); break;
		}

		funct poisk(hs);
		//определяем сколько сигналов
		//имеют данный параметр
		int n = count_if(l.begin(),
			l.end(), poisk);
		if (n>0) {
			p = l.begin();
			for (int i = 1; i <= n; i++)
			{
				ptr = find_if(p, l.end(), poisk);
				l.erase(ptr);
				cout << "Сигналов с " << modename.c_str() << " " << param << " удален" << endl;
				p = l.begin();
			}
		}
		else
			cout << "Сигналов с " << modename.c_str() << " " << param << " нет!" << endl;
	}

	void del(std::string param)
	{
		string modename = get_modename(MODE_NAME);
		//создаем итераторы для работы со списком
		std::vector<harmonic_signal>::iterator ptr, p;

		harmonic_signal hs;
		hs = harmonic_signal(-1, -1, -1, param, MODE_NAME);

		funct poisk(hs);
		//определяем сколько сигналов
		//имеют данный параметр
		int n = count_if(l.begin(),
			l.end(), poisk);
		if (n>0) {
			p = l.begin();
			for (int i = 1; i <= n; i++)
			{
				ptr = find_if(p, l.end(), poisk);
				l.erase(ptr);
				cout << "Сигналов с " << modename.c_str() << " " << param << " удален" << endl;
				p = l.begin();
			}
		}
		else
			cout << "Сигналов с " << modename.c_str() << " " << param << " нет!" << endl;
	}

	//перегруженная операция вставки в поток
	friend ostream& operator<<(ostream& st,
		harmonic_signal_list &o)
	{
		for (auto ptr = o.l.begin();
			ptr != o.l.end(); ++ptr)
			st << *ptr;
		return st;
	}

	//перегруженная операция
	//извлечения из потока
	friend istream& operator >> (istream& st,
		harmonic_signal_list &o)
	{
		harmonic_signal ob;
		st >> ob;
		o.l.push_back(ob);
		return st;
	}
};







int main()
{
	setlocale(LC_CTYPE, "Russian");
	//создаем список
	harmonic_signal_list ob;

	//добавляем объекты класса harmonic_signal
	// в конец списка
	ob.dobav(harmonic_signal(1500, 100, 101.7, "signal_1" ));
	ob.dobav(harmonic_signal(1200, 12, 95.2, "signal_2"));
	ob.dobav(harmonic_signal(1400, 38, 89.7, "signal_3"));
	ob.dobav(harmonic_signal(1000, 25, 105.9, "signal_4"));

	cout << "Список сигналов :" << endl << "Диапазон Длительность Частота Имя" << endl
		<< ob << endl;

	//сортировка сигналов по фазе (можно использовать такие же функции по частоте и амплитуде
	ob.sortphase();
	cout <<
		"Список сигналов после сортировки по диапазону:" << endl << "Диапазон Длительность Частота Имя"
		<< endl << ob << endl;

	ob.sortfreq();
	cout <<
		"Список сигналов после сортировки по частоте:" << endl << "Диапазон Длительность Частота Имя"
		<< endl << ob << endl;

	ob.sortamp();
	cout <<
		"Список сигналов после сортировки по длительности:" << endl << "Диапазон Длительность Частота Имя"
		<< endl << ob << endl;

	ob.sortname();
	cout <<
		"Список сигналов после сортировки по имени:" << endl << "Диапазон Длительность Частота Имя"
		<< endl << ob << endl;

	//поиск в списке сигналов
	//с заданым параметров
	int mode;
	cout << "Поиск по диапазону - 0 \nПоиск по длительности - 1 \nПоиск по частоте - 2 \nПоиск по имени - 3" << endl;
	cin >> mode;
	double param;
	std::string name_param;
	if (mode < 3) {
		cout << "Введите параметр для поиска:\n";
		cin >> param;
		ob.findParam(param, mode);
		cout << endl;
	}
	else {
		cout << "Введите параметр для поиска:\n";
		cin >> name_param;
		ob.findParam(name_param);
		cout << endl;
	}

	//удаление из списка сигналов
	if (mode < 3) {
		ob.del(param, mode);
		cout << "Список сигналов после удаления " << param << " :" << endl << "диапазону Амплитуда Частота"
			<< endl << ob << endl;
	}
	else {
		ob.del(name_param);
		cout << "Список сигналов после удаления " << name_param << " :" << endl << "диапазону Амплитуда Частота"
			<< endl << ob << endl;
	}

	return 0;
}