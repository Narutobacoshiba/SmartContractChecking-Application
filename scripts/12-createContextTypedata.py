import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '22042001',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO ContextType (name,description) VALUES (%s,%s)"
multi = [
    ("Context type 1","this is Context type 1"),
    ("Context type 2","this is Context type 2"),
    ("Context type 3","this is Context type 3"),
    ]
mycursor.executemany(sqlFomular,multi)
db.commit()