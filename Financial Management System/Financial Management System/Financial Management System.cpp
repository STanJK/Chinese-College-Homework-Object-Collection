#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//Extern functions
extern void mainmenu();
extern void exit_menu();

extern void income_management();
extern void add_income_management();
extern void search_income_management();
extern void search_income_by_member();
extern void search_income_by_date();
extern void modify_income_record();
extern void delete_income_management();
extern void print_income_management();

extern void payout_management();
extern void add_payout_management();
extern void search_payout_management();
extern void search_payout_by_member();
extern void search_payout_by_date();
extern void modify_payout_record();
extern void delete_payout_management();
extern void print_payout_management();

extern void load_example_record();
extern void init_file();
extern void print_all();

int menu_selection;

struct record_structure
{
	char member[200];
	char date[9];
	int amount;
	char reason[200];
	int type; //Define record type: 0 is income, 1 is payout, 2 is deleted
	int number;
};

int main()
{
	init_file();
	mainmenu();
	return 0;
}

void init_file()
{
	FILE* record;
	record = fopen("record_file.bin", "wb");
	if (record == NULL)
	{
		printf("创建/打开记录文件失败！程序退出\n");
		exit(1);
	}
	else
	{
		load_example_record();
	}
}

void load_example_record()
{
	//Open File to write income and payout examples
	FILE* record_file = fopen("record_file.bin", "wb");
	if (record_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}

	struct record_structure write_example;

	write_example = { "王二","23/12/31",15000,"12月工资",0,1 };
	fwrite(&write_example, sizeof(struct record_structure), 1, record_file);
	write_example = { "张三","24/01/05",200,"缴纳12月电费",1,2 };
	fwrite(&write_example, sizeof(struct record_structure), 1, record_file);
	write_example = { "张三","24/01/06",3000,"一月份生活费",1,3 };
	fwrite(&write_example, sizeof(struct record_structure), 1, record_file);
	write_example = { "王二","24/01/07",2500,"一月份生活费",1,4 };
	fwrite(&write_example, sizeof(struct record_structure), 1, record_file);
	write_example = { "张三","24/01/07",200,"一月七日加班费",0,5 };
	fwrite(&write_example, sizeof(struct record_structure), 1, record_file);

	fclose(record_file);
}

void mainmenu()
{
	printf("\n欢迎来到家庭财务小管家系统\n");
	printf("1.收入记录管理\n");
	printf("2.支出记录管理\n");
	printf("3.打印所有收入/支出记录\n");
	printf("4.退出系统\n");
	printf("请输入序号以进行操作:");
	scanf_s("%d", &menu_selection);
	if (menu_selection == 1)
	{
		income_management();
	}
	else if (menu_selection == 2)
	{
		payout_management();
	}
	else if (menu_selection == 3)
	{
		print_all();
	}
	else if (menu_selection == 4)
	{
		exit_menu();
	}
	else
	{
		printf("请输入正确的序号\n\n");
		mainmenu();
	}
}

void income_management()
{
	printf("\n收入记录管理\n");
	printf("1.添加收入记录\n");
	printf("2.查询收入记录\n");
	printf("3.修改收入记录\n");
	printf("4.删除收入记录\n");
	printf("5.打印全部收入记录\n");
	printf("6.回到主菜单\n");
	printf("请输入序号以进行操作:");
	scanf_s("%d", &menu_selection);
	if (menu_selection == 1)
	{
		add_income_management();
	}
	else if (menu_selection == 2)
	{
		search_income_management();
	}
	else if (menu_selection == 3)
	{
		modify_income_record();
	}
	else if (menu_selection == 4)
	{
		delete_income_management();
	}
	else if (menu_selection == 5)
	{
		print_income_management();
	}
	else if (menu_selection == 6)
	{
		mainmenu();
	}
	else
	{
		printf("请输入正确的序号\n\n");
		income_management();
	}
}

