import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = "",
    database="Project"
)
mycursor = db.cursor()
#mycursor.execute("CREATE DATABASE Project") # cau lenh nay chay 1 lan xong xuoc di ,go cai comment o tren connect
mycursor.execute("""CREATE TABLE Account (
id int primary key AUTO_INCREMENT,
username nvarchar(200),
password nvarchar(200),
role nvarchar(200)
)

""")
mycursor.execute("""CREATE TABLE Contact (
id int primary key AUTO_INCREMENT,
firstname nvarchar(200),
lastname nvarchar(200),
email nvarchar(200),
phone nvarchar(200),
birthdate datetime,
avartar LONGBLOB,
address nvarchar(200),
aid  int not null references Account(id)
)

""")
mycursor.execute("""
CREATE TABLE SmartContract (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
type nvarchar(50),
description text,
aid int not null references Account(id)
)

""")
mycursor.execute("""
CREATE TABLE History (
id int primary key AUTO_INCREMENT,
description text,
date_modified date,
scid int not null references SmartContract(id)
)
""")
mycursor.execute("""
CREATE TABLE History_Type (
id int primary key AUTO_INCREMENT,
history_name nvarchar(200),
htid int not null references History(id)
)

""")
mycursor.execute("""
CREATE TABLE Context (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
context text,
description text
)

""")
mycursor.execute("""
CREATE TABLE Template (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
formular text,
description nvarchar(200)
)

""")
mycursor.execute("""
CREATE TABLE ProVul (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
fomular text,
description nvarchar(200),
type nvarchar(200),
tpid int not null references Template(id)
)

""")
mycursor.execute("""
CREATE TABLE SC_ProVul (
id int AUTO_INCREMENT,
scid int not null references SmartContract(id),
pvid int not null references ProVul(id),
primary key(id,scid,pvid)
)

""")
mycursor.execute("""
CREATE TABLE SC_Context (
id int AUTO_INCREMENT,
scid int not null references SmartContract(id),
ctid int not null references Context(id),
primary key(id,scid,ctid)
)

""")
mycursor.execute("""
CREATE TABLE Function (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
bodycontent text,
scid int not null references SmartContract(id)
)

""")
mycursor.execute("""
CREATE TABLE GlobalVariable (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
vartype nvarchar(200),
type nvarchar(25),
value nvarchar(200),
scid int not null references SmartContract(id)
)

""")
mycursor.execute("""
create table LocalVariable (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
vartype nvarchar(200),
type nvarchar(200),
value nvarchar(200),
fid int not null references Function(id)
)

""")
mycursor.execute("""
CREATE table Argument (
id int primary key AUTO_INCREMENT,
fid int not null references Function(id),
name nvarchar(200),
type nvarchar(200)

)

""")