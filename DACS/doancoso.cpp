#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#define eps 1e-3
#define MAX 10
#define NFM 1000
/* y tuong: tao row, trong qua trinh tao row se tao ra cac node (phan tu) */
// struct node 
typedef struct Node
{
    float data;
    Node *next;
    Node *prev;
}Node;
// struct row
typedef struct row
{
    Node *data_r;
    row *nextrow;
    row *prevrow;
}row;
// khai bao 2 bien toan cuc N va M.
int N,M;
row *table = NULL;
/* cac nguyen mau ham */ 
void draw();                                                    // tao khung gioi thieu
void devide();                                                  // phan chia ranh gioi
void check(FILE *file);											// kiem tra file co ton tai khong
Node *CreateNode(float x);										// khoi tao node
row *CreateRow(float a[], int m);								// khoi tao hang, trong cac hang se tao ra cac node 
void input(FILE *file);											// dung de doc du lieu tu file va tao row
void outputForConsole();										// xuat ra console
void addBefore(int num);										// dung de chen phan tu
void outputForConsoleAndFile(FILE *file2);						// xuat ra file va console
void CalInitialSolution(float HS[MAX][MAX],float X[],int N);	// tinh nghiem xap xi ban dau
void checkSaiSo(float HS[MAX][MAX],float X[],int N);			// kiem tra sai so ket qua
void SolvingSystemOfEquations(FILE *file3,FILE *file4,int N);	// giai hpt theo phuong phap lap don
int main()
{
	draw();
	// cau a:
	// con tro tro den file DAYSO.IN.
    FILE *file;
    file = fopen("DAYSO.IN","r");
    // kiem tra xem file da co chua, neu chua xuat ra man hinh dong chu "we cannot open this file".
    check(file);
    // doc N tu file DAYSO.in
    fscanf(file, "%d", &N);
    M=N-1;
//    printf("%d\t%d\n",N,M);
	// doc du lieu tu file vao tao row 
    input(file);
    outputForConsole();
    devide();
    // cau b:
    FILE *file2;
    file2 = fopen("RESULT1.OUT","w");
    addBefore(M);
    printf("\n\nThe table after being inserted is : \n");
	outputForConsoleAndFile(file2);
	devide();
    // cau c:
    FILE *file3,*file4;
    file3 = fopen("RESULT1.OUT","r");
    file4 = fopen("RESULT2.OUT","w");
    SolvingSystemOfEquations(file3,file4,N);
}
void draw()
{
	for(int i=0;i<=90;i++){
		switch (i)
		{
			case 0: printf("+");break;
			case 45: printf("DO AN CO SO");break;
			case 90: printf("+\n");break;
			default: printf("-");
		}
	}
	for(int i=0;i<=90;i++){
		switch (i)
		{
			case 0: printf("|");break;
			case 45: printf("DE TAI 309:");break;
			case 90: printf("|\n");break;
			default: printf(" ");
		}
	}
	printf("|                   DOC GHI FILE VA GIAI HE PHUONG TRINH BANG PHUONG PHAP LAP DON                   |\n");
	printf("|                                                                                                   |\n");
	printf("|NGUOI HUONG DAN     : TS.PHAM CONG THANG                                                           |\n");
	printf("|SINH VIEN THUC HIEN : LE DANG TRUONG DAT                                                           |\n");
	printf("|LOP                 : 18TCLC_DT3                                                                   |\n");
	printf("|                                                                                                   |\n");
	for(int i=0;i<=100;i++){
		switch (i)
		{
			case 0: printf("+");break;
			case 100: printf("+\n");break;
			default: printf("-");
		}
	}
}
void devide()
{
	for(int i=0;i<=100;i++){
    	if(i==0||i==100) printf("\n");
    	else printf("-");
	}
}
void check(FILE *file)
{
	if (file == NULL)
    {
        printf("We cannot open this file");
        exit(0);
    }
}
Node *CreateNode(float x)
{
    Node *Np = new Node;
    Np->data = x;
    Np->next = NULL;
    Np->prev = NULL;
    return Np;
}
row *CreateRow(float a[], int m) 
{
    int i = 0;
    row *Rp = new row;
    Node *Nhead = NULL;
    Node *Nlast = NULL;
    Node *Ncurrent = NULL;
    while (i < m)
    {
        Node *p = CreateNode(a[i]);
        if (Nhead == NULL)
        {
            Nhead = p; 
        }
        else
        {
            Ncurrent = Nhead;
            while (Ncurrent->next != NULL)
                Ncurrent = Ncurrent->next;
            Ncurrent->next = p;
            p->prev = Ncurrent;
        }
        i++;
    }
    Rp->data_r = Nhead;
    Rp->nextrow = NULL;
    Rp->prevrow = NULL;
    return Rp;
}
void input(FILE *file)
{
	printf("We have the following series of numbers:\n");
//    printf("%d   %d\n", N, M);
    // khai bao cac con tro thuoc danh sach lien ket hang 
    row *Rhead = NULL;
    row *Rcurrent = NULL;
    row *Rlast = NULL;    
    while (!feof(file))
    {
            float a[M];
            for (int j = 0; j < M; j++)
            {
                fscanf(file, "%f", &a[j]);
            }
            row *r = CreateRow(a, M);
            if (Rhead == NULL)
            {
                Rhead = r;
            }
            else
            {
                Rcurrent = Rhead;
                while (Rcurrent->nextrow != NULL)
                	Rcurrent = Rcurrent->nextrow;
                Rcurrent->nextrow = r;
                r->prevrow = Rcurrent;
            }
    }
    table = Rhead;
    fclose(file);
}
void outputForConsole()
{
    row *var_run1 = table;
    while (var_run1 != NULL)
    {
        Node *var_run2 = var_run1->data_r;
        while (var_run2 != NULL)
        {
            printf("%.3f\t", var_run2->data);
            var_run2 = var_run2->next;
        }
        printf("\n\n");
        var_run1 = var_run1->nextrow;
    }
}
void addBefore(int num)
{
    int position = ceil(num/2.0) -1;
    printf("Position for inserting (Previous position of M/2 position): %d \n",position);
	row *tmp1= table;
    int varInPrint= 1;
    while (tmp1 !=NULL){
        Node *tmp2 = tmp1->data_r;
       	int dem=0;
        while (tmp2 !=NULL){
            if (dem == position){
                Node *x = new Node;
                printf("\nEnter the value that you want to insert to the list %d: " , varInPrint);
                float ValueInserted;
                scanf("%f",&ValueInserted);
                x->data = ValueInserted;
                x->prev = tmp2->prev;
                x->prev->next = x;
                x->next = tmp2;
                tmp2->prev = x;
            }
            dem++;
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->nextrow;
        varInPrint++;
    }
}
void outputForConsoleAndFile(FILE *file2)
{
    row *var_run1 = table;
    while (var_run1 != NULL)
    {
        Node *var_run2 = var_run1->data_r;
        while (var_run2 != NULL)
        {
            printf("%.3f\t", var_run2->data);
            fprintf(file2,"%.3f\t",var_run2->data);
            var_run2 = var_run2->next;
        }
        printf("\n\n");
        fprintf(file2,"\n");
        var_run1 = var_run1->nextrow;
    }
    fclose(file2);
}
void CalInitialSolution(float HS[MAX][MAX],float X[],int N)
{
	for(int i=0; i<N;i++){
		X[i]= HS[i+1][N+1]/HS[i+1][i+1];
	}
	printf("\nThe approximate initial solutions of this system of equations are:\n");
	for(int i=0;i<N;i++){
		printf("%.3f\t\t",X[i]);
	}
}
void checkSaiSo(float HS[MAX][MAX],float X[],int N){
	for(int i=1;i<=N;i++){
		float s=0;
		float saiso;
		for (int j=0;j<N;j++){
			s= s + X[j]*HS[i][j+1];
		}
//		printf("\n%f\n",HS[i][N+1]);
		saiso = HS[i][N+1]-s;
		printf("\nSai So cua phuong trinh %d: %f ",i,saiso); 
	}
}
void SolvingSystemOfEquations(FILE *file3,FILE *file4,int N)
{
	float B[N];
	float X[N];
	float XNext[N];
	printf("Enter the value of Matrix B : \n");
	for (int i = 0; i < N ; i ++ ){
		printf("B%d: ",i+1);
		scanf("%f",&B[i]);
	}
	float HS[MAX][MAX];
	for (int i=1;i<=N;i++){
		for (int j=1;j<=N;j++) {
			fscanf(file3,"%f",&HS[i][j]);
		}
	}
	for(int i=1;i<=N;i++){
		HS[i][N+1] = B[i-1];
	}
	printf("\nCoefficients of the system of equations:\n");
	for (int i = 1;i<=N;i++){
		for(int j=1;j<=N+1;j++){
			printf("%.3f\t",HS[i][j]);
		}
		printf("\n");
	}
	devide();
	int number;
	char con;
	while(1){
		printf("\nDo you want to type the approximate initial solutions manually  or calculate automatically?\n");
		printf("Notice: ");
		printf("\nTyping 1 if you want to type the approximate initial solutions manually");
		printf("\nThe other numbers if you want to calculate automatically");
		printf("\nThe number you choose: ");
		scanf("%d",&number);
		switch(number){
			case 1: {
				for(int i =0 ; i<N;i++){
					printf("Typing the approximate initial solution %d:  ",i+1);
					scanf("%f",&X[i]);
				}
			break;
			}
		default: 	CalInitialSolution(HS,X,N);
		}
		devide();
		bool loop; 								// de chay vong lap
		int count=0;							// dem so vong lap
		do {
			loop=false;count++;
				// vong lap tinh x1,x2,x3,...
			for(int i=1;i<=N;i++){
				float s=0;
				for(int j=1;j<=N;j++) 
					if(j!=i) 
						s+= HS[i][j]*X[j-1];
				XNext[i-1] = HS[i][N+1] - s;
				// tinh truoc s roi moi chia cho HS[i][i];
				if(HS[i][i]!=0) XNext[i-1]=XNext[i-1]/HS[i][i];
				else exit(0);
				if(fabs(X[i-1]-XNext[i-1])>eps && count < 30) loop = true; 
				for(int i=1;i<=N;i++) X[i-1] = XNext[i-1]; 
			}
		} while(loop);
		// xuat ket qua va in file "RESULT2.OUT" 
//		printf("\ncount: %d\n",count);
		if(count<30){
			printf("\nEquation Solutions:\n");
			fprintf(file4,"Equation Solutions:\n");
			for(int i=0;i<N;i++){
				printf("%.3f\t\t",X[i]);
				fprintf(file4,"%.3f\t\t",X[i]);
			}	
			devide();
			// lay chinh xac nghiem duoc in ra;
			float Y[N];
			for (int i=0;i<N;i++){
				Y[i] = floor(X[i]*1000+0.5);
				Y[i]/= 1000;
			}
			checkSaiSo(HS,Y,N);
		}
		else {
			printf("\nWe cannot solve this system of equations");
			fprintf(file4,"We cannot solve this system of equations");
		}
//		devide();
//		// lay chinh xac nghiem duoc in ra;
//		float Y[N];
//		for (int i=0;i<N;i++){
//			Y[i] = floor(X[i]*1000+0.5);
//			Y[i]/= 1000;
//		}
//		checkSaiSo(HS,Y,N);
		devide();
		printf("\nDo you want to continue (Y/N) ?\n");
		con = getch();
		if(con!='y') break;
		devide();
	}
		fclose(file3);
		fclose(file4);
}
