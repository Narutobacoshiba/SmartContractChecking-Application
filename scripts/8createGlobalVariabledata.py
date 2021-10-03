import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '22042001',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO GlobalVariable (name,vartype,type,value,scid) VALUES (%s,%s,%s,%s,%s)"
multi = [
    ("payoutMileStone1","uint","public","3 ether",1),
    ("mileStone1Reward","uint","public","2 ether",1),
    ("payoutMileStone2","uint","public","5 ether",1),
    ("mileStone2Reward","uint","public","3 ether",1),
    ("finalMileStone","uint","public","10 ether",1),
    ("finalReward","uint","public","5 ether",1),
    ("beneficiary","address","public","",2),
    ("auctionStart","uint","public","",2),
    ("biddingEnd","uint","public","",2),
    ("revealEnd","uint","public","",2),
    ("ended","bool","public","",2),
    ("highestBidder","address","public","",2),
    ("highestBid","uint","public","",2),
    ("owner","address","","",3),
    ("secretSeed","uint","private","",3),
    ("lastReseed","uint","private","",3),
    ("LuckyNumbe","uint","","7",3),
    ("TICKET_AMOUNT","uint","constant","10",4),
    ("FEE_AMOUNT","uint","constant","1",4),
    ("bank","address","public","",4),
    (" pot","uint","public","",4),
    ("Gamblers_Until_Jackpot","uint","public","0",5),
    ("Total_Gamblers","uint","public","0",5),
    ("FeeRate","uint","public","5",5),
    ("Bankroll","uint","public","0",5),
    ("Jackpot","uint","public","0",5),
    ("Total_Deposits","uint","public","0",5),
    ("Total_Payouts","uint","public","0",5),
    ("MinDeposit","uint","public","100 finney",5),
    ("owner","address","public","",5),
    ("Fees","uint","","0",5),
    ("blocksPerRound","uint","constant public","6800",6),
    ("ticketPrice","uint","constant public","100000000000000000",6),
    ("blockReward","uint","constant public","5000000000000000000",6)






]
mycursor.executemany(sqlFomular,multi)
db.commit()