#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MonHoc {
    char ma[10];
    char ten[50];
    int tinchi;
};

struct Vector {
    struct MonHoc *data;
    int size;
    int capacity;
};

void khoiTaoVector(struct Vector *v) {
    v->size = 0;
    v->capacity = 2;
    v->data = (struct MonHoc *)malloc(v->capacity * sizeof(struct MonHoc));
}

void giaiPhongVector(struct Vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void moRongVector(struct Vector *v) {
    v->capacity *= 2;
    v->data = (struct MonHoc *)realloc(v->data, v->capacity * sizeof(struct MonHoc));
}

void themMonHoc(struct Vector *v) {
    if (v->size >= v->capacity)
        moRongVector(v);

    struct MonHoc mh;
    printf("Nhap ma mon: ");
    fgets(mh.ma, sizeof(mh.ma), stdin);
    mh.ma[strcspn(mh.ma, "\n")] = '\0';

    printf("Nhap ten mon: ");
    fgets(mh.ten, sizeof(mh.ten), stdin);
    mh.ten[strcspn(mh.ten, "\n")] = '\0';

    printf("Nhap so tin chi: ");
    scanf("%d", &mh.tinchi);
    getchar();

    v->data[v->size++] = mh;
    printf("Da them mon hoc!\n");
}

void hienThiDanhSach(struct Vector v) {
    if (v.size == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("===== DANH SACH MON HOC =====\n");
    for (int i = 0; i < v.size; i++) {
        printf("%-3d Ma: %-8s | Ten: %-25s | Tin chi: %d\n",
               i + 1, v.data[i].ma, v.data[i].ten, v.data[i].tinchi);
    }
}

void tinhTongTinChi(struct Vector v) {
    int tong = 0;
    for (int i = 0; i < v.size; i++)
        tong += v.data[i].tinchi;
    printf("Tong so tin chi da dang ky: %d\n", tong);
}

void xoaMonHoc(struct Vector *v) {
    if (v->size == 0) {
        printf("Danh sach rong, khong the xoa!\n");
        return;
    }

    char maXoa[10];
    printf("Nhap ma mon can xoa: ");
    fgets(maXoa, sizeof(maXoa), stdin);
    maXoa[strcspn(maXoa, "\n")] = '\0';

    int timThay = 0;
    for (int i = 0; i < v->size; i++) {
        if (strcmp(v->data[i].ma, maXoa) == 0) {
            for (int j = i; j < v->size - 1; j++)
                v->data[j] = v->data[j + 1];
            v->size--;
            timThay = 1;
            break;
        }
    }

    if (timThay)
        printf("Da xoa mon hoc co ma %s.\n", maXoa);
    else
        printf("Khong tim thay ma mon can xoa.\n");
}

// ===== Doc va ghi file =====
void ghiFile(struct Vector v) {
    FILE *f = fopen("monhoc.txt", "w");
    if (f == NULL) {
        printf("Khong the mo file de ghi!\n");
        return;
    }

    for (int i = 0; i < v.size; i++) {
        fprintf(f, "%s|%s|%d\n", v.data[i].ma, v.data[i].ten, v.data[i].tinchi);
    }

    fclose(f);
}

void docFile(struct Vector *v) {
    FILE *f = fopen("monhoc.txt", "r");
    if (f == NULL) return; // file chua ton tai

    struct MonHoc mh;
    char line[200];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, "|");
        if (!token) continue;
        strcpy(mh.ma, token);

        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(mh.ten, token);

        token = strtok(NULL, "|");
        if (!token) continue;
        mh.tinchi = atoi(token);

        if (v->size >= v->capacity)
            moRongVector(v);

        v->data[v->size++] = mh;
    }
    fclose(f);
}

// ===== Menu =====
void menu() {
    struct Vector ds;
    khoiTaoVector(&ds);
    docFile(&ds); // tu dong doc du lieu neu co

    int chon;
    do {
        printf("\n==== MON HOC DA DANG KY ====\n");
        printf("1. Them mon hoc\n");
        printf("2. Xoa mon hoc\n");
        printf("3. Tinh tong so tin chi\n");
        printf("4. Hien thi danh sach mon hoc\n");
        printf("5. Thoat va luu file\n");
        printf("Chon: ");
        scanf("%d", &chon);
        getchar();

        switch (chon) {
            case 1:
                themMonHoc(&ds);
                break;
            case 2:
                xoaMonHoc(&ds);
                break;
            case 3:
                tinhTongTinChi(ds);
                break;
            case 4:
                hienThiDanhSach(ds);
                break;
            case 5:
                ghiFile(ds);
                printf("Da luu du lieu vao file monhoc.txt.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (chon != 5);

    giaiPhongVector(&ds);
}

int main() {
    menu();
    return 0;
}

