#include "sinhvien.cpp"
#include <iostream>
#include <list>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#ifndef _SINH_VIEN_LIST_CPP_
#define _SINH_VIEN_LIST_CPP_

using namespace std;

class ListSinhVien {
    list<SinhVien> a;

public:
    ListSinhVien() {}
    ListSinhVien(list<SinhVien> a) {
        this->a = a;
    }

    size_t size() {
        return a.size();
    }

    bool _filter(const SinhVien &x) {
        for (auto &sv : a) {
            if (x._msv() == sv._msv()) {
                cout << "Ma sinh vien da ton tai trong danh sach!" << endl;
                return false;
            }
        }
        return true;
    }

    void create() {
        while (true) {
            SinhVien x;
            cout << "\n=== Nhap thong tin sinh vien ===\n";
            cin >> x;

            if (_filter(x))
                a.push_back(x);
            else {
                cout << "Vui long nhap lai!\n";
                continue;
            }

            char choice;
            cout << "Ban co muon nhap them sinh vien khac (y/n)? ";
            cin >> choice;
            if (choice == 'n' || choice == 'N')
                break;
        }
    }

    void readFromFile(const string &filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file " << filename << endl;
            return;
        }

        int count = 0;
        while (file.good()) {
            SinhVien x;
            string temp_msv_str, hoTen, ngaySinh, gioiTinh, lop;
            int msv_int;

            if (!getline(file, temp_msv_str)) break;
            if (temp_msv_str.empty()) continue;

            stringstream ss(temp_msv_str);
            if (!(ss >> msv_int)) continue;
            x._set_msv(msv_int);

            if (!getline(file, hoTen)) break;
            x._set_hoTen(hoTen);

            if (!getline(file, ngaySinh)) break;
            x._set_ngaySinh(ngaySinh);

            if (!getline(file, gioiTinh)) break;
            x._set_gioiTinh(gioiTinh);

            if (!getline(file, lop)) break;
            x._set_lop(lop);

            if (_filter(x)) {
                a.push_back(x);
                count++;
            }
        }

        file.close();
        cout << "Da doc va them thanh cong " << count << " sinh vien tu file " << filename << endl;
    }

    // Tìm sinh viên theo mã số
    list<SinhVien>::iterator search(int msv) {
        for (auto it = a.begin(); it != a.end(); ++it) {
            if (msv == it->_msv()) {
                return it;
            }
        }
        return a.end();
    }

    // Tìm sinh viên theo tên
    list<list<SinhVien>::iterator> searchTheoTen(string name) {
        list<list<SinhVien>::iterator> result;
        for (auto it = a.begin(); it != a.end(); ++it) {
            if (name == it->_hoTen()) {
                result.push_back(it);
            }
        }
        return result;
    }

    list<SinhVien>::iterator _end() {
        return a.end();
    }

    // Xóa sinh viên
    void remove(list<SinhVien>::iterator it) {
        a.erase(it);
    }

    // Sửa thông tin sinh viên
    void edit(list<SinhVien>::iterator it) {
        while (true) {
            cout << "\nSua thong tin sinh vien co ma so: " << it->_msv() << endl;
            cout << "1. Ho va ten\n";
            cout << "2. Ngay sinh\n";
            cout << "3. Gioi tinh\n";
            cout << "4. Lop\n";
            cout << "5. Thoat sua\n";
            cout << "Chon muc can sua: ";
            int n;
            cin >> n;
            cin.ignore();

            if (n == 1) {
                string name;
                cout << "Nhap ho va ten moi: ";
                getline(cin, name);
                it->_set_hoTen(name);
            } else if (n == 2) {
                string ngaySinh;
                cout << "Nhap ngay sinh moi: ";
                getline(cin, ngaySinh);
                it->_set_ngaySinh(ngaySinh);
            } else if (n == 3) {
                string gioiTinh;
                cout << "Nhap gioi tinh moi: ";
                getline(cin, gioiTinh);
                it->_set_gioiTinh(gioiTinh);
            } else if (n == 4) {
                string lop;
                cout << "Nhap lop moi: ";
                getline(cin, lop);
                it->_set_lop(lop);
            } else if (n == 5) {
                break;
            } else {
                cout << "Lua chon khong hop le, vui long nhap lai.\n";
            }

            char t;
            cout << "Ban co muon tiep tuc sua sinh vien nay (y/n)? ";
            cin >> t;
            if (t != 'y' && t != 'Y') break;
        }
    }

    // Hiển thị danh sách sinh viên
    void display() {
        if (a.empty()) {
            cout << "Danh sach hien dang trong.\n";
            return;
        }

        cout << left << setw(15) << "Ma SV"
             << setw(25) << "Ho va Ten"
             << setw(15) << "Ngay Sinh"
             << setw(15) << "Gioi Tinh"
             << setw(10) << "Lop" << '\n';
        cout << string(80, '-') << endl;

        for (auto &sv : a)
            cout << sv;

        cout << string(80, '-') << endl;
    }

    // Xóa toàn bộ danh sách
    void del() {
        a.clear();
        cout << "Da xoa toan bo danh sach sinh vien.\n";
    }

    // Sắp xếp danh sách theo lớp và tên
    void sort() {
        if (a.empty()) {
            cout << "Danh sach trong, khong the sap xep.\n";
            return;
        }
        a.sort([](SinhVien &sv1, SinhVien &sv2) {
            if (sv1._lop() != sv2._lop())
                return sv1._lop() < sv2._lop();
            return sv1._hoTen() < sv2._hoTen();
        });

        cout << "Danh sach sau khi sap xep:\n";
        display();
    }
};

#endif
