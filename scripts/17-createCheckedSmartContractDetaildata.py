import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456789',
    database="soliditycpn"
)
def InsertIMG(FilePath):
    with open(FilePath,"rb") as File :
        BinaryData = File.read()
    return BinaryData
mycursor = db.cursor()
sqlFomular = "INSERT INTO CheckedSmartContractDetail (status,isLTLTemplate,LTLFormula,result,lnid,sid,lteid,cid,bid,imid) VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"
multi = [
    (True,True,"LTLFOMULA","",1,1,1,1,1,1),
    (True,False,"","244 places",2,2,2,2,2,2),
    (False,True,"LTLFORMULA","",3,1,1,1,1,1),
    (False,False,"","244 places /n 72 arcs",3,3,3,3,3,3)
    ]
mycursor.executemany(sqlFomular,multi)
db.commit()