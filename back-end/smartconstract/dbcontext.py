from django.db import connection
# GetGlobalBySCID
def getGlobalVarBySmartContractId(id):
    try:
        sql = '''select name,vartype,type,value  from GlobalVariable where sid = %s;'''
        cursor = connection.cursor()
        cursor.execute(sql, [id])
        dbData = cursor.fetchall()
        afterFormat = []
        for row in dbData:
            element = {
                "name":row[0],
                "vartype":row[1],
                "type":row[2],
                "value":row[3]
            }
            afterFormat.append(element)
        return afterFormat
    except:
        return None
    finally:
        connection.close()

# Get LocalVariable by Function Id

def getLocalVarByFuncId(id):
    try:
        sql = '''select id,name,vartype,type,value from LocalVariable where fid = %s;'''
        cursor = connection.cursor()
        cursor.execute(sql,[id])
        dbData = cursor.fetchall()
        afterFormat = []
        for row in dbData:
            element = {
                "id":row[0],
                "name":row[1],
                "vartype":row[2],
                "type":row[3],
                "value":row[4]
            }
            # print(element)
            afterFormat.append(element)
        return afterFormat
    except Exception as e:
        print(e)
        return None

#Get Function by Smart Contract Id
def getFunctionBySCId(id):
    try:
        sql = '''select fid,name,bodyContent from Functions where sid = %s;'''
        cursor = connection.cursor()
        cursor.execute(sql,[id])
        dbData = cursor.fetchall()
        afterFormat = []
        for row in dbData:
            element = {
                "fid":row[0],
                # "name":row[1],
                # "bodyContent":row[2],
                "argument":getArgumentByFuncID(row[0]),
                "localVar":getLocalVarByFuncId(row[0])
            }
            # print(element)
            afterFormat.append(element)
        return afterFormat
    except Exception as e:
        print(e)
        return None

# Get Argument by FunctionId
def getArgumentByFuncID(id):
    try:
        sql = '''select * from Argument where fid = %s;'''
        cursor = connection.cursor()
        cursor.execute(sql,[id])
        dbData = cursor.fetchall()
        afterFormat = []
        for row in dbData:
            element = {
                "id":row[0],
                "name":row[1],
                "vartype":row[2],
                "type":row[3],
                "value":row[4],
                "fid":row[5]
            }
            # print(element)
            afterFormat.append(element)
        return afterFormat
    except Exception as e:
        print(e)
        return None