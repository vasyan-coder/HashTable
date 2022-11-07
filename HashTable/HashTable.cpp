#include <iostream>
#include <fstream>

#include "FileBinManage.h"
#include "HashBin.h"
#include "HashTableManage.h"
#include "HashEl.h"

using namespace std;


int main() {
    setlocale(LC_ALL, "ru");
    
    HashBin hb;

    hb.CreateBinFile("test.txt", "test.bin");

    //HashTableManage table;
    //HashEl el;

    //fstream file("test.txt");

    //int num;
    //bool Popen;
    //bool Pdel;

    //char start_place[20];
    //char end_place[20];
    //char time[20];

    //if (!file) return 1;

    //file >> num;
    //el.num_train = num;
    //file >> Popen;
    //el.Popen = Popen;
    //file >> Pdel;
    //el.Pdel = Pdel;
    //file.get();
    //file.getline(el.start_place, 20, '\n');
    //file.getline(el.end_place, 20, '\n');
    //file.getline(el.time, 20, '\n');
    //table.insertInHashTable(el);
    //while (!file.eof()) {
    //    file >> num;
    //    el.num_train = num;
    //    file >> Popen;
    //    el.Popen = Popen;
    //    file >> Pdel;
    //    el.Pdel = Pdel;
    //    file.get();
    //    file.getline(el.start_place, 20, '\n');
    //    file.getline(el.end_place, 20, '\n');
    //    file.getline(el.time, 20, '\n');
    //    table.insertInHashTable(el);
    //}

    //table.delFromHashTable(10, table);

    //table.rehash();

    //table.print(table);

    //cout << table.find_value(table, 11) << '\n';

    return 0;
}