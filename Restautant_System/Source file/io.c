#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"
#include "ui.h"
#include "io.h"

//载入用户信息
void Load_users_data(struct User *(*users_head), int* cnt)
{
    FILE* fp = fopen("User_data.txt", "rb");
    (*cnt) = 0;
    if(fp== NULL)
    {
        printf("Cannot open \"User_data.txt\"\n");
        exit(1);
    }
    struct User temp;
    (*users_head) = (struct User*)malloc(sizeof(struct User));
    struct User* users_tail = (*users_head);
    users_tail -> next = NULL;
    struct User* p = (struct User*)malloc(sizeof(struct User));
    while(!feof(fp))
    {
        fscanf(fp, "%d%s%s%lf",&temp.id, temp.username, temp.password, &temp.Performance_amount);
        p -> id = temp.id;
        strcpy(p -> username, temp.username);
        strcpy(p -> password, temp.password);
        p -> Performance_amount = temp.Performance_amount;
        users_tail -> next = p;
        users_tail = p;
        (*cnt)++;
        p = (struct User*)malloc(sizeof(struct User));
    }
    users_tail -> next = NULL;
    if(p == NULL)
    {
        free(p);
    }
    fclose(fp);
}

//载入菜品信息
void Load_foods_data(struct Food *(*foods_head), int* cnt)
{
    FILE* fp = fopen("Food_data.txt", "rb");
    (*cnt) = 0;
    if(fp == NULL)
    {
        printf("Cannot open \"Food_data.txt\"\n");
        exit(1);
    }
    struct Food temp;
    (*foods_head) = (struct Food*)malloc(sizeof(struct Food));
    struct Food* foods_tail = (*foods_head);
    foods_tail -> next = NULL;
    struct Food* p = (struct Food*)malloc(sizeof(struct Food));
    while(!feof(fp))
    {
        fscanf(fp, "%d%s%lf%d",&temp.id, temp.name, &temp.price, &temp.cnt);
        p -> id = temp.id;
        strcpy(p -> name, temp.name);
        p -> price = temp.price;
        p -> cnt = temp.cnt;
        foods_tail -> next = p;
        foods_tail = p;
        (*cnt)++;
        p = (struct Food*)malloc(sizeof(struct Food));
    }
    foods_tail -> next = NULL;
    if(p == NULL)
    {
        free(p);
    }
    fclose(fp);
}

//载入座位信息
void Load_seats_data(struct Seat *(*seats_head), int* cnt)
{
    FILE* fp = fopen("Seat_data.txt", "rb");
    (*cnt) = 0;
    if(fp== NULL)
    {
        printf("Cannot open \"Seat_data.txt\"\n");
        exit(1);
    }
    struct Seat temp;
    (*seats_head) = (struct Seat*)malloc(sizeof(struct Seat));
    struct Seat* seats_tail = (*seats_head);
    seats_tail -> next = NULL;
    struct Seat* p = (struct Seat*)malloc(sizeof(struct Seat));
    while(!feof(fp))
    {
        fscanf(fp, "%d%d%d",&temp.flag, &temp.book, &temp.num);
        p -> flag = temp.flag;
        p -> book = temp.book;
        p -> num = temp.num;
        seats_tail -> next = p;
        seats_tail = p;
        (*cnt)++;
        p = (struct Seat*)malloc(sizeof(struct Seat));
    }
    seats_tail -> next = NULL;
    if(p == NULL)
    {
        free(p);
    }
    fclose(fp);
}

//载入顾客信息
void Load_customers_data(struct Customer*(*customers_head), int* cnt)
{
    FILE* fp = fopen("Customer_data.txt", "rb");
    (*cnt) = 0;
    if(fp== NULL)
    {
        printf("Cannot open \"Customer_data.txt\"\n");
        exit(1);
    }
    struct Customer temp;
    (*customers_head) = (struct Customer*)malloc(sizeof(struct Customer));
    struct Customer* customers_tail = (*customers_head);
    customers_tail -> next = NULL;
    struct Customer* p = (struct Customer*)malloc(sizeof(struct Customer));
    while(!feof(fp))
    {
        fscanf(fp, "%d %d",&temp.Seat_book, &temp.Order_id);
        p -> Seat_book = temp.Seat_book;
        p -> Order_id = temp.Order_id;
        customers_tail -> next = p;
        customers_tail = p;
        (*cnt)++;
        p = (struct Customer*)malloc(sizeof(struct Customer));
    }
    customers_tail -> next = NULL;
    if(p == NULL)
    {
        free(p);
    }
    fclose(fp);
}

