<template>
    <div>
        <div id="gcm-header">
            Generating CPN Model
        </div>
        <div id="gcm-content">
            <div id="gcm-smartcontract" class="gcm-c-row">
                <div class="gcm-c-label">
                    Smart Contracts
                </div>
                <div class="gcm-c-view">
                    <SmartcontractTable/>
                </div>
            </div>
            <div id="gcm-context" class="gcm-c-row">
                <div class="gcm-c-label">
                    Context
                </div>
                <div class="gcm-c-view">
                    <div id="gcm-context-text" class="gcm-c-name">
                        {{context_name}}
                    </div>
                </div>
            </div>
            <div id="gcm-property" class="gcm-c-row">
                <div class="gcm-c-label">
                    LTL property
                </div>
                <div class="gcm-c-view">
                    <div id="gcm-prop-text" class="gcm-c-name">
                        {{property_name}}
                    </div>
                </div>
            </div>
            <div id="gcm-configuration" class="gcm-c-row">
                <div class="gcm-c-label">
                    Configuration
                </div>
                <div class="gcm-c-view">
                    <div id="gcm-con-text" @click="goPrePage">
                        Link to the setting configuration
                    </div>
                </div>
            </div>

            <div id="gcm-loading-process" v-if="isGenerating == true">
                <div id="gcm-loading" v-if="waitResponse == true"></div>
                <div id="gcm-response" v-else>{{getResponse}}</div>
            </div>

            <div id="gcm-button" v-if="isGenerateSucess == false">
                <button class="button-style" role="button" @click="generateModel">Generate</button>
                <button class="button-style" role="button" @click="goPrePage">Back</button>
            </div>
            <div id="gcm-button" v-else>
                <button class="button-style" role="button" @click="goNextPage">next</button>
                <button class="button-style" role="button" @click="generateModel">Re-generate</button>
                <button class="button-style" role="button" @click="downloadData">Download</button>
                <button class="button-style" role="button" @click="goPrePage">Back</button>
            </div>
        </div>
    </div>
</template>

<script>
import SmartcontractTable from "../components/generate-cpn-model/SmartcontractTable.vue"
import {ToolsServices} from "../services/tools.services"
import { saveAs } from 'file-saver'

export default ({
    components: {SmartcontractTable},
    data() {
        return {
            context_name: "None",
            property_name: "None",
            generate_data: {},
            wait_response: false,
            response_message: "",
            is_success: false,
            is_generate: false,

            hcpn: {name:"",content:""},
            prop: {name:"",content:""},
        }
    },
    watch: {
        generate_data: {
            handler(val){
                if(val.generated && "hcpn" in val.data && "prop" in val.data){
                    this.hcpn = val.data.hcpn
                    this.prop = val.data.prop
                }
                this.$store.commit("data/SetGenerateModelData", val);
            },
            deep: true
        }
    },
    beforeMount(){
        let context = this.$store.getters["data/GetSelectedContext"]
        if(context.used && 'name' in context.data){
            this.context_name = context.data.name
        }

        let property = this.$store.getters["data/GetSelectedVulnerability"]
        if("name" in property.params){
            this.property_name = property.params.name
        }

        this.generate_data = this.$store.getters["data/GetGenerateModelData"]
        this.is_generate = this.generate_data.generated
        if(this.generate_data.generated){
            if(this.generate_data.code == "error"){
                this.is_success = false
                if("message" in this.generate_data.data){
                    this.response_message = this.generate_data.data.message
                }else{
                    this.generate_data.data.message = ""
                }
            }else if(this.generate_data.code == "success"){
                this.is_success = true
                this.response_message = "The generating process completed successfully"
                if("hcpn" in this.generate_data.data){
                    this.hcpn = this.generate_data.data.hcpn
                }
                if("prop" in this.generate_data.data){
                    this.prop = this.generate_data.data.prop
                }
            }
        }
    },
    computed:{
        isGenerating(){
            return this.is_generate
        },
        waitResponse(){
            return this.wait_response
        },
        getResponse(){
            return this.response_message
        },
        isGenerateSucess(){
            return this.is_success
        }
    },
    methods:{
        async generateModel(){
            try{
                this.$store.commit("data/SetCheckingRoadView",5)
                this.$store.commit("data/ResetGenerateModelData")
                this.$store.commit("data/ResetCheckingModelData")

                this.is_generate = true

                this.wait_response = true
                
                let selectedSc = this.$store.getters["data/GetSelectedSC"]
                let selectedContext = this.$store.getters["data/GetSelectedContext"]
                let selectedVulnerability = this.$store.getters["data/GetSelectedVulnerability"]
                
                let initialMarking = this.$store.getters["data/GetInitialMarking"]
                let ret_initialMarking = {"smart_contract":[],"balance":{},"NumberOfUser":""}
                ret_initialMarking["NumberOfUser"] = initialMarking["NumberOfUser"]
                ret_initialMarking["balance"] = initialMarking["Balance"]
                for (const [key, value] of Object.entries(initialMarking["Funtion_params"])) {
                    let sc = {}
                    sc["id"] = key
                    sc["name"] = value["name"]  
                    sc["functions"] = []   

                    let functions = value["functions"]
                    for (const [fkey, fvalue] of Object.entries(functions)) {
                        let func = {}
                        func["id"] = fkey
                        func["name"] = fvalue["name"]
                        func["argument"] = fvalue["argument"]
                        func["sender_value"] = fvalue["sender_value"]
                        sc["functions"].push(func)
                    }
                    ret_initialMarking["smart_contract"].push(sc)
                }
                
                let response = await ToolsServices.generateCpnModel(selectedSc,selectedContext,selectedVulnerability,ret_initialMarking)
                
                this.response_message = "The generating process completed successfully"
                this.wait_response = false
                this.is_success = true
                
                this.generate_data = {generated:true,code:"success",data:response.data}
            }catch(error){

                this.response_message = error.detail
                this.wait_response = false
                this.is_success = false

                this.generate_data = {generated:true,code:"error",data:{message:error.detail}}
            }
        },
        goPrePage(){
            this.$router.push({ name: "InitialMarkingSetting" })
        },
        goNextPage(){
            this.$router.push({ name: "CheckCPNModel" })
        },
        downloadData(){
            let blob_hcpn = new Blob([this.hcpn.content], {
                type: "text/plain;charset=utf-8;",
            });

            let blob_prop = new Blob([this.prop.content], {
                type: "text/plain;charset=utf-8;",
            });

            saveAs(blob_hcpn, this.hcpn.name);
            saveAs(blob_prop, this.prop.name);
        }
    }
})
</script>

