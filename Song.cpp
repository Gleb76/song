#include "Song.h"

#include <iostream>

void demo_8() {
	std::cout << "--- demo 8 ---" << std::endl;

	Song a("Demons", Genre::Rock, 2000);
	Song b("Trouble", Genre::Pop, 2002);
	Remake c("Demons", Genre::Rock, 2000, 2020);
	Remake d("Trouble", Genre::Pop, 2002, 2022);

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;

	std::cout << (a == b) << std::endl; // false
	std::cout << (c == d) << std::endl; // false
	std::cout << (a == c) << std::endl; // true
	std::cout << (b == d) << std::endl; // true

	Song e;
	e = d;
	Remake f;
	f = d;
	std::cout << e << std::endl;
	std::cout << f << std::endl;
}

void demo_10() {
	std::cout << "--- demo 10 ---" << std::endl;

	Song a("Demons", Genre::Rock, 2000);
	Song b("Trouble", Genre::Pop, 2002);
	Remake c("Hraj", Genre::Rock, 2000, 2020);
	Remake d("Trouble", Genre::Pop, 2002, 2022);

	int n = 8;
	Song** arr = new Song * [n];

	arr[0] = &a;
	arr[1] = &b;
	arr[2] = &c;
	arr[3] = &d;
	arr[4] = &Song("Lavon Volski - Hraj", Genre::Rock, 2004);
	arr[5] = &Song("Naviband - Vybieru sam", Genre::Pop, 2005);
	arr[6] = &Remake("Lavon Volski - Hraj", Genre::Rock, 2004, 2008);
	arr[7] = &Remake("Naviband - Vybieru sam", Genre::Pop, 2005, 2009);

	for (int i = 0; i < n; ++i) {
		if (arr[i]->get_c()) {
			std::cout << (Remake&)(*arr[i]) << std::endl;
		}
		else {
			std::cout << *arr[i] << std::endl;
		}
	}

	// count genres and classes

	int genres_size = 4;
	int genres[4];

	int songs = 0;
	int remakes = 0;

	for (int i = 0; i < genres_size; ++i) {
		genres[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		genres[arr[i]->get_genre()] += 1;
		if (arr[i]->get_c() == 0) {
			songs += 1;
		}
		else {
			remakes += 1;
		}
	}
	for (int i = 0; i < genres_size; ++i) {
		std::cout << genre_to_text(i) << " " << genres[i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "song " << songs << ", remake " << remakes << std::endl;

	// sort

	std::cout << "sort" << std::endl;

	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (arr[j]->get_c() > arr[j + 1]->get_c())
			{
				Song* temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		if (arr[i]->get_c()) {
			std::cout << (Remake&)(*arr[i]) << std::endl;
		}
		else {
			std::cout << *arr[i] << std::endl;
		}
	}

	// year_r


	int year_r = 2020;
	bool found = false;

	std::cout << "year_r < " << year_r << std::endl;

	for (int i = 0; i < n; ++i) {
		if (arr[i]->get_c()) {
			if (((Remake&)(*arr[i])).get_year_r() < year_r) {
				std::cout << (Remake&)(*arr[i]) << std::endl;
				found = true;
			}
		}
	}
	if (!found) {
		std::cout << "not found" << std::endl;
	}
}


int main() {
	demo_8();
	demo_10();

}