//载入订单信息
void Load_orders_data(struct Order*(*orders_head))
{
    FILE* fp = fopen("Order_data.txt", "rb");
    if(fp == NULL)
    {
        printf("Cannot open \"Order_data.txt\"\n");
        exit(1);
    }
    struct Order temp;
    (*orders_head) = (struct Order*)malloc(sizeof(struct Order));
    struct Order* orders_tail = (*orders_head);
    orders_tail -> next = NULL;
    struct Order* p = (struct Order*)malloc(sizeof(struct Order));
    while(!feof(fp))
    {
        fscanf(fp, "%d",&temp.orderid);
        p -> orderid = temp.orderid;

        int i = 0;
        do {
            i++;
            fscanf(fp, "%d", &temp.food[i]);
            p -> food[i] = temp.food[i];
        }while(temp.food[i] != -1);

        fscanf(fp, "%lf", &temp.Totalexpenses);
        p -> Totalexpenses = temp.Totalexpenses;

        orders_tail -> next = p;
        orders_tail = p;
        p = (struct Order*)malloc(sizeof(struct Order));
    }
    orders_tail -> next = NULL;
    if(p == NULL)
    {
        free(p);
    }
    fclose(fp);
}

//载入管理员密码
void Load_admin_data(char *(*admin_password))
{
    FILE* fp = fopen("Admin_data.txt", "rb");
    if(fp == NULL)
    {
        printf("Cannot open \"Admin_data.txt\"\n");
        exit(1);
    }
    (*admin_password) = (char*)malloc((ADMINPASSWORD_LENGTH) * sizeof(char));
    char password[ADMINPASSWORD_LENGTH];
    fscanf(fp, "%s", password);
    strcpy(*admin_password, password);
    fclose(fp);
}

//保存用户信息
void Save_user(struct User* users_head)//将链表内容写入文件
{
    FILE* fp = fopen("User_data.txt", "wb");
    if(fp == NULL)
    {
        printf("Cannot open \"User_data.txt\"\n");
        exit(1);
    }
    struct User* p = users_head -> next;
    while(p != NULL)
    {
        if(p -> next != NULL)
        {
            fprintf(fp, "%d %s %s %.2lf\n", p -> id, p -> username, p -> password, p -> Performance_amount);
            p = p -> next;
        }
        else
        {
            fprintf(fp, "%d %s %s %.2lf", p -> id, p -> username, p -> password, p -> Performance_amount);
            p = p -> next;
        }
    }
    fclose(fp);
}

//保存菜品信息
void Save_food(struct Food *foods_head)
{
    FILE* fp = fopen("Food_data.txt", "wb");
    if(fp == NULL)
    {
        printf("Cannot open \"Food_data.txt\"\n");
        exit(1);
    }
    struct Food* p = foods_head -> next;
    while(p != NULL)
    {
        if(p -> next != NULL)
        {
            fprintf(fp, "%d %s %.2lf %d\n", p -> id, p -> name, p -> price, p -> cnt);
            p = p -> next;
        }
        else
        {
            fprintf(fp, "%d %s %.2lf %d", p -> id, p -> name, p -> price, p -> cnt);
            p = p -> next;
        }
    }
    fclose(fp);
}

//保存座位信息
void Save_seat(struct Seat *seats_head)
{
    FILE* fp = fopen("Seat_data.txt", "wb");
    if(fp == NULL)
    {
        printf("Cannot open \"Seat_data.txt\"\n");
        exit(1);
    }
    struct Seat* p = seats_head -> next;
    while(p != NULL)
    {
        if(p -> next != NULL)
        {
            fprintf(fp, "%d %d %d\n", p -> flag, p -> book, p -> num);
            p = p -> next;
        }
        else
        {
            fprintf(fp, "%d %d %d", p -> flag, p -> book, p -> num);
            p = p -> next;
        }
    }
    fclose(fp);
}

//保存顾客信息
void Save_customer(struct Customer* customers_head)
{
    FILE* fp = fopen("Customer_data.txt", "wb");
    if(fp == NULL)
    {
        printf("Cannot open \"Customer_data.txt\"\n");
        exit(1);
    }
    struct Customer* p = customers_head -> next;
    while(p != NULL)
    {
        if(p -> next != NULL)
        {
            fprintf(fp, "%d %d\n", p -> Seat_book, p -> Order_id);
            p = p -> next;
        }
        else
        {
            fprintf(fp, "%d %d", p -> Seat_book, p -> Order_id);
            p = p -> next;
        }
    }
    fclose(fp);
}

//保存订单信息
void Save_order(struct Order* orders_head)
{
    FILE* fp = fopen("Order_data.txt", "wb");
    if(fp == NULL)
    {
        printf("Cannot open \"Order_data.txt\"\n");
        exit(1);
    }
    struct Order* p = orders_head -> next;
    while(p != NULL)
    {
        if(p -> next != NULL)
        {
            fprintf(fp, "%d", p -> orderid);
            int i = 0;
            do{
                i++;
                fprintf(fp, " %d", p -> food[i]);
            }while(p -> food[i] != -1);
            fprintf(fp, " %.2lf\n", p -> Totalexpenses);
            p = p -> next;
        }
        else
        {
            fprintf(fp, "%d", p -> orderid);
            int i = 0;
            do{
                i++;
                fprintf(fp, " %d", p -> food[i]);
            }while(p -> food[i] != -1);
            fprintf(fp, " %.2lf", p -> Totalexpenses);
            p = p -> next;
        }
    }
    fclose(fp);
}