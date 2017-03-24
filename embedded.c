#include <my_global.h>
#include <mysql.h>
#include <stdio.h>

struct employee
{
	char Fname[15], Minit, Lname[15], Address[30], Sex, Super_ssn[9],Ssn[9], Bdate[10], Mobile_no[10], Job[12];
	float Salary;
	int Dno;
};

struct department
{
	char Dname[15],Mgr_ssn[9],Mgr_start_date[10];
	int Dnumber;
};

struct project
{
	char Pname[15], Plocation[15];
	int Pnumber, Dnum;
};

struct works_on
{
	char Essn[9];
	int Pno;
	float Hours;
};

struct dept_locations
{
	int Dnumber
	char Dlocation[15];
};

struct dependent
{
	char Essn[9], Dependent_name[15], Sex;
	char Relationship[8], Bdate[10];
};

void finish_with_error(MYSQL *con)
{
	fprintf(stderr,"%s\n",mysql_error(con));
	mysql_close(con);
	exit(1);
}

void print_result(MYSQL *con)
{
	MYSQL_RES *result=mysql_store_result(con);
	int num_fields,i;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	if(result==NULL)
		finish_with_error(con);

	num_fields = mysql_num_fields(result);

	while(row=mysql_fetch_row(result))
	{
		for(i=0;i<num_fields;i++)
		{
			if(i==0)
			{
				while(field = mysql_fetch_field(result))
				{
					printf("%s ",field->name);
				}
				printf("\n");
			}
			printf("%s ",row[i] ? row[i]:"NULL");
		}
	}

	mysql_free_result(result);
}
void show_all_tables(MYSQL *con)
{
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPARTMENT"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM PROJECT"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM WORKS_ON"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPENDENT"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPT_LOCATIONS"))
		finish_with_error(con);
	print_result(con);
	printf("\n\n");
}

