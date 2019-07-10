#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define NSTUDS 100;  //maximum of records of students
#define getSex(num) ((num) == (1) ? ("男") : ("女"))

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
				printf("您想使用哪项功能>>>");
				char choice;
				scanf("%s", &choice);
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

		int fd = open("stu.txt", O_RDONLY);
		struct stat buf;
		fstat(fd, &buf);
		if(buf.st_size == 0){
				printf("暂时还没有数据呢！\n");
				return 0;
		}
		close(fd);

		char id[12];
		printf("请输入待查看学生编号：");
		scanf("%s", id);

		fseek(fp, (atoi(id) - 1) * sizeof(stu_info), SEEK_SET);
		fread(&stu, sizeof(stu_info), 1, fp);
		printf("学号：%s\n姓名：%s\n性别：%s\n电话：%s\n", stu.stu_num, stu.name, getSex(stu.sex), stu.mobile_phone);

		fclose(fp);
		return 1;
		

}

int insert()
{
		FILE *fp = fopen("stu.txt", "a+");

		printf("学号：");
		scanf("%s", stu.stu_num);
		printf("姓名：");
		scanf("%s", stu.name);
		printf("性别：");
		scanf("%hd", &stu.sex);
		printf("联系电话：");
		scanf("%s", stu.mobile_phone);

		if(fwrite(&stu, sizeof(stu_info), 1, fp) <= 0)
				exit(EXIT_FAILURE);

		printf("增加学生信息成功！\n");
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
		scanf("%s", id);
		fseek(fp, (atoi(id) - 1) * sizeof(stu_info), SEEK_SET);
		fread(&stu, sizeof(stu_info), 1, fp);

		printf("您想修改哪一部分？1姓名 2电话 3取消");
		char choice;
		scanf("%s", &choice);
		switch(choice){
				case '1':
						printf("请输入新的姓名：");
						scanf("%s", stu.name);
						break;
				case '2':
						printf("请输入新的电话：");
						scanf("%s", stu.mobile_phone);
						break;
				case '3':
						return 0;
				default:
						printf("请输入正确序号1或2");
						break;
		}

		fseek(fp, (atoi(id) - 1) * sizeof(stu_info), SEEK_SET);
		fwrite(&stu, sizeof(stu_info), 1, fp);

		printf("修改学生信息成功！\n");
		fclose(fp);
		return 1;
}

int delete()
{
		/*
		FILE *fp = fopen("stu.txt", "r+");

		char id[12];
		printf("请输入待删除学生学号：");
		fgets(id, 12, stdin);

		fclose(fp);
		*/
		printf("暂未实现！敬请期待！\n");
		return 1;
}
