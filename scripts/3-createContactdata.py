import mysql.connector
import datetime
import requests
res = requests.get('https://ipinfo.io/')
data = res.json()
city = data['city']
region = data['region']
country = data['country']
loc = city+ " " + region+ " " + country
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
sqlFomular = "INSERT INTO Contact (firstname,lastname,email,phone,birthdate,avartar,address,aid) VALUES (%s,%s,%s,%s,%s,%s,%s,%s)"
multi = [
    ("Le","Duc Anh","anhld@fpt.edu.vn","0984268930",datetime.datetime.now(),InsertIMG(r"C:\Users\dinht\Desktop\SmartContractChecking-Application\scripts\image\index.jpeg"),str(loc),1),
    ("Le","Anh Son","sonla@fpt.edu.vn","0123456789",datetime.datetime.now(),InsertIMG(r"C:\Users\dinht\Desktop\SmartContractChecking-Application\scripts\image\index.jpeg"),str(loc),2),
    ("Nguyen","Minh Hanh","hanhnm@fpt.edu.vn","0123456789",datetime.datetime.now(),InsertIMG(r"C:\Users\dinht\Desktop\SmartContractChecking-Application\scripts\image\index.jpeg"),str(loc),3),
    ("Nguyen","Minh Duc","ducnm@fpt.edu.vn","0123456789",datetime.datetime.now(),InsertIMG(r"C:\Users\dinht\Desktop\SmartContractChecking-Application\scripts\image\index.jpeg"),str(loc),4),
    ("Nguyen","Thanh Ha","hant@fpt.edu.vn","0123456789",datetime.datetime.now(),InsertIMG(r"C:\Users\dinht\Desktop\SmartContractChecking-Application\scripts\image\index.jpeg"),str(loc),5),
    ("Tran","Van Cuong","cuongtv@fpt.edu.vn","0123456789",datetime.datetime.now(),InsertIMG(r"C:\Users\dinht\Desktop\SmartContractChecking-Application\scripts\image\index.jpeg"),str(loc),6),
]
mycursor.executemany(sqlFomular,multi)
db.commit()