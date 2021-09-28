import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO SC_Context (scid,ctid) VALUES (%s,%s)"
multi = [
    (1,1),
    (2,2),
]
mycursor.executemany(sqlFomular,multi)
db.commit()