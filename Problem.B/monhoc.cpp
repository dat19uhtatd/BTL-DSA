#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

struct MonHoc {
    char ma[20];
    char ten[100];
    int tinchi;
};

void docFile(MonHoc ds[], int &n, const char *tenFile) {
    ifstream f(tenFile);
    if (!f) {
        cout << "Khong tim thay file. Bat dau voi danh sach rong.\n";
        n = 0;
        return;
    }

    n = 0;
    while (!f.eof()) {
        MonHoc mh;
        char line[200];
        f.getline(line, 200);
        if (strlen(line) == 0) continue;

        // tách d? li?u b?ng d?u |
        char *token = strtok(line, "|");
        if (token) strcpy(mh.ma, token);
        token = strtok(NULL, "|");
        if (token) strcpy(mh.ten, token);
        token = strtok(NULL, "|");
        if (token) mh.tinchi = atoi(token);

        ds[n++] = mh;
    }

    f.close();
    cout << "Da doc " << n << " mon hoc tu file.\n";
}

void ghiFile(MonHoc ds[], int n, const char *tenFile) {
    ofstream f(tenFile);
    for (int i = 0; i < n; i++) {
        f << ds[i].ma << "|" << ds[i].ten << "|" << ds[i].tinchi << "\n";
    }
    f.close();
    cout << "Da luu du lieu vao file.\n";
}

void themMonHoc(MonHoc ds[], int &n) {
    MonHoc mh;
    cout << "Nhap ma mon: ";
    cin.getline(mh.ma, 20);
    cout << "Nhap ten mon: ";
    cin.getline(mh.ten, 100);
    cout << "Nhap so tin chi: ";
    cin >> mh.tinchi;
    cin.ignore();

    ds[n++] = mh;
    cout << "Da them mon hoc thanh cong!\n";
}

void hienThi(MonHoc ds[], int n) {
    if (n == 0) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << "\n===== DANH SACH MON HOC =====\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". Ma: " << ds[i].ma
             << " | Ten: " << ds[i].ten
             << " | Tin chi: " << ds[i].tinchi << "\n";
    }
}

void xoaMonHoc(MonHoc ds[], int &n) {
    if (n == 0) {
        cout << "Danh sach rong!\n";
        return;
    }

    char maXoa[20];
    cout << "Nhap ma mon can xoa: ";
    cin.getline(maXoa, 20);

    int vt = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].ma, maXoa) == 0) {
            vt = i;
            break;
        }
    }

    if (vt == -1) {
        cout << "Khong tim thay mon hoc co ma " << maXoa << ".\n";
        return;
    }

    for (int i = vt; i < n - 1; i++) {
        ds[i] = ds[i + 1];
    }
    n--;

    cout << "Da xoa mon hoc co ma " << maXoa << ".\n";
}

void tinhTongTinChi(MonHoc ds[], int n) {
    int tong = 0;
    for (int i = 0; i < n; i++) {
        tong += ds[i].tinchi;
    }
    cout << "Tong so tin chi da dang ky: " << tong << "\n";
}

void menu() {
    MonHoc ds[200];
    int n = 0;
    char tenFile[] = "monhoc.txt";

    docFile(ds, n, tenFile);

    int chon;
    do {
        cout << "\n===== MON HOC DA DANG KY =====\n";
        cout << "1. Them mon hoc\n";
        cout << "2. Xoa mon hoc\n";
        cout << "3. Tinh tong so tin chi\n";
        cout << "4. Hien thi danh sach mon hoc\n";
        cout << "5. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
        cin.ignore();

        switch (chon) {
            case 1: themMonHoc(ds, n); break;
            case 2: xoaMonHoc(ds, n); break;
            case 3: tinhTongTinChi(ds, n); break;
            case 4: hienThi(ds, n); break;
            case 5:
                ghiFile(ds, n, tenFile);
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 5);
}

int main() {
    menu();
    return 0;
}
