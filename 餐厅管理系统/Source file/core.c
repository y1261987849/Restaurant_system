#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"
#include "ui.h"
#include "io.h"

//数据初始化
void data_init()
{
	//载入用户数据
	Load_users_data(&My_restaurant.users, &My_restaurant.userscnt);
	//载入菜品数据
	Load_foods_data(&My_restaurant.foods, &My_restaurant.foodscnt);
	//载入餐位数据
	Load_seats_data(&My_restaurant.seats, &My_restaurant.seatscnt);
	//载入顾客数据
	Load_customers_data(&My_restaurant.customers, &My_restaurant.customerscnt);
	//载入订单数据
	Load_orders_data(&My_restaurant.orders);
	//载入管理员数据
	Load_admin_data(&My_restaurant.admin_password);
}

//管理员密码的重新输入
enum UserType Re_enter_password()
{
    enum UserType usertype;
    char re_inputpassword[8];
    int cnt = 0;
    while(1)
    {
        printf("Please re-enter the administrator password:\n");
        scanf("%s", re_inputpassword);
        if(strcmp(re_inputpassword, My_restaurant.admin_password) == 0)
        {
            printf("Correct password!\n");
            printf("Successfully logged into the system!\n");
            usertype = admin;
            break;
        }
        else
        {
            if(cnt == 3)
            {
                printf("You have entered the wrong password several times\n");
                printf("The system will determine your identity as undefine!\n");
                break;
            }
            printf("Wrong password!\n");
            printf("Please re-enter the password again!\n");
            usertype = undefine;
        }
        cnt++;
    }
    return usertype;
}



//注册账户
void Register(struct User *(*users_head))
{
    struct User* temp = (struct User*)malloc(sizeof(struct User));
    printf("Welcome to register!\n");
    printf("Please enter user id:\n");
    scanf("%d", &temp -> id);
    printf("Please enter user name(11 digits or letters):\n");
    scanf("%s", temp -> username);
    printf("Please enter password (11 digits or letters):\n");
    scanf("%s", temp -> password);
    temp -> Performance_amount = 0.0;
    temp -> next = NULL;
    struct User* p = (*users_head) -> next;
    while((p -> next) != NULL)
    {
        p = p -> next;
    }
    p -> next = temp;
    My_restaurant.userscnt++;
    printf("Registered successfully!\n");
}

//浏览用户信息
void Browse_user(struct User* users_head)
{
    printf("Please enter the user id:\n");
    int id;
    scanf("%d", &id);
    struct User* p  = users_head -> next;
    while(p != NULL)
    {
        if(p -> id == id)
        {
            printf("User id: %d\n", p -> id);
            printf("Username: %s\n", p -> username);
            printf("Password: %s\n", p -> password);
            printf("Performance amount: %.2lf\n", p -> Performance_amount);
            break;
        }
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("No matching user id!\n");
    }
}

//更改用户信息
void Change_user(struct User *(*users_head))
{
    printf("Please enter the user id:\n");
    int id;
    scanf("%d", &id);
    struct User* p = (*users_head) -> next;
    while(p != NULL)
    {
        if(p -> id == id)
        {
            printf("1)I want to change username\n");
            printf("2)I want to change password\n");
            printf("3)I want to change user id\n");
            int choice = 0;
            while(!(choice >= 1 && choice <= 3))
            {
                printf("\tPlease enter the number of the function you want to do:\n");
                scanf("%d", &choice);
            }
            switch(choice)
            {
                case 1:
                    printf("Please enter a new username:\n");
                    scanf("%s", p -> username);
                    printf("User name changed successfully!\n");
                    break;
                case 2:
                    printf("Please enter a new password:\n");
                    scanf("%s", p -> password);
                    printf("Password changed successfully!\n");
                    break;
                case 3:
                    printf("Please enter a new user id:\n");
                    scanf("%d", &p -> id);
                    printf("User id changed successfully!\n");
                    break;
                default:
                    break;
            }
            break;
        }
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("No matching user id!\n");
    }
}



