#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void xuli(char c[], int dt[], int* mu_lon_nhat) {
    for (int i = 0; i < strlen(c); i++) {
        if (isdigit(c[i])) {
            int tmp = 0;
            while (c[i] != '*' && c[i] != '\0') {
                tmp = tmp * 10 + c[i] - '0';
                ++i;
            }
            i += 3;
            int mu = 0;
            while (isdigit(c[i])) {
                mu = mu * 10 + c[i] - '0'; 
                ++i;
            }
            dt[mu] += tmp;
            if (mu > (*mu_lon_nhat))
			{
				(*mu_lon_nhat) = mu;
			 } 
        }
    }
}

void NhapDaThuc(char c[], int dt[], int* mu_lon_nhat) {
	int  mu_lon_nhat_1 = 0, mu_lon_nhat_2 = 0;
	int count = 0;
    	if (mu_lon_nhat_1 > mu_lon_nhat_2){
    		*mu_lon_nhat = mu_lon_nhat_1; 
		}
		 else *mu_lon_nhat = mu_lon_nhat_2;
    fgets(c, 1000, stdin);
    c[strcspn(c, "\n")] = '\0';
    memset(dt, 0, sizeof(int) * 10001);
    xuli(c, dt, mu_lon_nhat);
    
}

void XuatDaThuc(int dt[], int mu_lon_nhat) {
	int count = 0;
    bool is_zero = true;
    
    printf("=> Da Thuc: ");

    for (int i = mu_lon_nhat; i >= 0; i--) {
        if (dt[i] != 0) {
        	if (i == 0) {
        		printf("%d", dt[i]); // Hang tu tu do
            } 
			else 
             if (dt[i] > 0) {
                    if (!is_zero) {
                        printf(" + ");
                    }
                    printf("%d*x^%d", dt[i], i);
                } else  {
                    printf(" - %d*x^%d", -dt[i], i);
                }
            }
            is_zero = false;
        }
    if (is_zero)
        printf("0");
    printf("\n");
}

void TongDaThuc(int dt1[], int dt2[], int dt_tong[], int mu_lon_nhat) {
    for (int i = 0; i <= mu_lon_nhat; i++) {
        dt_tong[i] = dt1[i] + dt2[i];
    }
}

void HieuDaThuc(int dt1[], int dt2[], int dt_hieu[], int mu_lon_nhat) {
    for (int i = 0; i <= mu_lon_nhat; i++) {
        dt_hieu[i] = dt1[i] - dt2[i];
    }
}

void TichDaThuc(int dt1[], int dt2[], int dt_tich[], int mu_lon_nhat_1, int mu_lon_nhat_2) {
    for (int i = 0; i <= mu_lon_nhat_1; i++) {
        for (int j = 0; j <= mu_lon_nhat_2; j++) {
            dt_tich[i + j] += dt1[i] * dt2[j];
        }
    }
}

void ThuongDaThuc (int dt1[], int dt2[],int dt_thuong[], int dt_du[], int mu_lon_nhat_1, int mu_lon_nhat_2){
	for (int i =  mu_lon_nhat_1 - mu_lon_nhat_2; i >= 0; i--){
		dt_thuong[i]= dt1[i+mu_lon_nhat_2] / dt2[mu_lon_nhat_2];
		for (int j = mu_lon_nhat_2; j >= 0; j--){
			dt1[i+j] -= dt_thuong[i] * dt2[j];
	}
}
		for (int i=0; i<mu_lon_nhat_1; i++)
			dt_du[i]=dt1[i];
}
int main() {
    char c1[1000], c2[1000];
    int dt1[10001], dt2[10001];
    int mu_lon_nhat = 0, mu_lon_nhat_1 = 0, mu_lon_nhat_2 = 0;


	printf("Nhap da thuc 1: ");
    NhapDaThuc(c1, dt1, &mu_lon_nhat_1);
    
    printf("Nhap da thuc 2: ");
    NhapDaThuc(c2, dt2, &mu_lon_nhat_2);
    
    printf("KET QUA:\n");
    
    // Tinh tong hai da thuc
    int dt_tong[10001];
    printf ("Tong 2 da thuc la:\t");
    TongDaThuc(dt1, dt2, dt_tong, mu_lon_nhat);
    XuatDaThuc(dt_tong, mu_lon_nhat);

    // Tinh hieu hai da thuc
    int dt_hieu[10001];
    printf ("Hieu 2 da thuc la:\t");
    HieuDaThuc(dt1, dt2, dt_hieu, mu_lon_nhat);
    XuatDaThuc(dt_hieu, mu_lon_nhat);

    // Tinh tich hai da thuc
    int dt_tich[10001];
    printf ("Tich 2 da thuc la:\t");
    TichDaThuc(dt1, dt2, dt_tich, mu_lon_nhat_1, mu_lon_nhat_2);
    XuatDaThuc(dt_tich, mu_lon_nhat_1 + mu_lon_nhat_2);

	//Tinh thuong hai da thuc
	int dt_thuong [10001], dt_du[10001];
	printf ("Thuong 2 da thuc la:\t");
	ThuongDaThuc(dt1, dt2, dt_thuong, dt_du, mu_lon_nhat_1, mu_lon_nhat_2);
   	XuatDaThuc(dt_thuong, mu_lon_nhat_1 - mu_lon_nhat_2);
   	printf ("\nPhan du:");
	XuatDaThuc(dt_du, mu_lon_nhat_1 - 1);
	
    return 0;
}

