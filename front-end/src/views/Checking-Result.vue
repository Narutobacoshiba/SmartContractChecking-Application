<template>
    <div>
        <div id="cr-header">
            Checking Result
        </div>
        <div id="cr-content">
            <div id="crc-show-text">
                {{getCheckingResult}}
            </div>
            <div id="crc-button">
                <button class="button-style" role="button" @click="checkSLTL">Checking with the same LTL property and different configuration</button>
                <button class="button-style" role="button" @click="SaveCheckedBatch">Save Session</button>
                <button class="button-style" role="button" @click="checkDLTL">Checking with different LTL property</button>
            </div>
            <div id="crc-button">
                <button class="button-style" role="button" @click="startNewSession">Start a new checking session</button>
                <button class="button-style" role="button" @click="goPrePage">Back</button>
            </div>
        </div>  
    </div>
</template>

<script>
import {HistoryServices} from "../services/history.services"

export default ({
    data() {
        return{
            checking_result: "",
        }
    },
    mounted(){
        let checking_data = this.$store.getters["data/GetCheckingModelData"]
        this.checking_result = checking_data.data
    },
    computed:{
        getCheckingResult(){
            return this.checking_result
        }
    },
    methods: {
        createSaveSelectedSc(id){
            let selectedSc = this.$store.getters["data/GetSelectedSC"]
            let ret = []
            for(let i = 0; i<selectedSc.length; i++){
                ret.push({sid:selectedSc[i].id,cbsid:id})
            }
            return ret
        },
        createSaveContext(){
            let data = this.$store.getters["data/GetSelectedContext"].data
            let cpnContextData = this.$store.getters["data/GetGenerateModelData"].data["context"]       
            let user_id = this.$store.state.user.currentUser.id
            cpnContextData["ccid"] = data["ccid"]
            cpnContextData["aid"] = user_id
            cpnContextData["description"] = data["description"]
            return cpnContextData
        },
        createSaveVulnerability(){
            let selectedVulnerability = this.$store.getters["data/GetSelectedVulnerability"] 
            let ret = {}
            let current_date = Date.now()
            let user_id = this.$store.state.user.currentUser.id
            ret["vusid"] = this.hashValue("vulnerability"+current_date+user_id)
            ret["type"] = selectedVulnerability.type
            ret["subtype"] = selectedVulnerability.subtype
            if(ret["type"] == "specific"){
                if(ret["subtype"] == "temp"){
                    ret["formula_id"] = selectedVulnerability.params.id
                }else{
                    ret["formula_id"] = ""
                }
            
                ret["formula_name"] = selectedVulnerability.params.name
                ret["formula_description"] = selectedVulnerability.params.description
                ret["formula_content"] = selectedVulnerability.params.formula
            }else{
                ret["formula_name"] = selectedVulnerability.params.name
                ret["formula_id"] = ""
                ret["formula_description"] = selectedVulnerability.params.description
                ret["formula_content"] = JSON.stringify(selectedVulnerability.params.inputs)
            }
            
            return ret
        },
        createSaveHcpn(){
            let hcpnData = this.$store.getters["data/GetGenerateModelData"].data
            let ret = {}

            let user_id = this.$store.state.user.currentUser.id
            let current_date = Date.now()
            ret["lnid"] = this.hashValue("lnafile"+current_date+user_id)

            if("hcpn" in hcpnData){
                ret["hcpn_name"] = hcpnData["hcpn"]["name"]
                ret["hcpn_content"] = hcpnData["hcpn"]["content"]
            }else{
                ret["hcpn_name"] = ""
                ret["hcpn_content"] = ""
            }
            
            if("prop" in hcpnData){
                ret["prop_name"] = hcpnData["prop"]["name"]
                ret["prop_content"] = hcpnData["prop"]["content"]
            }else{
                ret["prop_name"] = ""
                ret["prop_content"] = ""
            }

            return ret
        },
        createSaveInitialMarking(){
            let user_id = this.$store.state.user.currentUser.id
            let initialMarking = this.$store.getters["data/GetInitialMarking"]
            let ret = {"IM":{},"balance":"","IMFunc":"","IMArg":""}

            let im = {}
            let current_date = Date.now()
            im["imid"] = this.hashValue("im"+current_date+user_id)
            im["num_user"] = parseInt(initialMarking["NumberOfUser"], 10)
            im["IM_type"] = ""
            ret["IM"] = im

            let balance = {}
            let raw_balnace = initialMarking["Balance"]
            balance["type"] = raw_balnace["type"]
            balance["from_value"] = parseInt(raw_balnace["random"]["from"],10)
            balance["to_value"] = parseInt(raw_balnace["random"]["to"],10)
            balance["fixed_value"] = parseInt(raw_balnace["fixed"],10)
            balance["range_value"] = raw_balnace["map"]
            balance["imid"] = im["imid"]
            ret["balance"] = balance

            let raw_func = initialMarking["Funtion_params"]
            let list_imfunc = []
            let list_arg = []
            for(let sc_id in raw_func){
                let sc_name = raw_func[sc_id].name
                let func_list = raw_func[sc_id].functions
                for(let f_id in func_list){
                    let func_name = func_list[f_id].name
                    let sender_v = func_list[f_id].sender_value

                    let imfunc = {}
                    let current_date = Date.now()
                    imfunc["imfid"] = this.hashValue("imfunc"+current_date+user_id+func_name)
                    imfunc["sc_name"] = sc_name
                    imfunc["func_name"] = func_name
                    imfunc["sender_from"] = sender_v.from
                    imfunc["sender_to"] = sender_v.to
                    imfunc["imid"] = im["imid"]
                    list_imfunc.push(imfunc)

                    let args = func_list[f_id].arguments
                    for(let arg_id in args){
                        let arg = args[arg_id]

                        let imarg = {}
                        imarg["arg_name"] = arg.name
                        imarg["range_from"] = arg.from
                        imarg["range_to"] = arg.to
                        imarg["imfid"] = imfunc["imfid"]

                        list_arg.push(imarg)
                    }
                }
            }
            ret["IMFunc"] = list_imfunc
            ret["IMArg"] = list_arg
            return ret
        },
        createCheckedBatch(lnid,vusid,ccid,imid){
            let ret = {}

            let user_id = this.$store.state.user.currentUser.id
            let current_date = Date.now()
            ret["cbsid"] = this.hashValue("checkedbatch"+current_date+user_id)
            ret["lnid"] = lnid
            ret["vusid"] = vusid
            ret["ccid"] = ccid
            ret["imid"] = imid
            let selectedSc = this.$store.getters["data/GetSelectedSC"]
            ret["noSC"] = selectedSc.length
            ret["checkedDate"] = current_date
            ret["status"] = true
            ret["result"] = this.$store.getters["data/GetCheckingModelData"].data
            ret["aid"] = user_id
            return ret
        },
        async SaveCheckedBatch(){
            try{
                let selectedContext = this.createSaveContext()
                let selectedVulnerability = this.createSaveVulnerability()
                let initialMarking = this.createSaveInitialMarking()
                let hcpnData = this.createSaveHcpn()
                let checkedBatch = this.createCheckedBatch(hcpnData["lnid"],selectedVulnerability["vusid"],selectedContext["ccid"],initialMarking["IM"]["imid"])
                let selectedSc = this.createSaveSelectedSc(checkedBatch["cbsid"])
                /* console.log(selectedSc)
                console.log(selectedContext)
                console.log(selectedVulnerability)
                console.log(initialMarking)
                console.log(hcpnData)
                console.log(checkedBatch) */
                await HistoryServices.SaveCheckedBatchSmartContract(selectedSc,selectedContext,selectedVulnerability,initialMarking,hcpnData,checkedBatch)
            }catch(error){
                console.log(error)
            }
        },
        checkSLTL(){
            this.$store.commit("data/ResetGenerateModelData")
            this.$store.commit("data/ResetCheckingModelData")
            this.$store.commit("data/ResetInitialMarking")
            this.$store.commit("data/SetCheckingRoadView",3)
            this.$store.commit("data/SetCurrentRoadView",3)
            this.$router.push({ name: "InitialMarkingSetting" })
        },
        checkDLTL(){
            this.$store.commit("data/ResetGenerateModelData")
            this.$store.commit("data/ResetCheckingModelData")
            this.$store.commit("data/ResetSelectedVulnerability")
            this.$store.commit("data/SetCheckingRoadView",3)
            this.$store.commit("data/SetCurrentRoadView",3)
            this.$router.push({ name: "LtlCheckingOptions" })
        },
        startNewSession(){
            this.$store.commit("data/ResetAllData")
            this.$router.push({ name: "SmartContractSelection" })
        },
        goPrePage(){
            this.$router.push({ name: "CheckCPNModel" })
        },
    }
})
</script>

