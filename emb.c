#include <mysql.h>
#include <stdio.h>

int insertRecs(MYSQL *conn)
{
	char name[20];
	int yr, mnth, date, sal, sssn, dno, n;
	char statement[512];
	char *res = calloc(1, 512);
	printf("Enter the number of records: ");
	scanf("%d", &n);
	for (int i=0;i<n;i++)
	{
		printf("Enter Name:");
		scanf("%s", name);
		printf("Enter the dob (yyyy-mm-dd)");
		scanf("%d-%d-%d", &yr, &mnth, &date);
		printf("Enter the salary ");
		scanf("%d", &sal);
		printf("Enter the super SSN ");
		scanf("%d", &sssn);
		printf("Enter the Department No: ");
		scanf("%d", &dno);
		snprintf(statement,  512,  "INSERT INTO employee VALUES ('%s', ssn, '%d-%d-%d', %d, %d, %d)", name, yr, mnth, date, sal, sssn, dno);
		res = mysql_use_result(conn);
		printf("%s", res);
		if (mysql_query(conn, statement))
			return 1;
	}
	return 0;
}

int main()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server = "localhost";
	char *user = "root";
	char *password = "iiitdm123";
	char *database = "employee";

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	insertRecs(conn);
	return 0;
}
