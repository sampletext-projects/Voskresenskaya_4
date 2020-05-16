#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

//базовый класс деньги
class c_money
{
	long rubli_; //рубли
	unsigned char kopeyki_; //копейки
public:

	//конструктор без параметров
	c_money()
	{
		rubli_ = 0;
		kopeyki_ = 0;
	}

	//конструктор с параметрами
	c_money(int rubli, int kopeyki)
	{
		rubli_ = rubli;
		kopeyki_ = kopeyki;
	}

	//конструктор без параметров
	c_money(const c_money& money)
	{
		rubli_ = money.rubli_;
		kopeyki_ = money.kopeyki_;
	}

	void read()
	{
		cout << "Рубли -> ";
		cin >> rubli_;
		cout << "Копейки -> ";
		int t;
		cin >> t;
		kopeyki_ = t;
	}

	//функция конвертации в копейки
	int convert_to_kopeyki()
	{
		return rubli_ * 100 + kopeyki_;
	}

	//функция конвертации из копеек
	void convert_from_kopeyki(int kop)
	{
		rubli_ = kop / 100;
		kopeyki_ = kop % 100;
	}

	friend c_money& operator+(c_money& left, int& kop)
	{
		c_money* t = new c_money(left);
		t->plus(kop);
		return *t;
	}

	friend c_money& operator+(c_money& left, c_money& right)
	{
		c_money* t = new c_money(left);
		t->plus(right);
		return *t;
	}

	friend c_money& operator-(c_money& left, int& kop)
	{
		c_money* t = new c_money(left);
		t->minus(kop);
		return *t;
	}

	friend c_money& operator-(c_money& left, c_money& right)
	{
		c_money* t = new c_money(left);
		t->minus(right);
		return *t;
	}

	friend c_money& operator/(c_money& left, int& pieces)
	{
		c_money* t = new c_money(left);
		t->divide(pieces);
		return *t;
	}

	friend c_money& operator/(c_money& left, float& number)
	{
		c_money* t = new c_money(left);
		t->divide(number);
		return *t;
	}


	//функция сложения
	void plus(int kop)
	{
		convert_from_kopeyki(convert_to_kopeyki() + kop);
	}

	//метод добавления денег к деньгам
	void plus(c_money& m)
	{
		plus(m.convert_to_kopeyki());
	}

	//функция вычитания
	void minus(int kop)
	{
		convert_from_kopeyki(convert_to_kopeyki() - kop);
	}

	//метод вычитания денег из денег
	void minus(c_money& m)
	{
		minus(m.convert_to_kopeyki());
	}

	//деление на N частей
	void divide(int n)
	{
		this->convert_from_kopeyki(convert_to_kopeyki() / n);
	}

	//деление на дробное число
	void divide(float n)
	{
		this->convert_from_kopeyki((int)(convert_to_kopeyki() / n));
	}

	//умножение на дробное число
	void multiply(float n)
	{
		this->convert_from_kopeyki((int)(convert_to_kopeyki() * n));
	}

	//функция сравнения
	int compare(c_money& m)
	{
		int my_cop = convert_to_kopeyki();
		int sec_cop = m.convert_to_kopeyki();

		if (my_cop < sec_cop)
		{
			return -1;
		}
		else if (my_cop > sec_cop)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	//функция вывода
	string toString()
	{
		string s;
		if (rubli_ < 10)
		{
			s += "0"; //если рублей только на 1 цифру, выводим дополнительный 0
		}
		s += to_string(rubli_) + ",";
		if ((int)kopeyki_ < 10)
		{
			s += "0"; //если копеек только на 1 цифру, выводим дополнительный 0
		}
		s += to_string(static_cast<int>(kopeyki_)) + "к\n";
		return s;
	}
};


int main()
{
	setlocale(LC_ALL, "russian");

	c_money m1;
	cout << "Введите изначальную сумму денег: \n";
	m1.read();
	cout << m1.toString();
	cout << "Введите добавляемую сумму денег: \n";
	c_money m2;
	m2.read();
	cout << m2.toString();

	c_money m3 = m1 + m2;
	cout << "Сумма денег на счету: " << m3.toString();

	int add;
	cout << "Введите добавляемое количество копеек: ";
	cin >> add;

	c_money m4 = m3 + add;
	cout << "Сумма денег на счету: " << m4.toString();

	cout << "Введите вычитаемую сумму денег: \n";
	c_money m5;
	m5.read();
	cout << m5.toString();

	c_money m6 = m4 - m5;
	cout << "Сумма денег на счету: " << m6.toString();

	int sub;
	cout << "Введите вычитаемое количество копеек: ";
	cin >> sub;

	c_money m7 = m6 - sub;
	cout << "Сумма денег на счету: " << m7.toString();

	system("pause");
	return 0;
}
