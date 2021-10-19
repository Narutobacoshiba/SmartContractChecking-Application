import mysql.connector
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
sqlFomular = "INSERT INTO CheckedSmartContractDetail (sid,bid) VALUES (%s,%s)"
multi = [
    (1,1),
    (2,2),
    (3,3),
    ]
mycursor.executemany(sqlFomular,multi)
db.commit()