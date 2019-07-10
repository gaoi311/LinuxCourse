#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define NSTUDS 100;  //maximum of records of students

typedef struct{
		char stu_num[12];
		char name[10];
		short int sex;  //0 female, 1 male
		char mobile_phone[12];
}stu_info;

int query();
int insert();
int modify();
int delete();

stu_info stu;

int main()
{
		FILE *fp;
		fp = fopen("stu.txt", "r+");
		printf("****************************************\n");
		printf("*       欢迎进入学生信息管理系统       *\n");
		printf("*                                      *\n");
		printf("*           1.查看学生信息             *\n");
		printf("*           2.插入学生信息             *\n");
		printf("*           3.修改学生信息             *\n");
		printf("*           4.删除学生信息             *\n");
		printf("*           5.退出系统                 *\n");
		printf("*                                      *\n");
		printf("****************************************\n");

		while(1){			
				printf("您想使用哪项功能>>>\n");
				char choice = fgetc(stdin);
				switch(choice){
						case '1':
								query();
								break;
						case '2':
								insert();
								break;
						case '3':
								modify();
								break;
						case '4':
								delete();
								break;
						case '5':
								exit(0);
						default:
								printf("请输入正确的序号！");
								break;
				}
		}
		exit(0);
}

int query()
{
		FILE *fp =  fopen("stu.txt", "r");

		struct stat buf;
		int nstuds;

		int fd = open("stu.txt", O_RDONLY);

		fstat(fd, &buf);
		close(fd);
		nstuds = buf.st_size / sizeof(stu_info);
		if(nstuds = 0){
				printf("暂时还没有数据呢！");
				return 0;
		}
		stu_info nstu[nstuds];

		if(fread(&nstu[0], sizeof(stu_info), nstuds, fp) < 0)
				exit(EXIT_FAILURE);
		if(fwrite(&nstu[0], sizeof(stu_info), nstuds, stdout) < 0)
				exit(EXIT_FAILURE);

		return 1;
		

}

int insert()
{
		FILE *fp = fopen("stu.txt", "a+");

		printf("学号：");
		fgets(stu.stu_num, 12, stdin);
		printf("姓名：");
		fgets(stu.name, 10, stdin);
		printf("性别：");
		stu.sex = fgetc(stdin);
		printf("联系电话：");
		fgets(stu.mobile_phone, 12, stdin);

		if(fwrite(&stu, sizeof(stu_info), 1, fp) <= 0)
				exit(EXIT_FAILURE);

		fclose(fp);
		return 1;
}

int modify()
{
		FILE *fp = fopen("stu.txt", "r+");

		char id[12];
		char name[10];
		char phone[12];
		printf("请输入待修改学生学号：");
		fgets(id, 12, stdin);
		fseek(fp, atoi(id) * sizeof(stu_info), SEEK_SET);
		fread(&stu, sizeof(stu_info), 1, fp);

		printf("您想修改哪一部分？1姓名 2电话 3取消");
		char choice = fgetc(stdin);
		switch(choice){
				case '1':
						printf("请输入新的姓名：");
						fgets(name, 10, stdin);
						strcpy(stu.name, name);
						break;
				case '2':
						printf("请输入新的电话：");
						fgets(phone, 12, stdin);
						strcpy(stu.mobile_phone, phone);
						break;
				case '3':
						return 0;
				default:
						printf("请输入正确序号1或2");
						break;
		}

		fseek(fp, atoi(id) * sizeof(stu_info), SEEK_SET);
		fwrite(&stu, sizeof(stu_info), 1, fp);

		fclose(fp);
		return 1;
}

int delete()
{
		FILE *fp = fopen("stu.txt", "r+");

		char id[12];
		printf("请输入待删除学生学号：");
		fgets(id, 12, stdin);

		fclose(fp);
		return 1;
}
