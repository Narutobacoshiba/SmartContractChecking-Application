import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = "123456",
    database="soliditycpn"
)
mycursor = db.cursor()
mycursor.execute("""CREATE TABLE Account (
aid int primary key AUTO_INCREMENT,
username nvarchar(200),
password nvarchar(200),
role nvarchar(200)
)

""")
mycursor.close()
