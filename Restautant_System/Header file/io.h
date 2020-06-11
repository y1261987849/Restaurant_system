//包含 将数据载入程序和将数据输出到文件的函数声明

//载入数据
void Load_users_data(struct User *(*users_head), int* cnt);

void Load_foods_data(struct Food *(*foods_head), int* cnt);

void Load_seats_data(struct Seat *(*seats_head), int* cnt);

void Load_customers_data(struct Customer *(*customers_head), int* cnt);

void Load_orders_data(struct Order *(*orders_head));

void Load_admin_data(char *(*admin_password));


//将信息输出到文件，保存数据
void Save_user(struct User* users_head);

void Save_food(struct Food* foods_head);

void Save_seat(struct Seat* seats_head);

void Save_customer(struct Customer* customers_head);

void Save_order(struct Order* orderd_head);