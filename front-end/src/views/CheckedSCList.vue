<template>
    <div>
        <div id="csl-header">
            Checked Smart Contract List
        </div>
        <div id="csl-content">
            <div id="table-list">
                <div class="table-row" id="header-row">
                    <div class="table-cell header-cell first-cell">
                        #
                        <span class="material-icons "> swap_vert </span>
                    </div>
                    <div class="table-cell header-cell second-cell">
                        Checker
                        <span class="material-icons "> swap_vert </span>
                    </div>
                    <div class="table-cell header-cell third-cell">
                        Checked Date
                        <span class="material-icons "> swap_vert </span>
                    </div>
                    <div class="table-cell header-cell fourth-cell">
                        Number of smart contracts
                        <span class="material-icons "> swap_vert </span>
                    </div>
                </div>

                <div id="table-content">
                    <div class="table-row" v-for="(val, index) in getBatches" v-bind:key="val.id" :class="{ even_row: index % 2 == 0}" @click="selectBatch(val.id)">
                        <div class="table-cell first-cell">{{ index+1 }}</div>
                        <div class="table-cell second-cell">{{ val.checker }}</div>
                        <div class="table-cell third-cell">{{ convertDate(val.checkedDate) }}</div>
                        <div class="table-cell fourth-cell">{{ val.noSC}}</div>
                    </div>
                </div>
            </div>
            <div id="csl-button">
                <button class="button-style" role="button" @click="goNextPage" v-if="isCurrentData">next</button>
                <button class="button-style" role="button" @click="startNewCheckingSession">Start a new checking session</button>
                <button class="button-style" role="button" @click="goHome">Back</button>
            </div>
        </div>
    </div>
</template>

<script>
import {HistoryServices} from "../services/history.services"
import { SmartContractService } from "../services/smartcontract.services.js";

export default({
    data() {
        return {
            batches: []
        }  
    },
    mounted(){
        this.getCheckedBatchSc()
    },
    computed:{
        getBatches(){
            return this.batches
        },
        isCurrentData(){
            return this.$store.getters["data/GetCheckingRoadView"] > 1
        }
    },
    methods: {
        startNewCheckingSession(){
            this.$store.commit("data/ResetAllData")
            this.$router.push({ name: "SmartContractSelection" })
        },
        goHome(){
            this.$router.push({ name: "Index" })
        },
        goNextPage(){
            this.$router.push({ name: "SmartContractSelection" })
        },
        async getCheckedBatchSc(){
            try{
                let response = await HistoryServices.GetCheckedBatchSmartContract()
                this.batches = response.data
            }catch(error){
                console.log(error)
            }
        },
        convertDate(value){
            var date = new Date(value)
            var datestring = ""+date.getDate()
            var monthstring = ""+(date.getMonth()+1)
            var hourstring = ""+date.getHours()
            var minutestring = ""+date.getMinutes()
            hourstring = (hourstring.length == 1 ? '0'+hourstring:hourstring)
            minutestring = (minutestring.length == 1 ? '0'+minutestring:minutestring)
            datestring = (datestring.length == 1 ? '0'+datestring:datestring)
            monthstring = (monthstring.length == 1 ? '0'+monthstring:monthstring)
            return datestring+"/"+monthstring+"/"+date.getFullYear()+" "+hourstring+":"+minutestring
        },
        async selectBatch(id){
            try{
                let response = await HistoryServices.GetCheckedBatchByID(id)
                
                this.updateData(response.data)
            }catch(error){
                console.log(error)
            }
        },
        async updateAllSc(selected_sc){
            let pre_map = []    
            selected_sc.forEach(i => pre_map.push(i.id)) 

            let data = []
            try{
                let response = await SmartContractService.getSmartContractInformation(pre_map)
                data = response.data
            }catch(error){
                console.log(error)
            }

            this.$store.commit("data/SetSCSelectedInfo",data)
        },
        async updateData(data){
            this.$store.commit("data/ResetAllData")

            this.$store.commit("data/SetSelectedSC",data["selected-sc"])
           
            await this.updateAllSc(data["selected-sc"])

            this.$store.commit("data/SetSelectedContext",data["selected-context"])

            let vul = data["selected-vulnerability"]
            let vul_set = {type:"",subtype:"",params:{}}
            vul_set.type = vul.type
            vul_set.subtype = vul.subtype
            vul_set.params["name"] = vul.name
            if(vul_set.type == "general"){
                vul_set.params["inputs"] = JSON.parse(vul.content)
            }else if(vul_set.type == "specific"){
                vul_set.params["description"] = vul.description
                vul_set.params["formula"] = vul.content
                vul_set.params["formula_text"] = vul.content_text
                if(vul_set.subtype == "temp"){
                    vul_set.params["id"] = vul.id
                }
            }
            this.$store.commit("data/SetSelectedVulnerability",vul_set)

            let initialM = data["initial-marking"]
            let initialM_set = {NumberOfUser: null,Balance:{type: "fixed",fixed: null,random: {from: null, to: null},map: null},Funtion_params: {}}
            initialM_set.NumberOfUser = initialM["NumberOfUser"]
            initialM_set.Balance = initialM["Balance"]
            this.$store.commit("data/SetInitialMarking",initialM_set)

            let hcpn_set = {generated: true,code: "success",data: data["hcpn"]}
            this.$store.commit("data/SetGenerateModelData",hcpn_set)

            let checking_set = {checked: true,code: "success",data: data["checking-result"]}
            this.$store.commit("data/SetCheckingModelData",checking_set)

            this.$router.push({ name: "CheckingResult" })
        }
    }
})
</script>

<style scoped>
/* header */
#csl-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 30px;
    margin-bottom: 30px;
}
/* content */
#csl-content{
    width: 60%;
    height: 400px;
    margin: auto;
}

#table-list {
  width: 100%;
  margin: auto;
  font-size: 0.9em;
  height: 100%;
  border-radius: 4px;
  border: 2px solid black;
  
  background: rgb(241, 240, 240);
}
#table-content{
    height: 80%;
    overflow-y: auto;
}
.table-row{
  display: flex;
  height: 42px;
}
#header-row{
  background-color: rgb(196, 194, 194);
  font-weight: bold;
}
#table-list span {
  float: right;
  margin: 0 10% 0 0;
  padding: 0;
  font-size: 150%;
}
.even_row{
  background-color: rgb(226, 224, 224);
}
.table-cell{
    margin-top: 10px;
}
.first-cell{
  flex-basis: 20%;
  padding-left: 5px;
}
.second-cell{
  flex-basis: 30%;
}
.third-cell{
  flex-basis: 20%;
}
.fourth-cell{
    flex-basis: 30%;
    text-align: center;   
}
#table-content .table-row{
    cursor: pointer;
}
#table-content .table-row:hover{
    background-color: rgb(163, 189, 219);
}

/* Button */
#csl-button{
    height: 80px;
    margin-top: 20px;
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