import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = "123456",
    database="soliditycpn"
)
mycursor = db.cursor()
mycursor.execute("""CREATE TABLE Account (
aid int primary key AUTO_INCREMENT,
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
birthDate date,
avartar LONGBLOB,
address nvarchar(200),
aid  int not null references Account(aid)
)

""")
mycursor.execute("""
CREATE TABLE SmartContract (
sid int primary key AUTO_INCREMENT,
name nvarchar(200),
type nvarchar(50),
content text ,
description text,
aid int not null references Account(aid)
)

""")
mycursor.execute("""
CREATE TABLE History (
hid int primary key AUTO_INCREMENT,
description text,
modifiedDate date,
aid int not null references Account(aid)
)
""")
mycursor.execute("""
CREATE TABLE History_Type (
id int primary key AUTO_INCREMENT,
history_name nvarchar(200),
hid int not null references History(hid)
)

""")
mycursor.execute("""
CREATE TABLE GlobalVariable (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
vartype nvarchar(200),
type nvarchar(25),
value nvarchar(200),
sid int not null references SmartContract(sid)
)

""")
mycursor.execute("""
CREATE TABLE Functions (
fid int primary key AUTO_INCREMENT,
name nvarchar(200),
bodyContent text,
sid int not null references SmartContract(sid)
)

""")
mycursor.execute("""
CREATE table Argument (
id int primary key AUTO_INCREMENT,
fid int not null references Functions(fid),
name nvarchar(200),
type nvarchar(200)

)

""")
mycursor.execute("""
create table LocalVariable (
id int primary key AUTO_INCREMENT,
name nvarchar(200),
vartype nvarchar(200),
type nvarchar(200),
value nvarchar(200),
fid int not null references Functions(fid)
)

""")
mycursor.execute("""
CREATE TABLE CheckedBatchSC (
bid int primary key AUTO_INCREMENT,
aid int not null references Account(aid),
name nvarchar(200),
checkedDate date,
description text
)

""")
mycursor.execute("""
CREATE TABLE LNAFile (
lnid int primary key AUTO_INCREMENT,
hcpnFile LONGBLOB,
propFile LONGBLOB
)

""")
mycursor.execute("""
CREATE TABLE LTLType (
ltyid int primary key AUTO_INCREMENT,
name nvarchar(200),
description text
)

""")
mycursor.execute("""
CREATE TABLE LTLTemplate (
lteid int primary key AUTO_INCREMENT,
name nvarchar(200),
formula text,
description text,
ltyid int not null references LTLType(ltyid)
)

""")
mycursor.execute("""
CREATE TABLE IMTemplate (
imtid int primary key AUTO_INCREMENT,
name nvarchar(200),
formula text
)

""")
mycursor.execute("""
CREATE TABLE InitialMarking (
imid int primary key AUTO_INCREMENT,
numberUser int,
balance int,
value int,
orther_parameter nvarchar(200),
imtid int not null references IMTemplate(imtid)
)

""")
mycursor.execute("""
CREATE TABLE ContextType (
ctid int primary key AUTO_INCREMENT,
name nvarchar(200),
description text
)

""")
mycursor.execute("""
CREATE TABLE CPNContext (
cid int primary key AUTO_INCREMENT,
name nvarchar(200),
content text,
description text,
ctid int not null references ContextType(ctid)
)

""")
mycursor.execute("""
CREATE TABLE CheckedSmartContractDetail (
cscdid int primary key AUTO_INCREMENT,
status bool,
isLTLTemplate bool,
LTLFormula text,
result text,
lnid int not null references LNAFile(lnid),
sid int not null references SmartContract(sid),
lteid int not null references LTLTemplate(lteid),
cid int not null references CPNContext(cid),
bid int not null references CheckedBatchSC(bid),
imid int not null references InitialMarking(imid)
)

""")
