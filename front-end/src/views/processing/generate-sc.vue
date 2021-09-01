<template>
        <div id="body">
            <div id="showConfirmation" v-if="showConfirmation">
                    <div id="removeAll-holder" v-if="confirmation == 'removeAll'">
                        <confirm @cancel="closeConfirm" @confirm="cfRemoveAll" :dialog="dialog" />
                    </div>
                    <div id="removeSC-holder"  v-if="confirmation == 'removeSC'">
                        <confirm @cancel="closeConfirm" @confirm="cfRemoveSC(currentSC)" :dialog="dialog"/>
                    </div>
            </div>
            <div id="header">
                <p>Selected Smart Contracts</p>
            </div>
            <div id="table">
                <div id = "sscs-header">
                    <div id="sscsh-name">Selected Smart Contracts</div>
                    <div id="rma-button" @click="removeAllSc">Remove All</div>
                </div>
                <div id="sscs-table">
                    <div v-if="isSelectSomeThing != true" class="noneHandler">
                        <p>Please click on the <a id="link-text" @click="routing('sc-selection')">Add Smart Contracts</a> to select your Smart Contracts for checking!</p>
                    </div>
                    <div v-else>
                        <div v-for="(sc, idx) in selectedSc" :key="idx" class="table-row"> 
                            <div class="index-cell table-cell">{{inc(idx)}}</div>
                            <div class="name-cell table-cell">{{sc.name}}</div>
                            <div class="action-cell table-cell">
                                <i class="material-icons" @click="editSC(sc.id,sc.name)">build</i>
                                <i class="material-icons" @click="removeSC(sc)">delete</i>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div id="chosen-vul-context">
                <div class="row">
                    <div class="col-3 title">Vulnerability/CS-Property</div>
                    <div class="col-7 list">
                        <div v-if="list_selected_vuls.length > 0">
                            <div v-for="vul in list_selected_vuls" :key="vul">{{vul.name}}</div>
                        </div>
                        <div v-else>No selected Vulnerability, please click Add New</div>
                    </div>
                    <div class="col-2">
                        <button @click="routing('choose-vul')" class="btn btn-outline-primary btn-sm" title="Go back to Property Checking Options">Add New</button>
                    </div>
                </div>
                <div class="row">
                    <div class="col-3 title">Context</div>
                    <div class="col-7 list">
                        <div v-if="context.length > 0">
                            <div v-for="con in context" :key="con">{{con.context}}</div>
                        </div>
                        <div v-else>No selected Context, please click Add New</div>
                    </div>
                    <div class="col-2"><button @click="routing('select-context')" class="btn btn-outline-primary btn-sm" title="Change the Context">Change</button></div>
                </div>
            </div>

            <div id="processing-btn">
                <button v-if="step == 'initial' || step == 'generating'" class="btn btn-primary" @click="generate">Generate</button>
                <button v-else class="btn btn-primary" @click="check">Check</button>
            </div>        

            <div id="processing-section">

                
                <div id="download"><a v-if="showDownload" class="btn btn-primary btn-sm" href="" download="Solidity">Download</a></div>
                <div id="initial" v-if="step == 'initial'"></div>
                <div id="generating" v-show="step == 'generating'">
                    <div>The smart contract is generating...</div>
                    <div class="progress" id="progress">
                        <div id="progress-bar-gen" class="progress-bar progress-bar-striped bg-warning" role="progressbar" style="width: 0%"></div>
                    </div>
                </div>
                <div id="generated" v-if="step == 'generated'">The generating process completed successfully</div>
                <div id="checking" v-show="step == 'checking'">
                    <div>The smart contract is checking...</div>
                    <div class="progress" id="progress">
                        <div id="progress-bar-check" class="progress-bar progress-bar-striped bg-warning" role="progressbar" style="width: 0%"></div>
                    </div>
                </div>
                <div id="checked" v-if="step == 'checked'">The checking process completed successfully</div>
                <div id="results" v-if="this.results.length > 0 && step == 'finish'" >
                    <div><h3>Results:</h3></div>
                    <div v-for="r in this.results" :key="r">{{r}}</div>
                </div>
            </div>

            





        </div>
