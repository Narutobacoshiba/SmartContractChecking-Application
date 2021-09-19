import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '',
    database="Project"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO Function (name,bodycontent,scid) VALUES (%s,%s,%s)"
multi = [
    ("play() public payable","""
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
        """,1),
    ("claimReward() public","""
         // ensure the game is complete
        require(this.balance == finalMileStone);
        // ensure there is a reward to give
        require(redeemableEther[msg.sender] > 0); 
        redeemableEther[msg.sender] = 0;
        msg.sender.transfer(redeemableEther[msg.sender]);
        """,1),
    ("BlindAuction(uint _biddingTime, uint _revealTime, address _beneficiary)","""
        beneficiary = _beneficiary;
        auctionStart = now;
        biddingEnd = now + _biddingTime;
        revealEnd = biddingEnd + _revealTime;
    """,2),
    ("bid(bytes32 _blindedBid) payable onlyBefore(biddingEnd)","""
        bids[msg.sender].push(Bid({
        blindedBid : _blindedBid,
        deposit : msg.value
        }));
    """,2),
    ("reveal(uint[] _values, bool[] _fake, bytes32[] _secret) onlyAfter(biddingEnd) onlyBefore(revealEnd)","""
     // Conditions
        uint length = bids[msg.sender].length;
        require(_values.length == length);
        require(_fake.length == length);
        require(_secret.length == length);

        // Effects
        uint refund;
        for (uint i = 0; i < length; i++) {
            var bid = bids[msg.sender][i];

            var (value, fake, secret) = (_values[i], _fake[i], _secret[i]);
            if (bid.blindedBid != keccak256(value, fake, secret)) {
                // Bid was not actually revealed.
                // Do not refund deposit.
                continue;
            }
            refund += bid.deposit;
            if (!fake && bid.deposit >= value) {
                if (placeBid(msg.sender, value))
                refund -= value;
            }
            // Make it impossible for the sender to re-claim
            // the same deposit.
            bid.blindedBid = 0;
        }

        // Interactions
        msg.sender.transfer(refund);
    """,2),
    ("placeBid(address bidder, uint value) internal returns (bool success)","""
        if (value <= highestBid) {
            return false;
        }
        if (highestBidder != 0) {
            // Refund the previously highest bidder.
            pendingReturns[highestBidder] += highestBid;
        }
        highestBid = value;
        highestBidder = bidder;
        return true;
    """,2),
    ("withdraw() returns (bool)","""
    var amount = pendingReturns[msg.sender];
        if (amount > 0) {
            // It is important to set this to zero because the recipient
            // can call this function again as part of the receiving call
            // before `send` returns (see the remark above about
            // conditions -> effects -> interaction).
            pendingReturns[msg.sender] = 0;

            if (!msg.sender.send(amount)){
                // No need to call throw here, just reset the amount owing
                pendingReturns[msg.sender] = amount;
                return false;
            }
        }
        return true;
    """,2),
    ("auctionEnd() onlyAfter(revealEnd)","""
     require(!ended);

        AuctionEnded(highestBidder, highestBid);

        ended = true;

        // Interractions
        // We send all the money we have, because some
        // of the refunds might have failed.
        beneficiary.transfer(this.balance);
    """,2),
    ("OpenAddressLottery()","""
    owner = msg.sender;
        reseed(SeedComponents((uint)(block.coinbase), block.difficulty, block.gaslimit, block.timestamp));
    """,3),
    ("participate() payable","""
            if(msg.value<0.1 ether)
            return; //verify ticket price
        
        // make sure he hasn't won already
        require(winner[msg.sender] == false);
        
        if(luckyNumberOfAddress(msg.sender) == LuckyNumber){ //check if it equals 7
            winner[msg.sender] = true; // every address can only win once
            
            uint win=msg.value*7; //win = 7 times the ticket price
            
            if(win>this.balance) //if the balance isnt sufficient...
                win=this.balance; //...send everything we've got
            msg.sender.transfer(win);
        }
        
        if(block.number-lastReseed>1000) //reseed if needed
            reseed(SeedComponents((uint)(block.coinbase), block.difficulty, block.gaslimit, block.timestamp)); //generate a quality random seed
    """,3),
    ("luckyNumberOfAddress(address addr) constant returns(uint n)","""
     n = uint(keccak256(uint(addr), secretSeed)[0]) % 8;
    """,3),
    (" reseed(SeedComponents components) internal ","""
    secretSeed = uint256(keccak256(
            components.component1,
            components.component2,
            components.component3,
            components.component4
        )); //hash the incoming parameters and use the hash to (re)initialize the seed
        lastReseed = block.number;
    """,3),
    ("kill()","""
    require(msg.sender==owner);
        
        selfdestruct(msg.sender);
    """,3),
    (" forceReseed()","""
    require(msg.sender==owner);
        
        SeedComponents s;
        s.component1 = uint(msg.sender);
        s.component2 = uint256(block.blockhash(block.number - 1));
        s.component3 = block.difficulty*(uint)(block.coinbase);
        s.component4 = tx.gasprice * 7;
        
        reseed(s); //reseed
    """,3),
    ("() payable ","""
    if(msg.value>=0.1 ether && msg.sender!=owner) //owner can't participate, he can only fund the jackpot
            participate();""",3),
    ("EtherLotto()","""
    bank = msg.sender;
    """,4),
    (" play() payable","""
    
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
    """,4),
    ("SimpleDice()","""
     owner = 0xee462a6717f17c57c826f1ad9b4d3813495296c9;  //this contract is an attachment to EthVentures
    """,5),
    ("enter() ","""
    if (msg.value >10 finney) {

    uint amount=msg.value;
    uint payout;


    // add a new participant to the system and calculate total players
    uint list_length = gamblerlist.length;
    Total_Gamblers=list_length+1;
    Gamblers_Until_Jackpot=40-(Total_Gamblers % 40);
    gamblerlist.length += 1;
    gamblerlist[list_length].etherAddress = msg.sender;
    gamblerlist[list_length].amount = amount;



    // set payout variables
     Total_Deposits+=amount;       	//update deposited amount
	    
      Fees   =amount * FeeRate/100;    // 5% fee to the owner
      amount-=amount * FeeRate/100;
	    
      Bankroll += amount*80/100;     // 80% to the balance
      amount-=amount*80/100;  
	    
      Jackpot += amount;               	//remaining to the jackpot


    // payout fees to the owner
     if (Fees != 0) 
     {
	uint minimal= 1990 finney;
	if(Fees<minimal)
	{
      	owner.send(Fees);		//send fee to owner
	Total_Payouts+=Fees;        //update paid out amount
	}
	else
	{
	uint Times= Fees/minimal;

	for(uint i=0; i<Times;i++)   // send the fees out in packets compatible to EthVentures dividend function
	if(Fees>0)
	{
	owner.send(minimal);		//send fee to owner
	Total_Payouts+=Fees;        //update paid out amount
	Fees-=minimal;
	}
	}
     }
 
    if (msg.value >= MinDeposit) 
     {
	     
   //payout to participants	
     if(list_length%40==0 && Jackpot > 0)   				//every 40th player wins the jackpot if  it's not 0
	{
	gamblerlist[list_length].etherAddress.send(Jackpot);         //send pay out to participant
	Total_Payouts += Jackpot;               					//update paid out amount   
	Jackpot=0;									//jackpot update
	}
     else   											//you either win the jackpot or the balance, but not both in 1 round
	if(uint(sha3(gamblerlist[list_length].etherAddress,list_length))+uint(sha3(msg.gas)) % 4 ==0 && Bankroll > 0) 	//if the hashed length of your address is even, 
	{ 												   								//which is a 25% chance, then you get paid out all balance!
	gamblerlist[list_length].etherAddress.send(Bankroll);        //send pay out to participant
	Total_Payouts += Bankroll;               					//update paid out amount
	Bankroll = 0;                      						//bankroll update
	}
    
    
    
    //enter function ends
	}
    """,5),
    ("setOwner(address new_owner) onlyowner ","""
     owner = new_owner;
    """,5),
    ("setMinDeposit(uint new_mindeposit) onlyowner ","""
    MinDeposit = new_mindeposit;
    """,5),
    ("setFeeRate(uint new_feerate) onlyowner","""
    FeeRate = new_feerate;
    """,5),
    ("getBlocksPerRound() constant returns(uint)","""
    return blocksPerRound;
    """,6),
    ("getTicketPrice() constant returns(uint)","""
     return ticketPrice;
    """,6),
    ("getRoundIndex() constant returns (uint)","""
    return block.number/blocksPerRound;
    """,6),
    ("getIsCashed(uint roundIndex,uint subpotIndex) constant returns (bool)","""
    return rounds[roundIndex].isCashed[subpotIndex];
    """,6),
    ("calculateWinner(uint roundIndex, uint subpotIndex) constant returns(address)","""
            var decisionBlockNumber = getDecisionBlockNumber(roundIndex,subpotIndex);

        if(decisionBlockNumber>block.number)
            return;
        //We can't decided the winner if the round isn't over yet

        var decisionBlockHash = getHashOfBlock(decisionBlockNumber);
        var winningTicketIndex = decisionBlockHash%rounds[roundIndex].ticketsCount;
        //We perform a modulus of the blockhash to determine the winner

        var ticketIndex = uint256(0);

        for(var buyerIndex = 0; buyerIndex<rounds[roundIndex].buyers.length; buyerIndex++){
            var buyer = rounds[roundIndex].buyers[buyerIndex];
            ticketIndex+=rounds[roundIndex].ticketsCountByBuyer[buyer];

            if(ticketIndex>winningTicketIndex){
                return buyer;
            }
        }
    """,6),
    ("getDecisionBlockNumber(uint roundIndex,uint subpotIndex) constant returns (uint)","""
    return ((roundIndex+1)*blocksPerRound)+subpotIndex;
    """,6),
    ("getSubpotsCount(uint roundIndex) constant returns(uint)","""
    var subpotsCount = rounds[roundIndex].pot/blockReward;

        if(rounds[roundIndex].pot%blockReward>0)
            subpotsCount++;

        return subpotsCount;
    """,6),
    ("getSubpot(uint roundIndex) constant returns(uint)","""
    return rounds[roundIndex].pot/getSubpotsCount(roundIndex);
    """,6),
    ("cash(uint roundIndex, uint subpotIndex)","""
    var subpotsCount = getSubpotsCount(roundIndex);

        if(subpotIndex>=subpotsCount)
            return;

        var decisionBlockNumber = getDecisionBlockNumber(roundIndex,subpotIndex);

        if(decisionBlockNumber>block.number)
            return;

        if(rounds[roundIndex].isCashed[subpotIndex])
            return;
        //Subpots can only be cashed once. This is to prevent double payouts

        var winner = calculateWinner(roundIndex,subpotIndex);    
        var subpot = getSubpot(roundIndex);

        winner.send(subpot);

        rounds[roundIndex].isCashed[subpotIndex] = true;
    """,6),
    ("getHashOfBlock(uint blockIndex) constant returns(uint)","""
     return uint(block.blockhash(blockIndex));
    """,6),
    ("getBuyers(uint roundIndex,address buyer) constant returns (address[])","""
    return rounds[roundIndex].buyers;
    """,6),
    ("getTicketsCountByBuyer(uint roundIndex,address buyer) constant returns (uint)","""
    return rounds[roundIndex].ticketsCountByBuyer[buyer];
    """,6),
    ("getPot(uint roundIndex) constant returns(uint)","""
    return rounds[roundIndex].pot;
    """,6),
    ("function()","""
    var roundIndex = getRoundIndex();
        var value = msg.value-(msg.value%ticketPrice);

        if(value==0) return;

        if(value<msg.value){
            msg.sender.send(msg.value-value);
        }
        //no partial tickets, send a partial refund 

        var ticketsCount = value/ticketPrice;
        rounds[roundIndex].ticketsCount+=ticketsCount;

        if(rounds[roundIndex].ticketsCountByBuyer[msg.sender]==0){
            var buyersLength = rounds[roundIndex].buyers.length++;
            rounds[roundIndex].buyers[buyersLength] = msg.sender;
        }

        rounds[roundIndex].ticketsCountByBuyer[msg.sender]+=ticketsCount;
        rounds[roundIndex].ticketsCount+=ticketsCount;
        //keep track of the total tickets

        rounds[roundIndex].pot+=value;
        //keep track of the total pot
    """,6),
]
mycursor.executemany(sqlFomular,multi)
db.commit()