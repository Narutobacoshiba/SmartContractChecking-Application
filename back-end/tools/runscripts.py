import json
import requests
import subprocess
from subprocess import Popen, PIPE, STDOUT


# def unfolding_script(lna, context, param):
#     # command = [
#     #     "python", "/home/meedee/Desktop/project/call_tool/script.py", "this is string"]
#     #command = ["/home/meedee/Desktop/project/call_tool/script.cpp"]
#     # command = ["helena", "/home/meedee/Desktop/project/ducdm/SmartContractChecking-Application/tools/unfolding/output/out.lna"]
#     command = ["/home/meedee/Desktop/project/ducdm/SmartContractChecking-Application/tools/unfolding/./unfolding",
#                "--lna", "/home/meedee/Desktop/project/ducdm/SmartContractChecking-Application/tools/unfolding/test/EtherGame.lna",
#                ""]

#     try:
#         process = Popen(command, stdout=PIPE, stderr=STDOUT)
#         output = process.stdout.read()
#         output = str(output, 'utf-8')
#         exitstatus = process.poll()
#         p_status = process.wait()
#         print(type(output))
#         if (exitstatus == 0):
#             print("status: Success!", "output:", (output))
#         else:
#             print("status: Failed@", "output:", str(output))
#     except Exception as e:
#         print("status: failed!", "output:", str(e))


