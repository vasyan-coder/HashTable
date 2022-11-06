#pragma once
#include <iostream>
#include <string>
#include <vector>

class HashEl {
public:
	int num_train;         // ключ
	bool Popen = true; // признак открытой для вставки ячейки
	bool Pdel = false; // признак удаления

	char start_place[20];
	char end_place[20];
	char time[20];
};