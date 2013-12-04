#include "traffic.h"

Car::Car() {
    id = -1;
	arrival = -1;
	direction = -1;
}

Car::Car (int id_, int arrival_, int direction_) {
    id = id_;
	arrival = arrival_;
	direction = direction_;
}

void Car::set_values(int id_, int arrival_, int direction_) {
    id = id_;
	arrival = arrival_;
	direction = direction_;
}