void insert_employee(MYSQL *con)
{

	char query_statement[100];
	struct employee e1;
	system("clear");
	printf("\nEnter employee details: ");
	printf("\nFirst name: ");
	scanf("%s",e1.Fname);
	printf("\nMiddle Initial: ");
	scanf(" %c",&e1.Minit);
	printf("\nLast Name: ");
	scanf("%s",e1.Lname);
	printf("\nSSN: ");
	scanf("%s",e1.Ssn);
	printf("\nAddress: ");
	scanf("%s",e1.Address);
	printf("Mobile no: ");
	scanf("%s",e1.Mobile_no);
	printf("\nBirth date: ");
	scanf("%s",e1.Bdate);
	printf("\nGender: ");
	scanf(" %c",&e1.Sex);
	printf("\nJob: ");
	scanf("%s",e1.Job);
	printf("\nSalary: ");
	scanf("%f",&e1.Salary);
	printf("\nDepartment No: ");
	scanf("%d",&e1.Dno);
	printf("\nSupervisor SSN: ");
	scanf("%s",e1.Super_ssn);

	snprintf(query_statement,200,"INSERT INTO EMPLOYEE VALUES (\'%s\',\'%c\',\'%s\',\'%s\',\'%s\',\'%s\',\'%c\',\'%.2f\',\'%s\',\'%d\',\'%s\',\'%s\')",e1.Fname,e1.Minit,e1.Lname,e1.Ssn,e1.Bdate,e1.Address,e1.Sex,e1.Salary,e1.Super_ssn,e1.Dno,e1.Mobile_no,e1.Job);

	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");

	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void insert_department(MYSQL *con)
{
	struct department d1;
	char query_statement[200];

	printf("\nFill in details of new department: ");
	printf("\nDepartment Name: ");
	scanf("%s",d1.Dname);
	printf("\nDepartment Number: ");
	scanf("%d",&d1.Dnumber);
	printf("\nManager's SSN: ");
	scanf("%s",d1.Mgr_ssn);
	printf("\nStarting Date of manager: ");
	scanf("%s",d1.Mgr_start_date);

	snprintf(query_statement,200,"INSERT INTO DEPARTMENT VALUES (\'%s\',\'%d\',\'%s\',\'%s\')",d1.Dname,d1.Dnumber,d1.Mgr_ssn,d1.Mgr_start_date);

	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPARTMENT "))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void insert_project(MYSQL *con)
{
	struct project p1;
	char query_statement[200];

	printf("\nFill in details of new department: ");
	printf("\nProject Name: ");
	scanf("%s",p1.Pname);
	printf("\nProject Number: ");
	scanf("%d",&p1.Pnumber);
	printf("\nProject Location: ");
	scanf("%s",p1.Plocation);
	printf("\nDepartment Number: ");
	scanf("%d",&p1.Dnum);

	snprintf(query_statement,200,"INSERT INTO PROJECT VALUES (\'%s\',\'%d\',\'%s\',\'%d\')",p1.Pname,p1.Pnumber,p1.Plocation,p1.Dnum);

	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM PROJECT "))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void insert_works_on(MYSQL *con)
{
	struct works_on w1;
	char query_statement[200];

	printf("\nFill in details of new department: ");
	printf("\nEmployee SSN: ");
	scanf("%s",w1.Essn);
	printf("\nProject Number: ");
	scanf("%d",&w1.Pno);
	printf("\nHours Spent / Week: ");
	scanf("%f",&w1.Hours);

	snprintf(query_statement,200,"INSERT INTO WORKS_ON VALUES (\'%s\',\'%d\',\'%.2f\')",w1.Essn,w1.Pno,w1.Hours);

	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM WORKS_ON "))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void insert_dept_locations(MYSQL *con)
{
	struct dept_locations d1;
	char query_statement[200];

	printf("\nFill in details of new department: ");
	printf("\nDepartment Number: ");
	scanf("%d",&d1.Dnumber);
	printf("\nDepartment Location: ");
	scanf("%s",d1.Dlocation);

	snprintf(query_statement,200,"INSERT INTO DEPT_LOCATIONS VALUES (\'%d\',\'%s\')",d1.Dnumber,d1.Dlocation);

	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPT_LOCATIONS "))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void insert_dependents(MYSQL *con)
{
	struct dependent d1;
	char query_statement[200];

	printf("\nFill in details of new department: ");
	printf("\nEmployee SSN: ");
	scanf("%s",d1.Essn);
	printf("\nDependent Name: ");
	scanf("%s",d1.Dependent_name);
	printf("\nDependent Gender: ");
	scanf(" %c",&d1.Sex);
	printf("\nBirthday of dependent: ");
	scanf("%s",d1.Bdate);
	printf("\nRelationship with dependent: ");
	scanf("%s",d1.Relationship);

	snprintf(query_statement,200,"INSERT INTO DEPENDENT VALUES (\'%s\',\'%s\',\'%c\',\'%s\',\'%s\')",d1.Essn,d1.Dependent_name,d1.Sex,d1.Bdate,d1.Relationship);

	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPENDENT "))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void delete_employee(MYSQL *con)
{
	char ssn[9];
	char query_statement[200];

	printf("\nEnter SSN: ");
	scanf("%s",ssn);
	snprintf(query_statement,200,"DELETE FROM EMPLOYEE WHERE Ssn LIKE \'%s\'",ssn);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void delete_department(MYSQL *con)
{
	int Dnumber;
	char query_statement[200];

	printf("\nEnter Department Number: ");
	scanf("%d",&Dnumber);
	snprintf(query_statement,200,"DELETE FROM DEPARTMENT WHERE Dnumber LIKE \'%d\'",Dnumber);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPARTMENT"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void delete_project(MYSQL *con)
{
	int Pnumber;
	char query_statement[200];

	printf("\nEnter Project Number: ");
	scanf("%d",&Pnumber);
	snprintf(query_statement,200,"DELETE FROM PROJECT WHERE Pnumber = %d",Pnumber);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM PROJECT"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void delete_works_on(MYSQL *con)
{
	char Essn[9];
	int Pno;
	char query_statement[200];

	printf("\nEnter SSN: ");
	scanf("%s",Essn);
	printf("\nEnter Project number: ");
	scanf("%d",&Pno);
	snprintf(query_statement,200,"DELETE FROM WORKS_ON WHERE Essn LIKE \'%s\' AND Pno = %d",Essn,Pno);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM WORKS_ON"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void delete_dept_locations(MYSQL *con)
{
	char Dlocation[15];
	int Dnumber;
	char query_statement[200];

	printf("\nEnter Department Number: ");
	scanf("%d",&Dnumber);
	printf("\nEnter Department Location: ");
	scanf("%s",Dlocation);
	snprintf(query_statement,200,"DELETE FROM DEPT_LOCATIONS WHERE Dlocation LIKE \'%s\' AND Dnumber = %d",Dlocation,Dnumber);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPT_LOCATIONS"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void delete_dependents(MYSQL *con)
{
	char Essn[9];
	char Dependent_name[15];
	char query_statement[200];

	printf("\nEnter SSN: ");
	scanf("%s",Essn);
	printf("\nEnter Dependent name: ");
	scanf("%s",Dependent_name);
	snprintf(query_statement,200,"DELETE FROM DEPENDENT WHERE Essn LIKE \'%s\' AND Dependent_name LIKE \'%s\'",Essn,Dependent_name);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPENDENT"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void update_salary(MYSQL *con)
{
	char Ssn[9];
	float Salary;
	char query_statement[200];

	printf("\nEnter SSN: ");
	scanf("%s",Ssn);
	printf("\nSalary: ");
	scanf("%f",&Salary);
	snprintf(query_statement,200,"UPDATE EMPLOYEE SET Salary = %.2f WHERE Ssn LIKE \'%s\'",Salary,Ssn);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");

}

void update_dnum(MYSQL *con)
{
	char Ssn[9];
	int Dno;
	char query_statement[200];

	printf("\nEnter SSN: ");
	scanf("%s",Ssn);
	printf("\nDepartment Number: ");
	scanf("%d",&Dno);
	snprintf(query_statement,200,"UPDATE EMPLOYEE SET Dno = %d WHERE Ssn LIKE \'%s\'",Dno,Ssn);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");

}

void update_super_ssn(MYSQL *con)
{
	char Ssn[9];
	char Super_ssn[9];
	char query_statement[200];

	printf("\nEnter SSN: ");
	scanf("%s",Ssn);
	printf("\nSupervisor SSN: ");
	scanf("%s",Super_ssn);
	snprintf(query_statement,200,"UPDATE EMPLOYEE SET Super_ssn = %s WHERE Ssn LIKE \'%s\'",Super_ssn,Ssn);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");

}

void update_address(MYSQL *con)
{
	char Ssn[9];
	char Address[30];
	char query_statement[200];

	printf("\nEnter SSN: ");
	scanf("%s",Ssn);
	printf("\nAddress: ");
	scanf("%s",Address);
	snprintf(query_statement,200,"UPDATE EMPLOYEE SET Address = \'%s\' WHERE Ssn LIKE \'%s\'",Address,Ssn);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}

void update_employee(MYSQL *con)
{
	int choice;
	while(1)
	{
		printf("\n1. Update Salary\n2.Update Supervisor SSN\n3.Update Department Number \n4. Address\n5.Back");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1: update_salary(con);
					break;

			case 2: update_super_ssn(con);
					break;

			case 3: update_dnum(con);
					break;

			case 4: update_address(con);
					break;

			case 5: return;
		}
	}
}

void update_department(MYSQL *con)
{
	int Dnumber;
	char Mgr_ssn[9];
	char query_statement[200];

	printf("\nEnter Department Number: ");
	scanf("%d",&Dnumber);
	printf("\nManager SSN: ");
	scanf("%s",Mgr_ssn);
	snprintf(query_statement,200,"UPDATE DEPARTMENT SET Mgr_ssn = \'%s\' WHERE Dnumber = %d",Mgr_ssn,Dnumber);
	if(mysql_query(con,query_statement))
		finish_with_error(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPARTMENT"))
		finish_with_error(con);
	print_result(con);

	printf("\n\n");
}



void insert(MYSQL *con)
{
	int choice;
	while(1)
	{
		printf("\n1. Employee\n2. Department\n3. Project \n4. Works_on \n5. Department Location\n6. Dependents\n7. Back to main menu");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		system("clear");

		switch(choice)
		{
			case 1: insert_employee(con);
					break;

			case 2: insert_department(con);
					break;

			case 3: insert_project(con);
					break;

			case 4: insert_works_on(con);
					break;

			case 5: insert_dept_locations(con);
					break;

			case 6: insert_dependents(con);
					break;

			case 7: return;
		}
	}
}

void delete(MYSQL *con)
{
	int choice;
	while(1)
	{
		printf("\n1. Employee\n2. Department\n3. Project \n4. Works_on \n5. Department Location\n6. Dependents\n7. Back to main menu");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		system("clear");

		switch(choice)
		{
			case 1: delete_employee(con);
					break;

			case 2: delete_department(con);
					break;

			case 3: delete_project(con);
					break;

			case 4: delete_works_on(con);
					break;

			case 5: delete_dept_locations(con);
					break;

			case 6: delete_dependents(con);
					break;

			case 7: return;
		}
	}
}

void update(MYSQL *con)
{
	int choice;
	while(1)
	{
		printf("\n1. Employee\n2. Department\n3. Back to main menu");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		system("clear");

		switch(choice)
		{
			case 1: update_employee(con);
					break;

			case 2: update_department(con);
					break;

			case 3: return;
		}
	}
}



void main(void)
{
	MYSQL *con = mysql_init(NULL);

	if(con==NULL)
	{
		fprintf(stderr,"\nmysql_init() failed\n");
		exit(1);
	}

	if(mysql_real_connect(con,"localhost","james","password","COMPANY",0,NULL,0)==NULL)
		finish_with_error(con);

	show_all_tables(con);

	int choice;
	while(1)
	{
		printf("\n1. Insert\n2. Delete\n3. Update\n4. Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		system("clear");
		switch(choice)
		{
			case 1:	insert(con);
					break;

			case 2: delete(con);
					break;

			case 3: update(con);
					break;

			/* case 4: filter(con); */
			/* 		break; */

			case 4: mysql_close(con);
					exit(1);
		}

	}
}
