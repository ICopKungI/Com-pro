#include <stdio.h>
#include <string.h>

/*
    การResetค่าเป็นการเริ่มต้นใหม่ 
    1)ลบข้อมูลในไฟล์ booking.txt ทั้งหมด (ไฟล์ว่าง)
    2)ลบข้อมูลในไฟล์ stage.txt ทั้งหมดแล้วให้ใส่ข้อมูลใหม่ว่า False (เหลือแต่คำว่า False *เหลือเพียง 1บรรทัด*)
*/

double money; //เงินหลัก
double *add_money = &money;
double start;
double more = 0; //เงิน+รวม
double less = 0; //เงิน-รวม
int order(); //รับคำสั่งรายการ
int make_order1(); //ทำรายการ
int in_money(); //+
int out_money(); //-
int times = 0;
struct plan //ตาราง
{
    double num_money;
    char note[300];
} plan[100];
int table(); //ตารางรายการ
int check(); //ตรวจสอบหมายเหตุ

// เริ่ม function
int main() // สรุปผลรวม
{
    FILE *fp_tr, *fp_r, *fp_ta, *fp_a;
    fp_tr = fopen("stage.txt","r"); //ตรวจสอบการใช้งานครั้งแรก
    fp_ta = fopen("stage.txt","a");//เขียนบันทึกการLogin
    fp_r = fopen("booking.txt", "r");
    fp_a = fopen("booking.txt", "a");
    char test[100]; //ตัวทดสอบไฟล์ว่าง
    while(fscanf(fp_tr,"%s", test) != EOF)
    {
        if (strcmp(test,"False") == 0) //รับค่าเงินครั้งแรก
        {
            fprintf(fp_ta, "True");
            printf("\n==============================\n");
            printf("      First Times Login         ");
            printf("\n==============================\n\n");
            printf("Wellcome\n");
            printf("PLS Enter Money\n");
            scanf("%lf", &money);
        }
        else//เริ่มรับค่าครั้งที่2+
        {
            while(fscanf(fp_tr,"%lf", &money) != EOF)
            {
                printf("\n==============================\n");
                printf("        Wellcome Back!          ");
                printf("\n==============================\n\n");
            }
        }
    }
    start = money;
    order();
    printf("\n==============================\n");
    printf("เงินเริ่มต้น %.2lf บาท\n", start);
    printf("เพิ่ม : +%.2lf บาท\n", more);
    printf("ลด : -%.2lf บาท\n", less);
    double ans_mol = more - less; //ส่วนต่างรับ จ่าย
    if (ans_mol >= 0)
    {
        printf("ส่วนต่าง : +%.2lf\n", ans_mol);
    }
    else if (ans_mol < 0)
    {
        printf("ส่วนต่าง : %.2lf\n", ans_mol);
    }
    printf("THX YOU\n");
    //เก็บค่า

    fprintf(fp_a, "เงินเริ่มต้น %.2lf บาท\n", start);
    if (times > 0)
    {
        for (int i = 0; i < times; i++)
        {
            fprintf(fp_a, "รายการ %d : %.2lf บาท หมายเหตุ %s\n", i+1, plan[i].num_money, plan[i].note);
        }
    }
    else {
        fprintf(fp_a, "การทำรายการ : ไม่มีประวัติการทำรายการ\n");
    }
    fprintf(fp_a, "คงเหลือ : %.2lf บาท\n", *add_money);
    fprintf(fp_ta, "\n%lf", money);
    fclose(fp_a);
    fclose(fp_r);
    fclose(fp_ta);
    fclose(fp_tr);
    return 0;
}

