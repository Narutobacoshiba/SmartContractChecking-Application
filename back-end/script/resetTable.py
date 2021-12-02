import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="admin",
    passwd = '123456',
    database="solidityTocpn"
)
mycursor = db.cursor()

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
mycursor.execute("DROP TABLE INFunction")


#IMArgument table
mycursor.execute("DROP TABLE IMArgument")