void add_income_management()
{
	char confirm[2] = "a";
	char yes[2] = "y";
	char no[2] = "n";
	char Yes[2] = "Y";
	char No[2] = "N";
	printf("是否添加收入记录？(Y/N)\n");
	scanf("%s", &confirm);
	if ((strcmp(confirm, yes) == 0) || (strcmp(confirm, Yes) == 0))
	{
		//Open the file to read out last number
		FILE* record_file = fopen("record_file.bin", "rb");
		if (record_file == NULL)
		{
			printf("读取/写入文件记录失败！程序退出\n");
			exit(1);
		}
		struct record_structure read_data;
		rewind(record_file);
		int current_number = 0;
		while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
		{
			if (read_data.type == 0 || read_data.type == 1)
			{
				current_number = read_data.number;
			}
		}
		current_number = current_number + 1;
		fclose(record_file);

		//Open the file again to add record
		//New structure to add record
		FILE* write_to_record_file = fopen("record_file.bin", "ab");
		if (write_to_record_file == NULL)
		{
			printf("读取/写入文件记录失败！程序退出\n");
			exit(1);
		}

		struct record_structure add_income;
		add_income = { "member","date",1,"reason",1,0 };

		printf("请输入要添加的收入记录：\n");
		printf("输入模板：\n成员：某某某\n日期：YY/MM/DD\n数额：正整数\n事由：XXX\n");
		printf("成员:");
		scanf("%s", &add_income.member);
		printf("日期:");
		scanf("%s", &add_income.date);
		printf("数额:");
		scanf("%d", &add_income.amount);
		printf("事由:");
		scanf("%s", &add_income.reason);
		add_income.type = 0;
		add_income.number = current_number;
		int flag = 0;
		flag = fwrite(&add_income, sizeof(struct record_structure), 1, write_to_record_file);
		if (flag == 1)
		{
			printf("添加成功！\n");
		}
		else
		{
			printf("添加失败！\n");
		}

		fclose(write_to_record_file);
		income_management();
	}
	else if ((strcmp(confirm, no) == 0) || (strcmp(confirm, No) == 0))
	{
		income_management();
	}
	else
	{
		printf("请输入Y或N以确认添加收入记录\n");
		add_income_management();
	}
}

void search_income_management()
{
	printf("\n1.按成员搜索\n");
	printf("2.按日期搜索\n");
	printf("3.返回收入管理\n");
	printf("请选择操作：");
	scanf_s("%d", &menu_selection);
	if (menu_selection == 1)
	{
		search_income_by_member();
	}
	else if (menu_selection == 2)
	{
		search_income_by_date();
	}
	else if (menu_selection == 3)
	{
		income_management();
	}
	else
	{
		printf("请输入正确的序号\n\n");
		search_income_management();
	}
}

void search_income_by_member()
{
	char member_name[200] = "";
	printf("请输入要查找的成员名：");
	scanf("%s", &member_name);
	//Open the file to read out last number
	FILE* record_file = fopen("record_file.bin", "rb");
	if (record_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}
	struct record_structure read_data;
	rewind(record_file);
	int readcount = 0;
	printf("————————成员收入记录打印开始————————");
	while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
	{
		if ((strcmp(member_name, read_data.member) == 0))
		{
			if (read_data.type == 0)
			{
				printf("\n记录编号:%d\n", read_data.number);
				printf("成员:%s\n", read_data.member);
				printf("日期:%s\n", read_data.date);
				printf("数额:%d\n", read_data.amount);
				printf("事由:%s\n", read_data.reason);
				readcount = readcount + 1;
			}
		}
	}
	if (readcount == 0)
	{
		printf("\n未找到该成员的收入记录\n");
	}
	printf("————————成员收入记录打印结束————————");
	fclose(record_file);
	search_income_management();
}