//添加菜品
void Add_food(struct Food *(*foods_head))
{
    struct Food* temp = (struct Food*)malloc(sizeof(struct Food));
    printf("Please enter food id:\n");
    scanf("%d", &temp -> id);
    printf("Please enter food name(20 letters):\n");
    scanf("%s", temp -> name);
    printf("Please enter food price:\n");
    scanf("%lf", &temp -> price);
    temp -> cnt = 0;
    temp -> next = NULL;
    struct Food* p = (*foods_head) -> next;
    while((p -> next) != NULL)
    {
        p = p -> next;
    }
    p -> next = temp;
    My_restaurant.foodscnt++;
    printf("Added successfully!\n");
}

//查询浏览菜品信息
void Browse_food(struct Food * foods_head)
{
    printf("Please enter the food id:\n");
    int id;
    scanf("%d", &id);
    struct Food* p  = foods_head -> next;
    while(p != NULL)
    {
        if(p -> id == id)
        {
            printf("Food id: %d\n", p -> id);
            printf("Food name: %s\n", p -> name);
            printf("Food price: %.2lf\n", p -> price);
            printf("The number of orders: %d\n", p -> cnt);
            break;
        }
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("No matching food id!\n");
    }
}

//更改菜品信息
void Change_food(struct Food *(*foods_head))
{
    printf("Please enter the food id:\n");
    int id;
    scanf("%d", &id);
    struct Food* p = (*foods_head) -> next;
    while(p != NULL)
    {
        if(p -> id == id)
        {
            printf("1)I want to change food name\n");
            printf("2)I want to change food price\n");
            printf("3)I want to change food id\n");
            int choice = 0;
            while(!(choice >= 1 && choice <= 3))
            {
                printf("\tPlease enter the number of the function you want to do:\n");
                scanf("%d", &choice);
            }
            switch(choice)
            {
                case 1:
                    printf("Please enter a new food name:\n");
                    scanf("%s", p -> name);
                    printf("Food name changed successfully!\n");
                    break;
                case 2:
                    printf("Please enter a new price:\n");
                    scanf("%lf", &p -> price);
                    printf("Food price changed successfully!\n");
                    break;
                case 3:
                    printf("Please enter a new food id:\n");
                    scanf("%d", &p -> id);
                    printf("Food id changed successfully!\n");
                    break;
                default:
                    break;
            }
            break;
        }
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("No matching food id!\n");
    }
}


//添加座位
void Add_seat(struct Seat *(*seats_head))
{
    struct Seat* temp = (struct Seat*)malloc(sizeof(struct Seat));
    printf("Please enter seat id :\n");
    scanf("%d", &temp -> book);
    printf("Please enter the seating capacity :\n");
    scanf("%d", &temp -> num);
    temp -> flag = 0;
    temp -> next = NULL;
    struct Seat* p = (*seats_head) -> next;
    while((p -> next) != NULL)
    {
        p = p -> next;
    }
    p -> next = temp;
    My_restaurant.seatscnt++;
    printf("Added successfully!\n");
}

//查询浏览座位信息
void Browse_seat(struct Seat * seats_head)
{
    printf("Please enter the seat id:\n");
    int book;
    scanf("%d", &book);
    struct Seat* p  = seats_head -> next;
    while(p != NULL)
    {
        if(p -> book == book)
        {
            printf("Seat id: %d\n", p -> book);
            if(p -> num == 1)
                printf("Seating capacity : 1 person\n");
            else if(p -> num > 1)
                printf("Seating capacity : %d people\n", p -> num);
            if(p -> flag == 0)
                printf("Empty\n");
            else if(p -> flag == 1)
                printf("Seated\n");
            break;
        }
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("No matching seat id!\n");
    }
}

//更改座位信息
void Change_seat(struct Seat *(*seats_head))
{
    printf("Please enter the seat id:\n");
    int book;
    scanf("%d", &book);
    struct Seat* p = (*seats_head) -> next;
    while(p != NULL)
    {
        if(p -> book == book)
        {
            printf("1)I want to change seat capacity\n");
            printf("2)I want to change seat state\n");
            printf("3)I want to change seat id\n");
            int choice = 0;
            while(!(choice >= 1 && choice <= 3))
            {
                printf("\tPlease enter the number of the function you want to do:\n");
                scanf("%d", &choice);
            }
            switch(choice)
            {
                case 1:
                    printf("Please enter a new seat capcacity:\n");
                    scanf("%d", &p -> num);
                    printf("Seat capacity changed successfully!\n");
                    break;
                case 2:
                    printf("Please enter current seating state:\n");
                    scanf("%d", &p -> flag);
                    printf("Seating state changed successfully!\n");
                    break;
                case 3:
                    printf("Please enter a new seat id:\n");
                    scanf("%d", &p -> book);
                    printf("Seat id changed successfully!\n");
                    break;
                default:
                    break;
            }
            break;
        }
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("No matching seat id!\n");
    }
}

