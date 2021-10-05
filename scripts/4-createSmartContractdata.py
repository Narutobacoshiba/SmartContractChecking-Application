import mysql.connector
db = mysql.connector.connect(
    host = "localhost",
    user="root",
    passwd = '22042001',
    database="soliditycpn"
)
mycursor = db.cursor()
sqlFomular = "INSERT INTO SmartContract (name,type,content,description,aid) VALUES (%s,%s,%s,%s,%s)"
multi = [
    ("EtherGame","Pending","""
    uint public payoutMileStone1 = 3 ether;
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
    }""","This is discription ",1),
    ("indAuctionbl","Private","""
    struct Bid {
    bytes32 blindedBid;
    uint deposit;
    }

    address public beneficiary;

    uint public auctionStart;

    uint public biddingEnd;

    uint public revealEnd;

    bool public ended;

    mapping (address => Bid[]) public bids;

    address public highestBidder;

    uint public highestBid;

    // Allowed withdrawals of previous bids
    mapping (address => uint) pendingReturns;

    event AuctionEnded(address winner, uint highestBid);

    /// Modifiers are a convenient way to validate inputs to
    /// functions. `onlyBefore` is applied to `bid` below:
    /// The new function body is the modifier's body where
    /// `_` is replaced by the old function body.
    modifier onlyBefore(uint _time) {require(now < _time);
        _;}
    modifier onlyAfter(uint _time) {require(now > _time);
        _;}

    function BlindAuction(uint _biddingTime, uint _revealTime, address _beneficiary) {
        beneficiary = _beneficiary;
        auctionStart = now;
        biddingEnd = now + _biddingTime;
        revealEnd = biddingEnd + _revealTime;
    }

    /// Place a blinded bid with `_blindedBid` = keccak256(value,
    /// fake, secret).
    /// The sent ether is only refunded if the bid is correctly
    /// revealed in the revealing phase. The bid is valid if the
    /// ether sent together with the bid is at least "value" and
    /// "fake" is not true. Setting "fake" to true and sending
    /// not the exact amount are ways to hide the real bid but
    /// still make the required deposit. The same address can
    /// place multiple bids.
    function bid(bytes32 _blindedBid) payable onlyBefore(biddingEnd)
    {
        bids[msg.sender].push(Bid({
        blindedBid : _blindedBid,
        deposit : msg.value
        }));
    }

    /// Reveal your blinded bids. You will get a refund for all
    /// correctly blinded invalid bids and for all bids except for
    /// the totally highest.
    function reveal(uint[] _values, bool[] _fake, bytes32[] _secret) onlyAfter(biddingEnd) onlyBefore(revealEnd)
    {
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
    }

    // This is an "internal" function which means that it
    // can only be called from the contract itself (or from
    // derived contracts).
    function placeBid(address bidder, uint value) internal returns (bool success)
    {
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
    }

    /// Withdraw a bid that was overbid.
    function withdraw() returns (bool) {
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
    }

    /// End the auction and send the highest bid
    /// to the beneficiary.
    function auctionEnd() onlyAfter(revealEnd)
    {
        require(!ended);

        AuctionEnded(highestBidder, highestBid);

        ended = true;

        // Interractions
        // We send all the money we have, because some
        // of the refunds might have failed.
        beneficiary.transfer(this.balance);
    }
    ""","This is discription ",2),
    ("OpenAddressLottery","Common","""
    struct SeedComponents{
        uint component1;
        uint component2;
        uint component3;
        uint component4;
    }
    
    address owner; //address of the owner
    uint private secretSeed; //seed used to calculate number of an address
    uint private lastReseed; //last reseed - used to automatically reseed the contract every 1000 blocks
    uint LuckyNumber = 7; //if the number of an address equals 7, it wins
        
    mapping (address => bool) winner; //keeping track of addresses that have already won
    
    function OpenAddressLottery() {
        owner = msg.sender;
        reseed(SeedComponents((uint)(block.coinbase), block.difficulty, block.gaslimit, block.timestamp)); //generate a quality random seed
    }
    
    function participate() payable {
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
    }
    
    function luckyNumberOfAddress(address addr) constant returns(uint n){
        // calculate the number of current address - 1 in 8 chance
        n = uint(keccak256(uint(addr), secretSeed)[0]) % 8;
    }
    
    function reseed(SeedComponents components) internal {
        secretSeed = uint256(keccak256(
            components.component1,
            components.component2,
            components.component3,
            components.component4
        )); //hash the incoming parameters and use the hash to (re)initialize the seed
        lastReseed = block.number;
    }
    
    function kill() {
        require(msg.sender==owner);
        
        selfdestruct(msg.sender);
    }
    
    function forceReseed() { //reseed initiated by the owner - for testing purposes
        require(msg.sender==owner);
        
        SeedComponents s;
        s.component1 = uint(msg.sender);
        s.component2 = uint256(block.blockhash(block.number - 1));
        s.component3 = block.difficulty*(uint)(block.coinbase);
        s.component4 = tx.gasprice * 7;
        
        reseed(s); //reseed
    }
    
    function () payable { //if someone sends money without any function call, just assume he wanted to participate
        if(msg.value>=0.1 ether && msg.sender!=owner) //owner can't participate, he can only fund the jackpot
            participate();
    }
    ""","This is discription ",3),
    ("EtherLotto","Pending","""
    
    // Amount of ether needed for participating in the lottery.
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
    ""","This is discription ",4),
    ("SimpleDice","Common","""
    
  struct gamblerarray {
      address etherAddress;
      uint amount;
  }

//********************************************PUBLIC VARIABLES
  
  gamblerarray[] public gamblerlist;
  uint public Gamblers_Until_Jackpot=0;
  uint public Total_Gamblers=0;
  uint public FeeRate=5;
  uint public Bankroll = 0;
  uint public Jackpot = 0;
  uint public Total_Deposits=0;
  uint public Total_Payouts=0;
  uint public MinDeposit=100 finney;

  address public owner;
  uint Fees=0;
  // simple single-sig function modifier
  modifier onlyowner { if (msg.sender == owner) _ }

//********************************************INIT

  function SimpleDice() {
    owner = 0xee462a6717f17c57c826f1ad9b4d3813495296c9;  //this contract is an attachment to EthVentures
  }

//********************************************TRIGGER

  function() {
    enter();
  }
  
//********************************************ENTER

  function enter() {
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
    }
  }

//********************************************NEW OWNER

  function setOwner(address new_owner) onlyowner { //set new owner of the casino
      owner = new_owner;
  }
//********************************************SET MIN DEPOSIT

  function setMinDeposit(uint new_mindeposit) onlyowner { //set new minimum deposit rate
      MinDeposit = new_mindeposit;
  }
//********************************************SET FEE RATE

  function setFeeRate(uint new_feerate) onlyowner { //set new fee rate
      FeeRate = new_feerate;
  }
    ""","This is discription ",5),
    ("Lotto","Private","""
    uint constant public blocksPerRound = 6800;
    // there are an infinite number of rounds (just like a real lottery that takes place every week). `blocksPerRound` decides how many blocks each round will last. 6800 is around a day.

    uint constant public ticketPrice = 100000000000000000;
    // the cost of each ticket is .1 ether.

    uint constant public blockReward = 5000000000000000000;

    function getBlocksPerRound() constant returns(uint){ return blocksPerRound; }
    function getTicketPrice() constant returns(uint){ return ticketPrice; }
    //accessors for constants

    struct Round {
        address[] buyers;
        uint pot;
        uint ticketsCount;
        mapping(uint=>bool) isCashed;
        mapping(address=>uint) ticketsCountByBuyer;
    }
    mapping(uint => Round) rounds;
    //the contract maintains a mapping of rounds. Each round maintains a list of tickets, the total amount of the pot, and whether or not the round was "cashed". "Cashing" is the act of paying out the pot to the winner.

    function getRoundIndex() constant returns (uint){
        //The round index tells us which round we're on. For example if we're on block 24, we're on round 2. Division in Solidity automatically rounds down, so we don't need to worry about decimals.
        
        return block.number/blocksPerRound;
    }

    function getIsCashed(uint roundIndex,uint subpotIndex) constant returns (bool){
        //Determine if a given.
        
        return rounds[roundIndex].isCashed[subpotIndex];
    }


    function calculateWinner(uint roundIndex, uint subpotIndex) constant returns(address){
        //note this function only calculates the winners. It does not do any state changes and therefore does not include various validitiy checks

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
    }

    function getDecisionBlockNumber(uint roundIndex,uint subpotIndex) constant returns (uint){
        return ((roundIndex+1)*blocksPerRound)+subpotIndex;
    }

    function getSubpotsCount(uint roundIndex) constant returns(uint){
        var subpotsCount = rounds[roundIndex].pot/blockReward;

        if(rounds[roundIndex].pot%blockReward>0)
            subpotsCount++;

        return subpotsCount;
    }

    function getSubpot(uint roundIndex) constant returns(uint){
        return rounds[roundIndex].pot/getSubpotsCount(roundIndex);
    }

    function cash(uint roundIndex, uint subpotIndex){

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
        //Mark the round as cashed
    }

    function getHashOfBlock(uint blockIndex) constant returns(uint){
        return uint(block.blockhash(blockIndex));
    }
    
    function getBuyers(uint roundIndex,address buyer) constant returns (address[]){
        return rounds[roundIndex].buyers;
    }

    function getTicketsCountByBuyer(uint roundIndex,address buyer) constant returns (uint){
        return rounds[roundIndex].ticketsCountByBuyer[buyer];
    }

    function getPot(uint roundIndex) constant returns(uint){
        return rounds[roundIndex].pot;
    }

    function() {
        //this is the function that gets called when people send money to the contract.

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

    }
    ""","This is discription ",6),
]
mycursor.executemany(sqlFomular,multi)
db.commit()