# unfolding_script()
lna = '''	/******************************************************************************
	*
	*  File  : EtherGame.lna
	*  Author: Ikram GARFATTA
	*  Date  : 12 Sep. 2021
	*
	******************************************************************************/

	etherGame {/*(cb := 0, users := 1, v1 := 3, v2 := 2, v3 := 5, v4 := 3, v5 := 10, v6 := 5) { */ /*  CONTRACT STATE initialization  */



	/**************************
	*** Colours Definitions ***
	**************************/
		type ADDRESS : range 0 .. 100;
		
		type UINT : range 0 .. (int'last);
		
		type USER : struct { ADDRESS adr; UINT balance;};
		
		
		
		type STRUCT_REDEEMABLE_ETHER : struct { ADDRESS adr; UINT uint;};
		type LIST_REDEEMABLE_ETHER : list [nat] of STRUCT_REDEEMABLE_ETHER with capacity 100;/**/
		
		type STATE : struct { UINT contractBalance; UINT payoutMileStone1; UINT mileStone1Reward; UINT payoutMileStone2; UINT mileStone2Reward; UINT finalMileStone; UINT finalReward; LIST_REDEEMABLE_ETHER redeemableEther;};
		
		type PLAY_PAR : struct { USER sender; UINT value;};
		type CLAIM_REWARD_PAR : struct { USER sender; UINT value;};
		
		type PLAY_RETURN : struct { USER sender;};
		type CLAIM_REWARD_RETURN : struct { USER sender;};
		
		type PLAY_STATE : struct { STATE state; PLAY_PAR playPar;};
		type CLAIM_REWARD_STATE : struct { STATE state; CLAIM_REWARD_PAR claimRewardPar;};
		
		
	/****************************
	*** Functions Definitions ***
	****************************/

		function initRedeemableEther (nat n) -> LIST_REDEEMABLE_ETHER {
			LIST_REDEEMABLE_ETHER l := empty;
				for (i in ADDRESS range 1 .. ADDRESS (n)) l := {i,UINT(0)} & l;
				return l;
		}
		function getElement (LIST_REDEEMABLE_ETHER lre, ADDRESS adr) -> STRUCT_REDEEMABLE_ETHER {
			int i := 0;
			while (i<lre'size and lre[i].adr!=adr) i := i+1;
			if(i<lre'size)
				return lre[i];
			else
				return {0,0};
		}
		function getIndex (LIST_REDEEMABLE_ETHER lre, ADDRESS adr) -> int {
			int i := 0;
			while (i<lre'size and lre[i].adr!=adr) i := i+1;
			if(i<lre'size)
				return i;
			else
				return -1;
		}

	/*************
	*** PLACES ***
	*************/
	//these 3 places would be part of the free context in a final full model
	/*
	* Function: state
	*/
	place S {
		dom : STATE;
		init : <( {UINT(cb), UINT(v1), UINT(v2), UINT(v3), UINT(v4), UINT(v5), UINT(v6), initRedeemableEther(users)} )>;
	}
	/*
	* Function: play
	*/
	place P_Play {
		dom : PLAY_PAR;
		init : for (i in ADDRESS range 1 .. ADDRESS (users)) <( {{i , UINT(i*100)},UINT(1)} )>;
	}
	/*
	* Function: claimReward
	*/
	place P_ClaimReward {
		dom : CLAIM_REWARD_PAR;
	}

	/*
	* Function: play
	*/
	place PLAY_P1 {
		dom : PLAY_STATE;
	}
	place PLAY_P2 {
		dom : PLAY_STATE;
	}
	place PLAY_P3 {
		dom : PLAY_STATE;
	}
	place PLAY_P4 {
		dom : PLAY_STATE;
	}
	place PLAY_PT1 {
		dom : PLAY_STATE;
	}
	place PLAY_PT2 {
		dom : PLAY_STATE;
	}
	place PLAY_PT3 {
		dom : PLAY_STATE;
	}
	place PLAY_PF1 {
		dom : PLAY_STATE;
	}
	place PLAY_PF2 {
		dom : PLAY_STATE;
	}
	place PLAY_currentBalance {
		dom : UINT;
	}
	
	/*
	* Function: claimReward
	*/
	place CLAIM_REWARD_P1 {
		dom : CLAIM_REWARD_STATE;
	}
	place CLAIM_REWARD_P2 {
		dom : CLAIM_REWARD_STATE;
	}
	place CLAIM_REWARD_P3 {
		dom : CLAIM_REWARD_STATE;
	}
	
	/******************
	*** TRANSITIONS ***
	******************/

	/*
	* Function: play
	*/
		transition PLAY_revert1 {
			in {
				S : <( s )>;
				P_Play : <( p )>;
			}
			out {
				S : <( s )>;
			}
			guard : not (p.value = 1);
		}
		transition PLAY_n_revert1 {
			in {
				S : <( s )>;
				P_Play : <( p )>;
			}
			out {
				PLAY_P1 : <( {s,p} )>;
			}
			guard : p.value = 1;
		}
		transition PLAY_t1 {
			in {
				PLAY_P1 : <( sp )>;
			}
			out {
				PLAY_currentBalance : <( (sp.state.contractBalance) + (sp.playPar.value) )>;
				PLAY_P2 : <( sp )>;
			}
		}
		transition PLAY_revert2 {
			in {
				PLAY_P2 : <( sp )>;
				PLAY_currentBalance : <( currentBalance )>;
			}
			out {
				PLAY_currentBalance : <( currentBalance )>;
				S : <( sp.state )>;			
			}
			guard : not (currentBalance <= sp.state.finalMileStone);
		}
		transition PLAY_n_revert2 {
			in {
				PLAY_P2 : <( sp )>;
				PLAY_currentBalance : <( currentBalance )>;
			}
			out {
				PLAY_currentBalance : <( currentBalance )>;
				PLAY_P3 : <( sp )>;	
			}
			guard : currentBalance <= sp.state.finalMileStone;
		}
		transition PLAY_tT1 {
			in {
				PLAY_P3 : <( sp )>;
				PLAY_currentBalance : <( currentBalance )>;
			}
			out {
				PLAY_currentBalance : <( currentBalance )>;
				PLAY_PT1 : <( sp )>;	
			}
			guard : currentBalance = sp.state.payoutMileStone1;
		}
		transition PLAY_tF1 {
			in {
				PLAY_P3 : <( sp )>;
				PLAY_currentBalance : <( currentBalance )>;
			}
			out {
				PLAY_currentBalance : <( currentBalance )>;
				PLAY_PF1 : <( sp )>;	
			}
			guard : not (currentBalance = sp.state.payoutMileStone1);
		}
		transition PLAY_tT2 {
			in {
				PLAY_PF1 : <( sp )>;
				PLAY_currentBalance : <( currentBalance )>;
			}
			out {
				PLAY_currentBalance : <( currentBalance )>;
				PLAY_PT2 : <( sp )>;	
			}
			guard : currentBalance = sp.state.payoutMileStone2;
		}
		transition PLAY_tF2 {
			in {
				PLAY_PF1 : <( sp )>;
				PLAY_currentBalance : <( currentBalance )>;
			}
			out {
				PLAY_currentBalance : <( currentBalance )>;
				PLAY_PF2 : <( sp )>;	
			}
			guard : not (currentBalance = sp.state.payoutMileStone2);
		}
		transition PLAY_tT3 {
			in {
				PLAY_PF2 : <( sp )>;
				PLAY_currentBalance : <( currentBalance )>;
			}
			out {
				PLAY_currentBalance : <( currentBalance )>;
				PLAY_PT3 : <( sp )>;	
			}
			guard : currentBalance = sp.state.finalMileStone;
		}
		transition PLAY_tF3 {
			in {
				PLAY_PF2 : <( sp )>;
				PLAY_currentBalance : <( currentBalance )>;
			}
			out {
				PLAY_currentBalance : <( currentBalance )>;
				PLAY_P4 : <( sp )>;	
			}
			guard : not (currentBalance = sp.state.finalMileStone);
		}
		transition PLAY_t2 {
			in {
				PLAY_PT1 : <( sp )>;
			}
			out {
				PLAY_P4 : <( {sp.state :: (redeemableEther := nlre),sp.playPar} )>;
			}
			let {
				STRUCT_REDEEMABLE_ETHER re := getElement(sp.state.redeemableEther,sp.playPar.sender.adr);
				STRUCT_REDEEMABLE_ETHER nre := re :: (uint := re.uint + sp.state.mileStone1Reward);
				LIST_REDEEMABLE_ETHER nlre := sp.state.redeemableEther :: ([getIndex(sp.state.redeemableEther,sp.playPar.sender.adr)] := nre);
			}
		}
		transition PLAY_t3 {
			in {
				PLAY_PT2 : <( sp )>;
			}
			out {
				PLAY_P4 : <( {sp.state :: (redeemableEther := nlre),sp.playPar} )>;
			}
			let {
				STRUCT_REDEEMABLE_ETHER re := getElement(sp.state.redeemableEther,sp.playPar.sender.adr);
				STRUCT_REDEEMABLE_ETHER nre := re :: (uint := re.uint + sp.state.mileStone2Reward);
				LIST_REDEEMABLE_ETHER nlre := sp.state.redeemableEther :: ([getIndex(sp.state.redeemableEther,sp.playPar.sender.adr)] := nre);
			}
		}
		transition PLAY_t4 {
			in {
				PLAY_PT3 : <( sp )>;
			}
			out {
				PLAY_P4 : <( {sp.state :: (redeemableEther := nlre),sp.playPar} )>;
			}
			let {
				STRUCT_REDEEMABLE_ETHER re := getElement(sp.state.redeemableEther,sp.playPar.sender.adr);
				STRUCT_REDEEMABLE_ETHER nre := re :: (uint := re.uint + sp.state.finalReward);
				LIST_REDEEMABLE_ETHER nlre := sp.state.redeemableEther :: ([getIndex(sp.state.redeemableEther,sp.playPar.sender.adr)] := nre);
			}
		}
		transition PLAY_return {
			in {
				PLAY_P4 : <( sp )>;
			}
			out {
				//S : <( sp.state )>;
			}
		}
	/*
	* Function: claimReward
	*/
		transition CLAIM_REWARD_revert1 {
			in {
				S : <( s )>;
				P_ClaimReward : <( p )>;
			}
			out {
				S : <( s )>;
			}
			guard : not (s.contractBalance = s.finalMileStone);
		}
		transition CLAIM_REWARD_n_revert1 {
			in {
				S : <( s )>;
				P_ClaimReward : <( p )>;
			}
			out {
				CLAIM_REWARD_P1 : <( {s,p} )>;
			}
			guard : s.contractBalance = s.finalMileStone;
		}
		transition CLAIM_REWARD_revert2 {
			in {
				CLAIM_REWARD_P1 : <( sp )>;
			}
			out {
				S : <( sp.state )>;
			}
			guard : not (getElement(sp.state.redeemableEther,sp.claimRewardPar.sender.adr).uint > 0);
		}
		transition CLAIM_REWARD_n_revert2 {
			in {
				CLAIM_REWARD_P1 : <( sp )>;
			}
			out {
				CLAIM_REWARD_P2 : <( sp )>;
			}
			guard : getElement(sp.state.redeemableEther,sp.claimRewardPar.sender.adr).uint > 0;
		}
		transition CLAIM_REWARD_t1 {
			in {
				CLAIM_REWARD_P2 : <( sp )>;
			}
			out {
				CLAIM_REWARD_P3 : <( {sp.state :: (redeemableEther := nlre),sp.claimRewardPar} )>;
			}
			let {
				STRUCT_REDEEMABLE_ETHER re := getElement(sp.state.redeemableEther,sp.claimRewardPar.sender.adr);
				STRUCT_REDEEMABLE_ETHER nre := re :: (uint := 0);
				LIST_REDEEMABLE_ETHER nlre := sp.state.redeemableEther :: ([getIndex(sp.state.redeemableEther,sp.claimRewardPar.sender.adr)] := nre);
			}
		}
		transition CLAIM_REWARD_send {
			in {
				CLAIM_REWARD_P3 : <( sp )>;
			}
			out {
				S : <( sp.state :: (contractBalance := sp.state.contractBalance - getElement(sp.state.redeemableEther,sp.claimRewardPar.sender.adr).uint) )>;
			}
		}
	}'''

