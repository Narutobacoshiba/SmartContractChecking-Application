import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456789',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO LTLTemplate (name,formula,description,ltyid) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("interger_overflow_underflow", "const minThreshold = 0\nconst maxThreshold = 2147483647\nproposition outOfRange: ('variable' < minThreshold) | ('variable' > maxThreshold);\nproperty prop: !outOfRange;","outOfRange(x) is a proposition defining the conditions for overflow and underflow for the variable x w.r.t the range of its type which we delimit by defining lower and higher thresholds (minThreshold and maxThreshold respectively).",1),
    ("reetrancy", "template Reentrancy()","This vulnerability is related to functions that contain instructions responsible for Ether transfer."
,2),
    ("self_destruction", "template SelfDestruction();","This vulnerability is checked by detecting the presence of a test containing this.balance in the code of the inspected function",3),
    ("timestamp_dependence", "template TimestampDependence();","This vulnerability is checked by detecting the presence of timestamp dependence",4),
    ("skip_empty_string_literal", "template SkipEmptyStringLiteral();","This can be checked for the function calls contained in the definition of a function f by verifying that no empty string is passed as an argument (except for the last one) to any of the function calls.",5),
    ("uninitialized_storage_variable", "template UninitializedStorageVariable();","This can be checked for each variable x of a complex type by the LTL property.",6),

]
mycursor.executemany(sqlFomular,multi)
db.commit()