</template>



<script>
    import ConfirmationDialog from "../../components/ConfirmationDialog.vue"
    export default {
        components:{'confirm': ConfirmationDialog},
        data() {
            return {
                list_selected_sc: [],
                list_selected_vuls: [],
                context: [],
                user: {user_name: "Dinh Thanh Ha"},
                step: 'initial',
                error: true,
                view: '',
                results: ['Result 1', 'Result 2', 'Result 3'],
                showConfirmation: false,
                dialog: {},
                confirmation: '',
                currentSC: null
            };
        },
        methods: {
            move(id) {
                //let _this = this;
                var elem = document.getElementById(id);
                var width = elem.offsetWidth;
                if(width >= 0) width = 0;
                var inter = setInterval(() => {
                if (width >= 100) {
                    clearInterval(inter);
                } else {
                    width++;
                    elem.style.width = width + "%";
                }}, 10);
            },
            async delay(ms) {
                return await new Promise(resolve => setTimeout(resolve, ms));
            },
            async generate(){
                this.step = 'generating';
                this.move('progress-bar-gen');
                await this.delay(2000)
                this.step = 'generated';
                this.$store.commit("data/SetProcessView","check-sc")
            },
            async check(){
                this.step = 'checking';
                this.move('progress-bar-check');
                await this.delay(2000)
                if(this.error) confirm(
                    "We have discover some counter-examples with the smart contract code. Do you want tolook at them?"
                );
                this.step = 'checked';
                await this.delay(2000);
                this.step = 'finish';
                this.$store.commit("data/SetProcessView","finish")
            },
            routing(processview){
                this.$store.commit("data/SetProcessView", processview)
            },
            addSmartContract(){
                this.$store.commit("data/SetProcessView",'sc-selection')
            },
            inc(value){
                return value+1
            },
            removeSC(sc){
                this.dialog = {title: 'Remove Smart Contract', message: "Are you sure to remove '"+sc.name+"' ?", confirmbtn: 'Remove'}
                this.confirmation = 'removeSC'
                this.currentSC = sc.id
                this.showConfirmation = true
            },
            cfRemoveSC(id){
                for( var i = 0; i < this.list_selected_sc.length; i++){ 
                    if ( this.list_selected_sc[i].id === id) { 
                        this.list_selected_sc.splice(i, 1); 
                    }
                }
                this.$cookies.set("_ssc",JSON.stringify(this.list_selected_sc))
                this.closeConfirm()
            },
            editSC(sc_id,sc_name){
                this.$router.push({name: "EditSc", params: {sc_id: sc_id, name: sc_name, parent_path: "/process"}})
            },
            removeAllSc(){
                if(this.list_selected_sc.length > 0)
                {   
                    this.confirmation = 'removeAll'
                    this.dialog = {title: 'Remove All', message: 'Are you sure to remove all selected smart contracts?', confirmbtn: 'Remove All'}
                    this.showConfirmation = true
                }
            },
            cfRemoveAll(){
                this.list_selected_sc = []
                this.$store.commit("data/SetSelectedSC", this.list_selected_sc);
                this.$cookies.set("_ssc",JSON.stringify(this.list_selected_sc))
                this.closeConfirm();
            },
            closeConfirm(){
                this.showConfirmation = false
            }
        },
        mounted() {
            this.list_selected_sc = this.$store.getters["data/GetSelectedSC"];
            this.context = this.$store.getters["data/GetSelectedContext"];
            this.list_selected_vuls = this.$store.getters["data/GetSelectedVulnerbility"];
            this.view = this.$store.getters["data/GetProcessView"];
        },
        computed:{
            selectedSc(){
                return this.list_selected_sc
            },
            isSelectSomeThing(){
                return this.list_selected_sc.length > 0
            },
            getStep(){
                return this.step
            },
            showDownload(){
                return this.step != 'initial'&& this.step != 'generating';
            }
        },
    };
