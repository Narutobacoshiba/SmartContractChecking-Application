import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO CPNContext (name,content,context_type,description) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("EtherLotto Context", "this is Content 1","type1","This is desciption"),
    ("blindAuction Context", "This is Content 2 ","type2","This is desciption"),
    ("EtherGame Context", "This is Content 3 ","type3","This is desciption"),
]
mycursor.executemany(sqlFomular,multi)
db.commit()
