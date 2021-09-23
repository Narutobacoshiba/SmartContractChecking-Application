import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '',
    database="Project"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO Template (name,formular,description) VALUES (%s,%s,%s)"
multi = [
    ("Template1","1Khoong Bieets chenf gif vaof ddaay","This is template 1"),
    ("Template2","2Khoong Bieets chenf gif vaof ddaay","This is template 2"),
    ("Template3","3Khoong Bieets chenf gif vaof ddaay","This is template 3"),
    ("Template4","4Khoong Bieets chenf gif vaof ddaay","This is template 4"),
    ("Template5","5Khoong Bieets chenf gif vaof ddaay","This is template 5"),
]
mycursor.executemany(sqlFomular,multi)
db.commit()