#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core.h"
#include "ui.h"
#include "io.h"

//进入系统的初始界面
enum UserType Welcome_Menu(void)
{
    enum UserType usertype = undefine;
    int flag = 0;
    char inputpassword[ADMINPASSWORD_LENGTH];
    if(!(usertype == admin || usertype == waiter)) {
        printf("*************************************************\n");
        printf("*\t\tWelcome to the system!\t\t*\n");//初始界面
        printf("*************************************************\n");
        printf("Please select your identity:\n");
        printf("1)I'm a waiter\n");
        printf("2)I'm a system administrator\n");
        printf("Please enter the number corresponding to your identity:\n");
        scanf("%d", &flag);
        system("cls");
        if (flag == 1) {
            usertype = waiter;
        } else if (flag == 2) {
            printf("Please enter the administrator password:");
            scanf("%s", inputpassword);
            if (strcmp(inputpassword, My_restaurant.admin_password) == 0) {
                printf("Correct password!\n");
                printf("Successfully logged into the system!\n");
                usertype = admin;
            } else {
                printf("Wrong password!\n");
                printf("Do you want to re-enter the password?\n");
                printf("1)Yes!\n");
                printf("2)No!\n");
                printf("Please enter the function number you want to do:\n");
                int n;
                scanf("%d", &n);
                if (n == 1) {
                    usertype = Re_enter_password();
                } else if (n == 2) {
                    usertype = undefine;
                }
                system("cls");
            }
        }
    }
    return usertype;
}

//系统账户管理页面
void Account_management_Menu()
{
    printf("\t1)Register a new user\n\n");
    printf("\t2)Search and browse user information\n\n");
    printf("\t3)Change user information\n\n");
    printf("\t4)Return to the previous menu\n\n");
    int choice = 0;
    while(!(choice >= 1 && choice <= 4))
    {
        printf("\tPlease enter the number of the function you want to do:\n");
        scanf("%d", &choice);
    }
    switch(choice)
    {
        case 1:
            Register(&My_restaurant.users);
            Save_user(My_restaurant.users);
            break;
        case 2:
            Browse_user(My_restaurant.users);
            break;
        case 3:
            Change_user(&My_restaurant.users);
            Save_user(My_restaurant.users);
            break;
        default:
            break;
    }
}

//系统菜单管理页面
void Menu_management_Menu()
{
    printf("\t1)Add food\n\n");
    printf("\t2)Search and browse food information\n\n");
    printf("\t3)Change food information\n\n");
    printf("\t4)Return to the previous menu\n\n");
    int choice = 0;
    while(!(choice >= 1 && choice <= 4))
    {
        printf("\tPlease enter the number of the function you want to do:\n");
        scanf("%d", &choice);
    }
    switch(choice)
    {
        case 1:
            Add_food(&My_restaurant.foods);
            Save_food(My_restaurant.foods);
            break;
        case 2:
            Browse_food(My_restaurant.foods);
            break;
        case 3:
            Change_food(&My_restaurant.foods);
            Save_food(My_restaurant.foods);
            break;
        default:
            break;
    }
}

//管理员身份的初始界面
int Admin_Menu(void)
{
    printf("\tHello administrator!\n");
    printf("\t1)Manage users\n\n");
    printf("\t2)Manage menu\n\n");
    printf("\t3)View statistical analysis\n\n");
    printf("\t4)Manage seat\n\n");
    printf("\t5)View customer information\n\n");
    printf("\t6)Play game\n\n");
    printf("\t7)Exit system\n\n");
    int choice = 0;
    while(!(choice >= 1 && choice <= 7))
    {
        printf("\tPlease enter the number of the function you want to do:\n");
        scanf("%d", &choice);
    }
    return choice;
}

//用户登录页面
int Log_in(struct User *users_head)//从user链表中检索username,匹配password
{
    int flag;
    struct User* p;
    p = users_head -> next;
    printf("Please enter your username and password to log in!\n");
    printf("Username:\n");
    char input_username[USERNAME_LENGTH];
    scanf("%s", input_username);
    while(p != NULL)
    {
        if(strcmp(p -> username, input_username) == 0)
        {
            break;
        }
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("The Username does not exist!\n");
        flag = 0;
    }
    else
    {
        printf("Password:\n");
        char input_password[USERPASSWORD_LENGTH];
        scanf("%s", input_password);
        if(strcmp(p -> password, input_password) == 0)
        {
            printf("Successful login!\n");
            My_restaurant.Current_user_id = p -> id;
            flag = 1;
        }
        else
        {
            printf("Wrong password!\n");
            flag = 0;
        }
    }
    return flag;
}

//服务员的初始界面
int Waiter_Menu(void)
{
    printf("\tHello Waiter!\n");
    int flag;
    if(My_restaurant.Current_user_id == 0)
    {
        flag = Log_in(My_restaurant.users);
    }
    else
    {
        flag = 1;
    }
    int choice = 0;
    if(flag == 1)
    {
        printf("\tWelcome!\n" );
        printf("\t1)Entry customer information\n\n");
        printf("\t2)Brow menu\n\n");
        printf("\t3)Manage customer information\n\n");
        printf("\t4)Manage seat\n\n");
        printf("\t5)Play game\n\n");
        printf("\t6)Exit system\n\n");
        while(!(choice >= 1 && choice <= 6))
        {
            printf("\tPlease enter the number of the function you want to do:\n");
            scanf("%d", &choice);
        }
    }
    else if(flag == 0)
    {
        choice = 5;
    }
    return choice;
}

