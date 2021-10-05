import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '22042001',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO InitialMarking (numberUser,balance,value,orther_parameter,imtid) VALUES (%s,%s,%s,%s,%s)"
multi = [
    (10,200,15,"parameter1",1),
    (20,170,20,"parameter2",2),
    (30,150,18,"parameter3",3),
    ]
mycursor.executemany(sqlFomular,multi)
db.commit()