context = '''test(N := 2) {
type boolean : range 0 .. 1;
type count : range 0 .. N;
subtype event_id : count range 0 .. (count'last-1);
type marking_value : list[event_id] of boolean with capacity N;
type mvalue : struct { event_id id;boolean vl;};
type vchange : list[event_id] of mvalue with capacity N;
type cvalue : struct { boolean cv1;boolean cv2;};
type vcondition : list[event_id] of cvalue with capacity N;
function cvalue (marking_value mv, vchange lc) -> marking_value{
	marking_value m := empty;
	for(v in mv){
		m := m & v;
	}
	for(v in lc){
		m[v.id] := v.vl;
	}
	return m;
}
function confirm_condition (vcondition vc) -> boolean{
	boolean ret := 1;
	for(v in vc){
		if(v.cv1 = 1 and v.cv2 = 0) ret := 0;
	}
	return ret;
}
function confirm_milestone (vcondition vc) -> boolean{
	boolean ret := 1;
	for(v in vc){
		if(v.cv1 = 1 and v.cv2 = 1) ret := 0;
	}
	return ret;
}

/*
 * Function: state
 */
place marking {
	dom : marking_value*marking_value*marking_value;
	init : <(|0,0|,|0,0|,|1,1|)>;
}

/*
 * Function: play
 */
transition play {
	in {
		marking : <(execute,response,include)>;
	}
	out {
		marking : <(execute,cvalue(response,|{0,0}|),include)>;
	}
	guard : (include[0] = 1);
}

/*
 * Function: claimReward
 */
transition claimReward {
	in {
		marking : <(execute,response,include)>;
	}
	out {
		marking : <(execute,cvalue(response,|{1,0}|),cvalue(include,|{0,1}|))>;
	}
	guard : (include[1] = 1) and (confirm_condition(|{include[0],execute[0]}|) = 1);
}

}'''

