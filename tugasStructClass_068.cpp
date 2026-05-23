#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <algorithm> // Digunakan untuk fungsi pencarian nilai ekstrem (max_element) dan validasi (any_of)

using namespace std;

// Sesuai instruksi soal di gambar: Menggunakan 'class' Mahasiswa untuk merepresentasikan entitas
class Mahasiswa {
public:
    // Atribut wajib yang diminta oleh soal
    string nama, nim;
    float ipk;

    // Konstruktor dengan Member Initializer List untuk menginisialisasi objek mahasiswa baru secara cepat
    Mahasiswa(const string& n, const string& nm, float i) : nama(n), nim(nm), ipk(i) {}

    // --- METODE-METODE OPERASI DI DALAM CLASS (Sesuai Perintah Soal) ---
    // Menggunakan keyword 'static' agar metode ini milik kelas dan bisa dipanggil langsung di main tanpa membuat objek baru

    // a. Metode untuk menambahkan data mahasiswa baru ke dalam vector
    static void tambahData(vector<Mahasiswa>& daftarMahasiswa) {
        string nama, nim;
        float ipk;

        cout << "=== Tambah Data Mahasiswa ===\nMasukkan Nama : ";
        getline(cin >> ws, nama); // "ws" digunakan untuk membuang spasi/newline yang tertinggal sebelum membaca teks nama lengkap
        cout << "Masukkan NIM  : ";
        cin >> nim;

        // Validasi Duplikasi NIM: Memastikan NIM belum terdaftar menggunakan std::any_of
        bool nimSudahAda = any_of(daftarMahasiswa.begin(), daftarMahasiswa.end(), 
            [&nim](const Mahasiswa& msh) { return msh.nim == nim; });

        if (nimSudahAda) {
            cout << "\nGagal: NIM " << nim << " sudah terdaftar di sistem!\n";
            cin.ignore(); // Membersihkan sisa buffer input agar jeda layar berjalan normal
            return; // Menghentikan fungsi dan membatalkan input data
        }

        cout << "Masukkan IPK  : ";
        cin >> ipk;
        cin.ignore(); // Membuang sisa karakter 'Enter' di buffer setelah input angka desimal IPK

        // Validasi rentang standar nilai IPK (0.0 sampai 4.0)
        if (ipk < 0.0f || ipk > 4.0f) {
            cout << "\nGagal: Nilai IPK harus di antara 0.0 dan 4.0!\n";
        } else {
            // emplace_back mengonstruksi objek Mahasiswa langsung di dalam memori vector untuk menghemat RAM
            daftarMahasiswa.emplace_back(nama, nim, ipk);
            cout << "\nData berhasil disimpan!\n";
        }
    }

    // b. Metode untuk menampilkan seluruh data mahasiswa beserta informasinya masing-masing
    static void tampilkanSeluruhData(const vector<Mahasiswa>& daftarMahasiswa) {
        cout << "=== Seluruh Data Mahasiswa ===\n";
        // Validasi data kosong (Early Return) untuk mencegah error operasi pada vector kosong
        if (daftarMahasiswa.empty()) {
            cout << "Data masih kosong.\n";
            return;
        }

        int i = 1;
        // Menggunakan range-based loops dengan const auto& untuk mengakses data tanpa menyalin objek (menghemat memori)
        for (const auto& msh : daftarMahasiswa) {
            // fixed dan setprecision(2) digunakan untuk mengunci tampilan desimal IPK menjadi 2 angka di belakang koma
            cout << i++ << ". NIM: " << msh.nim << " | Nama: " << msh.nama 
                 << " | IPK: " << fixed << setprecision(2) << msh.ipk << "\n";
        }
    }

    // c. Metode untuk menghitung rata-rata IPK dari seluruh mahasiswa
    static void hitungRataRataIPK(const vector<Mahasiswa>& daftarMahasiswa) {
        cout << "=== Hitung Rata-Rata IPK ===\n";
        if (daftarMahasiswa.empty()) {
            cout << "Data masih kosong, rata-rata tidak bisa dihitung.\n";
            return;
        }

        double totalIPK = 0;
        // Akumulasi seluruh nilai IPK mahasiswa ke dalam variabel totalIPK
        for (const auto& msh : daftarMahasiswa) totalIPK += msh.ipk;

        // Pembagian total nilai dengan ukuran vector (daftarMahasiswa.size()) untuk mendapatkan nilai rata-rata
        cout << "Total Mahasiswa: " << daftarMahasiswa.size() << "\n"
             << "Rata-rata IPK  : " << fixed << setprecision(2) << totalIPK / daftarMahasiswa.size() << "\n";
    }

