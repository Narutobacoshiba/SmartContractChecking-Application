import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="admin",
    passwd = '123456',
    database="solidityTocpn"
)
mycursor = db.cursor()

#Account table
mycursor.execute("DROP TABLE Account")

#Contact table
mycursor.execute("DROP TABLE Contact")

#SmartContract table
mycursor.execute("DROP TABLE SmartContract")

#GlobalVariable table
mycursor.execute("DROP TABLE GlobalVariable")

#Functions table
mycursor.execute("DROP TABLE Functions")

#LocalVariable table
mycursor.execute("DROP TABLE LocalVariable")

#Argument table
mycursor.execute("DROP TABLE Argument")

#LTLTemplate table
mycursor.execute("DROP TABLE LTLTemplate")

#CheckedBatchSC table
mycursor.execute("DROP TABLE CheckedBatchSC")

#VulnerabilitySetting table
mycursor.execute("DROP TABLE VulnerabilitySetting")


#CPNContext table
mycursor.execute("DROP TABLE CPNContext")


#CheckedSmartContractDetail table
mycursor.execute("DROP TABLE CheckedSmartContractDetail")


#LNAFile table
mycursor.execute("DROP TABLE LNAFile")


#InitialMarking table
mycursor.execute("DROP TABLE InitialMarking")


#Balance table
mycursor.execute("DROP TABLE Balance")


#IMFunction table
mycursor.execute("DROP TABLE IMFunction")


#IMArgument table
mycursor.execute("DROP TABLE IMArgument")


