import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '22042001',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO Argument (fid,name,type) VALUES (%s,%s,%s)"
multi = [
    (3,"biddingTime","uint"),
    (3,"revealTime","uint"),
    (3,"beneficiary","address"),
    (4,"blindedBid","bytes32"),
    (5,"value","uint[]"),
    (5,"secret","bytes32[]"),
    (5,"fake","bool[]"),
    (6,"bidder","address"),
    (6,"value","uint"),
    (11,"addr","address"),
    (12,"components","SeedComponents"),
    (20,"new_owner","address"),
    (21,"new_mindeposit","uint"),
    (22,"new_feerate","uint"),
    (26,"roundIndex","uint"),
    (26,"subpotIndex","uint"),
    (27,"roundIndex","uint"),
    (27,"subpotIndex","uint"),
    (28,"roundIndex","uint"),
    (28,"subpotIndex","uint"),
    (29,"roundIndex","uint"),
    (30,"roundIndex","uint"),
    (31,"roundIndex","uint"),
    (31,"subpotIndex","uint"),
    (32," blockIndex","uint"),
    (33,"roundIndex","uint"),
    (33,"buyer","address"),
    (34,"roundIndex","uint"),
    (34,"buyer","address"),
    (35,"roundIndex","uint"),
]
mycursor.executemany(sqlFomular,multi)
db.commit()