    // d & e. Metode internal pembantu (helper function) untuk mencetak data mahasiswa secara rapi
    static void cetakDetail(const string& judul, const Mahasiswa& msh) {
        cout << "=== " << judul << " ===\n"
             << "Nama : " << msh.nama << "\nNIM  : " << msh.nim 
             << "\nIPK  : " << fixed << setprecision(2) << msh.ipk << "\n";
    }

    // Metode gabungan untuk mencari nilai ekstrem (IPK Tertinggi / Terendah) sesuai request menu 4 dan 5
    static void tampilkanNilaiEkstrem(const vector<Mahasiswa>& daftarMahasiswa, bool cariTertinggi) {
        if (daftarMahasiswa.empty()) {
            cout << "Data masih kosong.\n";
            return;
        }

        // max_element mencari elemen berbasis algoritma komparator lambda fungsi secara dinamis
        // "auto it" menampung hasil pencarian dalam tipe data Iterator (pointer penunjuk posisi memori di vector)
        auto it = max_element(daftarMahasiswa.begin(), daftarMahasiswa.end(), 
            [cariTertinggi](const Mahasiswa& a, const Mahasiswa& b) {
                // Jika cariTertinggi bernilai true, operator '<' digunakan untuk memicu pencarian nilai maks
                // Jika cariTertinggi bernilai false, operator '>' digunakan untuk memicu pencarian nilai min
                return cariTertinggi ? (a.ipk < b.ipk) : (a.ipk > b.ipk);
            });

        // Mengirimkan hasil dereferensi iterator (*it) untuk menampilkan data lengkap mahasiswa yang ditemukan
        cetakDetail(cariTertinggi ? "Mahasiswa dengan IPK Tertinggi" : "Mahasiswa dengan IPK Terendah", *it);
    }
};

// Fungsi utama alur program dijalankan
int main() {
    vector<Mahasiswa> m; // Deklarasi wadah array dinamis (vector) untuk menampung objek-objek class Mahasiswa
    char input; // Variabel penampung pilihan nomor menu dari pengguna

    do {
        system("cls"); // Membersihkan layar terminal sebelum menampilkan Menu Utama
        // Teks menu dibuat sama persis teksnya seperti gambar soal tugas Anda
        cout << "Menu:\n"
                "1. Tambah Data Mahasiswa\n"
                "2. Tampilkan Seluruh Data Mahasiswa\n"
                "3. Hitung Rata-rata IPK Mahasiswa\n"
                "4. Mahasiswa dengan IPK Tertinggi\n"
                "5. Mahasiswa dengan IPK Terendah\n"
                "6. Keluar\n"
                "Pilih menu (1-6): ";
        cin >> input;
        cin.ignore(); // Membersihkan buffer karakter 'Enter' setelah input menu agar fungsi getline() tidak terlewat
        
        system("cls"); // Membersihkan layar terminal sebelum masuk ke halaman konten sub-menu

        // Sesuai instruksi gambar: Pemanggilan metode operasi kini menggunakan namespace class 'Mahasiswa::'
        if (input == '1') Mahasiswa::tambahData(m);
        else if (input == '2') Mahasiswa::tampilkanSeluruhData(m);
        else if (input == '3') Mahasiswa::hitungRataRataIPK(m);
        else if (input == '4') Mahasiswa::tampilkanNilaiEkstrem(m, true);  // Kirim parameter true untuk mencari nilai tertinggi
        else if (input == '5') Mahasiswa::tampilkanNilaiEkstrem(m, false); // Kirim parameter false untuk mencari nilai terendah
        else if (input == '6') { cout << "Program selesai. Terima kasih!\n"; break; } // Keluar dari loop do-while dan selesai
        else cout << "Pilihan tidak valid!\n";

        // Fitur penahan layar menggunakan cin.get() agar output data sub-menu sempat dibaca oleh pengguna sebelum di-clear
        cout << "\nTekan Enter untuk kembali ke menu...";
        cin.get(); 

    } while (input != '6'); // Perulangan terus berjalan selama pengguna tidak memilih menu nomor 6
    
    return 0;
}
