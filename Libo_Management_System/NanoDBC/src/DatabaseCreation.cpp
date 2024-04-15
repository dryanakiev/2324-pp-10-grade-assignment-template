

#include <iostream>
#include "nanodbc/nanodbc.h"

void sqlConnect()
{
	nanodbc::connection conn(
		NANODBC_TEXT("Driver={ *server_driver[MSSMS20]* };Server= *server_name* ;Database=master;Trusted_Connection=yes"));

	std::cout << conn.connected();
	/*
	nanodbc::execute(conn, NANODBC_TEXT(
		CREATE DATABASE LiboUsers
		GO

		CREATE DATABASE LiboBooks
		GO
	));
	*/
}