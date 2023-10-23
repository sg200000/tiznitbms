import sqlite3
import json

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

data = {
    "db":"sqlite3",
    "path": "C:/Users/saidg/source/tiznitbms/bank.db"
}

# Specify the file path where you want to save the JSON data
file_path = "../db.json"

# Serialize and save the data to the file
with open(file_path, 'w') as json_file:
    json.dump(data, json_file)


