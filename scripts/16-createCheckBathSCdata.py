import mysql.connector
import datetime
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
def InsertIMG(FilePath):
    with open(FilePath,"rb") as File :
        BinaryData = File.read()
    return BinaryData
mycursor = db.cursor()
sqlFomular = "INSERT INTO CheckedBatchSC (aid,name,checkedDate,description) VALUES (%s,%s,%s,%s)"
multi = [
    (1,"checked1",datetime.datetime.now(),"This is checked 1"),
    (2,"checked2",datetime.datetime.now(),"This is checked 2"),
    (3,"checked3",datetime.datetime.now(),"This is checked 3"),
]
mycursor.executemany(sqlFomular,multi)
db.commit()