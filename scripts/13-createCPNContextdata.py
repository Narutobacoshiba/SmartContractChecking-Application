import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO CPNContext (name,content,description,ctid) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("EtherLotto Context", "this is Content 1","This is desciption",1),
    ("blindAuction Context", "This is Content 2 ","This is desciption",2),
    ("EtherGame Context", "This is Content 3 ","This is desciption",3),
]
mycursor.executemany(sqlFomular,multi)
db.commit()
