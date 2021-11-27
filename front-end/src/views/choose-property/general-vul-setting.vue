<template>
    <div id="gvs-container">
        <div id="gvs-header">
                General Vulnerabilty Setting 
        </div>
        <div id="gvs-frontbar">
            <div id="gvs-list-vul">
                <div class="gvs-list-label gvs-list-row">
                    Vulnerability
                </div>
                <div class="gvs-vul-element gvs-list-row" v-for="v in list_vulnerability" :key="v.id" @click="selectVul(v.id)" 
                    :class="{'gvs-selected-row':selected_vul == v.id, 'gvs-unselected-row': selected_vul != v.id}">
                    <li>{{v.name}}</li>
                </div>
            </div>  
            <div id="gvs-vul-description">
                <div class="gvs-list-label gvs-list-row">
                    Description
                </div>
                <div id="gvs-vul-text">
                    {{getVulDescription}}
                </div>
            </div>
        </div>
        <div id="gvs-content">
            <div id="gvsc-selec-vul">
                <IouConfig v-if="getSelectedVul == 'iou'"/>
                <TdepConfig v-if="getSelectedVul == 'tdep'"/>
                <SdesConfig v-if="getSelectedVul == 'sdes'"/>
                <!-- <img id="gvs-image-else" src="../../assets/dark-cloud.png" v-else> -->
            </div>
            <div id="ssc-button">
                <button class="button-style" role="button" @click="goNextPage">Next</button>
                <button class="button-style" role="button" @click="goPrePage">Back</button>
            </div>
        </div>
    </div>
</template>

<script>
import IouConfig from "../../components/general-vul-setting/iou-config.vue"
import TdepConfig from "../../components/general-vul-setting/tdep-config.vue"
import SdesConfig from "../../components/general-vul-setting/sdes-config.vue"

export default({
    components: {IouConfig,TdepConfig,SdesConfig},
    data() {
        return{
            list_vulnerability: [{name:"Interger Overflow/Underflow",id:"iou"},{name:"Reetrancy",id:"ree"},{name:"Self-destruction",id:"sdes"},
                        {name:"Timestamp Dependence",id:"tdep"},{name:"Skip Empty String Literal",id:"sesl"},{name:"Uninitialized Storage Variable",id:"usv"},
                        {name:"Others",id:"oth"}],
            selected_vul: "",
            vulnerability_descriptions: {"iou":"outOfRange(x) = (x < minThreshold) V (x > maxThreshold)",
                                         "sdes":"There are 2 options: \n   • The user chooses only one smart contract then the user needs to choose a function in the smart contract for the vulnerability. \n   • If the user chooses more than one smart contract and after choosing a function in the frst one the user chooses another smart contract, the system will go to option 2 of Self-destruction (2 functions). If the user does not choose any function, the system goes to option 1 (only one function is chosen)",
                                         "tdep":"Since the execution on a Blockchain needs to be deterministic for all the miners to get the same results and reach a consensus, users usually resort to block-related variables such as timestamp as a source of entropy"},
        }
    },
    beforeMount(){
        let temp = this.$store.getters["data/GetSelectedVulnerability"]
        if(!("id" in temp.params)){
            this.selected_vul = "iou"
            this.setOutData()
        }else{
            let id = temp.params.id
            this.selected_vul = id
            if(id == "iou"){
                this.setOutData()
            }else if(id == "sdes"){
                this.setSdesData()
            }else if(id == "tdep"){
                this.setTdepData()
            }
        }
    },
    computed: {
        getVulDescription(){
            return this.vulnerability_descriptions[this.selected_vul]
        },
        getSelectedVul(){
            return this.selected_vul
        }
    },
    methods: {
        selectVul(id){
            if(this.selected_vul != id){
                if(confirm("Current you choose iou vulnerability, did you want to reset it!") == true){
                    if(id == "iou"){
                        this.setOutData()
                    }else if(id == "sdes"){
                        this.setSdesData()
                    }else if(id == "tdep"){
                        this.setTdepData()
                    }
                    this.selected_vul = id
                }
            }
        },
        setOutData(){
            let temp = this.$store.getters["data/GetSelectedVulnerability"]
            if(!("inputs" in temp.params) || this.selected_vul != "iou"){
                temp.params = {id:"iou",name:"under_over_flow",description:this.vulnerability_descriptions["iou"],inputs:{"min_threshold":"0","max_threshold":"65535","selected_variable":""}} 
                this.$store.commit("data/SetSelectedVulnerability",temp)   
            }
        },
        setSdesData(){
            let temp = this.$store.getters["data/GetSelectedVulnerability"]
            if(!("inputs" in temp.params) || this.selected_vul != "sdes"){
                temp.params = {id:"sdes",name:"self_destruction",description:this.vulnerability_descriptions["sdes"],inputs:{"selected_function":""}} 
                this.$store.commit("data/SetSelectedVulnerability",temp)   
            }
        },
        setTdepData(){
            let temp = this.$store.getters["data/GetSelectedVulnerability"]
            if(!("inputs" in temp.params) || this.selected_vul != "tdep"){
                temp.params = {id:"tdep",name:"timestamp_dependence",description:this.vulnerability_descriptions["tdep"],inputs:{"selected_function":""}} 
                this.$store.commit("data/SetSelectedVulnerability",temp)   
            }
        },
        goNextPage(){
            this.$router.push({ name: "InitialMarkingSetting"})
        },
        goPrePage(){
            this.$router.push({ name: "LtlCheckingOptions"})
        }
    }
})
</script>

<style scoped>
#gvs-container{
    min-width: 900px;
}
/* header */
#gvs-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 20px;
    margin-bottom: 20px;
}
/* front-bar */
#gvs-frontbar{
    position: fixed;
    margin-left: 2%;
    width: 28%;
    min-width: 260px;
    background-color: #f6f8fa;
    border: 0.5px solid #dfe4e9;
    border-radius: 6px;
    box-sizing: border-box;
}

.gvs-list-row{
    border: 0.5px solid #dfe4e9;
    height: 40px;
    display: flex;
    align-items: center;
    color: #24292f;
    text-overflow: ellipsis;
}

.gvs-list-label{
    padding-left: 5px;
    font-size: 15px;
    font-weight: bold;
    border: 1px solid #dddfe0;
    background-color: #ebecec;
    color: #383b3f;
}
.gvs-vul-element{
    padding-left: 25px;
    font-size: 14px;
    cursor: pointer;
}

.gvs-unselected-row:hover{
    background-color: #f0f1f3;
}

#gvs-vul-text{
    width: 96%;
    height: 140px;
    margin: 2% 2% 2% 2%;
    background-color: white;
    padding: 2% 2% 2% 2%;
    font-size: 12px;
}

.gvs-selected-row{
    background-color: #ffffff;
    border-left: 2px solid brown;
}

/* content */
#gvs-content{
    margin-left: 35%;
    width: 55%;
    height: 580px;
}

#gvsc-selec-vul{
    width: 100%;
    height: 500px;
}

#gvs-image-else{
    height: 200px;
    width: 400px;
    margin-left: calc(50% - 200px);
    margin-top: 150px;
}
/* Button */
#ssc-button{
    width: 100%;
    height: 80px;
    margin: auto;
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