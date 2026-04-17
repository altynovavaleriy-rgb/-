#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
using namespace std;
enum gender {Male, Female};
const int SIZE = 20;
struct date {
	int d, m, y;
};
struct children {
	char fam_name[30];
	gender pol;
	int rost;
	date birthday;
	int siblings;
};

double middle_rost(children arr[], int size) {
	int sum = 0;
	int number = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i].pol == Male) {
			sum += arr[i].rost;
			number++;
		}
	}
	double middle_rost = (double)sum / number;
	return middle_rost;
}

children* tallest_girls(children arr[], int size, int& resultCount) {
	int girls_count = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i].pol == Female) {
			girls_count++;
		}
	}
	children* girls = new children[girls_count];
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i].pol == Female) {
			girls[index] = arr[i];
			index++;
		}
	}
	for (int i = 0; i < girls_count - 1; i++) {
		for (int j = 0; j < girls_count - i - 1; j++) {
			if (girls[j].rost < girls[j + 1].rost) {
				children temp = girls[j];
				girls[j] = girls[j + 1];
				girls[j + 1] = temp;
			}
		}
	}
	int top_count = (girls_count < 5) ? girls_count : 5;
	children* top_tallest = new children[top_count];
	for (int i = 0; i < top_count; i++) {
		top_tallest[i] = girls[i];
	}
	delete[] girls;
	resultCount = top_count;
	return top_tallest;
}


void aphabet_children(children arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (strcmp(arr[j].fam_name, arr[j + 1].fam_name) > 0) {
				children temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void find_ByName(children arr[], int size) {
	char searchName[30];
	cout << "Введите фамилию и имя: "; 
	cin.getline(searchName, 30);

	bool found = false;

	for (int i = 0; i < size; i++) {
		if (strcmp(arr[i].fam_name, searchName) == 0) {
			cout << "\nУченик найден!" << endl;
			cout << "ФИО: " << arr[i].fam_name << endl;
			cout << "Пол: " << (arr[i].pol == Male ? "Мальчик" : "Девочка") << endl;
			cout << "Рост: " << arr[i].rost << " см" << endl;
			cout << "Дата рождения: " << arr[i].birthday.d << "."
				<< arr[i].birthday.m << "."
				<< arr[i].birthday.y << endl;
			found = true;
			break;  
		}
	}

	if (!found) {
		cout << "Ученик с именем \"" << searchName << "\" не найден!" << endl;
	}
}

void edit_Student(children arr[], int size) {
	char searchName[30];
	cout << "\nРедактирование ученика" << endl;
	cout << "Введите фамилию и имя ученика: ";
	cin.getline(searchName, 30);

	bool found = false;

	for (int i = 0; i < size; i++) {
		if (strcmp(arr[i].fam_name, searchName) == 0) {
			found = true;

			cout << "\nТекущие данные" << endl;
			cout << "ФИО: " << arr[i].fam_name << endl;
			cout << "Пол: " << (arr[i].pol == Male ? "Мальчик" : "Девочка") << endl;
			cout << "Рост: " << arr[i].rost << " см" << endl;
			cout << "Дата рождения: " << arr[i].birthday.d << "."
				<< arr[i].birthday.m << "."
				<< arr[i].birthday.y << endl;

			cout << "\nВведите новые данные:" << endl;

			cout << "Новое ФИО: ";
			cin.getline(arr[i].fam_name, 30);

			int genderChoice;
			cout << "Пол (1 - Мальчик, 2 - Девочка): ";
			cin >> genderChoice;
			arr[i].pol = (genderChoice == 1) ? Male : Female;

			cout << "Новый рост (см): ";
			cin >> arr[i].rost;

			cout << "Новая дата рождения (день месяц год): ";
			cin >> arr[i].birthday.d >> arr[i].birthday.m >> arr[i].birthday.y;

			aphabet_children(arr, size); 
			cout << "\nДанные успешно обновлены!" << endl;
			cout << "\nСписок отсортирован заново!" << endl;
			cin.ignore();  
			break;
		}
	}

	if (!found) {
		cout << "Ученик не найден!" << endl;
	}
}

int now_month() {
	time_t now = time(0);           
	tm* ltm = localtime(&now);      
	return ltm->tm_mon + 1;         
}

children* BirthdaysThisMonth(children arr[], int size, int& resultCount) {
	int nowing_month = now_month();

	int count = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i].birthday.m == nowing_month) {
			count++;
		}
	}

	children* birthdays = new children[count];

	int index = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i].birthday.m == nowing_month) {
			birthdays[index] = arr[i];
			index++;
		}
	}

	resultCount = count;
	return birthdays;
}

void printBirthdays(children arr[], int count, int month) {
	if (count == 0) {
		cout << "В этом месяце нет именинников!" << endl;
		return;
	}

	cout << "\n Именинники " << month << "-го МЕСЯЦА" << endl;
	for (int i = 0; i < count; i++) {
		cout << i + 1 << ". " << arr[i].fam_name
			<< " - день рождения: " << arr[i].birthday.d << "."
			<< arr[i].birthday.m << "."
			<< arr[i].birthday.y << endl;
	}
}

void read_file(children arr[], int size) {
	ifstream fin;
	fin.open("siblings.txt");
	if (fin.is_open()) {
		int i = 0;
		while (fin >> arr[i].siblings && i < size) {
			cout << arr[i].fam_name << " - братьев/сестер: " << arr[i].siblings << endl;
			i++;
		}
		fin.close();
		cout << "Загружено записей: " << i << endl;
	}
	else {
		cout << "Файл siblings.txt не найден!" << endl;
	}
}

