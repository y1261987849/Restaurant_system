#include "core.h"
#include "ui.h"
#include "io.h"
#include "t.h" 

int main()
{
    //数据文件读取、全局变量初始化
    data_init();
    //验证用户身份
    enum UserType userType = Welcome_Menu();
    if(userType == admin)
    {
        while(1)
        {
            int choice = Admin_Menu();
            switch(choice)
            {
                case 1: //管理用户操作
                    Account_management_Menu();
                    break;
                case 2: //管理菜单操作
                    Menu_management_Menu();
                    break;
                case 3: //查看统计分析操作
                    Statistical_analysis_Menu();
                    break;
                case 4: //餐位信息操作
                    Seat_information_Menu_Admin();
                    break;
                case 5: //顾客信息浏览
                    Customer_information_browsing(My_restaurant.customers, My_restaurant.orders, My_restaurant.foods);
                    break;
                case 6:
					game();
					break; 
                default:
                    Exit(&My_restaurant.seats);
                    break;
            }
        }
    }
    else if(userType == waiter)
    {
        while(1)
        {
            int choice = Waiter_Menu();
            switch(choice)
            {
                case 1: //顾客信息录入
                    Customer_information_entry(&My_restaurant.customers, &My_restaurant.customerscnt, &My_restaurant.seats, &My_restaurant.foods, &My_restaurant.orders, &My_restaurant.users, My_restaurant.Current_user_id);
                    Save_customer(My_restaurant.customers);
                    Save_seat(My_restaurant.seats);
                    Save_order(My_restaurant.orders);
                    Save_food(My_restaurant.foods);
                    Save_user(My_restaurant.users);
                    break;
                case 2: //菜单信息浏览
                    Show_Menu(My_restaurant.foods);
                    break;
                case 3:
                    Customer_information_Menu();
                    break;
                case 4:
                    Seat_information_Menu_Waiter();
                    break;
                case 5:
					game();
					break; 
                default:
                    Exit(&My_restaurant.seats);
                    break;
            }
        }
    }
    return 0;
}