<style scoped>
/* header */
#cr-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 20px;
    margin-bottom: 20px;
}

/* content */
#cr-content{
    width: 60%;
    margin:auto;
}

#crc-show-text{
    width: 90%;
    height: 400px;
    margin: auto;
    margin-bottom: 20px;
    padding-left: 10px;
    padding-top: 5px;
    padding-bottom: 5px;
    border: 1px solid black;
    border-radius: 4px;
    white-space: pre-line;
    overflow-y: auto;
}

/* Button */
#crc-button{
    width: 100%;
    height: 60px;
    margin: auto;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.button-style {
  background-color: #FFFFFF;
  border: 0;
  border-radius: .5rem;
  box-sizing: border-box;
  color: #111827;
  font-family: "Inter var",ui-sans-serif,system-ui,-apple-system,system-ui,"Segoe UI",Roboto,"Helvetica Neue",Arial,"Noto Sans",sans-serif,"Apple Color Emoji","Segoe UI Emoji","Segoe UI Symbol","Noto Color Emoji";
  font-size: .875rem;
  font-weight: 600;
  line-height: 1.25rem;
  padding: .75rem 1rem;
  text-align: center;
  text-decoration: none #D1D5DB solid;
  text-decoration-thickness: auto;
  box-shadow: 0 2px 4px 0 rgba(0, 0, 0, 0.1), 0 2px 3px 0 rgba(0, 0, 0, 0.06);
  cursor: pointer;
  user-select: none;
  -webkit-user-select: none;
  touch-action: manipulation;
}

.button-style:hover {
  background-color: rgb(249,250,251);
}

.button-style:focus {
  outline: 2px solid transparent;
  outline-offset: 2px;
}

.button-style:focus-visible {
  box-shadow: none;
}
</style>