//根据顾客人数查询可用空座位
void Browse_empty_seats(struct Seat* seats_head)
{
    printf("\tPlease enter the number of customers:\n");
    int num;
    scanf("%d", &num);
    struct Seat *p = seats_head -> next;
    while(p != NULL)
    {
        if(p -> flag == 0 && p -> num >= num)
        {
            printf("Seat %d is available!\n", p -> book);
        }
        p = p -> next;
    }
}

//下单录入顾客信息
void Customer_information_entry(struct Customer *(*customers_head), int* customers_cnt, struct Seat *(*seats_head), struct Food *(*foods_head), struct Order *(*orders_head), struct User *(*users_head), int Current_user_id)
{
    struct Customer* temp = (struct Customer*)malloc(sizeof(struct Customer));
    (*customers_cnt)++;
    temp -> Order_id = (*customers_cnt);
    printf("Please enter the seat id:\n");
    scanf("%d", &temp -> Seat_book);
    temp -> next = NULL;
    struct Customer * q = (*customers_head);
    while(q -> next != NULL)
    {
        q = q -> next;
    }
    q -> next = temp;

    struct Seat *p = (*seats_head) -> next;
    while(p != NULL)
    {
        if(p -> book == temp -> Seat_book)
        {
            p -> flag = 1;
            break;
        }
        p = p -> next;
    }

    struct Order *l = (struct Order*)malloc(sizeof(struct Order));
    l -> orderid = temp -> Order_id;
    printf("Please enter the id of the orderd food (Enter -1 to end the input）:\n");
    int i = 0;
    do {
        i++;
        scanf("%d", &l -> food[i]);
    }while(l -> food[i] != -1);
    l -> Totalexpenses = 0.0;
    struct Food *f = (*foods_head) -> next;
    while(f != NULL)
    {
        i = 1;
        while(l -> food[i] != -1)
        {
            if(f -> id == l -> food[i])
            {
                l -> Totalexpenses += f -> price;
                f -> cnt++;
            }
            i++;
        }
        f = f -> next;
    }
    l -> next = NULL;

    struct User *u = (*users_head) -> next;
    while(u != NULL)
    {
        if(u -> id == Current_user_id)
        {
            u -> Performance_amount += l -> Totalexpenses;
            break;
        }
        u = u -> next;
    }

    struct Order *o = (*orders_head);
    while(o -> next != NULL)
    {
        o = o -> next;
    }
    o -> next = l;

    printf("Enter successfully!\n");
}

//浏览顾客下单信息
void Customer_information_browsing(struct Customer *customers_head, struct Order *orders_head, struct Food *foods_head)
{
    printf("Please enter the Customer's seat id:\n");
    int book;
    scanf("%d", &book);
    struct Customer* p  = customers_head -> next;
    while(p != NULL)
    {
        if(p -> Seat_book == book)
        {
            printf("Seat id:%d\n", p -> Seat_book);
            printf("Order id:%d\n", p -> Order_id);
            struct Order *q = orders_head -> next;
            printf("Ordered food:\n");
            while(q != NULL)
            {
                if(p -> Order_id == q -> orderid)
                {
                    struct Food *l = foods_head -> next;
                    int i = 1;
                    while(q -> food[i] != -1)
                    {
                        while(l != NULL)
                        {
                            if(q -> food[i] == l -> id)
                            {
                                printf("%s  %.2lf\n", l -> name, l -> price);
                                break;
                            }
                            l = l -> next;
                        }
                        i++;
                    }
                    printf("Total expenses:%.2lf\n", q -> Totalexpenses);
                    break;
                }
                q = q -> next;
            }
            break;
        }
        p = p -> next;
    }
    if(p == NULL)
    {
        printf("No matching id!\n");
    }
}

