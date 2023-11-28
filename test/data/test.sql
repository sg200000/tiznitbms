CREATE TABLE "test" (
	"id"	INTEGER,
	"firstName"	TEXT,
	"lastName"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
);

INSERT INTO "test" ("firstName","lastName") 
VALUES ("testFirst","testSecond");