#pragma once
#include <iostream>
#include <string>
#include <vector>

class HashEl {
public:
	int num_train;         // ����
	bool Popen = true; // ������� �������� ��� ������� ������
	bool Pdel = false; // ������� ��������

	char start_place[20];
	char end_place[20];
	char time[20];
};