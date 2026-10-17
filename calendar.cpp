#include <iostream>

void Ulday(int month, int year, unsigned long long& JD) {
	unsigned long long a = (14 - month) / 12;
	unsigned long long y = year + 4800 - a;
	unsigned long long m = month + 12 * a - 3;

	JD = (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32044;
}

int dayInMonth(int month, int year) {
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;

	case 4: case 6: case 9: case 11:
		return 30;

	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return 29;
		}
		return 28;
	default:
		return 0;
	}
}

void usmonth(int month) {
	switch (month) {
	case 1: std::cout << "January\n"; break;
	case 2: std::cout << "February\n"; break;
	case 3: std::cout << "March\n"; break;
	case 4: std::cout << "April\n"; break;
	case 5: std::cout << "May\n"; break;
	case 6: std::cout << "June\n"; break;
	case 7: std::cout << "July\n"; break;
	case 8: std::cout << "August\n"; break;
	case 9: std::cout << "September\n"; break;
	case 10: std::cout << "October\n"; break;
	case 11: std::cout << "November\n"; break;
	case 12: std::cout << "December\n"; break;
	}
}

void hat() {
	std::cout << "Su Mo Tu We Th Fr Sa" << std::endl;
}

void def_y(const char* x, int& year, bool& f_y) {
	for (int i = 0; x[i] != '\0'; ++i) {
		if (x[i] < '0' || x[i] > '9') {
			f_y = false;
		}
		year = 10 * year + (x[i] - '0');
	}
}

void def_m(const char* x, int& month, bool& f_m) {
	for (int i = 0; x[i] != '\0'; ++i) {
		if (x[i] < '0' || x[i] > '9') {
			f_m = false;
		}
		month = 10 * month + (x[i] - '0');
	}
}

int startday(int month, int year) {
	unsigned long long JD;
	Ulday(month, year, JD);
	return static_cast<int>((JD + 1) % 7);
}

void unk() {
	std::cout << "Unknown";
}

int curr_pos(const char* month) {
	int i = 0;
	while (month[i] != '\0') {
		++i;
	}
	return i;
}

void space(int pos) {
	for (int i = 0; i < pos; ++i) {
		std::cout << " ";
	}
}

int leng(const char* month) {
	int length = 0;
	while (month[length] != '\0') {
		++length;
	}
	return length;
}

int main(int argc, char* argv[]) {

	int year = 0;

	if (argc == 2) {
		const char* ch_y = argv[1];

		bool f_y = true;
		def_y(ch_y, year, f_y);

		if (!f_y) {
			unk();
			return 0;
		}

		std::cout << year << std::endl;

		const char* months[12] = { "January", "February", "March", "April",
		"May", "June", "July", "August", "September", "October", "November", "December" };


		for (int block = 0; block < 4; ++block) {
			int m1 = 3 * block;
			int m2 = 3 * block + 1;
			int m3 = 3 * block + 2;

			std::cout << months[m1];
			space(22 - leng(months[m1]));
			std::cout << months[m2];
			space(22 - leng(months[m2]));
			std::cout << months[m3] << std::endl;

			int st[3] = { startday(m1 + 1,year), startday(m2 + 1,year), startday(m3 + 1,year) };
			int end[3] = { dayInMonth(m1 + 1,year), dayInMonth(m2 + 1,year), dayInMonth(m3 + 1,year) };
			bool status[3] = { false };
			int curr[3] = { 0 };
			int curr_day[3] = { 1,1,1 };

			std::cout << "Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa" << std::endl;

			while (!(status[0] && status[1] && status[2])) {
				for (int i = 0; i < 3; ++i) {
					if (status[i]) {
						space(22);
						continue;
					}

					while (curr_day[i] == 1 && curr[i] != st[i]) {
						std::cout << "   ";
						++curr[i];
					}

					while (true) {
						if (curr_day[i] < end[i]) {
							if (curr_day[i] < 10) {
								if (i == 2 && curr[i] == 6) {
									std::cout << " " << curr_day[i];
								}
								else {
									std::cout << " " << curr_day[i] << " ";
								}
							}
							else {
								if (i == 2 && curr[i] == 6) {
									std::cout << curr_day[i];
								}
								else {
									std::cout << curr_day[i] << " ";
								}
							}
							++curr_day[i];
						}
						else if (curr_day[i] == end[i]) {

							if (i == 2 || (i == 1 && status[2]) || (i == 0 && status[1] && status[2])) {
								std::cout << curr_day[i];
							}
							else {
								std::cout << curr_day[i] << " ";
							}
							status[i] = true;
							break;
						}
						++curr[i];
						if (curr[i] == 7) {
							break;
						}
					}

					if (i == 2) {
						std::cout << std::endl;	
					}
					else if ((status[0] && status[1] && status[2])) {
						std::cout << std::endl;
						break;
					}
					else {
						for (int j = curr[i]; j < 6; ++j) {
							std::cout << "   ";
						}
						std::cout << " ";
					}
					curr[i] = 0;
				}
			}
			if (block < 3) {
				std::cout << std::endl;
			}
		}
	}
	else if (argc == 3) {
		int month = 0;
		const char* ch_y = argv[2];
		const char* ch_m = argv[1];

		bool f_y = true;
		bool f_m = true;

		def_y(ch_y, year, f_y);
		def_m(ch_m, month, f_m);

		if (!f_m || !f_y || month < 1 || month > 12) {
			unk();
			return 0;
		}

		int stday = startday(month, year);

		int curr_position = 0;
		int days = dayInMonth(month, year);

		std::cout << year << std::endl;
		usmonth(month);

		hat();
		for (int i = 1; i <= days; ++i) {
			while (curr_position != stday && i == 1) {
				std::cout << "   ";
				++curr_position;
			}

			if (i < 10) {
				if (curr_position == 6) {
					std::cout << ' ' << i << std::endl;
					curr_position = 0;
				}
				else {
					std::cout << ' ' << i << ' ';
					++curr_position;
				}
			}
			else {
				if (curr_position == 6 || i == days) {
					std::cout << i << std::endl;
					curr_position = 0;
				}
				else {
					std::cout << i << ' ';
					++curr_position;
				}
			}
		}
	}
	else {
		unk();
		return 0;
	}

	return 0;
}
