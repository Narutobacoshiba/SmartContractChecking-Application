<template>
    <div>
        <div id="uc-header">
            <p>Upload SmartContract</p>
        </div>
        <div id="uc-body">
            <div class="uc-row">
                <div class="uc-first-cell">
                    <p>Upload</p>
                </div>
                <div class="uc-second-cell">
                    <div class="uc-show-smartcontract-info">
                        <input type="file" id="uc-upload-file" spellcheck="false" @change="uploadFile">
                    </div>
                </div>
            </div>
            <div class="uc-row">
                <div class="uc-first-cell">
                    <p>Name</p>
                </div>
                <div class="uc-second-cell">
                    <input class="uc-show-smartcontract-info" id="uc-set-smartcontract-name" type="text" v-model="smartcontract_name" />
                </div>
            </div>
            <div class="uc-row" id="uc-select-type">
                <div class="uc-first-cell">
                    <p>Type</p>
                </div>
                <div class="uc-second-cell">
                    <div class="uc-show-smartcontract-info">
                        <div id="select-box">
                            <input type="checkbox" id="options-view-button">
                            <div id="select-button">
                                <div id="selected-value">
                                    <span>{{getSelectSmartContractType}}</span>
                                </div>
                                <div id="chevrons">
                                    <span class="material-icons">expand_less</span>
                                    <span class="material-icons">expand_more</span>
                                </div>
                            </div>
                            <div id="options">
                                <span v-for="c in list_smartcontracts_type" :key="c" class="label" @click="selected_smartcontract_type = c" :class="{selected_smartcontract_type_row: c == selected_smartcontract_type}">{{c}}</span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="uc-row">
                <div class="uc-first-cell">
                    <p>Description</p>
                </div>
                <div class="uc-second-cell">
                    <textarea id="uc-description-text-input" spellcheck="false" v-model="smartcontract_description" />
                </div>
            </div>
        </div>
        <div id="ssc-button">
            <button role="button" @click="okEvent" :class="{'disable-button': is_uploaded == false,'button-style': is_uploaded == true}">Ok</button>
            <button class="button-style" role="button" @click="saveUploadFile">Upload</button>
            <button class="button-style" role="button" @click="cancelEvent">Cancel</button>
        </div>
    </div>
</template>

<script>
import { SmartContractService } from "../../services/smartcontract.services";

export default ({
    data(){
        return{
            smartcontract_description: "",
            smartcontract_name: "",
            smartcontract_content: "",

            list_smartcontracts_type: ["common","private"],
            selected_smartcontract_type: "common",
            file: null,
            is_uploaded: false
        }
    },
    computed: {
        getSelectSmartContractType(){
            return this.selected_smartcontract_type
        }
    },
    methods: {
        uploadFile(value){
            this.file = value.target.files.item(0)

            let file_name = this.file.name
            let holder = file_name.split(".")
            holder.pop()
            this.smartcontract_name = holder.join(".")
        },
        async saveUploadFile(){
            if(this.file == null){
                alert("You have to select the file to upload!")
            }else if(this.fileupload_name == '' || this.selected_smartcontract_type == '')
            {
                alert("You cannot leave the name field and the type field blank!")
            }else{
                try{
                    this.smartcontract_content = await this.file.text();
                    this.is_uploaded = true
                }
                catch (error){
                    this.is_uploaded = false
                }
            }
        },
        async okEvent(){
            if(this.is_uploaded){
                try{
                    let current_date = Date.now()
                    let user_id = this.$store.state.user.currentUser.id
                    let s_id = this.hashValue(this.smartcontract_name+current_date+user_id)

                    const res = await SmartContractService.createAllSmartContract(
                        s_id,
                        this.smartcontract_name,
                        this.selected_smartcontract_type,
                        current_date,
                        this.smartcontract_content,
                        this.smartcontract_description
                    )
                
                    this.selected_sc = this.$store.getters["data/GetSelectedSC"]
                    this.selected_sc.push({
                        id: s_id,
                        name: this.smartcontract_name,
                        description: this.smartcontract_description,
                        type: this.selected_smartcontract_type,
                        date_modified: current_date,
                        content: this.smartcontract_content
                    })
                    this.$store.commit("data/SetSelectedSC", this.selected_sc);
                    
                    console.log(res)

                    this.$router.push({ name: "SmartContractSelection"});
                }catch(error){
                    alert("failed to upload smart contract")
                }
            }else{
                alert("You have to upload the file first!")
            }
        },
        cancelEvent(){
            this.$router.push({ name: "SmartContractSelection"});
        }
    }
})
</script>

<style scoped>
#uc-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 40px;
    margin-bottom: 40px;
}

textarea{
    resize: none;
}
/* body */
#uc-body{
    width: 50%;
    margin: auto;
}
.uc-row{
    width: 100%;
    height: 80px;
    display: flex;
    justify-content: space-between;
}
.uc-first-cell{
    font-weight: bold;
    color: rgb(53, 46, 46);
    flex-basis: 20%;
}
.uc-second-cell{
    flex-basis: 80%;
}
.uc-show-smartcontract-info{
    width: 100%;
    height: 36px;
    border: 2px solid rgb(155, 154, 154);
    border-radius: 4px;
}
#uc-type-text{
    padding: 6px 14px;
    font-size: 13px;
    color: rgb(36, 34, 34);
}
.selected_smartcontract_type_row{
    background-color: #ece6e6;
}

#uc-upload-file{
    height: 100%;
    font-size: 13px;
    margin: 4px 8px;
}

#uc-set-smartcontract-name{
    padding-left: 8px;
    font-size: 13px;
    color: rgb(36, 34, 34);
}

#uc-description-text-input{
    width: 100%;
    height: 100px;
}

#uc-select-type{
    height: 140px;
}
/* select box */
#select-box
{
    top: 0;
    position: relative;
    right: 0;
    left: 0;
    width: 100%;
}

#select-button
{
    position: relative;
    height: 36px;
    padding: 10px 8px;
    cursor: pointer;
}

#options-view-button
{
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    width: 100%;
    height: 100%;
    margin: 0;
    opacity: 0;
    cursor: pointer;
    z-index: 3;
}

#selected-value
{
    font-size: 16px;
    line-height: 1;
    margin-right: 26px;
    font-size: 13px;
    color: rgb(36, 34, 34);
}

#chevrons
{
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    padding-right: 6px;
}

#cheverons{
    display: block;
    height: 60%;
    color: rgb(202, 199, 199);
    mask-repeat: 20px;
}

#chevrons span
{
    display: block;
    height: 50%;
    color: rgb(204, 197, 197);
    font-size: 17px;
    text-align: right;
}

#options-view-button:checked + #select-button #chevrons span
{
    color: rgb(73, 72, 72);
}

#options
{
    top: 40px;
    position: absolute;
    right: 0;
    width: 320px;
    height: 100px;
    background-color: #fff;
    border-radius: 4px;
    overflow-y: auto;
    display: none;
}

#options-view-button:checked ~ #options
{
    border: 1px solid #e2eded;
    border-color: #eaf1f1 #e4eded #dbe7e7 #e4eded;
    display: block;
}

.label
{
    display: none;
    cursor: pointer;
    font-size: 14px;
}

#options-view-button:checked ~ #options .label
{
    display: block;
    padding: 6px 7px;    
}

.label:hover
{
    background-color: #fafafa;
}

/* Button */
#ssc-button{
    width: 50%;
    height: 80px;
    margin: auto;
    margin-top: 40px;
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

.disable-button{
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
    color: rgb(240, 240, 240);
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