# param = 'play'


# def unfolding(lna, context, param):
#     lnaFile = "EtherGame.lna"
#     contextFile = "context.lna"
#     param = "function1"
#     outFileUnf = "./output/out123"
#     commandUnf = "./unfolding --lna ./test/" + lnaFile + "  --context ./test/" + \
#         contextFile + " --param " + param + " --out_file "+outFileUnf
#     pathUnf = r"C:\Users\Admin\Desktop\(dev)SmartContractChecking-Application\tools\unfolding"

#     unfolding = subprocess.run(
#         commandUnf, cwd=pathUnf, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)


# def dcr2cpn(xml):
#     xmlFile = "test.xml"
#     outFile = "outFile"
#     commandDcr = "./dcr2cpn --xml ./test/" + xmlFile + " --out_file " + outFile
#     pathDcr = r"C:\Users\Admin\Desktop\(dev)SmartContractChecking-Application\tools\dcr2cpn"
#     dcr2cpnpro = subprocess.run(
#         commandDcr, cwd=pathDcr, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)


# def runHelena():
#     # helenaFile1=""
#     # helenaFile2 = ""
#     # helena - N = CHECK-prop out.lna
#     #helena = "helena " + "outFile.lna"
#     helena = "helena " + "/home/meedee/helena/examples/lna/allocator.lna"
#     #helenaPath = r"/home/meedee/Desktop/project/ducdm/SmartContractChecking-Application/tools/ltl2prop"
#     # pro4 = subprocess.run(helena, cwd=helenaPath, shell=True,
#     #                       stdout=subprocess.PIPE, stderr=subprocess.PIPE)
#     pro4 = subprocess.run(helena, shell=True,
#                           stdout=subprocess.PIPE, stderr=subprocess.PIPE)
#     output = str(pro4.stdout.decode("cp932"))
#     start = output.find("Helena report")
#     report = output[start:]
#     # print(report)
#     return report

