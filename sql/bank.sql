CREATE TABLE "accounts" (
	"id"	INTEGER,
	"balance"	REAL NOT NULL,
	"min"	INTEGER NOT NULL DEFAULT 0,
	"currency"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE "customers" (
	"id"	INTEGER,
	"firstName"	TEXT,
	"lastName"	TEXT,
	"email"	TEXT,
	"phone"	TEXT,
	"accountId"	INTEGER,
	"userName"	TEXT UNIQUE,
	"password"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE "tellers" (
	"id"	INTEGER,
	"firstName"	TEXT,
	"lastName"	TEXT,
	"email"	TEXT,
	"phone"	TEXT,
	"userName"	TEXT UNIQUE,
	"password"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
);

INSERT INTO "tellers" ("firstName","lastName","email","phone","userName","password") 
VALUES ("admin","admin","admin@gmail.com","0612356789","admin","16559146482384667732");