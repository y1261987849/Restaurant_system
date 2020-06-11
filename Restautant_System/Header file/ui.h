//包含有关系统界面、菜单选项的函数声明

//用户类型选择
enum UserType Welcome_Menu(void);

//管理员页面
int Admin_Menu(void);

//服务员页面
int Waiter_Menu(void);

//服务员登录
int Log_in(struct User* users_head);

//管理用户页面
void Account_management_Menu();

//管理菜单页面
void Menu_management_Menu();


//查看统计分析
void Statistical_analysis_Menu();
//显示菜品名称和被点次数
void Show_food(struct Food*);
//显示服务员业绩
void Show_waiter(struct User*);
//显示总营业额
void Show_turnover(struct User*);


//查询、浏览餐位信息（管理员）
void Seat_information_Menu_Admin();

//显示菜单
void Show_Menu(struct Food*);


//顾客信息浏览页面
void Customer_information_browsing(struct Customer*, struct Order*, struct Food*);

//顾客信息操作页面
void Customer_information_Menu();



//查询、浏览餐位信息（服务员）
void Seat_information_Menu_Waiter();


