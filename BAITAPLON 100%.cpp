#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct MonAn{ // Dinh nghia kieu cau truc MonAn
    char ten[50];
    float gia;
    struct MonAn *next; // Cau truc tu tru: con tro tro toi MonAn tiep theo
}MonAn;
typedef struct DonHang{ // Dinh nghia kieu cau truc DonHang
    char ten[50];
    int soLuong;
    float tongTien;
    struct DonHang *next; // Con tro den don hang tiep theo
}DonHang;
typedef struct BanAn{ // Dinh nghia kieu cau truc BanAn
    int soBan;
    DonHang *donHang; // Danh sach don hang cua ban
}BanAn;
int n=10; // Bien toan cuc chi quan co 10 ban
// Ham tao mon an moi
MonAn* taoMonAn(){
    MonAn *MonMoi=(MonAn*)malloc(sizeof(MonAn)); // Cap phat dong MonMoi
    if(MonMoi==NULL){ // Kiem tra loi bo nho
        printf("Loi cap phat bo nho!\n");
        return NULL;
    }
    printf("Nhap ten mon an: ");
    fgets(MonMoi->ten,sizeof(MonMoi->ten),stdin); // Doc ten MonMoi tu ban phim
    MonMoi->ten[strcspn(MonMoi->ten,"\n")]=0; // Thay ki tu '\n' thanh '\0'
    printf("Nhap gia mon an: ");
    while(scanf("%f",&MonMoi->gia)!=1){ // Nhap lai neu nhap ki tu khac so thuc
        printf("Gia mon an vua nhap khong phu hop dinh dang.\nVui long nhap lai: ");
        while(getchar()!='\n'); // Xoa ki tu xuong dong
    }
    while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc
    MonMoi->next=NULL;
    return MonMoi;
}
// Ham them mon moi vao thuc don
void themMonAn(MonAn **thucDon) {
    MonAn *MonMoi=taoMonAn(); // Khoi tao mon moi
    if (*thucDon==NULL) { // Kiem tra neu thuc don trong
        *thucDon=MonMoi; // Gan mon moi la mon dau tien trong thuc don
        printf("Mon an da duoc them vao thuc don.\n");
        return; // Thoat ham
    }
    MonAn *temp=*thucDon; // Khoi tao con tro chay tim thay thuc don
    while(temp->next!=NULL){ // Duyet thuc don den mon cuoi cung
        temp=temp->next;
    }
    temp->next=MonMoi; // Gan mon moi vao mon cuoi cung trong thuc don
    printf("Mon an da duoc them vao thuc don.\n");
}
// Ham xac nhan nguoi dung co muon tiep tuc thao tac
int xacNhan(){
    char yn;
    printf("Nhap 'Y' de dong y.\nNhap 'N' de huy bo.\nLua chon cua ban la: ");
    while(1){ // Lap vo han
        scanf("%c",&yn); // Nhap ki tu
        while(getchar()!='\n'); // Xoa ki tu xuong dong
        if(yn=='y' || yn=='Y') return 1; // Neu nhap y/Y thi thoat va ham tra ve 1
        else if (yn=='n' || yn=='N') return 0; // Neu nhap n/N thi thoat va ham tra ve 0
        else printf("Lua chon cua ban khong hop le.\nVui long nhap lai: ");
    }
}
// Ham tim mon an trong thuc don, tra ve so luong mon an tim duoc
int timMonAn(MonAn *thucDon,const char *a){
    int dem=0; // Khoi tao bien dem bang 0
    MonAn *temp=thucDon; // Khoi tao con tro tim thay thuc don
    while(temp!=NULL){ // Duyet thuc don den mon an cuoi cung
        if(strcmp(temp->ten, a)==0){ // Kiem tra mon an trong thuc don co giong voi mon an can tim
            dem++; // Bien tang 1
        }
        temp=temp->next; // Chuyen den mon tiep theo trong thuc don
    }
    return dem; // Tra ve gia tri bien dem va thoat ham
}
// Ham cap nhat gia mon an trong thuc don
void capNhatGiaMonAn(MonAn *thucDon,const char *tenMon){
    int dem=timMonAn(thucDon,tenMon); // Khoi tao dem la so mon an tim duoc
    if(dem==0){ // Kiem tra khong tim thay mon an can cap nhat gia
        printf("Mon an %s khong co trong thuc don.\n",tenMon);
        return; // Thoat
    }
    float giaMoi; // Khoi tao gia moi
    printf("Nhap gia moi cho mon %s: ",tenMon);
    while(scanf("%f",&giaMoi)!=1 || giaMoi<=0){ // Nhap lai gia moi neu sai dinh dang
        printf("Gia nhap khong hop le. Vui long nhap lai: ");
        while(getchar()!='\n'); // Xoa ki tu xuong dong
    }
    while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc vong lap
    printf("Xac nhan cap nhat gia %d mon %s?\n",dem,tenMon);
    if(!xacNhan()){ // Kiem tra nguoi dung co muon dung thao tac cap nhat gia
        printf("Da huy thao tac cap nhat gia.\n");
        return; // Thoat ham
    }
    MonAn *temp=thucDon; // Khoi tao con tro tim thay thuc don
    while(temp!=NULL){ // Duyet thuc don den mon an cuoi cung
        if(strcmp(temp->ten,tenMon)==0){ // Kiem tra neu la mon an can cap nhat
            temp->gia=giaMoi; // Gan gia trong thuc don bang gia moi
        }
        temp=temp->next; // Di chuyen den mon tiep theo
    }
    printf("Da cap nhat gia mon an %s thanh %.0f VND cho %d mon.\n", tenMon, giaMoi, dem);
}
// Ham xoa mon an trong thuc don
void xoaMonAn(MonAn **thucDon,const char *a) {
    MonAn *temp=*thucDon; // Khoi tao con tro tim thay thuc don
    MonAn *truoc=NULL; //Khoi tao con tro truoc thay mon truoc mon bi xoa
    int dem=timMonAn(*thucDon,a); // Tao dem bang so luong mon can xoa tim duoc
	if(dem==0){ // Kiem tra neu khong tim duoc mon can xoa
		printf("Mon an %s khong co trong thuc don.\n",a);
		return; // Thoat ham
	}
	printf("Xac nhan xoa %d mon an %s trong thuc don?\n",dem,a);
	if(!xacNhan()){// Kiem co muon dung thao tac xoa mon
		printf("Da xac nhan huy thao tac xoa.\n");
		return;	// Thoat ham							
	}
    while(temp!=NULL){  // Duyet thuc don den mon an cuoi cung
        if(strcmp(temp->ten,a)==0){ // Kiem tra neu la mon can xoa 
            MonAn *diaChi=temp;//Khoi tao con tro luu dia chi mon can xoa
            if(truoc==NULL){ // Kiem tra neu mon can xoa la mon dau thuc don
                *thucDon=temp->next;//Gan thuc don bat dau tu mon ke tiep 
            }else{
                truoc->next=temp->next;//Duyet thuc don bo qua mon bi xoa 
            }
            free(diaChi); // Giai phong dia chi mon bi xoa
// Kiem tra neu xoa mon dau thi temp thanh mon dau danh sach, nguoc lai thi tiep tuc
            temp=(truoc==NULL) ? *thucDon : truoc->next;
            continue; // Neu co mon bi xoa thi bat dau lai vong lap  
        }
        truoc=temp; // Cap nhat lai con tro truoc
        temp=temp->next; // Di chuyen den mon tiep theo
    }
    printf("Da xoa tat ca mon %s khoi thuc don.\n",a);
}
// Ham duyet cac mon an trong thuc don
void duyetThucDon(MonAn *thucDon){
	if(thucDon==NULL){ // Kiem tra neu thuc don trong
		printf("Thuc don trong. Vui long them mon an vao thuc don!\n");
		return; // Thoat ham
	}
	printf("\n<=================== THUC DON ====================>\n");
	printf("------------------~~~o~oOo~o~~~--------------------\n");
	printf("|STT| Ten mon an                     | Gia        |\n");
	printf("---------------------------------------------------\n");
	MonAn *temp=thucDon; // Khoi tao con tro tim thay thuc don
	int i=1; // Khoi tao bien i la so thu tu mon an trong thuc don
	while(temp!=NULL){
		printf("|%-3d| %-30s | %-10.0f |\n",i,temp->ten,temp->gia);
		temp= temp->next; // Di chuyen den mon tiep theo
		i++; // Tang i
	}
	printf("---------------------------------------------------\n");
}
// Ham tao danh sach ban an
BanAn* taoBanAn(){	
    BanAn *danhSach=(BanAn*)malloc(n*sizeof(BanAn)); // Cap phat bo nho 
    if(!danhSach){ // Kiem tra neu cap phat that bai
        printf("\nKhong the cap phat bo nho cho danh sach ban\n");
        return NULL; // Tra ve NULL neu khong cap phat duoc
    }
    for(int i=0;i<n;i++) { // Khoi tao thong tin cho tung ban
        danhSach[i].soBan=i+1; // Danh so ban tu 1 den n
        danhSach[i].donHang=NULL; // Chua co don hang nao
    }
    return danhSach; // Tra ve con tro toi mang ban an 
}
// Ham dat mon an cho mot ban
int DatMonAn(BanAn **danhSachBan,MonAn *thucDon){ 
    if(thucDon==NULL){ // Kiem tra neu thuc don trong thi khong dat mon
		printf("Thuc don trong. Vui long them mon an vao thuc don!\n");
		return 0; // Khong the dat mon 
	}
	int soBan;
    printf("Nhap so ban muon dat trong pham vi tu 1-%d ban: ",n);
    // Nhap va kiem tra dau vao cho so ban
    while(scanf("%d",&soBan)!=1 || soBan<=0 || soBan>n){
		printf("So ban vua nhap khong phu hop dinh dang.\nVui long nhap lai: ");
		while(getchar()!='\n'); // Xoa ki tu xuong dong 
	}
	while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc
    BanAn *ban=danhSachBan[soBan-1]; // Lay con tro den ban duoc chon 
    char tenMon[50];
    int soLuong;
    MonAn *mon; 
    do{ // Vong lap de nhap ten mon co trong thuc don
        printf("Nhap ten mon an: "); 
        fgets(tenMon,sizeof(tenMon),stdin); // Nhap chuoi co khoang trang
        tenMon[strcspn(tenMon,"\n")]=0; // Xoa ki tu newline cuoi chuoi 
        mon=thucDon; // Tim mon an trong thuc don theo ten
        while(mon && strcmp(mon->ten,tenMon)!=0){
            mon=mon->next; // Duyet tiep neu ten khong khop
        }
        if(!mon){
            printf("Mon an khong ton tai trong thuc don. Moi nhap lai\n");
        }
    }while(!mon); // Lap lai neu mon an khong tim thay
    printf("Nhap so luong: ");// Nhap so luong mon
    while(scanf("%d",&soLuong)!=1 || soLuong<=0){
		printf("So luong vua nhap khong phu hop dinh dang.\nVui long nhap lai: ");
		while(getchar()!='\n'); // Xoa ki tu xuong dong
	}
	while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc 
    DonHang *don=(DonHang*)malloc(sizeof(DonHang)); // Cap phat bo nho
    if(!don){
        printf("Khong the cap phat bo nho cho don hang\n");
        return 0;
    }
    // Gan thong tin cho don hang
    strcpy(don->ten,tenMon); // Sao chep ten mon vao don hang
    don->soLuong=soLuong; // Gan so luong
    don->tongTien=mon->gia*soLuong; // Tinh tong tien = gia * so luong
    don->next=NULL; // Don hang moi nam cuoi, nen tro next = NULL
    if(!ban->donHang){ // Them don hang vao cuoi danh sach don hang cua ban
        ban->donHang=don; // Neu ban chua co don hang nao
    }
	else{ // Them don hang vao cuoi danh sach don hang cua ban
        DonHang *TongDuyet=ban->donHang;
        while(TongDuyet->next){
            TongDuyet=TongDuyet->next; // Duyet toi cuoi danh sach
        }
        TongDuyet->next=don; // Gan don hang moi vao cuoi danh sach
    }
    printf("Dat thanh cong %d %s cho ban %d\n",soLuong,tenMon,soBan);
    return 1; // Tra ve 1 de bao dat mon thanh cong
}
// Ham tinh tong tien cac mon an dat cua mot ban an
float tinhTongTien(BanAn *ban) {
    if(!ban){ // Kiem tra neu con tro ban la NULL
        printf("\nBan nay khong ton tai");
        return 0; // Tra ve 0 neu ban khong hop le
    }
    if(!ban->donHang){ // Kiem tra neu ban chua dat mon nao
        printf("\nBan %d chua dat mon nao",ban->soBan);
        return 0; // Tra ve 0 neu khong co don hang
    }
    float tongTien=0;
    DonHang *TongDuyet=ban->donHang; // Con tro duyet danh sach don hang cua ban
    while(TongDuyet){ // Duyet qua danh sach don hang va tinh tong tien
        tongTien+=TongDuyet->tongTien; // Cong tong don hang vao tong  
        TongDuyet=TongDuyet->next; // Chuyen sang don hang tiep theo
    }
    return tongTien; // Tra ve tong tien tat ca cac don hang cua ban
}
// Ham in hoa don cho mot ban an
void inHoaDon(BanAn *ban){    
    if(!ban){ // Kiem tra neu con tro ban la NULL
        printf("\nBan nay khong ton tai");
        return; // Khong in hoa don neu ban khong hop le
    }	
    if(!ban->donHang) { // Kiem tra neu ban chua goi mon nao
        printf("\nBan %d chua dat mon nao",ban->soBan);
        return; // Khong in hoa don neu khong co don hang
    }
    printf("\n                    HOA DON CUA BAN %d                   \n",ban->soBan);
    printf("-----------------------~~~o~oOo~o~~~---------------------\n");
    printf("%-30s | %-10s | %-10s|\n","Ten Mon","So Luong","Thanh Tien");
    printf("---------------------------------------------------------\n");
    // Duyet danh sach don hang va in tung mon
    DonHang *TongDuyet=ban->donHang;
    while(TongDuyet){
        printf("%-30s | %-10d | %-10.0f|\n",TongDuyet->ten,TongDuyet->soLuong,TongDuyet->tongTien);
        TongDuyet=TongDuyet->next; // Chuyen den don hang tiep theo
    } 
    printf("---------------------------------------------------------\n");    
    float tong=tinhTongTien(ban); // Tinh va in tong tien
    printf("\nTong so tien can thanh toan la: %.0f VND\n",tong);
}
// Ham xoa mot mon an khoi don hang cua mot ban co the
void xoaDonHang(BanAn **danhSachBan,int n) {
    int soBan;
    printf("\nNhap so ban muon xoa don hang trong pham vi tu 1-%d ban: ",n); // Nhap va kiem tra so ban
    while(scanf("%d",&soBan)!=1 || soBan<=0 || soBan>n){
		printf("So ban vua nhap khong phu hop dinh dang.\nVui long nhap lai: ");
		while(getchar()!='\n'); // Xoa ki tu xuong dong
	}
	while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc 
    BanAn *ban=danhSachBan[soBan-1]; // Lay con tro den ban can xoa don    
    if(!ban->donHang){ // Kiem tra xem ban co don hang nao khong
        printf("Ban %d chua co don hang nao\n",soBan);
        return; // Neu khong co don hang thi thoat ham
    }
    char tenMon[50];
    printf("Nhap ten mon an muon xoa: "); // Nhap ten mon an can xoa 
    fgets(tenMon,sizeof(tenMon),stdin);
    tenMon[strcspn(tenMon, "\n")]=0; // Xoa ky tu newline cuoi chuoi
    printf("Xac nhan xoa mon %s khoi don hang ban so %d?\n", tenMon, soBan); // Xac nhan truoc khi xoa
    if (!xacNhan()) { // Gia dinh ban co ham xacNhan() tra ve 1 neu dong y 
        printf("Da huy thao tac xoa mon an.\n");
        return; // Neu khong dong y thi thoat ham
    }
    // Khoi tao con tro de duyet danh sach don hang
    DonHang *truoc=NULL;
    DonHang *hienTai=ban->donHang;
    while(hienTai){ // Tim mon an can xoa trong danh sach
        if(strcmp(hienTai->ten,tenMon)==0){
            if(truoc==NULL){ // Neu la phan tu dau danh sach
                ban->donHang=hienTai->next; // Cap nhat con tro dau danh sach
            } 
			else{
                truoc->next=hienTai->next; // Bo qua phan tu hien tai trong danh sach
            }
            free(hienTai); // Giai phong bo nho cho don hang bi xoa
            printf("Da xoa mon %s khoi don hang cua ban %d\n",tenMon,soBan);
            return; // Ket thuc ham sau khi xoa
        }
        truoc=hienTai; // Luu lai nut truoc do
        hienTai=hienTai->next; // Di chuyen den nut tiep theo
    }
    printf("Khong tim thay mon %s trong don hang cua ban %d\n",tenMon,soBan); // Neu khong tim thay mon an
}
// Ham menu lua chon
int menu() {
    int luaChon; 
    printf("\n----------------------------------------------------------\n");
    printf("CAP NHAT THUC DON:\n");
    printf("	[1]. Them mon an vao thuc don.\n");
    printf("	[2]. Cap nhat gia mon an trong thuc don.\n");
    printf("	[3]. Xoa mon an khoi thuc don.\n");
    printf("	[4]. Hien thi danh sach mon an trong thuc don.\n");
    printf("DAT MON CHO BAN AN:\n");
    printf("	[5]. Nhap don hang.\n");
    printf("	[6]. Xoa don hang.\n");
    printf("	[7]. In hoa don.\n");
    printf("[0]. THOAT CHUONG TRINH.\n");
    printf("----------------------------------------------------------\n");
    printf("Vui long nhap lua chon: ");
    while(scanf("%d",&luaChon)!=1){
		printf("So ban vua nhap khong phu hop dinh dang.\nVui long nhap lai: ");
		while(getchar()!='\n'); // Xoa ki tu xuong dong 
	}
	while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc  
    return luaChon; 
}
// Ham giai phong thuc don 
void giaiPhongThucDon(MonAn **thucDon){
    if(!thucDon || !(*thucDon)) return;//Kiem tra thuc don rong thi thoat
    MonAn *temp; // Khoi tao con tro tim 
    while(*thucDon){ // Lap den khi thuc don trong
        temp=*thucDon; // Gan con tro tim thay thuc don
        *thucDon=(*thucDon)->next; // Di chuyen den mon tiep theo
        free(temp); // Giai phong con tro tim 
    }
}
// Ham giai phong toan bo danh sach don hang (DonHang) cua mot ban
void giaiPhongDonHang(DonHang **donHang){
    if(!donHang || !(*donHang)) return; // Neu con tro NULL hoac danh sach rong thi thoat
    DonHang *temp;
    while(*donHang){    // Duyet tung nut trong danh sach va giai phong
        temp=*donHang; // Luu dia chi nut hien tai
        *donHang=(*donHang)->next; // Di chuyen sang nut tiep theo
        free(temp); // Giai phong nut hien tai
    }
}
// Ham giai phong toan bo danh sach ban an va cac don hang tuong ung
void giaiPhongDanhSachBan(BanAn **danhSachBan, int n){
    if (!danhSachBan) return; // Neu danh sach khong ton tai thi thoat
    for (int i=0;i<n;i++){ // Duyet qua tung ban an trong mang
        if (danhSachBan[i]){ // Giai phong danh sach don hang cua ban
            giaiPhongDonHang(&(danhSachBan[i]->donHang));
            free(danhSachBan[i]); // Giai phong vung nho cua ban an
        }
    }
    free(danhSachBan); // Giai phong mang chua con tro den cac ban
}
int main() {
    int luaChon;
    MonAn *thucDon=NULL; // Khoi tao con tro thuc don rong 
    BanAn **danhSachBan=NULL; // Khoi tao mang con tro danh sach ban an
    // Cap phat bo nho cho mang con tro danh sach ban an (gom n ban)
    danhSachBan=(BanAn**)malloc(n*sizeof(BanAn*));
    if(!danhSachBan){
        printf("\nLoi cap phat bo nho cho danh sach ban\n");
        return 1; // Thoat chuong trinh neu cap phat that bai
    }
    BanAn *banKhoiTao=taoBanAn(); //Khoi tao ban an dung con tro don
    // Cap phat bo nho tung ban va gan so ban, khoi tao don hang = NULL
    for(int i=0;i<n;i++) {
        danhSachBan[i] = (BanAn*)malloc(sizeof(BanAn)); // Cap phat bo nho cho tung ban
        danhSachBan[i]->soBan = i + 1; // Gan so ban tu 1 den n
        danhSachBan[i]->donHang = NULL;//Khoi tao danh sach don hang rong
    }
    do{
        luaChon=menu(); // Goi ham menu va nhan lua chon 
        DonHang *don=NULL; // Khoi tao con tro don hang  
        switch(luaChon){
            case 1: // Lua chon 1 
                int soLuongMon;
                printf("Nhap so luong mon an can them: ");
                // Nhap lai neu nhap so luong mon an sai dinh dang
                while(scanf("%d",&soLuongMon)!=1 || soLuongMon<=0){
                    printf("So luong mon an ban nhap khong dung dinh dang.\nVui long nhap lai: ");
                    while(getchar()!='\n'); // Xoa ki tu xuong dong
                }
                while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc vong lap
                for(int i=0;i<soLuongMon;i++){
                    themMonAn(&thucDon); // Goi ham them mon an vao thuc don
                }
                break;
            case 2: // Lua chon 2
                if (thucDon==NULL) { // Kiem tra neu thuc don trong
                    printf("Thuc don trong, khong co mon an de cap nhat!\n");
                    break; // Dung case 2
                }
                int n2;
                printf("Nhap so luong mon an can cap nhat gia: ");
                // Nhap lai neu nhap so luong mon an sai dinh dang
                while(scanf("%d",&n2)!= 1 || n2<=0){
                    printf("So luong khong hop le.Vui long nhap lai: ");
                    while(getchar()!='\n'); // Xoa ki tu xuong dong
                }
                while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc vong lap
                {   // Cap phat dong mang con tro ten mon an
                    char **a2=(char**)malloc(n2*sizeof(char*));    
                    printf("Nhap ten cac mon an can cap nhat gia:\n");
                    for (int i=0;i<n2;i++) {
                        a2[i]=(char*)malloc(30*sizeof(char));
                        printf("Mon so %d: ",i+1);
                        fgets(a2[i],50,stdin);
                        a2[i][strcspn(a2[i],"\n")]= 0; // Xoa ki tu xuong dong
                        capNhatGiaMonAn(thucDon,a2[i]); // Cap nhat gia mon an
                        free(a2[i]); // Giai phong con tro ten mon an
                    }
                    free(a2); // Giai phong mang con tro ten mon an
                }
                break;
            case 3: // Lua chon 3
                if(thucDon==NULL){ // Kiem tra thuc don rong
                    printf("Thuc don trong, khong co mon an de xoa!\n");
                    break; // Dung case 3
                }
                    int n3;
                    printf("Nhap so luong mon an can xoa: ");
                    // Nhap lai neu nhap so luong mon an sai dinh dang
                    while(scanf("%d", &n3)!=1 || n3<=0){
                        printf("So luong mon an can xoa vua nhap khong dung dinh dang.\nVui long nhap lai: ");
                        while(getchar()!='\n'); // Xoa ki tu xuong dong
                    }
                    while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc lap
                    { // Cap phat dong mang con tro ten mon an can xoa
                    char **a3=(char**)malloc(n3*sizeof(char*));
                    printf("Nhap ten cac mon an can xoa:\n");
                    for(int i=0;i<n3;i++){
                        a3[i]=(char*)malloc(30 * sizeof(char));
                        printf("Mon so %d: ",i+1);
                        fgets(a3[i],50,stdin);
                        a3[i][strcspn(a3[i],"\n")]=0; // Xoa ki tu xuong dong 
                        xoaMonAn(&thucDon,a3[i]); // Goi ham xoa mon an
                        free(a3[i]); // Giai phong con tro ten mon an
                    }
                    free(a3); // Giai phong mang con tro ten mon an
                }
                break; // Dung case 3
            case 4: // Lua chon 4
                duyetThucDon(thucDon); // Duyet va in thuc don
                break;
            case 5: // Lua chon 5
                DatMonAn(danhSachBan,thucDon); // Dat mon an cho ban
                break;
            case 6: // Lua chon 6
                xoaDonHang(danhSachBan,n); // Xoa mon an khoi don hang da dat
                break;
            case 7: // Lua chon 7
                // In hoa don cho ban cu the
                int soBan; 
                printf("\nNhap so ban can in hoa don: ");
                // Kiem tra dinh dang va gioi han so ban
                while(scanf("%d",&soBan)!=1 || soBan<=0 || soBan>n){
                    printf("So ban vua nhap khong phu hop dinh dang.\nVui long nhap lai: ");
                    while(getchar()!='\n'); // Xoa ki tu xuong dong
                }
                while(getchar()!='\n'); // Xoa ki tu xuong dong khi ket thuc lap
                inHoaDon(danhSachBan[soBan-1]); // Goi ham in hoa don cho ban da chon
                break;
            case 0: // Lua chon 0
                // Thoat chuong trinh, giai phong bo nho
                giaiPhongThucDon(&thucDon); // Giai phong danh sach thuc don
                free(banKhoiTao); // Giai phong con tro ban khoi tao
                giaiPhongDanhSachBan(danhSachBan, n); // Giai phong danh sach cac ban an
                printf("Thoat chuong trinh thanh cong\n"); // Thong bao thoat
                break;
            default: // Xu ly lua chon khong hop le
                printf("Lua chon khong hop le.Vui long nhap lai\n");
        }
    } while(luaChon!=0); // Lap lai cho den khi nguoi dung chon 0
    return 0; // Ket thuc chuong trinh
}


