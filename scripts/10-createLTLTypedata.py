import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO LTLType (name,description) VALUES (%s,%s)"
multi = [
    ("LTL1","this is LTL 1"),
    ("LTL2","this is LTL 2"),
    ("LTL3","this is LTL 3"),
    ]
mycursor.executemany(sqlFomular,multi)
db.commit()