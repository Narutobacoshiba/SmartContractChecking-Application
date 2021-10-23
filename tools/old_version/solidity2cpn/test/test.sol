// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.7.0 <0.9.0;

contract EtherLotto {
    address public bank ;
    struct GameRecord {
    address winner ;
    uint amount ;
    }
    uint8 gameNum ;
    GameRecord [] LottoLog ;
    GameRecord gr;
    bool won ;
    uint constant TICKET_AMOUNT = 10;
    uint constant FEE_AMOUNT = 1;
    uint public pot ;

    function EtherLottos () public {
        bank = msg.sender ;
        won = false ;
        gameNum = 0;
    }
    function RestartLotto () public {
        require (msg. sender == bank ) ;
        require (won == true );
        require (pot == 0) ;
        won = false ;
        gameNum += 1;
    }
    function playTicket () public payable {
        require (msg.value == TICKET_AMOUNT );
        require (won == false);
        pot += msg.value ;
        
        won = true;
        
        gr.winner = msg.sender ;
        gr.amount = pot - FEE_AMOUNT ;
        LottoLog [gameNum] = gr;
    }

    function getPot () public {
        require (won == true );
        if(msg.sender == LottoLog[gameNum].winner ){
            pot = 0;
        }
    }
}