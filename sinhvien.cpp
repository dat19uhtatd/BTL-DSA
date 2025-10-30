#include <iostream>
#include <iomanip>
#include <string>

#ifndef _SINH_VIEN_CPP_
#define _SINH_VIEN_CPP_

using namespace std;

class SinhVien {
private:
    int msv;               // Mã sinh viên
    string hoTen;          // Họ và tên
    string ngaySinh;       // Ngày sinh
    string gioiTinh;       // Giới tính
    string lop;            // Lớp

public:
    // ====== Constructor ======
    SinhVien() {
        msv = 0;
        hoTen = "";
        ngaySinh = "";
        gioiTinh = "";
        lop = "";
    }

    SinhVien(int msv, string hoTen, string ngaySinh, string gioiTinh, string lop) {
        this->msv = msv;
        this->hoTen = hoTen;
        this->ngaySinh = ngaySinh;
        this->gioiTinh = gioiTinh;
        this->lop = lop;
    }

    // ====== Getter (thêm const để có thể gọi từ đối tượng const) ======
    int _msv() const { return msv; }
    string _hoTen() const { return hoTen; }
    string _ngaySinh() const { return ngaySinh; }
    string _gioiTinh() const { return gioiTinh; }
    string _lop() const { return lop; }

    // ====== Setter ======
    void _set_msv(int m) { msv = m; }
    void _set_hoTen(const string &h) { hoTen = h; }
    void _set_ngaySinh(const string &n) { ngaySinh = n; }
    void _set_gioiTinh(const string &g) { gioiTinh = g; }
    void _set_lop(const string &l) { lop = l; }

    // ====== Toán tử nhập dữ liệu ======
    friend istream &operator>>(istream &in, SinhVien &sv) {
        cout << "Nhap ma sinh vien: ";
        in >> sv.msv;
        in.ignore();

        cout << "Nhap ho va ten: ";
        getline(in, sv.hoTen);

        cout << "Nhap ngay sinh: ";
        getline(in, sv.ngaySinh);

        cout << "Nhap gioi tinh: ";
        getline(in, sv.gioiTinh);

        cout << "Nhap lop: ";
        getline(in, sv.lop);

        return in;
    }

    // ====== Toán tử xuất dữ liệu ======
    friend ostream &operator<<(ostream &out, const SinhVien &sv) {
        out << left
            << setw(15) << sv.msv
            << setw(25) << sv.hoTen
            << setw(15) << sv.ngaySinh
            << setw(15) << sv.gioiTinh
            << setw(10) << sv.lop
            << '\n';
        return out;
    }
};

#endif
