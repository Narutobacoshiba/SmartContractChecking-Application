import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '',
    database="Project"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO LocalVariable (name,vartype,type,value,fid) VALUES (%s,%s,%s,%s,%s)"
multi = [
    ("currentBalance","public"," uint","this.balance + msg.value",1),
    ("length","public","unit","bids[msg.sender].length",5),
    ("refund","public","unit","+= bid.deposit",5),
    ("bid","public","var","bids[msg.sender][i]",5),
    ("(value,fake,secret)","public","var","(_values[i], _fake[i], _secret[i])",5),
    ("amount","public","var","pendingReturns[msg.sender]",7),
    ("win","public","var","msg.value*7",10),
    ("random","public","var","uint(sha3(block.timestamp)) % 2",17),
    ("amount","public","uint","msg.value",19),
    ("payout","public","uint","",19),
    ("list_length","public","uint","gamblerlist.length",19),
    ("minimal","public","uint"," 1990 finney",19),
    ("Times","public","unit","Fees/minimal",19),
    ("decisionBlockNumber","public","var","getDecisionBlockNumber(roundIndex,subpotIndex)",27),
    ("decisionBlockHash","public","var","getHashOfBlock(decisionBlockNumber)",27),
    ("winningTicketIndex","public","var","decisionBlockHash%rounds[roundIndex].ticketsCount",27),
    ("ticketIndex","public","var","uint256(0)",27),
    ("buyerIndex","public","var",0,27),
    ("buyer","public","var","rounds[roundIndex].buyers[buyerIndex]",27),
    ("subpotsCount","public","var","rounds[roundIndex].pot/blockReward",29),
    ("subpotsCount","public","var","getSubpotsCount(roundIndex)",31),
    ("decisionBlockNumber","public","var","getDecisionBlockNumber(roundIndex,subpotIndex)",31),
    ("winner","public","var"," calculateWinner(roundIndex,subpotIndex)",31),
    ("subpot","public","var","getSubpot(roundIndex)",31),
    ("roundIndex","public","var","getRoundIndex()",36),
    ("value","public","var","msg.value-(msg.value%ticketPrice)",36),
    ("ticketsCount","public","var","value/ticketPrice",36),
    ("buyersLength","public","var","rounds[roundIndex].buyers.length++",36),
]
mycursor.executemany(sqlFomular,multi)
db.commit()