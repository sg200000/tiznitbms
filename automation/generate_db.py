import sqlite3

database_file = "bank.db"
conn = sqlite3.connect(database_file)
cursor = conn.cursor()

sql_file = "generate_db.sql"
with open(sql_file, "r") as file:
    sql_commands = file.read()

try:
    cursor.executescript(sql_commands)
    conn.commit()
    print("SQL commands executed successfully.")
except sqlite3.Error as e:
    print(f"Error executing SQL commands: {e}")
    conn.rollback()

conn.close()
