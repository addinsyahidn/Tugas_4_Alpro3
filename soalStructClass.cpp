#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Mahasiswa {
private:
    string nama;
    string nim;
    float ipk;

public:
    Mahasiswa(string n, string ni, float i) {
        nama = n;
        nim = ni;
        ipk = i;
    }

    string getNama() {
        return nama;
    }

    string getNIM() {
        return nim;
    }

    float getIPK() {
        return ipk;
    }

    void tampilkanData() {
        cout << "Nama : " << nama << endl;
        cout << "NIM  : " << nim << endl;
        cout << "IPK  : " << fixed << setprecision(2) << ipk << endl;
        cout << "------------------------" << endl;
    }
};

int main() {
    vector<Mahasiswa> daftarMahasiswa;
    int pilihan;

    do {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Tambah Data Mahasiswa" << endl;
        cout << "2. Tampilkan Seluruh Data Mahasiswa" << endl;
        cout << "3. Hitung Rata-rata IPK Mahasiswa" << endl;
        cout << "4. Mahasiswa dengan IPK Tertinggi" << endl;
        cout << "5. Mahasiswa dengan IPK Terendah" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {

        case 1: {
            string nama, nim;
            float ipk;

            cin.ignore();

            cout << "Masukkan Nama : ";
            getline(cin, nama);

            cout << "Masukkan NIM  : ";
            getline(cin, nim);

            cout << "Masukkan IPK  : ";
            cin >> ipk;

            daftarMahasiswa.push_back(Mahasiswa(nama, nim, ipk));

            cout << "Data mahasiswa berhasil ditambahkan!\n";
            break;
        }

        case 2: {
            if (daftarMahasiswa.empty()) {
                cout << "Belum ada data mahasiswa.\n";
            } else {
                cout << "\n=== DATA MAHASISWA ===" << endl;
                for (int i = 0; i < daftarMahasiswa.size(); i++) {
                    daftarMahasiswa[i].tampilkanData();
                }
            }
            break;
        }

        case 3: {
            if (daftarMahasiswa.empty()) {
                cout << "Belum ada data mahasiswa.\n";
            } else {
                float total = 0;

                for (int i = 0; i < daftarMahasiswa.size(); i++) {
                    total += daftarMahasiswa[i].getIPK();
                }

                float rata = total / daftarMahasiswa.size();

                cout << "Rata-rata IPK Mahasiswa = "
                     << fixed << setprecision(2)
                     << rata << endl;
            }
            break;
        }

        case 4: {
            if (daftarMahasiswa.empty()) {
                cout << "Belum ada data mahasiswa.\n";
            } else {
                int indeksMax = 0;

                for (int i = 1; i < daftarMahasiswa.size(); i++) {
                    if (daftarMahasiswa[i].getIPK() >
                        daftarMahasiswa[indeksMax].getIPK()) {
                        indeksMax = i;
                    }
                }

                cout << "\nMahasiswa dengan IPK Tertinggi:\n";
                daftarMahasiswa[indeksMax].tampilkanData();
            }
            break;
        }

        case 5: {
            if (daftarMahasiswa.empty()) {
                cout << "Belum ada data mahasiswa.\n";
            } else {
                int indeksMin = 0;

                for (int i = 1; i < daftarMahasiswa.size(); i++) {
                    if (daftarMahasiswa[i].getIPK() <
                        daftarMahasiswa[indeksMin].getIPK()) {
                        indeksMin = i;
                    }
                }

                cout << "\nMahasiswa dengan IPK Terendah:\n";
                daftarMahasiswa[indeksMin].tampilkanData();
            }
            break;
        }

        case 6:
            cout << "Program selesai. Terima kasih!\n";
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 6);

    return 0;
}// Kerjakan soal di Modul 8