void search_income_by_date()
{
	char search_date[200] = "";
	printf("请输入要查找的日期(格式：YY/MM/DD):");
	scanf("%s", &search_date);
	//Open the file to read out last number
	FILE* record_file = fopen("record_file.bin", "rb");
	if (record_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}
	struct record_structure read_data;
	rewind(record_file);
	int readcount = 0;
	printf("————————%s收入记录打印开始————————", search_date);
	while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
	{
		if ((strcmp(search_date, read_data.date) == 0))
		{
			if (read_data.type == 0)
			{
				printf("\n记录编号:%d\n", read_data.number);
				printf("成员:%s\n", read_data.member);
				printf("日期:%s\n", read_data.date);
				printf("数额:%d\n", read_data.amount);
				printf("事由:%s\n", read_data.reason);
				readcount = readcount + 1;
			}
		}
	}
	if (readcount == 0)
	{
		printf("\n未找到该日期的收入记录\n");
	}
	printf("————————%s收入记录打印结束————————", search_date);
	fclose(record_file);
	search_income_management();
}

void modify_income_record()
{
	int modify_id = 0;
	long data_position = 0; //Used to store record head position

	printf("请输入要修改的收入记录编号：");
	scanf("%d", &modify_id);

	//Open the file in rb+ mode instead of wb
	//If using wb, the whole file content will be overwritten
	FILE* modify_file = fopen("record_file.bin", "rb+");
	if (modify_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}

	//Setup search and read structure
	struct record_structure read_data;

	//Rewind pointer to start of the file
	rewind(modify_file);

	while (fread(&read_data, sizeof(struct record_structure), 1, modify_file))
	{
		if ( modify_id == read_data.number )
		{
			if (read_data.type == 0)
			{
				printf("\n已找到下列收入记录：\n\n");
				printf("记录编号:%d\n", read_data.number);
				printf("成员:%s\n", read_data.member);
				printf("日期:%s\n", read_data.date);
				printf("数额:%d\n", read_data.amount);
				printf("事由:%s\n\n", read_data.reason);

				//Get current record head position
				data_position = (ftell(modify_file)- sizeof(struct record_structure));
			}
			else
			{
				printf("未找到该编号的收入记录，请检查！\n");
				income_management();
			}
		}
	}

	//Set position indicator to the head of the modifying record
	fseek(modify_file, data_position, SEEK_SET);

	//Setup modify structure
	struct record_structure modify_income_record;
	modify_income_record = { "member","date",1,"reason",1,0 };

	printf("请重新输入该条目的内容以进行修改：\n\n");
	printf("输入模板：\n成员：某某某\n日期：YY/MM/DD\n数额：正整数\n事由：XXX\n\n");
	printf("成员:");
	scanf("%s", &modify_income_record.member);
	printf("日期:");
	scanf("%s", &modify_income_record.date);
	printf("数额:");
	scanf("%d", &modify_income_record.amount);
	printf("事由:");
	scanf("%s", &modify_income_record.reason);
	modify_income_record.type = 0;
	modify_income_record.number = modify_id;
	int flag = 0;
	flag = fwrite(&modify_income_record, sizeof(struct record_structure), 1, modify_file);
	if (flag == 1)
	{
		
		printf("\n修改成功！\n修改后记录为：\n\n");
		fseek(modify_file, data_position, SEEK_SET);
		fread(&read_data, sizeof(struct record_structure), 1, modify_file);
		printf("记录编号:%d\n", read_data.number);
		printf("成员:%s\n", read_data.member);
		printf("日期:%s\n", read_data.date);
		printf("数额:%d\n", read_data.amount);
		printf("事由:%s\n", read_data.reason);
		
		fclose(modify_file);
		income_management();
	}
	else
	{
		printf("修改失败！文件出错\n");
		exit(1);
	}
}