</script>


<style scoped>
    
#body{
    width: 60%;
    padding: auto;
    margin: auto;
}
#header{
    margin-top: 20px;
    text-align: center;
    font-size: 2.3em;
    font-weight: bold;
}
/*--table-- */
#table{
    height: auto;
    width: 100%;
    border: 1px solid #d9edf7;
    border-radius: 6px;
    margin: auto;
}
#sscs-body{
    width: 100%;
    border: 1px solid #d9edf7;
    border-radius: 6px;
}
#sscs-header{
    width: 100%;
    height: 40px;
    background-color: #d9edf7;
    padding: 9px;
}
#sscs-header #sscsh-name{
    display: inline-block;
    margin-left: 4%;
    font-size: 13;
    font-weight: bold;
    color: #3a7694;
}
#sscs-header #rma-button{
    width: 100px;
    height: 24px;

    float: right;
    border: 1px solid #4b97bd;
    border-radius: 2px;
    color: #4b97bd;
    padding: 0px 8px;
    cursor: pointer;
}
#sscs-header #rma-button:hover{
    background-color: #3c7c9c;
    color: white;
}
#sscs-table{
    width: 100%;
    height: auto;
    min-height: 120px;
    max-height: 180px;
    overflow-y: auto;
}

#link-text{
    color: #5ca5d3;
    font-weight: bold;
    cursor: pointer;
}
#link-text:hover{
    color: #77c0ec;
}
.noneHandler{
    font-size: 13px;
    margin-top: 10px;
    margin-left: 10px;
    color: rgb(43, 41, 41);
}
/* --- table --- */
.table-row{
    width: 100%;
    height: 40px;
    
    display: flex;
    color: #585858;
    border-bottom: 0.5px solid #d8d7d7;
}
.index-cell{
    flex-basis: 10%;
    justify-content: center;
}
.name-cell{
    flex-basis: 70%;
    padding-left: 6%;
    justify-content: left;
    overflow: hidden;
    text-overflow: ellipsis;
}
.action-cell{
    flex-basis: 20%;
    justify-content: center;
}
.action-cell i{
    padding: 8px;
    color: #858383;
    cursor: pointer;
}
.table-cell{
    overflow: hidden;
    display: flex;
    align-items: center;
}
.table-row:hover{
    background-color: #fafafa;
}
.action-cell i:hover{
    color: #5e5d5d;
}
/*--Selected Vul-Context-- */
#chosen-vul-context{
    margin-top: 30px;
}
#chosen-vul-context .row{
    margin-top: 30px;
}
.title{
    font-size:17px;
}
.list{
    border: solid rgba(0,0,0,.125) 1px;
    border-radius: 3px;
    padding: 8px;
}
#chosen-vul-context button{
    float: right;
    width: 100%;
    max-width: 80px;
}

/*Process Section */
#processing-btn{
    margin: 40px;
    text-align: center;
}
#download{
    text-align: right;
    padding: 20px;
    height: 60px;
}
#processing-section{
    height: 300px;
    margin: auto;
    border: 1px black solid;
    border-radius: 3px;
    text-align: center;
    background-color: #f5f5f5;
}
#generating .progress, #checking .progress{
    width: 100%;
    margin: 10px 0;
    height: 20px;
}
#generating, #checking{
    margin: auto;
    margin-top: 60px;
    padding: 0;
    width: 70%;
}
#results{
    margin-left: 40px;
    text-align: left;
    margin-top: 0;
}
#generated, #checked{
    margin-top: 100px;
} 
/*---- showConfirmation */
 #showConfirmation{
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0,0,0,0.2);
    z-index: 1;
    align-items: center;
    justify-content: center;
}
#removeSC-holder{
    margin-top: 200px;
}
#removeAll-holder{
    margin-top: 50px;
}
</style>