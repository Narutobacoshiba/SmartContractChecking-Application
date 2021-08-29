<template>
    <div id="ssc-body">
        <div id="ssc-header">
            <p>Smart Contracts Selection</p>
        </div>
        <div id="ssc-selected">
            <div id="sscs-body">
                <div id = "sscs-header">
                    <div id="sscsh-name">Selected Smart Contracts</div>
                    <div id="rma-button" @click="removeAllSc">Remove All</div>
                </div>
                <div id="sscs-table">
                    <div v-if="isSelectSomeThing != true" class="noneHandler">
                        <p>Please click on the <a id="link-text" @click="addSmartContract">Add Smart Contracts</a> to select your Smart Contracts for checking!</p>
                    </div>
                    <div v-else>
                        <div v-for="(sc,idx) in selectedSc" :key="idx" class="table-row"> 
                            <div class="index-cell table-cell">
                                {{inc(idx)}}
                            </div>
                            <div class="name-cell table-cell">
                                {{sc.name}}
                            </div>
                            <div class="action-cell table-cell">
                                <i class="material-icons" @click="editSC(sc.id,sc.name)">build</i>
                                <i class="material-icons" @click="removeSC(sc)">delete</i>
                            </div>
                        </div>
                    </div>
                </div>
                <div id="ssc-action">
                    <div id="first-action">
                        <div id="ssc-add" @click="addSmartContract">Add Smart Contracts</div>
                    </div>
                    <div id="second-action">
                        <div id="ssc-upload" @click="uploadFile">Upload File</div>
                    </div>
                    <div id="third-action">
                        <div id="ssc-back" @click="routing('back')">Back</div>
                    </div>
                    <div id="fourth-action">
                        <div id="ssc-next" @click="routing('next')">Next</div>
                    </div>
                </div>
                
                <div id="showComponents" v-if="getShowComponents">
                    <div>
                        <AddSc @closeComponents="cComponents" v-if="getSelectComponents=='add'"/>
                        <UpLoadItems @closeComponents="cComponents" v-if="getSelectComponents=='upload'"/>
                    </div>
                </div>
                <div id="showConfirmation" v-if="showConfirmation">
                    <div id="removeAll-holder" v-if="confirmation == 'removeAll'">
                        <confirm @cancel="closeConfirm" @confirm="cfRemoveAll" :dialog="dialog" />
                    </div>
                    <div id="removeSC-holder"  v-if="confirmation == 'removeSC'">
                        <confirm @cancel="closeConfirm" @confirm="cfRemoveSC(idxSC)" :dialog="dialog"/>
                    </div>
                </div>
            </div>
            </div>
        </div>
</template>

<script>
import AddSc from "./sc-selection/add-multi-sc.vue"
import UpLoadItems from "./sc-selection/upload-data.vue"
import ConfirmationDialog from "../../components/ConfirmationDialog.vue"
export default ({
    components: {AddSc,UpLoadItems, 'confirm': ConfirmationDialog},
    data(){
        return {
            list_selected_sc: [],
            showComponents: false,
            selectComponents: '',
            showConfirmation: false,
            dialog: {},
            confirmation: '',
            idxSC: null
        }
    },
    mounted(){
        this.list_selected_sc = this.$store.getters["data/GetSelectedSC"]
    },
    computed: {
        selectedSc(){
            return this.list_selected_sc
        },
        isSelectSomeThing(){
            return this.list_selected_sc.length > 0
        },
        getShowComponents(){
            return this.showComponents
        },
        getSelectComponents(){
            return this.selectComponents
        }
    },
    methods: {
        cComponents(){
            this.list_selected_sc = this.$store.getters["data/GetSelectedSC"]
            this.showComponents = false
        },
        inc(value){
            return value+1
        },
        removeSC(sc){
            this.dialog = {title: 'Remove Smart Contract', message: "Are you sure to remove '"+sc.name+"' ?", confirmbtn: 'Remove'}
            this.confirmation = 'removeSC'
            this.showConfirmation = true
        },
        cfRemoveSC(idx){
            this.list_selected_sc.splice(idx,1)
            this.$cookies.set("_ssc",JSON.stringify(this.list_selected_sc))
            this.closeConfirm()
        },
        routing(param){
            if(param == "back"){
                this.$router.push("/")
            }
            if(param == "next"){
                this.$store.commit("data/SetProcessView","select-context")
            }
        },
        editSC(sc_id,sc_name){
            this.$router.push({name: "EditSc", params: {sc_id: sc_id, name: sc_name, parent_path: "/process"}})
        },
        addSmartContract(){
            this.selectComponents = 'add'
            this.showComponents = true
        },
        uploadFile(){
            this.selectComponents = 'upload'
            this.showComponents = true
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
    }
})
</script>

<style scoped>
#ssc-body{
    width: 100%;
    height: 530px;
}
#ssc-header{
    margin-top: 20px;
    text-align: center;
    font-size: 2.3em;
    font-weight: bold;
    color: #5fb8ee;
}
#ssc-selected{
    width: 60%;
    margin: 0 auto;
}

#sscs-body{
    height: 350px;
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
    height: 310px;
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

/* --- action --- */
#ssc-action{
    width: 100%;
    display: flex;
    justify-content: space-between;
    margin: 0 auto;
    margin-top: 30px;
}
#first-action{
    flex-basis: 20%;
}
#second-action{
    flex-basis: 60%;
}
#third-action{
    flex-basis: 15%;
}
#fourth-action{
    flex-basis: 5%;
}
#ssc-add{
    width: 160px;
    height: 30px;
    background-color: #2196f3;
    text-align: center;
    color: white;
    font-size: 13px;
    line-height: 22px;
    font-weight: 600;
    padding: 4px 3px;
    border-radius: 4px;
    cursor: pointer;
    border-width: 0px;
}
#ssc-add:hover{
    background-color: #1079cf;
}
#ssc-upload{
    width: 160px;
    height: 30px;
    background-color: #2196f3;
    text-align: center;
    color: white;
    font-size: 13px;
    line-height: 22px;
    font-weight: 600;
    padding: 4px 3px;
    border-radius: 4px;
    cursor: pointer;
    border-width: 0px;
}
#ssc-upload:hover{
    background-color: #1079cf;
}
#ssc-back{
    width: 60px;
    height: 30px;
    border: 1px solid rgb(221, 227, 240);
    border-radius: 4px;
    text-align: center;
    font-size: 13px;
    line-height: 22px;
    font-weight: 600;
    padding: 4px 3px;
    cursor: pointer;
}
#ssc-back:hover{
    border-color: #1079cf;
    color: #1079cf;
}
#ssc-next{

    width: 60px;
    height: 30px;
    background-color: #2196f3;
    text-align: center;
    color: white;
    font-size: 13px;
    line-height: 22px;
    font-weight: 600;
    padding: 4px 3px;
    border-radius: 4px;
    cursor: pointer;
    border-width: 0px;
}
#ssc-next:hover{
    background-color: #1079cf;
}

/* ---- showComponents ---- */
#showComponents{
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0,0,0,0.7);
    z-index: 100;
    display: flex;
    align-items: center;
    justify-content: center;
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