void delete_income_management()
{
	int modify_id = 0;
	long data_position = 0; //Used to store record head position

	printf("请输入要删除的收入记录编号：");
	scanf("%d", &modify_id);

	//Open the file in rb+ mode instead of wb
	//If using wb, the whole file content will be overwritten
	FILE* modify_file = fopen("record_file.bin", "rb+");
	if (modify_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}

	//Setup search and read structure
	struct record_structure read_data;

	//Rewind pointer to start of the file
	rewind(modify_file);

	while (fread(&read_data, sizeof(struct record_structure), 1, modify_file))
	{
		if (modify_id == read_data.number)
		{
			if (read_data.type == 0)
			{
				printf("\n已找到下列收入记录：\n\n");
				printf("记录编号:%d\n", read_data.number);
				printf("成员:%s\n", read_data.member);
				printf("日期:%s\n", read_data.date);
				printf("数额:%d\n", read_data.amount);
				printf("事由:%s\n\n", read_data.reason);

				//Get current record head position
				data_position = (ftell(modify_file) - sizeof(struct record_structure));
			}
			else
			{
				printf("未找到该编号的收入记录，请检查！\n");
				income_management();
			}
		}
	}

	//Set position indicator to the head of the modifying record
	fseek(modify_file, data_position, SEEK_SET);

	//Setup modify structure
	struct record_structure delete_income_record;

	char confirm[2] = "a";
	char yes[2] = "y";
	char no[2] = "n";
	char Yes[2] = "Y";
	char No[2] = "N";
	printf("是否删除收入记录？(Y/N)\n");
	scanf("%s", &confirm);
	if ((strcmp(confirm, yes) == 0) || (strcmp(confirm, Yes) == 0))
	{
		//Override record information and set type to 2 (deleted)
		delete_income_record = { "blank","blank",0,"reason",2,0 };

		int flag = 0;
		flag = fwrite(&delete_income_record, sizeof(struct record_structure), 1, modify_file);
		if (flag == 1)
		{

			printf("\n删除成功！\n\n");
			fclose(modify_file);
			income_management();
		}
		else
		{
			printf("删除失败！文件出错\n");
			exit(1);
		}
	}
	else if ((strcmp(confirm, no) == 0) || (strcmp(confirm, No) == 0))
	{
		printf("\n删除取消\n\n");
		income_management();
	}
	else
	{
		printf("请输入Y或N以确认删除收入记录\n");
		delete_income_management();
	}
}

void print_income_management()
{
	FILE* record_file = fopen("record_file.bin", "rb");
	if (record_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}

	printf("————————收入记录打印开始————————");

	//Create read structure pointers
	struct record_structure read_data;
	rewind(record_file);

	int readcount = 0;

	while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
	{
		if (read_data.type == 0)
		{
			printf("\n记录编号:%d\n", read_data.number);
			printf("成员:%s\n", read_data.member);
			printf("日期:%s\n", read_data.date);
			printf("数额:%d\n", read_data.amount);
			printf("事由:%s\n", read_data.reason);
			readcount = readcount + 1;
		}
	}
	if (readcount == 0)
	{
		printf("\n未找到收入记录\n");
	}
	fclose(record_file);
	printf("————————收入记录打印结束————————");
	income_management();
}

void payout_management()
{
	printf("\n支出记录管理\n");
	printf("1.添加支出记录\n");
	printf("2.查询支出记录\n");
	printf("3.修改支出记录\n");
	printf("4.删除支出记录\n");
	printf("5.打印全部支出记录\n");
	printf("6.回到主菜单\n");
	printf("请输入序号以进行操作:");
	scanf_s("%d", &menu_selection);
	if (menu_selection == 1)
	{
		add_payout_management();
	}
	else if (menu_selection == 2)
	{
		search_payout_management();
	}
	else if (menu_selection == 3)
	{
		modify_payout_record();
	}
	else if (menu_selection == 4)
	{
		delete_payout_management();
	}
	else if (menu_selection == 5)
	{
		print_payout_management();
	}
	else if (menu_selection == 6)
	{
		mainmenu();
	}

	else
	{
		printf("请输入正确的序号\n\n");
		payout_management();
	}
}

