#include "mainwindow.h"
#include "ecc.h"

#include <QApplication>
#include <QDateTime>
#include <QDesktopWidget>

#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ret = 0;
    if(argc == 1) {
        QSettings settings("csnc","config");
        MainWindow w(settings);
        w.show();
        w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
        ret = a.exec();
    } else if(argc == 3 && "encrypt" == a.arguments()[1]) {
        ifstream reader(a.arguments()[2].toLocal8Bit().data(),ios::in | ios::binary);
        ofstream writer(a.arguments()[2].replace(".json",".key",Qt::CaseInsensitive).toLocal8Bit().data(),ios::out | ios::binary);

        while(true) {
            int c = reader.get();
            if(c == -1) break;
            writer.put(static_cast<char>(c) ^ 'c');
        }

        writer.close();
        reader.close();
    } else if(argc == 3 && "sign" == a.arguments()[1]) {
        uint8_t publicKey[ECC_BYTES + 1];
        uint8_t privateKey[ECC_BYTES];
        uint8_t signature[ECC_BYTES * 2];
        QString hash = a.arguments()[2];

        ecc_make_key(publicKey,privateKey);
        ecdsa_sign(privateKey,(uint8_t*)hash.toLocal8Bit().data(),signature);

        for(int i=0;i < ECC_BYTES + 1;i++){
            cout.width(2);
            cout.fill('0');
            cout << std::hex << (int)publicKey[i];
        }

        cout << endl;

        for(int i=0;i < ECC_BYTES * 2;i++){
            cout.width(2);
            cout.fill('0');
            cout << std::hex << (int)signature[i];
        }
    } else if(argc == 3 && "decrypt" == a.arguments()[1]) {
        ifstream reader(a.arguments()[2].toLocal8Bit().data(),ios::binary);
        ofstream writer(a.arguments()[2].replace(".key",".json",Qt::CaseInsensitive).toLocal8Bit().data(),ios::binary);

        while(true) {
            int c = reader.get();
            if(c == -1) break;
            writer.put(static_cast<char>(c) ^ 'c');
        }

        writer.close();
        reader.close();
    }

    return ret;
}
