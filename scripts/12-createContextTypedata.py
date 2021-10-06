import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO ContextType (name,description) VALUES (%s,%s)"
multi = [
    ("DCR","This is the declarative context"),
    ("Free-context","This is free-context, it mean the system generate a default context"),
    ("Context type 3","this is Context type 3"),
    ]
mycursor.executemany(sqlFomular,multi)
db.commit()
