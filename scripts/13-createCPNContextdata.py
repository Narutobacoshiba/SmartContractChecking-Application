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
    ("template 1", "this is Content 1","This is desciption",1),
    ("template 2", "This is Content 2 ","This is desciption",2),
    ("template 3", "This is Content 3 ","This is desciption",3),
]
mycursor.executemany(sqlFomular,multi)
db.commit()