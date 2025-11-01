#include <iostream>
#include "sinhvien_list.cpp"
#include <string> // Bổ sung để dùng string cho tên file

#ifndef APP_CPP
#define APP_CPP

using namespace std; // Sử dụng namespace std

class App {
    ListSinhVien a;

public:
    void run() {
        home();
        end();
    }

private:
    void home() {
        while (true) {
            system("cls");
            cout << "\t----------------------------------------------------------\n";
            cout << "\t1. Tao danh sach sinh vien moi\n";
            cout << "\t2. Them mot sinh vien moi (Nhap bang tay)\n";
            cout << "\t3. Xem danh sach sinh vien\n";
            cout << "\t4. Tim kiem sinh vien\n";
            cout << "\t5. Xoa mot sinh vien\n";
            cout << "\t6. Sap xep sinh vien\n";
            cout << "\t7. Nhap du lieu tu FILE\n"; // Tùy chọn mới
            cout << "\t8. Thoat chuong trinh\n";  // Tùy chọn thoát được chuyển xuống 8
            cout << "\t-----------------------------------------------------------\n";
            cout << "Chon thao tac: ";
            int n;
            cin >> n;

            switch (n) {
                case 1: create(); break;
                case 2: add(); break;
                case 3: show(); break;
                case 4: search(); break;
                case 5: remove(); break;
                case 6: sort(); break;
                case 7: importFile(); break; // Gọi hàm nhập file
                case 8: return;             // Thoát chương trình
                default: 
                    cout << "Lua chon khong hop le!\n";
                    system("pause");
                    break;
            }
        }
    }

    void create() {
        a.create();
    }

    void add() {
        a.create();
    }

    void show() {
        system("cls");
        a.display();
        system("pause");
    }

    void search() {
        system("cls");
        int choice;
        cout << "Tim kiem theo:\n1. Ma sinh vien\n2. Ten sinh vien\nChon: ";
        cin >> choice;
        if (choice == 1) {
            int msv;
            cout << "Nhap ma sinh vien: ";
            cin >> msv;
            auto it = a.search(msv);
            if (it != a._end()) {
                system("cls");
                cout << "Thong tin sinh vien:\n";
                cout << *it;
            } else {
                cout << "Khong tim thay sinh vien\n";
            }
        } else if (choice == 2) {
            string name;
            cin.ignore();
            cout << "Nhap ten sinh vien: ";
            getline(cin, name);
            auto results = a.searchTheoTen(name);
            if (!results.empty()) {
                for (auto it : results) {
                    cout << *it;
                }
            } else {
                cout << "Khong tim thay sinh vien\n";
            }
        }
        system("pause");
    }

    void remove() {
        system("cls");
        int msv;
        cout << "Nhap ma sinh vien muon xoa: ";
        cin >> msv;
        auto it = a.search(msv);
        if (it != a._end()) {
            a.remove(it);
            cout << "Xoa thanh cong!\n";
        } else {
            cout << "Khong tim thay sinh vien\n";
        }
        system("pause");
    }

    void sort() {
        system("cls");
        a.sort();
        system("pause");
    }
    
    // HÀM MỚI: Xử lý nhập file
    void importFile() {
        system("cls");
        string filename;
        cout << "Nhap ten file du lieu (vi du: data.txt). File phai co 5 dong du lieu cho moi sinh vien (MSV, HoTen, NgaySinh, GioiTinh, Lop):\n";
        cin.ignore(); // Đảm bảo bộ đệm sạch trước khi dùng getline
        cout << "Ten file: ";
        getline(cin, filename); 
        
        a.readFromFile(filename);
        system("pause");
    }

    void end() {
        system("cls");
        cout << "\n\n";
        cout << "=============================================================\n";
        cout << "=                                                           =\n";
        cout << "=                THANK YOU FOR USING PROGRAM                =\n";
        cout << "=                                                           =\n";
        cout << "=                     SEE YOU NEXT TIME!                    =\n";
        cout << "=                                                           =\n";
        cout << "=============================================================\n";
    }
};

#endif