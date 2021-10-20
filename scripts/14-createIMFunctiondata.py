import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO IMFunction (fun_name,sender_from,sender_to,imid) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("IMFunction1",20,35,1),
    ("IMFunction1",30,45,2),
    ("IMFunction1",21,42,3),
]

mycursor.executemany(sqlFomular,multi)
db.commit()