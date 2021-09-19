import mysql.connector
#from django.contrib.auth.hashers import hash,check_password

db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '',
    database="Project"
)
pass1= hash("1234567")
pass2= hash("qwerty")
pass3= hash("135790246")
pass4= hash("asdcxz123")
pass5= hash("qwertgfdaxz")
pass6= hash("123@123a")
mycursor = db.cursor()
sqlFomular = "INSERT INTO Account (username,password,role) VALUES (%s,%s,%s)"
multi = [
    ("leducanh123",pass1,"admin"),
    ("leanhson",pass2,"admin"),
    ("minhhanh123",pass3,"user"),
    ("minhduc",pass4,"user"),
    ("thanhha",pass5,"user"),
    ("vancuong",pass6,"user"),
]
mycursor.executemany(sqlFomular,multi)
db.commit()