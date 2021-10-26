import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO Balance (blfrom,blto,blvalue,blrange,imid) VALUES (%s,%s,%s,%s,%s)"
multi = [ 
    (10,20,13,10,1),
    (5,30,17,25,2),
    (9,21,12,12,3),
]

mycursor.executemany(sqlFomular,multi)
db.commit()