void add_payout_management()
{
	char confirm[2] = "a";
	char yes[2] = "y";
	char no[2] = "n";
	char Yes[2] = "Y";
	char No[2] = "N";
	printf("是否添加支出记录？(Y/N)\n");
	scanf("%s", &confirm);
	if ((strcmp(confirm, yes) == 0) || (strcmp(confirm, Yes) == 0))
	{
		//Open the file to read out last number
		FILE* record_file = fopen("record_file.bin", "rb");
		if (record_file == NULL)
		{
			printf("读取/写入文件记录失败！程序退出\n");
			exit(1);
		}
		struct record_structure read_data;
		rewind(record_file);
		int current_number = 0;
		while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
		{
			if (read_data.type == 0 || read_data.type == 1)
			{
				current_number = read_data.number;
			}
		}
		current_number = current_number + 1;
		fclose(record_file);

		//Open the file again to add record
		//New structure to add record
		FILE* write_to_record_file = fopen("record_file.bin", "ab");
		if (write_to_record_file == NULL)
		{
			printf("读取/写入文件记录失败！程序退出\n");
			exit(1);
		}

		struct record_structure add_payout;
		add_payout = { "member","date",1,"reason",1,0 };

		printf("请输入要添加的支出记录：\n");
		printf("输入模板：\n成员：某某某\n日期：YY/MM/DD\n数额：正整数\n事由：XXX\n");
		printf("成员:");
		scanf("%s", &add_payout.member);
		printf("日期:");
		scanf("%s", &add_payout.date);
		printf("数额:");
		scanf("%d", &add_payout.amount);
		printf("事由:");
		scanf("%s", &add_payout.reason);
		add_payout.type = 1;
		add_payout.number = current_number;
		int flag = 0;
		flag = fwrite(&add_payout, sizeof(struct record_structure), 1, write_to_record_file);
		if (flag == 1)
		{
			printf("添加成功！\n");
		}
		else
		{
			printf("添加失败！\n");
		}

		fclose(write_to_record_file);
		payout_management();
	}
	else if ((strcmp(confirm, no) == 0) || (strcmp(confirm, No) == 0))
	{
		payout_management();
	}
	else
	{
		printf("请输入Y或N以确认添加支出记录\n");
		add_payout_management();
	}
}

void search_payout_management()
{
	printf("\n1.按成员搜索\n");
	printf("2.按日期搜索\n");
	printf("3.返回支出管理\n");
	printf("请选择操作：");
	scanf_s("%d", &menu_selection);
	if (menu_selection == 1)
	{
		search_payout_by_member();
	}
	else if (menu_selection == 2)
	{
		search_payout_by_date();
	}
	else if (menu_selection == 3)
	{
		income_management();
	}
	else
	{
		printf("请输入正确的序号\n\n");
		search_income_management();
	}
}

void search_payout_by_member()
{
	char member_name[200] = "";
	printf("请输入要查找的成员名：");
	scanf("%s", &member_name);
	//Open the file to read out last number
	FILE* record_file = fopen("record_file.bin", "rb");
	if (record_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}
	struct record_structure read_data;
	rewind(record_file);
	int readcount = 0;
	printf("————————成员支出记录打印开始————————");
	while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
	{
		if ((strcmp(member_name, read_data.member) == 0))
		{
			if (read_data.type == 1)
			{
				printf("\n记录编号:%d\n", read_data.number);
				printf("成员:%s\n", read_data.member);
				printf("日期:%s\n", read_data.date);
				printf("数额:%d\n", read_data.amount);
				printf("事由:%s\n", read_data.reason);
				readcount = readcount + 1;
			}
		}
	}
	if (readcount == 0)
	{
		printf("\n未找到该成员的支出记录\n");
	}
	printf("————————成员支出记录打印结束————————");
	fclose(record_file);
	search_income_management();
}

