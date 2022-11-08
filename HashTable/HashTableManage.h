#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <stdio.h>
#include "HashEl.h"
#include "Hash.h"

using namespace std;

class HashTableManage {
protected:
	int M = 10; // ����� �������
	int N = 0; // ���������� �������� ������� �������
	int count_del_el = 0; // ���������� ��������� ��������� �������

public:
	Hash* values = new Hash[M]; // hash �������	


public:
	// ������� �����������
	int hash(int id, int len) { return id % len; }

	// ������� � ���-�������
	void insertInHashTable(Hash el) {
		int index = hash(el.num_train, this->M);
		int num = 0;
		// ��������� �������� (������� �����������)
		// ���� ����� ������
		if (!this->values[index].Popen) {
			index = hash(index + index / this->M, this->M);
			int num = this->values[index].num;
			num++;
		}

		if (index < this->M) {
			this->values[index] = el;
			this->N = this->N + 1;
			this->values[index].Popen = false;
			this->values[index].num = num;
		}
	}

	// ������� ��������
	int find_value(int key) {
		int i = hash(key, this->M);
		
		// ��������� �������� (������� �����������)
		// ���� ����� ������
		if (!this->values[i].Popen) {
			i = hash(i + i / this->M, this->M);
			
		}

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
		//memset(this->values[index].start_place, 0, sizeof(this->values[index].start_place));
		//memset(this->values[index].end_place, 0, sizeof(this->values[index].end_place));
		//memset(this->values[index].time, 0, sizeof(this->values[index].time));
		count_del_el += 1;
	}

	void rehash() {
		Hash *temp = new Hash[M*2];
		for (int i = 0; i < M; i++)
			temp[i] = this->values[i];
		
		M *= 2;
		delete[] values;
		for (int i = 0; i < M * 2; i++) {
			insertInHashTable(temp[i]);
		}
	}
};