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
historyName nvarchar(200),
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
name nvarchar(200),
vartype nvarchar(200),
type nvarchar(50),
value int,
fid int not null references Functions(fid)

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
CREATE TABLE LNAFile (
lnid int primary key AUTO_INCREMENT,
hcpnFile LONGBLOB,
propFile LONGBLOB
)

""")

mycursor.execute("""
CREATE TABLE LTLTemplate (
lteid int primary key AUTO_INCREMENT,
name nvarchar(200),
formula text,
template_type nvarchar(200),
description text

)

""")
mycursor.execute("""
CREATE TABLE CPNContext (
cid int primary key AUTO_INCREMENT,
name nvarchar(200),
content text,
context_type nvarchar(200),
description text
)

""")
mycursor.execute("""
Create table InitialMarking (
imid int primary key AUTO_INCREMENT,
num_user int,
IM_type varchar(200)
)
""")

mycursor.execute("""
Create table Balance (
blid int primary key AUTO_INCREMENT,
blfrom int,
blto int,
blvalue int,
blrange varchar(200),
imid int not null references InitialMarking(imid)
)
""")
mycursor.execute("""
Create table IMFunction (
imfid int primary key AUTO_INCREMENT,
fun_name varchar(200),
sender_from int,
sender_to int,
imid int not null references InitialMarking(imid)
)
""")
mycursor.execute("""
Create table IMArgument (
imaid int primary key AUTO_INCREMENT,
arg_name varchar(200),
IMfrom int,
IMto int,
imfid int not null references IMFunction(imfid)
)
""")
mycursor.execute("""
CREATE TABLE CheckedBatchSC (
bid int primary key AUTO_INCREMENT,
aid int not null references Account(aid),
lnid int not null references LNAFile(lnid),
lteid int not null references LTLTemplate(lteid),
cid int not null references CPNContext(cid),
imid int not null references InitialMarking(imid),
noSC int,
checkedDate date,
status bit,
LTLformula text,
result varchar(200)
)
""")
mycursor.execute("""
CREATE TABLE CheckedSmartContractDetail (
sid int not null references SmartContract(sid),
bid int not null references CheckedBatchSC(bid),
PRIMARY KEY(sid,bid)
)
""")