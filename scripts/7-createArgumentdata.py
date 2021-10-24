import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '123456',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO Argument (fid,name,type,vartype,value) VALUES (%s,%s,%s,%s,%s)"
multi = [
    (3,"biddingTime","uint","state",1),
    (3,"revealTime","uint","local",3),
    (3,"beneficiary","address","state",5),
    (4,"blindedBid","bytes32","local",7),
    (5,"value","uint[]","state",9),
    (5,"secret","bytes32[]","local",0),
    (5,"fake","bool[]","state",2),
    (6,"bidder","address","local",4),
    (6,"value","uint","state",6),
    (11,"addr","address","local",8),
    (12,"components","SeedComponents","local",10),
    (20,"new_owner","address","state",12),
    (21,"new_mindeposit","uint","local",14),
    (22,"new_feerate","uint","local",16),
    (26,"roundIndex","uint","local",18),
    (26,"subpotIndex","uint","local",20),
    (27,"roundIndex","uint","local",11),
    (27,"subpotIndex","uint","state",13),
    (28,"roundIndex","uint","state",15),
    (28,"subpotIndex","uint","state",17),
    (29,"roundIndex","uint","state",19),
    (30,"roundIndex","uint","local",21),
    (31,"roundIndex","uint","state",23),
    (31,"subpotIndex","uint","state",25),
    (32," blockIndex","uint","state",27),
    (33,"roundIndex","uint","state",29),
    (33,"buyer","address","state",22),
    (34,"roundIndex","uint","local",24),
    (34,"buyer","address","state",26),
    (35,"roundIndex","uint","local",28),
]
mycursor.executemany(sqlFomular,multi)
db.commit()