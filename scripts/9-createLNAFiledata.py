import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '22042001',
    database="soliditycpn"
)
def InsertIMG(FilePath):
    with open(FilePath,"rb") as File :
        BinaryData = File.read()
    return BinaryData
mycursor = db.cursor()
sqlFomular = "INSERT INTO LNAFile (hcpnfile,propfile) VALUES (%s,%s)"
multi = [
    (InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.lna"),InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.prop.lna")),
    (InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.lna"),InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.prop.lna")),
     (InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.lna"),InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.prop.lna")),
      (InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.lna"),InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.prop.lna")),
       (InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.lna"),InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.prop.lna")),
        (InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.lna"),InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.prop.lna")),
         (InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.lna"),InsertIMG(r"C:\Users\PC\Desktop\SmartContractChecking-Application\scripts\XMLfile\finnal_model.prop.lna")),
         
]
mycursor.executemany(sqlFomular,multi)
db.commit()