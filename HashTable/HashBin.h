#pragma once
#include "HashEl.h"
#include "HashTableManage.h"
#include "FileBinManage.h"

using namespace std;

class HashBin : public FileBinManage, public HashTableManage {
    
public:

    int CreateBinFile(string nametf, string namebf) {
        ifstream itf(nametf);
        if (!itf) return 1;
        fstream bf(namebf, ios::binary | ios::out); //поток для записи в бинарный файл
        HashEl r;
        int i = 0;
        while (!itf.eof()) {
            itf >> r.num_train;
            //itf.get(); // считывает 1 символ
            //itf >> r.Popen;
            //itf.get(); // считывает 1 символ
            //itf >> r.Pdel;
            itf.get(); // считывает 1 символ
            itf.getline(r.start_place, 20, '\n'); // 2 параметр - максимальная длина, 3 параметр - разделитель
            itf.getline(r.end_place, 20, '\n');
            itf.getline(r.time, 20, '\n');
            
            if (i > M) {
                rehash();
            }
            Hash hash1;
            hash1.num_train = hash(r.num_train, M);
            hash1.Popen = true;
            hash1.Pdel = false;
            values[i] = hash1;
            i++;

            bf.write((char*)&r, sizeof(HashEl)); // 1 - откуда писать, 2 - сколько писать
        }
        itf.close();
        bf.close();
        return 0;
    }

    virtual int searchKeyInBinFIle(string namebf, int num_train) {
        fstream bf(namebf, ios::binary | ios::in); // поток для чтения из бинарного файла
        if (!bf) return 2;
        HashEl r;
        int len = sizeof(HashEl);
        int offset = (hash(num_train, M) - 1) * sizeof(HashEl);
        bf.seekg(offset, ios::beg);
        bf.read((char*)&r, sizeof(HashEl));
        if (!bf.fail()) {
            return r.num_train;
        }
        else {
            return 1;
        }
        bf.close();
        //bf.read((char*)&r, len);
/*        int numrecord = 1;
        while (!bf.eof()) {
            if (r.num_train == num_train) return numrecord;
            bf.read((char*)&r, len);
            numrecord++;
        }
        bf.close();
        return -1; */// запись с данные номером не найдена
    }

    virtual int delete_railwayHash(string namebf, int num_train) {
        vector<HashEl> vector_file;
        fstream bf(namebf, ios::binary | ios::in); // поток для чтения из бинарного файла
        if (!bf) return 1;
        HashEl r;
        int len = sizeof(HashEl);
        int offset = (hash(num_train, M) - 1) * sizeof(HashEl);
        bf.seekg(offset, ios::beg);
        bf.read((char*)&r, len);
        vector_file.push_back(r);
        bf.close();
        delFromHashTable(num_train);
        fstream bf2(namebf, ios::binary | ios::out); //поток для записи в бинарный файл
        for (int i = 0; i < vector_file.size(); i++)
            bf2.write((char*)&vector_file[i], sizeof(HashEl)); // 1 - откуда писать, 2 - сколько писать

        bf2.close();
        return 0;
    }

    int testHeshT() {
        HashTableManage table;
        Hash el;

        string file_name = "test.bin";

        CreateBinFile("test.txt", file_name);

        cout << "searchKeyInBinFIle(file_name, 111)" << '\n';
        cout << searchKeyInBinFIle(file_name, 111) << '\n';
        cout << "delete_railwayHash(file_name, 111)" << '\n';
        cout << delete_railwayHash(file_name, 111) << '\n';

        cout << "find_value(11)" << '\n';
        cout << find_value(11) << '\n';

        delFromHashTable(11);

        HashEl el1;
        el1.num_train = 10213;
        strcpy(el1.start_place, "Magadan");
        strcpy(el1.end_place, "Tver");
        strcpy(el1.time, "10:00");

        insertInHashTable(el);
        cout << "\nInsert " << el.num_train << " is done\n";

        return 0;
    }

};