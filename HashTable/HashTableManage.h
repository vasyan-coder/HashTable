#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <stdio.h>
#include "HashEl.h"

using namespace std;

class HashTableManage {
	int M; // длина таблицы
	int N = 0; // количество закрытых адресов таблицы
	int count_del_el = 0; // количество удаленных элементов таблицы

public:
	HashEl* values; // hash таблица

public:
	HashTableManage(int M = 10) {
		this->M = M;
		values = new HashEl[M];
	}
	


public:
	// функция хеширования
	int hash(int id, int len) { return id % len; }

	// вставка в хеш-таблицу
	void insertInHashTable(HashEl el, HashTableManage &table) {
		int index = hash(el.num_train, table.M);

		// обработка коллизии (двойное хеширование)
		// если адрес закрыт
		if (!table.values[index].Popen)
			index = hash(index + index / table.M, table.M);

		if (index < table.M) {
			table.values[index] = el;
			table.N = table.N + 1;
			table.values[index].Popen = false;
		}
	}

	// вернуть значение
	int find_value(HashTableManage& table, int key) {
		int i = hash(key, table.M);
		
		while (!table.values[i].Pdel && table.values[i].Popen && table.values[i].num_train != key) {
			i++;
		}
		if (table.values[i].Pdel && table.values[i].Popen)
			return -1; // если элемент имеет признаки записи и удаления
		else
			return i; // смещение
	}

	// удаление из хеш-таблицы
	void delFromHashTable(int key, HashTableManage& table) {
		int index = find_value(table, key);
		table.values[index].Popen = true;
		table.values[index].Pdel = true;
		table.values[index].num_train = NULL;
		memset(table.values[index].start_place, 0, sizeof(table.values[index].start_place));
		memset(table.values[index].end_place, 0, sizeof(table.values[index].end_place));
		memset(table.values[index].time, 0, sizeof(table.values[index].time));
		count_del_el += 1;
	}

	void rehash(HashTableManage& table) {
		HashEl *temp = new HashEl[M*2];
		for (int i = 0; i < M; i++)
			temp[i] = table.values[i];
		
		M *= 2;
		delete[] values;
		values = temp;
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