//显示菜品数据（名称 ： 被点次数）
void Show_food(struct Food* foods_head)
{
    struct Food *p = foods_head -> next;
    while(p != NULL)
    {
        printf("%s : %d time(s)\n", p -> name, p -> cnt);
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("Food data analysis completed!\n");
    }
}

//显示服务员数据（用户名 ： 业绩）
void Show_waiter(struct User* users_head)
{
    struct User *p = users_head -> next;
    while(p != NULL)
    {
        printf("%d %s : %.2lf$\n", p -> id, p -> username, p -> Performance_amount);
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("User data analysis completed!\n");
    }
}

//显示营业额数据
void Show_turnover(struct User* users_head)
{
    struct User *p = users_head -> next;
    double total_turnover = 0.0;
    while(p != NULL)
    {
        total_turnover += p -> Performance_amount;
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("The total turnover from business to the present is : %.2lf\n", total_turnover);
        printf("Data analysis completed!\n");
    }
}

//数据分析页面
void Statistical_analysis_Menu(void)
{
    printf("\t1)Show the number of times each food was ordered\n\n");
    printf("\t2)Show the performance account of each waiter\n\n");
    printf("\t3)Show the total turnover\n\n");
    printf("\t4)Return to the previous menu\n\n");
    int choice = 0;
    while(!(choice >= 1 && choice <= 4))
    {
        printf("\tPlease enter the number of the function you want to do:\n");
        scanf("%d", &choice);
    }
    switch(choice)
    {
        case 1:
            Show_food(My_restaurant.foods);
            break;
        case 2:
            Show_waiter(My_restaurant.users);
            break;
        case 3:
            Show_turnover(My_restaurant.users);
            break;
        default:
            break;
    }
}

//管理员的座位信息页面
void Seat_information_Menu_Admin()
{
    printf("\t1)Add a seat\n\n");
    printf("\t2)Search and browse seat information\n\n");
    printf("\t3)Change seat information\n\n");
    printf("\t4)Return to the previous menu\n\n");
    int choice = 0;
    while(!(choice >= 1 && choice <= 4))
    {
        printf("\tPlease enter the number of the function you want to do:\n");
        scanf("%d", &choice);
    }
    switch(choice)
    {
        case 1:
            Add_seat(&My_restaurant.seats);
            Save_seat(My_restaurant.seats);
            break;
        case 2:
            Browse_seat(My_restaurant.seats);
            break;
        case 3:
            Change_seat(&My_restaurant.seats);
            Save_seat(My_restaurant.seats);
            break;
        default:
            break;
    }
}

//显示所有菜品
void Show_Menu(struct Food* foods_head)
{
    struct Food *p = foods_head -> next;
    while(p != NULL)
    {
        printf("Food name: %s\n", p -> name);
        printf("Price: %.lf\n\n", p -> price);
        p = p -> next;
        if(p == NULL)
            break;
    }
    if(p == NULL)
    {
        printf("No more food!\n\n");
    }
}

//服务员的座位信息页面
void Seat_information_Menu_Waiter()
{
    printf("\t1)Show empty seats by number of customers\n\n");
    printf("\t2)Update seat status\n\n");
    printf("\t3)Return to the previous menu\n\n");
    int choice = 0;
    while(!(choice >= 1 && choice <= 3))
    {
        printf("\tPlease enter the number of the function you want to do:\n");
        scanf("%d", &choice);
    }
    switch(choice)
    {
        case 1:
            Browse_empty_seats(My_restaurant.seats);
            break;
        case 2:
            Change_seat(&My_restaurant.seats);
            Save_seat(My_restaurant.seats);
            break;
        default:
            break;
    }
}

//顾客信息页面
void Customer_information_Menu()
{
    printf("\t1)Browse customer information\n\n");
    printf("\t2)Change customer information\n\n");
    printf("\t3)Return to the previous menu\n\n");
    int choice = 0;
    while(!(choice >= 1 && choice <= 3))
    {
        printf("\tPlease enter the number of the function you want to do:\n");
        scanf("%d", &choice);
    }
    switch(choice)
    {
        case 1:
            Customer_information_browsing(My_restaurant.customers, My_restaurant.orders, My_restaurant.foods);
            break;
        case 2:
            Change_customer(&My_restaurant.customers, &My_restaurant.seats, &My_restaurant.foods, &My_restaurant.orders, &My_restaurant.users, My_restaurant.Current_user_id);
            Save_customer(My_restaurant.customers);
            Save_seat(My_restaurant.seats);
            Save_order(My_restaurant.orders);
            Save_food(My_restaurant.foods);
            Save_user(My_restaurant.users);
            break;
        default:
            break;
    }
}
