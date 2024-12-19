#include <iostream>
#include <string>

using namespace std;

struct Node {
    string ten;               
    int soTrang;              
    string loai;             
    Node* cha;                
    Node* conDau;             
    Node* anhEmKeTiep;        

    Node(string t, int s, string l) 
        : ten(t), soTrang(s), loai(l), cha(NULL), conDau(NULL), anhEmKeTiep(NULL) {}
};

Node* taoNode(const string& ten, int soTrang, const string& loai, Node* cha = NULL) {
    Node* nutMoi = new Node(ten, soTrang, loai);
    nutMoi->cha = cha;
    return nutMoi;
}

int demChuong(Node* goc) {
    int dem = 0;
    Node* hienTai = goc->conDau;
    while (hienTai != NULL) {
        if (hienTai->loai == "chapter") {
            dem++;
        }
        hienTai = hienTai->anhEmKeTiep;
    }
    return dem;
}

Node* timChuongDaiNhat(Node* goc) {
    Node* chuongDaiNhat = NULL;
    int soTrangMax = 0;
    Node* hienTai = goc->conDau;
    while (hienTai != NULL) {
        if (hienTai->loai == "chapter" && hienTai->soTrang > soTrangMax) {
            soTrangMax = hienTai->soTrang;
            chuongDaiNhat = hienTai;
        }
        hienTai = hienTai->anhEmKeTiep;
    }
    return chuongDaiNhat;
}

bool xoaNode(Node* goc, const string& ten) {
    if (goc == NULL) return false;

    Node* hienTai = goc->conDau;
    Node* truoc = NULL;

    while (hienTai != NULL) {
        if (hienTai->ten == ten) {
            goc->soTrang -= hienTai->soTrang;

            if (truoc == NULL) {
                goc->conDau = hienTai->anhEmKeTiep;
            } else {
                truoc->anhEmKeTiep = hienTai->anhEmKeTiep;
            }

            delete hienTai;
            return true;
        }

        truoc = hienTai;
        hienTai = hienTai->anhEmKeTiep;
    }

    hienTai = goc->conDau;
    while (hienTai != NULL) {
        if (xoaNode(hienTai, ten)) return true;
        hienTai = hienTai->anhEmKeTiep;
    }

    return false;
}

int main() {
    Node* sach = taoNode("A", 0, "root");

    Node* chuong1 = taoNode("Chuong 1", 30, "chapter", sach);
    Node* chuong2 = taoNode("Chuong 2", 50, "chapter", sach);

    sach->conDau = chuong1;
    chuong1->anhEmKeTiep = chuong2;

    Node* muc1 = taoNode("M?c 1.1", 10, "section", chuong1);
    Node* muc2 = taoNode("M?c 1.2", 20, "section", chuong1);

    chuong1->conDau = muc1;
    muc1->anhEmKeTiep = muc2;

    cout << "S? chuong: " << demChuong(sach) << endl;

    Node* chuongDaiNhat = timChuongDaiNhat(sach);
    if (chuongDaiNhat != NULL) {
        cout << "Chuong dài nh?t: " << chuongDaiNhat->ten << " v?i " << chuongDaiNhat->soTrang << " trang." << endl;
    }

    if (xoaNode(sach, "M?c 1.2")) {
        cout << "Ðã xóa m?c M?c 1.2." << endl;
    }

    cout << "S? chuong sau khi xóa: " << demChuong(sach) << endl;

    delete sach;
    delete chuong1;
    delete chuong2;
    delete muc1;

    return 0;
}

