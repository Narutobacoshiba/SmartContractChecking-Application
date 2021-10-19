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
sqlFomular = "INSERT INTO CheckedBatchSC (aid,lnid,lteid,cid,imid,noSC,checkedDate,status,LTLformula,result) VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"
multi = [
    (1,1,1,1,1,4,datetime.datetime.now(),True,"LTLformula 1","result 1"),
    (2,2,2,2,2,2,datetime.datetime.now(),False,"LTLformula 2","result 2"),
    (3,3,3,3,3,7,datetime.datetime.now(),True,"LTLformula 3","result 3"),
]
mycursor.executemany(sqlFomular,multi)
db.commit()