<style scoped>
/* header */
#gcm-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 30px;
    margin-bottom: 30px;
}

/* content */
#gcm-content{
    width: 60%;
    margin: auto;
}
.gcm-c-row{
    display: flex;
    justify-content: space-between;
}
.gcm-c-label{
    flex-basis: 20%;
    font-weight: bold;
}
.gcm-c-view{
    flex-basis: 80%;
}
#gcm-smartcontract{
    height: 180px;
}
#gcm-property, #gcm-configuration, #gcm-context{
    margin-top: 40px;
    height: 40px;
}
.gcm-c-name{
    width: 100%;
    height: 30px;
    border: 1px solid rgb(36, 35, 35);
    border-radius: 4px;
    display: flex;
    align-items: center;
    padding-left: 1%;
}
#gcm-con-text{
    color: rgb(55, 55, 248);
    text-decoration: underline;   
    cursor: pointer;   
}
#gcm-con-text:hover{
    color: rgb(4, 4, 167);
}
/* Button */
#gcm-button{
    width: 60%;
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

/* loading */
#gcm-loading-process{
    width: 50%;
    height: 140px;
    margin: auto;
    margin-top: 20px;
    
    border: 1px solid rgb(36, 35, 35);
    border-radius: 4px;

    overflow: hidden;
    background: white;
    display: flex;
    justify-content: center;
    align-items: center;
    overflow-y: auto;
}
#gcm-loading {
  width: 0.5em;
  height: 0.5em;
  border-radius: 50%;
  box-shadow:
    0 -1.5em rgb(66, 66, 66),
    1.125em -1.125em rgba(66, 66, 66, 0.875),
    1.5em 0 rgba(66, 66, 66, 0.75),
    1.125em 1.125em rgba(66, 66, 66, 0.625),
    0 1.5em rgba(66, 66, 66, 0.5),
    -1.125em 1.125em rgba(66, 66, 66, 0.375),
    -1.5em 0 rgba(66, 66, 66, 0.25),
    -1.125em -1.125em rgba(66, 66, 66, 0.125)
    ;
  animation: spin 1.2s linear infinite;
}

#gcm-response{
    font-weight: 500;
    padding-left: 3px;
    padding-right: 3px;
}

@keyframes spin {
  100% { transform: rotate(-360deg) }
}
</style>