//更改顾客信息
void Change_customer(struct Customer*(*customers_head), struct Seat*(*seats_head), struct Food *(*foods_head), struct Order*(*orders_head), struct User *(*users_head), int Current_user_id)
{
    printf("Please enter the seat id of the customer you want to change\n");
    int book;
    scanf("%d", &book);
    struct Customer *p = (*customers_head) -> next;
    while(p != NULL)
    {
        if(book == p -> Seat_book)
        {
            break;
        }
    }
    printf("\t1)I want to change the customer's seat id\n\n");
    printf("\t2)I want to change the customer's order\n\n");
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
        {
            struct Seat *q = (*seats_head) -> next;
            while(q != NULL)
            {
                if(q -> book == book)
                {
                    q -> flag = 0;
                    break;
                }
                q = q -> next;
            }
            printf("Please enter a new seat id:\n");
            scanf("%d", &p -> Seat_book);
            q = (*seats_head) -> next;
            while(q != NULL)
            {
                if(p -> Seat_book == q -> book)
                {
                    q -> flag = 1;
                    break;
                }
                q = q -> next;
            }
            printf("Seat id changed successfully!\n");
        }
            break;
        case 2:
        {
            printf("\t1)I want to add food\n\n");
            printf("\t2)I want to return food\n\n");
            printf("\t3)I want to replace food\n\n");
            printf("\t4)Return to the previous menu\n\n");
            int selection = 0;
            while(!(selection >= 1 && selection <= 4))
            {
                printf("\tPlease enter the number of the function you want to do:\n");
                scanf("%d", &selection);
            }
            struct User *u = (*users_head) -> next;
            while(u != NULL)
            {
                if(u -> id == Current_user_id)
                {
                    break;
                }
                u = u -> next;
            }
            struct Order *l = (*orders_head) -> next;
            while(l != NULL)
            {
                if(p -> Order_id == l -> orderid)
                    break;
                l = l -> next;
            }
            switch(selection)
            {
                case 1:
                {
                    printf("Please enter the food id you want to add:\n");
                    int id;
                    scanf("%d", &id);
                    int i = 1;
                    while(l -> food[i] != -1)
                    {
                        i++;
                    }
                    l -> food[i++] = id;
                    l -> food[i] = -1;
                    struct Food *f = (*foods_head) -> next;
                    while(f != NULL)
                    {
                        if(id == f -> id)
                        {
                            f -> cnt++;
                            l -> Totalexpenses += f -> price;
                            u -> Performance_amount += f -> price;
                            break;
                        }
                        f = f -> next;
                    }
                    printf("Added successfully!\n");
                }
                    break;
                case 2:
                {
                    printf("Please enter the food id you want to return:\n");
                    int id;
                    scanf("%d", &id);
                    int i = 1;
                    while(l -> food[i] != id)
                    {
                        i++;
                    }
                    l -> food[i] = 0;
                    struct Food *f = (*foods_head) -> next;
                    while(f != NULL)
                    {
                        if(f -> id == id)
                        {
                            f -> cnt--;
                            l -> Totalexpenses -= f -> price;
                            u -> Performance_amount -= f -> price;
                            break;
                        }
                        f = f -> next;
                    }
                    printf("Returned successfully!\n");
                }
                    break;
                case 3:
                {
                    printf("Please enter the food id you want to replace:\n");
                    int id;
                    scanf("%d", &id);
                    int i = 1;
                    while(l -> food[i] != id)
                    {
                        i++;
                    }
                    struct Food *f = (*foods_head) -> next;
                    while(f != NULL)
                    {
                        if(f -> id == id)
                        {
                            f -> cnt--;
                            l -> Totalexpenses -= f -> price;
                            u -> Performance_amount -= f -> price;
                            break;
                        }
                        f = f -> next;
                    }
                    printf("Please enter a new food id:\n");
                    int rid;
                    scanf("%d", &rid);
                    l -> food[i] = rid;
                    while(f != NULL)
                    {
                        if(f -> id == rid)
                        {
                            f -> cnt++;
                            l -> Totalexpenses += f -> price;
                            u -> Performance_amount += f -> price;
                            break;
                        }
                        f = f -> next;
                    }

                }
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;

    }
}

//退出系统
void Exit(struct Seat *(*seats_head)) //将所有餐桌置空，退出系统
{
    struct Seat *p = (*seats_head) -> next;
    while(p != NULL)
    {
        p -> flag = 0;
        p = p -> next;
    }
    Save_seat(My_restaurant.seats);
    printf("******************************************\n");
    printf("*You have successfully exited the system!*\n");
    printf("******************************************\n");
    exit(EXIT_SUCCESS);
}

