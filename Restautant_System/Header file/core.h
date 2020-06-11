//系统核心部分，包含 宏定义、所有用到的结构体的定义、主要功能函数的声明
#define FOODNAME_LENGTH 30 //食物名称的最大长度
#define USERNAME_LENGTH 12 //用户名的最大长度
#define USERPASSWORD_LENGTH 12 //用户密码最大长度
#define ADMINPASSWORD_LENGTH 9 //管理员密码最大长度

//公共数据
struct Restaurant
{
    int Current_user_id;
	struct User* users;
	struct Food* foods;
	struct Seat* seats;
	struct Customer* customers;
	struct Order* orders;
	int userscnt;
	int foodscnt;
	int seatscnt;
	int customerscnt;
	char* admin_password;
}My_restaurant;

enum UserType
{
	undefine,
	waiter,
	admin
};

//菜品
struct Food
{
	int id;//菜品id
	char name[FOODNAME_LENGTH];
	double price;
	int cnt;//菜品自添加到系统一共被点的次数
	struct Food* next;
};

//订单
struct Order
{
	int orderid;//订单号
	int food[20];
	double Totalexpenses;
	struct Order* next;
};
//餐位
struct Seat
{
	int flag;//餐位是否有人
	int book;//餐位序号
	int num;//可坐人数
	struct Seat* next;
};
//用户
struct User
{
	int id; //工号
	char username[USERNAME_LENGTH];
	char password[USERPASSWORD_LENGTH];
	double Performance_amount;//业绩总金额
	struct User* next;
};

//顾客
struct Customer
{
	int Seat_book;//餐位
    int Order_id;//订单信息
	struct Customer* next;
};



//初始化函数
void data_init();

//重新输入管理员密码
enum UserType Re_enter_password();


//用户注册
void Register(struct User *(*users_head));

//浏览用户信息
void Browse_user(struct User* users_head);

//用户信息更改
void Change_user(struct User *(*users_head));



//菜品添加
void Add_food(struct Food **);

//浏览菜品信息
void Browse_food(struct Food* foods_head);

//菜品信息更改
void Change_food(struct Food **);

//添加座位
void Add_seat(struct Seat**);
//浏览座位信息
void Browse_seat(struct Seat *);
//更改座位信息
void Change_seat(struct Seat**);

//浏览空座位
void Browse_empty_seats(struct Seat *);

//顾客信息录入
void Customer_information_entry(struct Customer **, int* , struct Seat**, struct Food **, struct Order **, struct User**, int);

//顾客信息浏览页面
void Customer_information_browsing(struct Customer*, struct Order*, struct Food*);

void Change_customer(struct Customer **, struct Seat **, struct Food **, struct Order **, struct User**, int);

void Exit(struct Seat**);