# #runHelena()

# def ltlToPro():
#     lnaFileLtl = "out.lna"
#     ltlFile = "test.prop"
#     jsonFile = "etherGame.json"
#     outltlFile = "outFile"
#     ltlcommand = "./ltl2prop --lna ./test/" + lnaFileLtl + " --json ./test/" + jsonFile + " --ltl ./test/" + ltlFile + " --out_file " + outltlFile
#     ltlPath = r"C:\Users\Admin\Desktop\(dev)SmartContractChecking-Application\tools\ltl2prop"
#     ltl2propro = subprocess.run(
#         ltlcommand, cwd=ltlPath, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

#ltlToPro()


##################################################################2
def dcr2cpn(xml):
    xmlFile = "test.xml"
    outFile = "outFile"
    commandDcr = "dcr2cpn --xml ./test/"+ xmlFile +" --out_file "+ outFile
    pathDcr = r"C:\Users\Admin\Desktop\(dev)SmartContractChecking-Application\tools\dcr2cpn"
    dcr2cpnpro = subprocess.run(commandDcr, cwd= pathDcr,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)

def unfolding(lna, context, param):
    lnaFile = "EtherGame.lna"
    contextFile = "context.lna"
    param = "function1"
    outFileUnf = "outFile"
    commandUnf = "unfolding --lna ./test/"+ lnaFile +"  --context ./test/"+ contextFile +" --param "+ param +" --out_file "+outFileUnf
    pathUnf = r"C:\Users\Admin\Desktop\(dev)SmartContractChecking-Application\tools\unfolding"
    unfolding = subprocess.run(commandUnf, cwd= pathUnf,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	
def ltlToPro():
    lnaFileLtl = "out.lna"
    ltlFile = "test.prop"
    jsonFile = "etherGame.json"
    outltlFile = "outFile"
    ltlcommand="ltl2prop --lna ./test/" + lnaFileLtl + " --json ./test/" + jsonFile + " --ltl ./test/"+ ltlFile + " --out_file " + outltlFile
    ltlPath = r"C:\Users\Admin\Desktop\(dev)SmartContractChecking-Application\tools\ltl2prop"
    ltl2propro = subprocess.run(ltlcommand, cwd= ltlPath,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)

def solidityToCpn():
	sodityFile = ""
	outsodility = ""
	soditycommand = ""
	soldityPath = r"C:\Users\Admin\Desktop\(dev)SmartContractChecking-Application\tools\ltl2prop"
	solidity2cpnpro = subprocess.run(soditycommand, cwd= soldityPath,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)


def runHelena():
	helenaFile1=""
	helenaFile2 = ""
	helena = "helena "+"output.lna"
	helenaPath = r"C:\Users\Admin\Desktop\(dev)SmartContractChecking-Application\tools\ltl2prop"
	pro4 = subprocess.run(helena, cwd= helenaPath,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	output = str(pro4.stdout.decode("cp932"))	
	start = output.find("Helena report")
	report = output[start:]
	print(report)
	return report