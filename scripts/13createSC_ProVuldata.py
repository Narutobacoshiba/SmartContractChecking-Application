import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO SC_ProVul (scid,pvid) VALUES (%s,%s)"
multi = [
    (1,3),
    (2,4),
    (3,5),
    (4,6),
    (5,1),
    (6,2),
]
mycursor.executemany(sqlFomular,multi)
db.commit()