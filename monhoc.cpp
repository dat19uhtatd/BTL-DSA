#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct MonHoc {
    string ma;
    string ten;
    int tinchi;
};

// ======== Các hàm xử lý ========

// Đọc dữ liệu từ file
void docFile(vector<MonHoc> &ds, const string &tenFile) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong tim thay file, bat dau voi danh sach rong.\n";
        return;
    }

    ds.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        MonHoc mh;
        string tinchiStr;

        getline(ss, mh.ma, '|');
        getline(ss, mh.ten, '|');
        getline(ss, tinchiStr, '|');
        mh.tinchi = stoi(tinchiStr);

        ds.push_back(mh);
    }
    file.close();
    cout << "Da doc " << ds.size() << " mon hoc tu file.\n";
}

// Ghi dữ liệu ra file
void ghiFile(const vector<MonHoc> &ds, const string &tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi!\n";
        return;
    }

    for (const auto &mh : ds) {
        file << mh.ma << "|" << mh.ten << "|" << mh.tinchi << "\n";
    }

    file.close();
    cout << "Da luu du lieu vao file " << tenFile << ".\n";
}

// Thêm môn học
void themMonHoc(vector<MonHoc> &ds) {
    MonHoc mh;
    cout << "Nhap ma mon: ";
    getline(cin, mh.ma);
    cout << "Nhap ten mon: ";
    getline(cin, mh.ten);
    cout << "Nhap so tin chi: ";
    cin >> mh.tinchi;
    cin.ignore();

    ds.push_back(mh);
    cout << "Da them mon hoc thanh cong!\n";
}

// Hiển thị danh sách
void hienThiDanhSach(const vector<MonHoc> &ds) {
    if (ds.empty()) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << "\n===== DANH SACH MON HOC =====\n";
    for (size_t i = 0; i < ds.size(); ++i) {
        cout << i + 1 << ". Ma: " << ds[i].ma
             << " | Ten: " << ds[i].ten
             << " | Tin chi: " << ds[i].tinchi << "\n";
    }
}

// Xóa môn học theo mã
void xoaMonHoc(vector<MonHoc> &ds) {
    if (ds.empty()) {
        cout << "Danh sach rong, khong the xoa!\n";
        return;
    }

    string maXoa;
    cout << "Nhap ma mon can xoa: ";
    getline(cin, maXoa);

    bool timThay = false;
    for (auto it = ds.begin(); it != ds.end(); ++it) {
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

// Tính tổng số tín chỉ
void tinhTongTinChi(const vector<MonHoc> &ds) {
    int tong = 0;
    for (const auto &mh : ds)
        tong += mh.tinchi;

    cout << "Tong so tin chi da dang ky: " << tong << "\n";
}

// ======== Menu chính ========
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
        cin.ignore(); // loại bỏ ký tự xuống dòng còn lại

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

// ======== Hàm main ========
int main() {
    menu();
    return 0;
}