#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/statement.h> 
#include <iostream> 
#include <mysql_connection.h> 
#include <mysql_driver.h> 
#include<string>

using namespace std;
int main()
{
	try {
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;

		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://localhost:3306",
			"andrejmanin", "pfRto0$gosArO");

		con->setSchema("tasks_db"); // your database name 

		sql::Statement* stmt;
		stmt = con->createStatement();

		// SQL query to create a table 
		string createTableSQL
			= "CREATE TABLE IF NOT EXISTS Tasks ("
			"id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
			"tasks VARCHAR(255) NOT NULL"
			")";

		stmt->execute(createTableSQL);
		string inp = "";
		while (true)
		{
			getline(cin, inp);
			if (inp == "no")
				break;
			string insertDataSQL = "INSERT INTO Tasks (tasks) VALUES ""(\"" + inp + "\")";
			stmt->execute(insertDataSQL);
		}

		// SQL query to retrieve data from the table 
		string selectDataSQL = "SELECT * FROM Tasks";

		sql::ResultSet* res
			= stmt->executeQuery(selectDataSQL);

		// Loop through the result set and display data 
		int count = 0;
		while (res->next()) {
			cout << " Task " << ++count << ": "
				<< res->getString("tasks") << endl;
		}
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}

	return 0;
}
