#pragma once

#include <iostream>
#include <iomanip>

class IdGenerator {
public:
	static int value;

public:
	static int next() {
		return value++;
	}
};

int IdGenerator::value = 0;

enum Genre {
	Classical, Jazz, Pop, Rock
};

const char* genre_to_text(int genre) {
	switch (genre) {
	case 1:
		return "Jazz";
	case 2:
		return "Pop";
	case 3:
		return "Rock";
	default:
		return "Classical";
	}
}

class Song
{
protected:
	int c_;
	const int id_;
	const char* name_;
	Genre genre_;
	int year_;

	void clone(const Song& song) {
		set_name(song.get_name());
		set_genre(song.get_genre());
		set_year(song.get_year());
	}

public:
	// constructor, destructor

	Song(const char* name = "default name", Genre genre = Genre::Classical, int year = 100)
		: id_(IdGenerator::next()), name_(nullptr), genre_(genre), year_(year)
	{
		c_ = 0;
		set_name(name);
	}
	explicit Song(const Song& song)
		: id_(IdGenerator::next()), name_(nullptr), genre_(song.genre_), year_(song.year_)
	{
		c_ = 0;
		set_name(song.name_);
	}
	~Song() {
		return;
		if (name_ != nullptr) {
			delete[] name_;
			name_ = nullptr;
		}
	}

	// get, set

	int get_c() const {
		return c_;
	}
	int get_id() const {
		return id_;
	}

	const char* get_name() const {
		return name_;
	}
	void set_name(const char* name) {
		if (name_ != nullptr) {
			delete[] name_;
			name_ = nullptr;
		}
		name_ = new char[strlen(name) + 1];
		strcpy_s(const_cast<char*>(name_), strlen(name) + 1, name);
	}

	Genre get_genre() const {
		return genre_;
	}
	void set_genre(Genre value) {
		genre_ = value;
	}

	int get_year() const {
		return year_;
	}
	void set_year(int value) {
		year_ = value;
	}

	// operator

	Song& operator = (const Song& song) {
		if (this == &song) {
			return *this;
		}
		clone(song);
		return *this;
	}

	bool operator == (const Song& song) const {
		return genre_ == song.genre_;
	}

	friend std::ostream& operator << (std::ostream& os, const Song& song);
};

std::ostream& operator << (std::ostream& os, const Song& song) {
	os
		<< std::setw(2) << song.id_ << " | "
		<< std::setw(30) << song.name_ << " | "
		<< std::setw(9) << genre_to_text((int)song.genre_) << " | "
		<< std::setw(4) << song.year_;
	return os;
}

class Remake : public Song {
protected:
	int year_r_;

public:
	// constructor, destructor

	Remake(const char* name = "default name", Genre genre = Genre::Classical, int year = 100, int year_r = 50)
		: Song(name, genre, year), year_r_(year_r)
	{
		c_ = 1;
	}
	explicit Remake(const Remake& remake)
		: Song(remake), year_r_(remake.year_r_)
	{
		c_ = 1;
	}

	// get, set

	int get_year_r() const {
		return year_r_;
	}
	void set_year_r(int value) {
		year_r_ = value;
	}

	// operator

	Remake& operator = (const Remake& remake) {
		if (this == &remake) {
			return *this;
		}
		clone((Song&)remake);
		year_r_ = remake.year_r_;
		return *this;
	}

	friend std::ostream& operator << (std::ostream& os, const Remake& remake);
};

std::ostream& operator << (std::ostream& os, const Remake& remake) {
	os
		<< (Song&)remake << " | "
		<< std::setw(4) << remake.year_r_;
	return os;
}