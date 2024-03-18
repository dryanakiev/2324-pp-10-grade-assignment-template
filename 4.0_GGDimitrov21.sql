/*Напишете заявка, която създава базата данни "School"  и създава таблица "Students", в която има "Id, FirstName, MiddleName, LastName, Year, Age".

Поставете Primary key. Добавете 5 записа в таблицата.

Изпратете задачата като .sql файл*/

CREATE DATABASE School

USE School

CREATE TABLE Students (
	Id INT IDENTITY(0, 1) PRIMARY KEY,
	FirstName CHAR(20) NOT NULL,
	MiddleName CHAR(20) NOT NULL,
	LastName CHAR(20) NOT NULL,
	BirthYear INT NOT NULL,
	Age INT NOT NULL
)

INSERT INTO Students(FirstName, MiddleName, LastName, BirthYear, Age)
VALUES('fname1', 'mname1', 'lname1', 1900, 124);

SELECT * FROM Students

DROP TABLE Students

DROP DATABASE School