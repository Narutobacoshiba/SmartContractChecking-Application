import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO InitialMarking (num_user,IM_type) VALUES (%s,%s)"
multi = [
    (10,"IM_type1"),
    (20,"IM_type2"),
    (30,"IM_type3"),
    ]
mycursor.executemany(sqlFomular,multi)
db.commit()