import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '',
    database="Project"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO ProVul (name,fomular,description,type,tpid) VALUES (%s,%s,%s,%s,%s)"
multi = [
    ("Property1","Temple1","1 template ","Property",1),
    ("Property1","Temple2","2 template ","Property",2),
    ("Property2","Temple3","3 template ","Property",3),
    ("Vul1","Template4","4 template","Vulnerabilty",4),
    ("Vul1","Template5","5 template","Vulnerabilty",5),
    ("Vul3","Template4","4 template","Vulnerabilty",4)
]
mycursor.executemany(sqlFomular,multi)
db.commit()