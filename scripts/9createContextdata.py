import mysql.connector
import requests
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="Project"
)
def InsertContent(FilePath):
    with open(FilePath,"rb") as File :
        BinaryData = File.read()
    return BinaryData
mycursor = db.cursor()
sqlFomular = "INSERT INTO Context (name,context,description) VALUES (%s,%s,%s)"
multi = [
    ("DCR",InsertContent("./XMLfile/test.xml"),"Use for SC1"),
("BPMN",InsertContent("./XMLfile/test0.xml"),"Use for SC2"),
]
mycursor.executemany(sqlFomular,multi)
db.commit()