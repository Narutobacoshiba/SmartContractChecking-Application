import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="admin",
    passwd = '123456',
    database="solidityTocpn"
)
mycursor = db.cursor()

#Account table
mycursor.execute("""
CREATE TABLE Account (
aid nvarchar(64) primary key,
username nvarchar(200),
password nvarchar(200),
role nvarchar(200)
)
""")

sqlFomular = "INSERT INTO Account (aid,username,password,role) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("0863e75515b4efeba7216d384091be00d18f149a7fa822807901fae602d723d0","thanhha","123456","user"),
    ("2c0afaf6e2b3af8189ad2d914456df5f38c67a75b2458d7001c6ca58a3bb7e7c","admin","1234","admin")
]
mycursor.executemany(sqlFomular,multi)

#Contact
mycursor.execute("""
CREATE TABLE Contact (
cid int primary key AUTO_INCREMENT,
firstname nvarchar(200),
lastname nvarchar(200),
email nvarchar(200),
aid nvarchar(64) references Account(aid)
)
""")

sqlFomular = "INSERT INTO Contact (firstname,lastname,email,aid) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("Ha","Dinh Thanh","thanhha@gmail.com","0863e75515b4efeba7216d384091be00d18f149a7fa822807901fae602d723d0"),
    ("Admin","T","admin@gmail.com","2c0afaf6e2b3af8189ad2d914456df5f38c67a75b2458d7001c6ca58a3bb7e7c")
]
mycursor.executemany(sqlFomular,multi)

#SmartContract
mycursor.execute("""
CREATE TABLE SmartContract (
sid nvarchar(64) primary key,
name nvarchar(200),
type nvarchar(50),
content text ,
description text,
created_timestamp BIGINT,
aid nvarchar(64) references Account(aid)
)

""")

sqlFomular = "INSERT INTO SmartContract (sid,name,type,content,description,aid,created_timestamp) VALUES (%s,%s,%s,%s,%s,%s,%s)"
multi = [ 
    ("f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa","EtherGame","private","""uint public payoutMileStone1 = 3 ether;
    uint public mileStone1Reward = 2 ether;
    uint public payoutMileStone2 = 5 ether;
    uint public mileStone2Reward = 3 ether; 
    uint public finalMileStone = 10 ether; 
    uint public finalReward = 5 ether; 
    
    mapping(address => uint) redeemableEther;
    // users pay 0.5 ether. At specific milestones, credit their accounts
    function play() public payable {
        require(msg.value == 0.5 ether); // each play is 0.5 ether
        uint currentBalance = this.balance + msg.value;
        // ensure no players after the game as finished
        require(currentBalance <= finalMileStone);
        // if at a milestone credit the players account
        if (currentBalance == payoutMileStone1) {
            redeemableEther[msg.sender] += mileStone1Reward;
        }
        else if (currentBalance == payoutMileStone2) {
            redeemableEther[msg.sender] += mileStone2Reward;
        }
        else if (currentBalance == finalMileStone ) {
            redeemableEther[msg.sender] += finalReward;
        }
        return;
    }
    
    function claimReward() public {
        // ensure the game is complete
        require(this.balance == finalMileStone);
        // ensure there is a reward to give
        require(redeemableEther[msg.sender] > 0); 
        redeemableEther[msg.sender] = 0;
        msg.sender.transfer(redeemableEther[msg.sender]);
    }""","EtherGame description","0863e75515b4efeba7216d384091be00d18f149a7fa822807901fae602d723d0","1607110465663"),
    ("e6440c761f42ba6ec74bf25d1649296de26be2e4e7b716367232504bf5ac86bf","EtherLotto","common","""// Amount of ether needed for participating in the lottery. 
    uint constant TICKET_AMOUNT = 10;

    // Fixed amount fee for each lottery game.
    uint constant FEE_AMOUNT = 1;

    // Address where fee is sent.
    address public bank;

    // Public jackpot that each participant can win (minus fee).
    uint public pot;

    // Lottery constructor sets bank account from the smart-contract owner.
    function EtherLotto() {
        bank = msg.sender;
    }

    // Public function for playing lottery. Each time this function
    // is invoked, the sender has an oportunity for winning pot.
    function play() payable {

        // Participants must spend some fixed ether before playing lottery.
        assert(msg.value == TICKET_AMOUNT);

        // Increase pot for each participant.
        pot += msg.value;

        // Compute some *almost random* value for selecting winner from current transaction.
        var random = uint(sha3(block.timestamp)) % 2;

        // Distribution: 50% of participants will be winners.
        if (random == 0) {

            // Send fee to bank account.
            bank.transfer(FEE_AMOUNT);

            // Send jackpot to winner.
            msg.sender.transfer(pot - FEE_AMOUNT);

            // Restart jackpot.
            pot = 0;
        }
    }
    
    ""","EtherLoto description","0863e75515b4efeba7216d384091be00d18f149a7fa822807901fae602d723d0","1608110465663")
]
mycursor.executemany(sqlFomular,multi)

#GlobalVariable table
mycursor.execute("""
CREATE TABLE GlobalVariable (
gid int primary key AUTO_INCREMENT,
name nvarchar(200),
vartype nvarchar(200),
type nvarchar(25),
value nvarchar(200),
sid nvarchar(64) references SmartContract(sid)
)

""")

