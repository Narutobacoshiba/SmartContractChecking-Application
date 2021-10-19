import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO LTLTemplate (name,formula,template_type,description) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("interger_overflow_underflow", "const minThreshold = 0\nconst maxThreshold = 2147483647\nproposition outOfRange: ('variable' < minThreshold) | ('variable' > maxThreshold);\nproperty prop: !outOfRange;","type0","outOfRange(x) is a proposition defining the conditions for overflow and underflow for the variable x w.r.t the range of its type which we delimit by defining lower and higher thresholds (minThreshold and maxThreshold respectively)."),
    ("reetrancy", "template Reentrancy()","type1","This vulnerability is related to functions that contain instructions responsible for Ether transfer."),
    ("self_destruction", "template SelfDestruction();","type2","This vulnerability is checked by detecting the presence of a test containing this.balance in the code of the inspected function"),
    ("timestamp_dependence", "template TimestampDependence();","Type3","This vulnerability is checked by detecting the presence of timestamp dependence"),
    ("skip_empty_string_literal", "template SkipEmptyStringLiteral();","type4","This can be checked for the function calls contained in the definition of a function f by verifying that no empty string is passed as an argument (except for the last one) to any of the function calls."),
    ("uninitialized_storage_variable", "template UninitializedStorageVariable();","Type5","This can be checked for each variable x of a complex type by the LTL property."),

]
mycursor.executemany(sqlFomular,multi)
db.commit()