void search_payout_by_date()
{
	char search_date[200] = "";
	printf("请输入要查找的日期(格式：YY/MM/DD):");
	scanf("%s", &search_date);
	//Open the file to read out last number
	FILE* record_file = fopen("record_file.bin", "rb");
	if (record_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}
	struct record_structure read_data;
	rewind(record_file);
	int readcount = 0;
	printf("————————%s支出记录打印开始————————", search_date);
	while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
	{
		if ((strcmp(search_date, read_data.date) == 0))
		{
			if (read_data.type == 1)
			{
				printf("\n记录编号:%d\n", read_data.number);
				printf("成员:%s\n", read_data.member);
				printf("日期:%s\n", read_data.date);
				printf("数额:%d\n", read_data.amount);
				printf("事由:%s\n", read_data.reason);
				readcount = readcount + 1;
			}
		}
	}
	if (readcount == 0)
	{
		printf("\n未找到该日期的支出记录\n");
	}
	printf("————————%s支出记录打印结束————————", search_date);
	fclose(record_file);
	search_income_management();
}

void modify_payout_record()
{

	int modify_id = 0;
	long data_position = 0; //Used to store record head position

	printf("请输入要修改的支出记录编号：");
	scanf("%d", &modify_id);

	//Open the file in rb+ mode instead of wb
	//If using wb, the whole file content will be overwritten
	FILE* modify_file = fopen("record_file.bin", "rb+");
	if (modify_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}

	//Setup search and read structure
	struct record_structure read_data;

	//Rewind pointer to start of the file
	rewind(modify_file);

	while (fread(&read_data, sizeof(struct record_structure), 1, modify_file))
	{
		if (modify_id == read_data.number)
		{
			if (read_data.type == 1)
			{
				printf("\n已找到下列支出记录：\n\n");
				printf("记录编号:%d\n", read_data.number);
				printf("成员:%s\n", read_data.member);
				printf("日期:%s\n", read_data.date);
				printf("数额:%d\n", read_data.amount);
				printf("事由:%s\n\n", read_data.reason);

				//Get current record head position
				data_position = (ftell(modify_file) - sizeof(struct record_structure));
			}
			else
			{
				printf("未找到该编号的收入记录，请检查！\n");
				income_management();
			}
		}
	}

	//Set position indicator to the head of the modifying record
	fseek(modify_file, data_position, SEEK_SET);

	//Setup modify structure
	struct record_structure modify_payout_record;
	modify_payout_record = { "member","date",1,"reason",1,0 };

	printf("请重新输入该条目的内容以进行修改：\n\n");
	printf("输入模板：\n成员：某某某\n日期：YY/MM/DD\n数额：正整数\n事由：XXX\n\n");
	printf("成员:");
	scanf("%s", &modify_payout_record.member);
	printf("日期:");
	scanf("%s", &modify_payout_record.date);
	printf("数额:");
	scanf("%d", &modify_payout_record.amount);
	printf("事由:");
	scanf("%s", &modify_payout_record.reason);
	modify_payout_record.type = 1;
	modify_payout_record.number = modify_id;
	int flag = 0;
	flag = fwrite(&modify_payout_record, sizeof(struct record_structure), 1, modify_file);
	if (flag == 1)
	{

		printf("\n修改成功！\n修改后记录为：\n\n");
		fseek(modify_file, data_position, SEEK_SET);
		fread(&read_data, sizeof(struct record_structure), 1, modify_file);
		printf("记录编号:%d\n", read_data.number);
		printf("成员:%s\n", read_data.member);
		printf("日期:%s\n", read_data.date);
		printf("数额:%d\n", read_data.amount);
		printf("事由:%s\n", read_data.reason);

		fclose(modify_file);
		income_management();
	}
	else
	{
		printf("修改失败！文件出错\n");
		exit(1);
	}
}