sqlFomular = "INSERT INTO GlobalVariable (name,vartype,type,value,sid) VALUES (%s,%s,%s,%s,%s)"
multi = [ 
    ("payoutMileStone1","uint","public","3 ether","f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa"),
    ("mileStone1Reward","uint","public","2 ether","f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa"),
    ("payoutMileStone2","uint","public","5 ether","f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa"),
    ("mileStone2Reward","uint","public","3 ether","f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa"),
    ("finalMileStone","uint","public","10 ether","f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa"),
    ("finalReward","uint","public","5 ether","f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa"),
    ("TICKET_AMOUNT","uint","constant","10","e6440c761f42ba6ec74bf25d1649296de26be2e4e7b716367232504bf5ac86bf"),
    ("FEE_AMOUNT","uint","constant","1","e6440c761f42ba6ec74bf25d1649296de26be2e4e7b716367232504bf5ac86bf"),
    ("bank","address","public","","e6440c761f42ba6ec74bf25d1649296de26be2e4e7b716367232504bf5ac86bf"),
]
mycursor.executemany(sqlFomular,multi)

#Functions table
mycursor.execute("""
CREATE TABLE Functions (
fid nvarchar(64) primary key,
name nvarchar(200),
bodyContent text,
sid nvarchar(64) references SmartContract(sid)
)

""")

sqlFomular = "INSERT INTO Functions (fid,name,bodyContent,sid) VALUES (%s,%s,%s,%s)"
multi = [ 
    ("87fe2ff705acabf3668933492f49f32a825b3e145c6eca893f4dfe8104902ea8","play","""require(msg.value == 0.5 ether); // each play is 0.5 ether
        uint currentBalance = this.balance + msg.value;
        // ensure no players after the game as finished
        require(currentBalance <= finalMileStone);
        // if at a milestone credit the players account
        if (currentBalance == payoutMileStone1) {
            redeemableEther[msg.sender] += mileStone1Reward;
        }
        else if (currentBalance == payoutMileStone2) {
            redeemableEther[msg.sender] += mileStone2Reward;
        }
        else if (currentBalance == finalMileStone ) {
            redeemableEther[msg.sender] += finalReward;
        }
        return;
    ""","f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa"),
    ("6e335687f24494ca572e3b23ff209720eb20e23324104328546d427f172b1b1e","claimReward","""// ensure the game is complete
        require(this.balance == finalMileStone);
        // ensure there is a reward to give
        require(redeemableEther[msg.sender] > 0); 
        redeemableEther[msg.sender] = 0;
        msg.sender.transfer(redeemableEther[msg.sender]);
    ""","f124d6ab446a36daf4ddb194838f3101c3d531842b1e1f8e941309b1781582aa"),
    ("ba66a918c41a53b67ea5855dea4013e1b9422542d5f55be720258bfd962b7c1b","EtherLotto","""bank = msg.sender;
    ""","e6440c761f42ba6ec74bf25d1649296de26be2e4e7b716367232504bf5ac86bf"),
    ("e9cd29d1fb66bae00f77439cb1de6e9bff4fd631c0873f9c2ae4a8ce0f5d4268","play","""// Participants must spend some fixed ether before playing lottery.
        assert(msg.value == TICKET_AMOUNT);

        // Increase pot for each participant.
        pot += msg.value;

        // Compute some *almost random* value for selecting winner from current transaction.
        var random = uint(sha3(block.timestamp)) % 2;

        // Distribution: 50% of participants will be winners.
        if (random == 0) {

            // Send fee to bank account.
            bank.transfer(FEE_AMOUNT);

            // Send jackpot to winner.
            msg.sender.transfer(pot - FEE_AMOUNT);

            // Restart jackpot.
            pot = 0;
    ""","e6440c761f42ba6ec74bf25d1649296de26be2e4e7b716367232504bf5ac86bf")
]
mycursor.executemany(sqlFomular,multi)

#LocalVariable
mycursor.execute("""
create table LocalVariable (
lid int primary key AUTO_INCREMENT,
name nvarchar(200),
vartype nvarchar(200),
type nvarchar(200),
value nvarchar(200),
fid nvarchar(64) references Functions(fid)
)

""")

sqlFomular = "INSERT INTO LocalVariable (name,vartype,type,value,fid) VALUES (%s,%s,%s,%s,%s)"
multi = [ 
    ("currentBalance","public","uint","this.balance + msg.value ","87fe2ff705acabf3668933492f49f32a825b3e145c6eca893f4dfe8104902ea8"),
    ("random","public","var","uint(sha3(block.timestamp)) % 2","e9cd29d1fb66bae00f77439cb1de6e9bff4fd631c0873f9c2ae4a8ce0f5d4268"),
]

mycursor.executemany(sqlFomular,multi)

#Argument
mycursor.execute("""
CREATE table Argument (
arid int primary key AUTO_INCREMENT,
name nvarchar(200),
vartype nvarchar(200),
type nvarchar(50),
value nvarchar(200),
fid nvarchar(64) references Functions(fid)
)
""")

#LTLTemplate table
mycursor.execute("""
CREATE TABLE LTLTemplate (
lteid nvarchar(64) primary key,
name nvarchar(200),
formula text,
formula_text text,
created_timestamp BIGINT, 
template_type nvarchar(200),
description text
)
""")

sqlFomular = "INSERT INTO LTLTemplate (lteid,name,formula,formula_text,created_timestamp,template_type,description) VALUES (%s,%s,%s,%s,%s,%s,%s)"
multi = [ 
    ("82cc3c00eb933b3b679a02521d9863bbfbd14292cbb62d9ce688d2844c93b6fe","interger_overflow_underflow", "const minThreshold = 0;\nconst maxThreshold = 100;\nproposition outOfRange: ('variable' < minThreshold) | ('variable' > maxThreshold);\nproperty prop: G(! outOfRange);",
    "test","1607110465663","type0","outOfRange(x) is a proposition defining the conditions for overflow and underflow for the variable x w.r.t the range of its type which we delimit by defining lower and higher thresholds (minThreshold and maxThreshold respec tively).")
]
mycursor.executemany(sqlFomular,multi)

mycursor.close()

db.commit()
