import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO IMTemplate (name,formula) VALUES (%s,%s)"
multi = [
    ("IM template 1","this is IM  1"),
    ("IM template 2","this is IM  2"),
    ("IM template 3","this is IM  3"),
    ]
mycursor.executemany(sqlFomular,multi)
db.commit()