int order()
{
    printf("\n==============================\n");
    printf("เงิน : %.2lf บาท\n", *add_money);
    printf("Order 1 : ทำรายการ\nOrder 2 : เสร็จสิ้น\nOrder 3 : ประวัติรายการ\n");
    char order_1[2];
    printf("EnterOrder : ");
    scanf("%s", &order_1);
    if (strlen(order_1) != 1)
    {
        printf("Error\nTry Again\n");
        order();
    }
    else if (order_1[0] == '1')
    {
        printf("ทำรายการ\n");
        make_order1();
    }
    else if (order_1[0] == '2')
    {
        printf("เสร็จสิ้น\n");
        printf("\nคงเหลือ : %.2lf บาท\n", *add_money);
    }
    else if (order_1[0] == '3')
    {
        printf("ประวัติรายการ\n");
        table();
    }
    else{
        printf("Error\nTry Again\n");
        order();
    }
    return 0;
}

int make_order1(){
    printf("\n==============================\n");
    printf("เงิน : %.2lf บาท\n", *add_money);
    char order_1[2];
    printf("Order 1 : รายการ รับเงิน\nOrder 2 : รายการ จ่ายเงิน\nOrder 3 : ย้อนกลับ\nOrder 4 : เสร็จสิ้น\n");
    printf("EnterOrder : ");
    scanf("%s", &order_1);
    if (strlen(order_1) != 1)
    {
        printf("Error\nTry Again\n");
        make_order1();
    }
    else if (order_1[0] == '1')
    {
        printf("รายการ รับเงิน\n");
        in_money();
    }
    else if (order_1[0] == '2')
    {
        printf("รายการ จ่ายเงิน\n");
        out_money();
    }
    else if (order_1[0] == '3')
    {
        printf("ย้อนกลับ\n");
        order();
    }
    else if (order_1[0] == '4')
    {
        printf("เสร็จสิ้น\n");
        printf("\nคงเหลือ : %.2lf บาท\n", *add_money);
    }
    else{
        printf("Error\nTry Again\n");
        make_order1();
    }
    return 0;
}

int in_money(){
    times += 1;
    printf("\nเงิน : %.2lf บาท\n", *add_money);
    printf("Enter Money : +");
    double num; // ตัวแปรเฉพาะในนี้(เงินที่จะ+เพิ่ม)
    scanf("%lf", &num);
    money += num;
    more += num;
    printf("คงเหลือ : %.2lf บาท\n", *add_money);
    plan[times-1].num_money = num;
    check();
    make_order1();
    return 0;
}

int out_money(){
    times += 1;
    printf("\nเงิน : %.2lf บาท\n", *add_money);
    printf("Enter Money : -");
    double num; // ตัวแปรเฉพาะในนี้(เงินที่จะ-อีก)
    scanf("%lf", &num);
    money -= num;
    less += num;
    printf("คงเหลือ : %.2lf บาท\n", *add_money);
    plan[times-1].num_money = -num;
    check();
    make_order1();
    return 0;
}

int table(){
    printf("\n==============================\n");
    printf("เงินเริ่มต้น %.2lf บาท\n", start);
    if (times > 0)
    {
        for (int i = 0; i < times; i++)
        {
            printf("รายการ %d : %.2lf บาท หมายเหตุ %s\n", i+1, plan[i].num_money, plan[i].note);
        }
    }
    else {
        printf("ไม่มีประวัติการทำรายการ\n");
    }
    printf("คงเหลือ : %.2lf บาท\n", *add_money);
    printf("==============================\n");
    order();
    return 0;
}

int check(){
    printf("เพิ่มหมายเหตุ หรือไม่ : เพิ่ม(T) ไม่(F)\n");
    char check_t[2];
    scanf("%s", &check_t);
    if (strlen(check_t) != 1)
    {
        printf("Error\nTry Again\n");
        check();
    }
    else if (check_t[0] == 'T' || check_t[0] == 't')
    {
        printf("หมายเหตุ\n");
        scanf(" %[^\n]%c", &plan[times-1].note);
    }
    else if (check_t[0] == 'F' || check_t[0] == 'f')
    {
        strcpy(plan[times-1].note, "-");
    }
    return 0;
}
