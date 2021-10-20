import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO IMArgument (arg_name,IMfrom,IMto,imfid) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("IMArgument1",20,35,1),
    ("IMArgument2",30,45,2),
    ("IMArgument3",21,42,3),
]

mycursor.executemany(sqlFomular,multi)
db.commit()