void delete_payout_management()
{
	int modify_id = 0;
	long data_position = 0; //Used to store record head position

	printf("请输入要删除的支出记录编号：");
	scanf("%d", &modify_id);

	//Open the file in rb+ mode instead of wb
	//If using wb, the whole file content will be overwritten
	FILE* modify_file = fopen("record_file.bin", "rb+");
	if (modify_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}

	//Setup search and read structure
	struct record_structure read_data;

	//Rewind pointer to start of the file
	rewind(modify_file);

	while (fread(&read_data, sizeof(struct record_structure), 1, modify_file))
	{
		if (modify_id == read_data.number)
		{
			if (read_data.type == 1)
			{
				printf("\n已找到下列支出记录：\n\n");
				printf("记录编号:%d\n", read_data.number);
				printf("成员:%s\n", read_data.member);
				printf("日期:%s\n", read_data.date);
				printf("数额:%d\n", read_data.amount);
				printf("事由:%s\n\n", read_data.reason);

				//Get current record head position
				data_position = (ftell(modify_file) - sizeof(struct record_structure));
			}
			else
			{
				printf("未找到该编号的支出记录，请检查！\n");
				income_management();
			}
		}
	}

	//Set position indicator to the head of the modifying record
	fseek(modify_file, data_position, SEEK_SET);

	//Setup modify structure
	struct record_structure delete_payout_record;

	char confirm[2] = "a";
	char yes[2] = "y";
	char no[2] = "n";
	char Yes[2] = "Y";
	char No[2] = "N";
	printf("是否删除支出记录？(Y/N)\n");
	scanf("%s", &confirm);
	if ((strcmp(confirm, yes) == 0) || (strcmp(confirm, Yes) == 0))
	{
		//Override record information and set type to 2 (deleted)
		delete_payout_record = { "blank","blank",0,"reason",2,0 };

		int flag = 0;
		flag = fwrite(&delete_payout_record, sizeof(struct record_structure), 1, modify_file);
		if (flag == 1)
		{
			printf("\n删除成功！\n\n");
			fclose(modify_file);
			income_management();
		}
		else
		{
			printf("删除失败！文件出错\n");
			exit(1);
		}
	}
	else if ((strcmp(confirm, no) == 0) || (strcmp(confirm, No) == 0))
	{
		printf("\n删除取消\n\n");
		income_management();
	}
	else
	{
		printf("请输入Y或N以确认删除收入记录\n");
		delete_income_management();
	}
}

void print_payout_management()
{
	FILE* record_file = fopen("record_file.bin", "rb");
	if (record_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}

	printf("————————支出记录打印开始————————");

	//Create read structure pointers
	struct record_structure read_data;
	rewind(record_file);

	int readcount = 0;

	while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
	{
		if (read_data.type == 1)
		{
			printf("\n记录编号:%d\n", read_data.number);
			printf("成员:%s\n", read_data.member);
			printf("日期:%s\n", read_data.date);
			printf("数额:%d\n", read_data.amount);
			printf("事由:%s\n", read_data.reason);
			readcount = readcount + 1;
		}
	}
	if (readcount == 0)
	{
		printf("\n未找到支出记录\n");
	}
	fclose(record_file);
	printf("————————支出记录打印结束————————");
	payout_management();
}

void print_all()
{
	FILE* record_file = fopen("record_file.bin", "rb");
	if (record_file == NULL)
	{
		printf("读取/写入文件记录失败！程序退出\n");
		exit(1);
	}

	printf("————————记录打印开始————————");

	//Create read structure pointers
	struct record_structure read_data;
	rewind(record_file);

	int readcount = 0;

	while (fread(&read_data, sizeof(struct record_structure), 1, record_file))
	{
		if (read_data.type == 2)
		{
			continue;
		}
		printf("\n记录编号:%d\n", read_data.number);
		if (read_data.type == 1)
		{
			printf("记录类型:支出\n");
		}
		else if (read_data.type == 0)
		{
			printf("记录类型:收入\n");
		}
		printf("成员:%s\n", read_data.member);
		printf("日期:%s\n", read_data.date);
		printf("数额:%d\n", read_data.amount);
		printf("事由:%s\n", read_data.reason);
		readcount = readcount + 1;
	}
	fclose(record_file);
	printf("————————记录打印结束————————");
	mainmenu();
}

void exit_menu()
{
	printf("\n系统已退出\n");
	exit(1);
}