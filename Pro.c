#include <stdio.h>
#include <string.h>

float money; //เงินหลัก
float *add_money = &money;
float start;
float more = 0; //เงิน+รวม
float less = 0; //เงิน-รวม
int order(); //รับคำสั่งรายการ
int make_order1(); //ทำรายการ
int in_money(); //+
int out_money(); //-
int times = 0;
struct plan //ตาราง
{
    float num_money;
    char note[300];
} plan[100];
int table(); //ตารางรายการ
int check(); //ตรวจสอบหมายเหตุ

// เริ่ม function
int main() // สรุปผลรวม
{
    printf("Wellcome\n");
    printf("PLS Enter Money\n");
    scanf("%f", &money);
    start = money;
    order();
    printf("เงินเริ่มต้น %.2f บาท\n", start);
    printf("เพิ่ม : +%.2f บาท\n", more);
    printf("ลด : -%.2f บาท\n", less);
    float ans_mol = more - less; //ส่วนต่างรับ จ่าย
    if (ans_mol >= 0)
    {
        printf("ส่วนต่าง : +%.2f\n", ans_mol);
    }
    else if (ans_mol < 0)
    {
        printf("ส่วนต่าง : %.2f\n", ans_mol);
    }
    printf("THX YOU\n");
    return 0;
}

int order()
{
    printf("\nเงิน : %.2f บาท\n", *add_money);
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
        printf("\nคงเหลือ : %.2f บาท\n", *add_money);
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
    printf("\nเงิน : %.2f บาท\n", *add_money);
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
        printf("\nคงเหลือ : %.2f บาท\n", *add_money);
    }
    else{
        printf("Error\nTry Again\n");
        make_order1();
    }
    return 0;
}

int in_money(){
    times += 1;
    printf("\nเงิน : %.2f บาท\n", *add_money);
    printf("Enter Money : +");
    float num; // ตัวแปรเฉพาะในนี้(เงินที่จะ+เพิ่ม)
    scanf("%f", &num);
    money += num;
    more += num;
    printf("คงเหลือ : %.2f บาท\n", *add_money);
    plan[times-1].num_money = num;
    check();
    make_order1();
    return 0;
}

int out_money(){
    times += 1;
    printf("\nเงิน : %.2f บาท\n", *add_money);
    printf("Enter Money : -");
    float num; // ตัวแปรเฉพาะในนี้(เงินที่จะ-อีก)
    scanf("%f", &num);
    money -= num;
    less += num;
    printf("คงเหลือ : %.2f บาท\n", *add_money);
    plan[times-1].num_money = -num;
    check();
    make_order1();
    return 0;
}

int table(){
    printf("\nเงินเริ่มต้น %.2f บาท\n", start);
    if (times > 0)
    {
        for (int i = 0; i < times; i++)
        {
            printf("รายการ %d : %.2f บาท หมายเหตุ %s\n", i+1, plan[i].num_money, plan[i].note);
        }
    }
    else {
        printf("ไม่มีประวัติการทำรายการ\n");
    }
    printf("คงเหลือ : %.2f บาท\n", *add_money);
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