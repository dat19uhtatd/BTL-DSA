#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>  // cho atoi
using namespace std;

// ====== C?u trúc môn h?c ======
struct MonHoc {
    string ma;
    string ten;
    int tinchi;
};

// ====== Đ?c d? li?u t? file ======
void docFile(vector<MonHoc> &ds, const string &tenFile) {
    ifstream f(tenFile.c_str());
    if (!f.is_open()) {
        cout << "Khong tim thay file " << tenFile << ", bat dau voi danh sach rong.\n";
        return;
    }

    ds.clear();
    string dong;
    while (getline(f, dong)) {
        stringstream ss(dong);
        MonHoc mh;
        string tinchiStr;

        getline(ss, mh.ma, '|');
        getline(ss, mh.ten, '|');
        getline(ss, tinchiStr, '|');

        mh.tinchi = atoi(tinchiStr.c_str());
        ds.push_back(mh);
    }
    f.close();
    cout << "Da doc " << ds.size() << " mon hoc tu file.\n";
}

// ====== Ghi d? li?u ra file ======
void ghiFile(const vector<MonHoc> &ds, const string &tenFile) {
    ofstream f(tenFile.c_str());
    if (!f.is_open()) {
        cout << "Khong the mo file de ghi!\n";
        return;
    }

    for (size_t i = 0; i < ds.size(); i++) {
        f << ds[i].ma << "|" << ds[i].ten << "|" << ds[i].tinchi << "\n";
    }
    f.close();
    cout << "Da luu du lieu vao file " << tenFile << ".\n";
}

// ====== Thêm môn h?c ======
void themMonHoc(vector<MonHoc> &ds) {
    MonHoc mh;
    cout << "Nhap ma mon: ";
    getline(cin, mh.ma);

    // --- Kiểm tra trùng mã ---
    for (size_t i = 0; i < ds.size(); i++) {
        if (ds[i].ma == mh.ma) {
            cout << "Mon hoc co ma " << mh.ma << " da ton tai trong danh sach!\n";
            return; // Không thêm nữa
        }
    }
    
    cout << "Nhap ten mon: ";
    getline(cin, mh.ten);
    cout << "Nhap so tin chi: ";
    cin >> mh.tinchi;
    cin.ignore();

    ds.push_back(mh);
    cout << "Da them mon hoc thanh cong!\n";
}

// ====== Xóa môn h?c theo m? ======
void xoaMonHoc(vector<MonHoc> &ds) {
    if (ds.empty()) {
        cout << "Danh sach rong, khong the xoa!\n";
        return;
    }

    string maXoa;
    cout << "Nhap ma mon can xoa: ";
    getline(cin, maXoa);

    bool timThay = false;
    for (vector<MonHoc>::iterator it = ds.begin(); it != ds.end(); ++it) {
        if (it->ma == maXoa) {
            ds.erase(it);
            timThay = true;
            cout << "Da xoa mon hoc co ma " << maXoa << ".\n";
            break;
        }
    }

    if (!timThay)
        cout << "Khong tim thay mon hoc co ma " << maXoa << ".\n";
}

// ====== Hi?n th? danh sách ======
void hienThiDanhSach(const vector<MonHoc> &ds) {
    if (ds.empty()) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << "\n===== DANH SACH MON HOC =====\n";
    for (size_t i = 0; i < ds.size(); i++) {
        cout << i + 1 << ". Ma: " << ds[i].ma
             << " | Ten: " << ds[i].ten
             << " | Tin chi: " << ds[i].tinchi << "\n";
    }
}

// ====== Tính t?ng s? tín ch? ======
void tinhTongTinChi(const vector<MonHoc> &ds) {
    int tong = 0;
    for (size_t i = 0; i < ds.size(); i++)
        tong += ds[i].tinchi;

    cout << "Tong so tin chi da dang ky: " << tong << "\n";
}

// ====== Menu chính ======
void menu() {
    vector<MonHoc> ds;
    string tenFile = "monhoc.txt";
    docFile(ds, tenFile);

    int chon;
    do {
        cout << "\n===== MON HOC DA DANG KY =====\n";
        cout << "1. Them mon hoc\n";
        cout << "2. Xoa mon hoc\n";
        cout << "3. Tinh tong so tin chi\n";
        cout << "4. Hien thi danh sach mon hoc\n";
        cout << "5. Luu va thoat\n";
        cout << "Chon: ";
        cin >> chon;
        cin.ignore();

        switch (chon) {
            case 1: themMonHoc(ds); break;
            case 2: xoaMonHoc(ds); break;
            case 3: tinhTongTinChi(ds); break;
            case 4: hienThiDanhSach(ds); break;
            case 5:
                ghiFile(ds, tenFile);
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 5);
}

// ====== Hàm main ======
int main() {
    menu();
    return 0;
}
