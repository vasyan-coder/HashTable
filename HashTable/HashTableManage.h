#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <stdio.h>
#include "HashEl.h"

using namespace std;

class HashTableManage {
protected:
	int M = 10; // ����� �������
	int N = 0; // ���������� �������� ������� �������
	int count_del_el = 0; // ���������� ��������� ��������� �������

public:
	HashEl* values = new HashEl[M]; // hash �������	


public:
	// ������� �����������
	int hash(int id, int len) { return id % len; }

	// ������� � ���-�������
	void insertInHashTable(HashEl el) {
		int index = hash(el.num_train, this->M);

		// ��������� �������� (������� �����������)
		// ���� ����� ������
		if (!this->values[index].Popen)
			index = hash(index + index / this->M, this->M);

		if (index < this->M) {
			this->values[index] = el;
			this->N = this->N + 1;
			this->values[index].Popen = false;
		}
	}

	// ������� ��������
	int find_value(int key) {
		int i = hash(key, this->M);
		
		while (!this->values[i].Pdel && this->values[i].Popen && this->values[i].num_train != key) {
			i++;
		}
		if (this->values[i].Pdel && this->values[i].Popen)
			return -1; // ���� ������� ����� �������� ������ � ��������
		else
			return i; // ��������
	}

	// �������� �� ���-�������
	void delFromHashTable(int key) {
		int index = find_value(key);
		this->values[index].Popen = true;
		this->values[index].Pdel = true;
		this->values[index].num_train = NULL;
		memset(this->values[index].start_place, 0, sizeof(this->values[index].start_place));
		memset(this->values[index].end_place, 0, sizeof(this->values[index].end_place));
		memset(this->values[index].time, 0, sizeof(this->values[index].time));
		count_del_el += 1;
	}

	void rehash() {
		HashEl *temp = new HashEl[M*2];
		for (int i = 0; i < M; i++)
			temp[i] = this->values[i];
		
		M *= 2;
		delete[] values;
		for (int i = 0; i < M * 2; i++) {
			insertInHashTable(temp[i]);
		}
	}

	void print(HashTableManage& table) {
		for (int i = 0; i < M; i++) {
			if (!table.values[i].Popen) {
				cout << table.values[i].num_train << '\n';
				cout << table.values[i].Popen << '\n';
				cout << table.values[i].Pdel << '\n';
				cout << table.values[i].start_place << '\n';
				cout << table.values[i].end_place << '\n';
				cout << table.values[i].time << '\n';
				cout << '\n';
			}
		}
	}
};