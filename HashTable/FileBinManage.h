#pragma once
#include "HashEl.h"

using namespace std;

class FileBinManage {
public:
    virtual int CreateBinFile(string nametf, string namebf) {
        ifstream itf(nametf);
        if (!itf) return 1;
        fstream bf(namebf, ios::binary | ios::out); //поток дл€ записи в бинарный файл
        HashEl r;
        while (!itf.eof()) {
            itf >> r.num_train;
            itf.get(); // считывает 1 символ
            itf >> r.Popen;
            itf.get(); // считывает 1 символ
            itf >> r.Pdel;
            itf.get(); // считывает 1 символ
            itf.getline(r.start_place, 20, '\n'); // 2 параметр - максимальна€ длина, 3 параметр - разделитель
            itf.getline(r.end_place, 20, '\n');
            itf.getline(r.time, 20, '\n');
            bf.write((char*)&r, sizeof(HashEl)); // 1 - откуда писать, 2 - сколько писать
        }
        itf.close();
        bf.close();
        return 0;
    }
    virtual int outBinFile(string namebf) {
        fstream bf(namebf, ios::binary | ios::in); // поток дл€ чтени€ из бинарного файла
        if (!bf) return 1;
        HashEl r;
        int len = sizeof(HashEl);
        bf.read((char*)&r, len);
        while (!bf.eof()) {
            cout << r.num_train << ' ' << r.time << endl;
            cout << r.start_place << ' ' << r.end_place << endl;
            bf.read((char*)&r, len);
        }
        bf.close();
        return 0;
    }
    virtual int searchKeyInBinFIle(string namebf, int num_train) {
        fstream bf(namebf, ios::binary | ios::in); // поток дл€ чтени€ из бинарного файла
        if (!bf) return 0;
        HashEl r;
        int len = sizeof(HashEl);
        bf.read((char*)&r, len);
        int numrecord = 1;
        while (!bf.eof()) {
            if (r.num_train == num_train) return numrecord;
            bf.read((char*)&r, len);
            numrecord++;
        }
        bf.close();
        return -1; // запись с данные номером не найдена
    }
    int directAccess_to_the_railwayInBinFile(string namebf, int numTrain, HashEl& r) {
        fstream bf(namebf, ios::binary | ios::in);
        int kod;
        if (bf.is_open()) {
            int offset = (numTrain - 1) * sizeof(HashEl);
            bf.seekg(offset, ios::beg);
            bf.read((char*)&r, sizeof(HashEl));
            if (!bf.fail()) {
                kod = 0;
            }
            else {
                kod = 1;
            }
        }
        else {
            kod = 2;
        }
        bf.close();
        return kod;
    }
    virtual int delete_railway(string namebf, int num_train) {
        //fstream bf(namebf, ios::binary | ios::in); // поток дл€ чтени€ из бинарного файла
        //if (!bf) return 1;
        //railway r;
        //int len = sizeof(railway);
        //bf.read((char*)&r, len);
        //while (!bf.eof()) {
        //    if (r.num_train != num_train)
        //        vector_file.push_back(r);
        //    bf.read((char*)&r, len);
        //}
        //bf.close();

        //fstream bf2(namebf, ios::binary | ios::out); //поток дл€ записи в бинарный файл
        //for (int i = 0; i < vector_file.size(); i++)
        //    bf2.write((char*)&vector_file[i], sizeof(railway)); // 1 - откуда писать, 2 - сколько писать

        //bf2.close();
        //return 0;

        //////////////////////////
        fstream bf(namebf, ios::binary | ios::in); // поток дл€ чтени€ из бинарного файла
        if (!bf) return 1;
        fstream bf2(namebf, ios::binary | ios::out); //поток дл€ записи в бинарный файл
        if (!bf2) return 1;
        HashEl r;
        int len = sizeof(HashEl);
        bf.read((char*)&r, len);
        while (!bf.eof()) {
            if (r.num_train != num_train)
                bf2.write((char*)&r, sizeof(HashEl));
            bf.read((char*)&r, len);
        }

        bf2.close();
        bf.close();

    }
    // 1 доп. задание
    // —формировать справку по поездам, отправл€ющимс€ в указанный пункт назначени€. –езультаты записать в новый двоичный файл такой же структуры, как и исходный.
    int reference_city_end(string namebf, string nametf, char end_place[20]) {
        //vector<HashEl> vector_file;
        //fstream bf(namebf, ios::binary | ios::in); // поток дл€ чтени€ из бинарного файла
        //if (!bf) return 1;
        //HashEl r;
        //int len = sizeof(HashEl);
        //bf.read((char*)&r, len);
        //while (!bf.eof()) {
        //    if (!strcmp(r.end_place, end_place))
        //        vector_file.push_back(r);
        //    bf.read((char*)&r, len);
        //}
        //bf.close();

        //fstream bf2(nametf, ios::binary | ios::out); //поток дл€ записи в бинарный файл
        //for (int i = 0; i < vector_file.size(); i++)
        //    bf2.write((char*)&vector_file[i], sizeof(HashEl)); // 1 - откуда писать, 2 - сколько писать

        //bf2.close();
        //return 0;


        fstream bf(namebf, ios::binary | ios::in); // поток дл€ чтени€ из бинарного файла
        if (!bf) return 1;
        fstream bf2(nametf, ios::binary | ios::out); //поток дл€ записи в бинарный файл
        if (!bf2) return 1;
        HashEl r;
        int len = sizeof(HashEl);

        bf.read((char*)&r, len);
        while (!bf.eof()) {
            if (!strcmp(r.end_place, end_place))
                bf2.write((char*)&r, sizeof(HashEl));
            bf.read((char*)&r, len);
        }

        bf.close();
        bf2.close();
        return 0;
    }

};