void saveToBinaryFile(children arr[], int size) {
	ofstream out("children.dat", ios::binary | ios::out);

	if (!out.is_open()) {
		cout << "Ошибка открытия файла для записи!" << endl;
		return;
	}
	out.write((char*)arr, sizeof(children) * size);

	out.close(); 
	cout << "Данные сохранены в бинарный файл!" << endl;
}

children* loadFromBinaryFile(int& size) {
	fstream in("children.dat", ios::binary | ios::in);
	if (!in.is_open()) {
		cout << "Файл children.dat не найден!" << endl;
		return nullptr;
	}
	in.seekg(0, ios::end);
	long fileSize = in.tellg();
	in.seekg(0, ios::beg);
	size = fileSize / sizeof(children);
	children* arr = new children[size];
	in.read((char*)arr, sizeof(children) * size);
	in.close();
	cout << "Загружено " << size << " записей из бинарного файла!" << endl;
	return arr;
}


void printChildrenArray(children arr[], int count, const char* title) {
	cout << "\n=== " << title << " ===" << endl;

	if (count == 0) {
		cout << "Нет данных!" << endl;
		return;
	}

	cout << "+-----+--------------------------------+-----+-------+----------------+--------+" << endl;
	cout << "|  №  | ФИО                            | Пол | Рост  | Дата рождения  | Братья/|" << endl;
	cout << "|     |                                |     |       |                | сестры |" << endl;
	cout << "+-----+--------------------------------+-----+-------+----------------+--------+" << endl;

	for (int i = 0; i < count; i++) {
		printf("| %3d | %-30s | %s   | %3d   | %2d.%2d.%4d   |   %2d   |\n",
			i + 1,
			arr[i].fam_name,
			(arr[i].pol == Male ? "М" : "Ж"),
			arr[i].rost,
			arr[i].birthday.d,
			arr[i].birthday.m,
			arr[i].birthday.y,
			arr[i].siblings);  
	}

	cout << "+-----+--------------------------------+-----+-------+----------------+--------+" << endl;
	cout << "Всего: " << count << " записей" << endl;
}


children* init() {
	int loadedSize = 0;

	children* childrens = loadFromBinaryFile(loadedSize);

	if (childrens != nullptr && loadedSize == SIZE) {
		cout << "Данные загружены из бинарного файла!" << endl;
		return childrens;
	}

	cout << "Создаем новый массив данных..." << endl;
	childrens = new children[SIZE];
	childrens[0] = { "Ivanov Petya", Male, 136, {5,12,2016}, 0 };
	childrens[1] = { "Malyshev Egor", Male, 125, {25,2,2014}, 0 };
	childrens[2] = { "Ivanchenko Olesya", Female, 142, {12,9,2018}, 0 };
	childrens[3] = { "Tarasenko Nikola", Male, 150, {5,1,2016}, 0 };
	childrens[4] = { "Kirilova Anna", Female, 146, {8,6,2013}, 0 };
	childrens[5] = { "Raydos Viktoria", Female, 163, {18,4,2012}, 0 };
	childrens[6] = { "Cherevatyi Vlad", Male, 170, {28,3,2018}, 0 };
	childrens[7] = { "Cherbakova Varvara", Female, 145, {31,3,2017}, 0 };
	childrens[8] = { "Mygkova Irina", Female, 163, {23,2,2012}, 0 };
	childrens[9] = { "Orlov Ilya", Male, 120, {13,12,2012}, 0 };
	childrens[10] = { "Kozlova Veronika", Female, 169, {14,7,2013}, 0 };
	childrens[11] = { "Klimov Igor", Male, 168, {16,6,2011}, 0 };
	childrens[12] = { "Varnava Ekaterina", Female, 156, {19,3,2015}, 0 };
	childrens[13] = { "Musagaliev Azamat", Male, 170, {23,5,2016}, 0 };
	childrens[14] = { "Romanova Masha", Female, 161, {21,5,2018}, 0 };
	childrens[15] = { "Juravlev Dmitriy", Male, 171, {14,11,2009}, 0 };
	childrens[16] = { "Yarovitcina Zoya", Female, 168, {11,11,2013}, 0 };
	childrens[17] = { "Ivanushkin Konstantin", Male, 191, {26,12,2007}, 0 };
	childrens[18] = { "Lermontov Uriy", Male, 96, {17,4,2024}, 0 };
	childrens[19] = { "Peregudova Ksenia", Female, 148, {13,7,2015}, 0 };

	return childrens;
}

int main() {
	setlocale(LC_ALL, "Ru");
	children* childrens = init();  
	read_file(childrens, SIZE);
	double result = middle_rost(childrens, SIZE);
	cout << "Средний рост мальчиков: " << result << endl;
	int girlsCount = 0;
	children* topGirls = tallest_girls(childrens, SIZE, girlsCount);

	printChildrenArray(topGirls, girlsCount, "Топ 5 самых высоких девочек");

	aphabet_children(childrens, SIZE);
	printChildrenArray(childrens, SIZE, "Список детей по алфавиту: "); 

	cout << "\nПоиск ребенка:" << endl;
	find_ByName(childrens, SIZE);

	cout << "\nРедактирование ребенка:" << endl;
	edit_Student(childrens, SIZE);
	
	cout << "\n Обновленный список" << endl;
	printChildrenArray(childrens, SIZE, "Измененный список");

	cout << "\n Именниники текущего месяца" << endl;
	int birthdayCount = 0;
	children* birthdayKids = BirthdaysThisMonth(childrens, SIZE, birthdayCount);
	int nowing_month = now_month();
	printBirthdays(birthdayKids, birthdayCount, nowing_month);
	printChildrenArray(birthdayKids, birthdayCount, "Именинники текущего месяца");
	saveToBinaryFile(childrens, SIZE);
	delete[] childrens;
	delete[] topGirls;
	delete[] birthdayKids;

	return 0;
}

	






