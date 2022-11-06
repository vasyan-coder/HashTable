#pragma once
#include "HashEl.h"
#include "HashTableManage.h"
#include "FileBinManage.h"

using namespace std;

class HashBin : public FileBinManage {

public:
    virtual int searchKeyInBinFIle(string namebf, int num_train) {
        fstream bf(namebf, ios::binary | ios::in); // поток для чтения из бинарного файла
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

    //virtual int directAccess_to_the_railwayInBinFileHash(string namebf, int num_train) override;
    //virtual int delete_railwayHash(string namebf, int numTrain, HashEl& r) override;
    //virtual int reference_city_endHash(string namebf, int num_train) override;

    int testHeshT();
    

    
    int testHeshT() {

    }

};