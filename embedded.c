#include <my_global.h>
#include <mysql.h>
#include <stdio.h>

void finishQuery(MYSQL *con) {
	fprintf(stderr,"%s\n",mysql_error(con));
	mysql_close(con);
	exit(1);
}

void printResult(MYSQL *con) {
	MYSQL_RES *result=mysql_store_result(con);
	int num_fields,i;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	if(result==NULL)
		finishQuery(con);
	num_fields = mysql_num_fields(result);
	while(row=mysql_fetch_row(result)) {
		for(i=0;i<num_fields;i++) {
			if(i==0) {
				while(field = mysql_fetch_field(result))
					printf("%s ",field->name);
				printf("\n");
			}
			printf("%s ",row[i] ? row[i]:"NULL");
		}
	}
	mysql_free_result(result);
}

void showTable(MYSQL *con, char *tablename) {
	printf("\n\n");
	char query_statement[2000];
	snprintf(query_statement,500,"SELECT * FROM %s", tablename);
	if(mysql_query(con, query_statement))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void showAllTables(MYSQL *con) {
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPARTMENT"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM PROJECT"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM WORKS_ON"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPENDENT"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPT_LOCATIONS"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void insertEmployee(MYSQL *con) {
	char query_statement[1000];
	char Fname[15], Minit, Lname[15], Address[30], Sex, Super_ssn[9],Ssn[9], Bdate[10], Mobile_no[10], Job[12];
	float Salary;
	int Dno;
	showTable(con, "EMPLOYEE");
	printf("\nEnter employee details: ");
	printf("\nFirst name: ");
	scanf("%s",Fname);
	printf("\nMiddle Initial: ");
	scanf(" %c",&Minit);
	printf("\nLast Name: ");
	scanf("%s",Lname);
	printf("\nSSN: ");
	scanf("%s",Ssn);
	printf("\nAddress: ");
	scanf("%s",Address);
	printf("Mobile no: ");
	scanf("%s",Mobile_no);
	printf("\nBirth date: ");
	scanf("%s",Bdate);
	printf("\nGender: ");
	scanf(" %c",&Sex);
	printf("\nJob: ");
	scanf("%s",Job);
	printf("\nSalary: ");
	scanf("%f",&Salary);
	printf("\nDepartment No: ");
	scanf("%d",&Dno);
	printf("\nSupervisor SSN: ");
	scanf("%s",Super_ssn);
	snprintf(query_statement,500,"INSERT INTO EMPLOYEE VALUES (\'%s\',\'%c\',\'%s\',\'%s\',\'%s\',\'%s\',\'%c\',\'%.2f\',\'%s\',\'%d\',\'%s\',\'%s\')",Fname,Minit,Lname,Ssn,Bdate,Address,Sex,Salary,Super_ssn,Dno,Mobile_no,Job);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void insertDepartment(MYSQL *con) {
	showTable(con, "DEPARTMENT");
	char Dname[15],Mgr_ssn[9],Mgr_start_date[10];
	int Dnumber;
	char query_statement[2000];
	printf("\nFill in details of new department: ");
	printf("\nDepartment Name: ");
	scanf("%s",Dname);
	printf("\nDepartment Number: ");
	scanf("%d",&Dnumber);
	printf("\nManager's SSN: ");
	scanf("%s",Mgr_ssn);
	printf("\nStarting Date of manager: ");
	scanf("%s",Mgr_start_date);
	snprintf(query_statement,600,"INSERT INTO DEPARTMENT VALUES (\'%s\',\'%d\',\'%s\',\'%s\')",Dname,Dnumber,Mgr_ssn,Mgr_start_date);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPARTMENT "))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void insertProject(MYSQL *con) {
	showTable(con, "PROJECT");
	char Pname[15], Plocation[15];
	int Pnumber, Dnum;
	char query_statement[2000];
	printf("\nFill in details of new department: ");
	printf("\nProject Name: ");
	scanf("%s",Pname);
	printf("\nProject Number: ");
	scanf("%d",&Pnumber);
	printf("\nProject Location: ");
	scanf("%s",Plocation);
	printf("\nDepartment Number: ");
	scanf("%d",&Dnum);
	snprintf(query_statement,600,"INSERT INTO PROJECT VALUES (\'%s\',\'%d\',\'%s\',\'%d\')",Pname,Pnumber,Plocation,Dnum);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM PROJECT "))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void insertWorksOn(MYSQL *con) {
	showTable(con, "WORKS_ON");
	char Essn[9];
	int Pno;
	float Hours;
	char query_statement[2000];
	printf("\nFill in details of new department: ");
	printf("\nEmployee SSN: ");
	scanf("%s",Essn);
	printf("\nProject Number: ");
	scanf("%d",&Pno);
	printf("\nHours Spent / Week: ");
	scanf("%f",&Hours);
	snprintf(query_statement,600,"INSERT INTO WORKS_ON VALUES (\'%s\',\'%d\',\'%.2f\')",Essn,Pno,Hours);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM WORKS_ON "))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void insertDeptLocations(MYSQL *con) {
	showTable(con, "DEPT_LOCATIONS");
	int Dnumber;
	char Dlocation[15];
	char query_statement[2000];
	printf("\nFill in details of new department: ");
	printf("\nDepartment Number: ");
	scanf("%d",&Dnumber);
	printf("\nDepartment Location: ");
	scanf("%s",Dlocation);
	snprintf(query_statement,600,"INSERT INTO DEPT_LOCATIONS VALUES (\'%d\',\'%s\')",Dnumber,Dlocation);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPT_LOCATIONS "))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void insertDependents(MYSQL *con) {
	showTable(con, "DEPENDENTS");
	char Essn[9], Dependent_name[15], Sex;
	char Relationship[8], Bdate[10];
	char query_statement[2000];
	printf("\nFill in details of new department: ");
	printf("\nEmployee SSN: ");
	scanf("%s",Essn);
	printf("\nDependent Name: ");
	scanf("%s",Dependent_name);
	printf("\nDependent Gender: ");
	scanf(" %c",&Sex);
	printf("\nBirthday of dependent: ");
	scanf("%s",Bdate);
	printf("\nRelationship with dependent: ");
	scanf("%s",Relationship);
	snprintf(query_statement,600,"INSERT INTO DEPENDENT VALUES (\'%s\',\'%s\',\'%c\',\'%s\',\'%s\')",Essn,Dependent_name,Sex,Bdate,Relationship);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPENDENT "))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void deleteEmployee(MYSQL *con) {
	showTable(con, "EMPLOYEE");
	char ssn[9];
	char query_statement[2000];
	printf("\nEnter SSN: ");
	scanf("%s",ssn);
	snprintf(query_statement,600,"DELETE FROM EMPLOYEE WHERE Ssn LIKE \'%s\'",ssn);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void deleteDepartment(MYSQL *con) {
	showTable(con, "DEPARTMENT");
	int Dnumber;
	char query_statement[2000];
	printf("\nEnter Department Number: ");
	scanf("%d",&Dnumber);
	snprintf(query_statement,600,"DELETE FROM DEPARTMENT WHERE Dnumber LIKE \'%d\'",Dnumber);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPARTMENT"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void deleteProject(MYSQL *con) {
	int Pnumber;
	char query_statement[2000];
	printf("\nEnter Project Number: ");
	scanf("%d",&Pnumber);
	snprintf(query_statement,600,"DELETE FROM PROJECT WHERE Pnumber = %d",Pnumber);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM PROJECT"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void deleteWorksOn(MYSQL *con) {
	showTable(con, "WORKS_ON");
	char Essn[9];
	int Pno;
	char query_statement[2000];
	printf("\nEnter SSN: ");
	scanf("%s",Essn);
	printf("\nEnter Project number: ");
	scanf("%d",&Pno);
	snprintf(query_statement,600,"DELETE FROM WORKS_ON WHERE Essn LIKE \'%s\' AND Pno = %d",Essn,Pno);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM WORKS_ON"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void deleteDeptLocations(MYSQL *con) {
	showTable(con, "DEPT_LOCATIONS");
	char Dlocation[15];
	int Dnumber;
	char query_statement[2000];
	printf("\nEnter Department Number: ");
	scanf("%d",&Dnumber);
	printf("\nEnter Department Location: ");
	scanf("%s",Dlocation);
	snprintf(query_statement,600,"DELETE FROM DEPT_LOCATIONS WHERE Dlocation LIKE \'%s\' AND Dnumber = %d",Dlocation,Dnumber);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPT_LOCATIONS"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void deleteDependents(MYSQL *con) {
	showTable(con, "DEPENDENTS");
	char Essn[9];
	char Dependent_name[15];
	char query_statement[2000];
	printf("\nEnter SSN: ");
	scanf("%s",Essn);
	printf("\nEnter Dependent name: ");
	scanf("%s",Dependent_name);
	snprintf(query_statement,600,"DELETE FROM DEPENDENT WHERE Essn LIKE \'%s\' AND Dependent_name LIKE \'%s\'",Essn,Dependent_name);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPENDENT"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

/* void update(MYSQL *con) { */
/* 	showTable(con, "EMPLOYEE"); */
/* 	char data[100]; */
/* 	float Salary; */
/* 	char query_statement[2000]; */
/* 	printf("\nEnter SSN: "); */
/* 	scanf("%s",Ssn); */
/* 	printf("\nSalary: "); */
/* 	scanf("%f",&Salary); */
/* 	snprintf(query_statement,600,"UPDATE EMPLOYEE SET Salary = %.2f WHERE Ssn LIKE \'%s\'",Salary,Ssn); */
/* 	if(mysql_query(con,query_statement)) */
/* 		finishQuery(con); */
/* 	system("clear"); */
/* 	printf("\n\n"); */
/* 	if(mysql_query(con,"SELECT * FROM EMPLOYEE")) */
/* 		finishQuery(con); */
/* 	printResult(con); */
/* 	printf("\n\n"); */
/* } */

void updateSalary(MYSQL *con) {
	float Salary;
	char Ssn[9];
	int Dno;
	char query_statement[2000];
	printf("\nEnter SSN: ");
	scanf("%s",Ssn);
	printf("\nSalary: ");
	scanf("%f",&Salary);
	snprintf(query_statement,600,"UPDATE EMPLOYEE SET Salary = %f WHERE Ssn LIKE \'%s\'",Salary,Ssn);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");

}

void updateDnum(MYSQL *con) {
	char Ssn[9];
	int Dno;
	char query_statement[2000];
	printf("\nEnter SSN: ");
	scanf("%s",Ssn);
	printf("\nDepartment Number: ");
	scanf("%d",&Dno);
	snprintf(query_statement,600,"UPDATE EMPLOYEE SET Dno = %d WHERE Ssn LIKE \'%s\'",Dno,Ssn);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");

}

void updateSuperSsn(MYSQL *con) {
	char Ssn[9];
	char Super_ssn[9];
	char query_statement[2000];
	printf("\nEnter SSN: ");
	scanf("%s",Ssn);
	printf("\nSupervisor SSN: ");
	scanf("%s",Super_ssn);
	snprintf(query_statement,600,"UPDATE EMPLOYEE SET Super_ssn = %s WHERE Ssn LIKE \'%s\'",Super_ssn,Ssn);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void updateAddress(MYSQL *con) {
	char Ssn[9];
	char Address[30];
	char query_statement[2000];
	printf("\nEnter SSN: ");
	scanf("%s",Ssn);
	printf("\nAddress: ");
	scanf("%s",Address);
	snprintf(query_statement,600,"UPDATE EMPLOYEE SET Address = \'%s\' WHERE Ssn LIKE \'%s\'",Address,Ssn);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM EMPLOYEE"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void updateEmployee(MYSQL *con) {
	showTable(con, "EMPLOYEE");
	int choice;
	while(1) {
		printf("\n1. Update Salary\n2.Update Supervisor SSN\n3.Update Department Number \n4. Address\n5.Back");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		switch(choice) {
			case 1: updateSalary(con); break;
			case 2: updateSuperSsn(con); break;
			case 3: updateDnum(con); break;
			case 4: updateAddress(con); break;
			case 5: return;
		}
	}
}

void updateDepartment(MYSQL *con) {
	showTable(con, "DEPARTMENT");
	int Dnumber;
	char Mgr_ssn[9];
	char query_statement[200];
	printf("\nEnter Department Number: ");
	scanf("%d",&Dnumber);
	printf("\nManager SSN: ");
	scanf("%s",Mgr_ssn);
	snprintf(query_statement,200,"UPDATE DEPARTMENT SET Mgr_ssn = \'%s\' WHERE Dnumber = %d",Mgr_ssn,Dnumber);
	if(mysql_query(con,query_statement))
		finishQuery(con);
	system("clear");
	printf("\n\n");
	if(mysql_query(con,"SELECT * FROM DEPARTMENT"))
		finishQuery(con);
	printResult(con);
	printf("\n\n");
}

void insert(MYSQL *con) {
	int choice;
	while(1) {
		printf("\n1. Employee\n2. Department\n3. Project \n4. Works_on \n5. Department Location\n6. Dependents\n7. Back to main menu");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		system("clear");
		switch(choice) {
			case 1: insertEmployee(con); break;
			case 2: insertDepartment(con); break;
			case 3: insertProject(con); break;
			case 4: insertWorksOn(con); break;
			case 5: insertDeptLocations(con); break;
			case 6: insertDependents(con); break;
			case 7: return;
		}
	}
}

void delete(MYSQL *con) {
	int choice;
	while(1) {
		printf("\n1. Employee\n2. Department\n3. Project \n4. Works_on \n5. Department Location\n6. Dependents\n7. Back to main menu");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		system("clear");
		switch(choice) {
			case 1: deleteEmployee(con); break;
			case 2: deleteDepartment(con); break;
			case 3: deleteProject(con); break;
			case 4: deleteWorksOn(con); break;
			case 5: deleteDeptLocations(con); break;
			case 6: deleteDependents(con); break;
			case 7: return;
		}
	}
}

void update(MYSQL *con) {
	int choice;
	while(1) {
		printf("\n1. Employee\n2. Department\n3. Back to main menu");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		system("clear");
		switch(choice) {
			case 1: updateEmployee(con); break;
			case 2: updateDepartment(con); break;
			case 3: return;
		}
	}
}

void outputTable(MYSQL *con) {
	printf("Enter the table name to be shown: ");
	printf("\n1. Employee\n2. Department\n3. Project\n4. Works On\n5. Dependent\n6. Dept Locations");
	printf("\nEnter your choice: ");
	int choice;
	scanf("%d",&choice);
	system("clear");
	switch(choice) {
		case 1:	showTable(con, "EMPLOYEE"); break;
		case 2:	showTable(con, "DEPARTMENT"); break;
		case 3:	showTable(con, "PROJECT"); break;
		case 4:	showTable(con, "WORKS_ON"); break;
		case 5:	showTable(con, "DEPENDENT"); break;
		case 6:	showTable(con, "DEPT_LOCATIONS"); break;
	}
}

int main() {
	MYSQL *con = mysql_init(NULL);
	if(con==NULL) {
		fprintf(stderr,"\nmysql_init() failed\n");
		exit(1);
	}
	if(mysql_real_connect(con,"localhost","root","","employee",0,NULL,0)==NULL)
		finishQuery(con);
	/* showAllTables(con); */
	int choice;
	while(1) {
		printf("\n1. Insert\n2. Delete\n3. Update\n4. Output table\n5. Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		system("clear");
		switch(choice) {
			case 1:	insert(con); break;
			case 2: delete(con); break;
			case 3: update(con); break;
			case 4: outputTable(con); break;
			case 5: mysql_close(con); exit(0);
		}
	}
}
