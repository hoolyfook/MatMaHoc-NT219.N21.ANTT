#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SinhVien {
    int maSV;
    char hoTen[40];
    float diemTB;
    struct SinhVien *next;
};

struct SinhVien *taoSinhVien(int maSV, char hoTen[], float diemTB) {
    struct SinhVien *sinhVien = (struct SinhVien*)malloc(sizeof(struct SinhVien));
    sinhVien->maSV = maSV;
    strcpy(sinhVien->hoTen, hoTen);
    sinhVien->diemTB = diemTB;
    sinhVien->next = NULL;
    return sinhVien;
}

void themSinhVien(struct SinhVien **pHead, struct SinhVien *sinhVienMoi) {
    if (*pHead == NULL) {
        *pHead = sinhVienMoi;
        return;
    }
    struct SinhVien *p = *pHead;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = sinhVienMoi;
}

void xuatSinhVien(struct SinhVien *sinhVien) {
    if(sinhVien) printf("%-10d %-40s %-1.2f\n", sinhVien->maSV, sinhVien->hoTen, sinhVien->diemTB);
}

void xuatDanhSach(struct SinhVien *pHead) {
        printf("%-10s %-40s %s\n", "Ma SV", "Ho Ten", "Diem TB");
        printf("------------------------------------------------\n");
    struct SinhVien *p;
    for (p = pHead; p != NULL; p = p->next) {
        xuatSinhVien(p);
    }
}

void xuatDanhSachDiemTBLonHon5(struct SinhVien *pHead) {
    printf("Danh sach sinh vien co diem TB >= 5:\n");
        printf("%-10s %-40s %s\n", "Ma SV", "Ho Ten", "Diem TB");
        printf("------------------------------------------------\n");
    struct SinhVien *p;
    for (p = pHead; p != NULL; p = p->next) {
        if (p->diemTB >= 5) {
            xuatSinhVien(p);
        }
    }
}

void xuatDanhSachDiemTBBeHon5(struct SinhVien *pHead) {
    printf("Danh sach sinh vien co diem TB < 5:\n");
        printf("%-10s %-40s %s\n", "Ma SV", "Ho Ten", "Diem TB");
        printf("------------------------------------------------\n");
    struct SinhVien *p;
    for (p = pHead; p != NULL; p = p->next) {
        if (p->diemTB < 5) {
            xuatSinhVien(p);
        }
    }
}

// Hàm sắp xếp danh sách sinh viên theo điểm trung bình tăng dần
void sapXepDiemTB(struct SinhVien *pHead) {
    if (pHead == NULL || (pHead)->next == NULL) {
        return;
    }
    struct SinhVien *p, *q, *temp;
    for (p = pHead; p != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {
            if (p->diemTB > q->diemTB) 
            {
                temp = taoSinhVien(p->maSV, p->hoTen, p->diemTB);
                p->maSV = q->maSV;
                strcpy(p->hoTen, q->hoTen);
                p->diemTB = q->diemTB;
                q->maSV = temp->maSV;
                strcpy(q->hoTen, temp->hoTen);
                q->diemTB = temp->diemTB;
            }
        }
    }
}

/*void xoaDanhSach(struct SinhVien *pHead) {
    struct SinhVien *p = pHead;
    while (p != NULL) {
        pHead = (pHead)->next;
        free(p);
        p = pHead;
    }
}*/
void xoaDanhSach(struct SinhVien** pHead)
{
   struct SinhVien* current = *pHead;
   struct SinhVien* next;
 
   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }
   *pHead = NULL;
}


int main() {
    int n, maSV;
    char hoTen[40];
    float diemTB;
    struct SinhVien *sinhVienMoi, **pHead = NULL;
    int choice = 0;
    do {
        printf("Menu:\n");
        printf("1. Tao danh sach sinh vien\n");
        printf("2. Xuat danh sach sinh vien\n");
        printf("3. Xuat danh sach sinh vien co diem TB >= 5\n");
        printf("4. Dem so sinh vien co diem TB < 5 va in danh sach nay\n");
        printf("5. Sap xep danh sach tang dan theo diem trung binh\n");
        printf("6. Xoa danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("Nhap so luong sinh vien: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) 
                {
                    printf("Nhap thong tin sinh vien thu %d:\n", i + 1);
                    printf("Ma SV: ");
                    scanf("%d", &maSV);
                    fflush(stdin);
                    printf("Ho ten: ");
                    fgets(hoTen, sizeof(hoTen), stdin);
                    hoTen[strlen(hoTen)-1] = '\0';                 
                    fflush (stdin);
                    printf("Diem TB: ");
                    scanf("%f", &diemTB);
                    sinhVienMoi = taoSinhVien(maSV, hoTen, diemTB);
                    themSinhVien(&pHead, sinhVienMoi);
                }
                break;
            case 2:
                xuatDanhSach(pHead);
                break;
            case 3:
                xuatDanhSachDiemTBLonHon5(pHead);
                break;
            case 4:
                xuatDanhSachDiemTBBeHon5(pHead);
                break;
            case 5:
                sapXepDiemTB(pHead);
                xuatDanhSach(pHead);
                break;
            case 6:
                xoaDanhSach(pHead);
                printf("Danh sach sinh vien da bi xoa!\n");
                break;
            case 7:
                printf("Chuong trinh ket thuc.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
                break;
        }
    } while (choice != 7);
    return 0;
}