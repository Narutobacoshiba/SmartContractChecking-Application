import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '12345678',
    database="solidityTocpn"
)
mycursor = db.cursor()

#CheckedBatchSC table

mycursor.execute("""
CREATE TABLE CheckedBatchSC (
cbsid nvarchar(64) primary key,
aid nvarchar(64) references Account(aid),
lnid nvarchar(64),
vusid nvarchar(64),
ccid nvarchar(64),
imid nvarchar(64),
noSC int,
checkedDate BIGINT,
status BOOLEAN,
result text
)
""")

#VulnerabilitySetting table
mycursor.execute("""
CREATE TABLE VulnerabilitySetting (
vusid nvarchar(64) primary key,
type nvarchar(50),
subtype nvarchar(50),

formula_id nvarchar(64),
formula_name nvarchar(200), 
formula_description text,
formula_content text
)
""")

#CPNContext table

mycursor.execute("""
CREATE TABLE CPNContext (
ccid nvarchar(64) primary key,
aid nvarchar(64) references Account(aid),
name nvarchar(200),
content text,
created_timestamp BIGINT, 
context_type nvarchar(50),
description text
)
""")

#CheckedSmartContractDetail table

mycursor.execute("""
CREATE TABLE CheckedSmartContractDetail (
cscid int primary key AUTO_INCREMENT,
sid nvarchar(64),
cbsid nvarchar(64) references CheckedBatchSC(cbsid)
)
""")

#LNAFile table

mycursor.execute("""
CREATE TABLE LNAFile (
lnid nvarchar(64) primary key,
hcpn_name nvarchar(200),
hcpn_content text,
prop_name nvarchar(200),
prop_content text
)
""")

#InitialMarking table

mycursor.execute("""
CREATE TABLE InitialMarking (
imid nvarchar(64) primary key,
num_user int,
IM_type nvarchar(50)
)
""")

#Balance table

mycursor.execute("""
CREATE TABLE Balance (
blid int primary key AUTO_INCREMENT,
type nvarchar(50),
from_value int,
to_value int,
fixed_value int,
range_value nvarchar(1000),
imid nvarchar(64) references InitialMarking(imid)
)
""")

#IMFunction table

mycursor.execute("""
CREATE TABLE IMFunction (
imfid nvarchar(64) primary key,
sc_name nvarchar(200),
func_name nvarchar(200),
sender_from int,
sender_to int,
imid nvarchar(64) references InitialMarking(imid)
)
""")

#IMArgument table

mycursor.execute("""
CREATE TABLE IMArgument (
imaid int primary key AUTO_INCREMENT,
arg_name nvarchar(200),
range_from int,
range_to int,
imfid nvarchar(64) references InitialMarking(imfid)
)
""")


