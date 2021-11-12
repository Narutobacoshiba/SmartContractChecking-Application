<template>
    <div>
        <div id="cs-header">
            <p>Select Context</p>
        </div>
        <div id="cs-body">
            <div class="cs-row">
                <div class="cs-first-cell">
                    <p>Name</p>
                </div>
                <div class="cs-second-cell">
                    <div class="cs-show-context-info">
                        <div id="select-box">
                            <input type="checkbox" id="options-view-button">
                            <div id="select-button">
                                <div id="selected-value">
                                    <span>{{getSelectContextName}}</span>
                                </div>
                                <div id="chevrons">
                                    <span class="material-icons">expand_less</span>
                                    <span class="material-icons">expand_more</span>
                                </div>
                            </div>
                            <div id="options">
                                <span v-for="c in getListContext" :key="c.ccid" class="label" @click="selected_context = c" :class="{selected_context_row: c.ccid == getSelectContextId}">{{c.name}}</span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="cs-row">
                <div class="cs-first-cell">
                    <p>Type</p>
                </div>
                <div class="cs-second-cell">
                    <div class="cs-show-context-info">
                        <div id="cs-type-text">{{getSelectContextType}}</div>
                    </div>
                </div>
            </div>
            <div class="cs-row">
                <div class="cs-first-cell">
                    <p>Description</p>
                </div>
                <div class="cs-second-cell" v-if="getDescription == ''">
                    <p>There are several options:</p>
                    <ul>
                        <li>BPMN: The user will choose the BPMN context by clicking on the "Load a Context" button.</li>
                        <li>DCR: The user will choose the DCR context by clicking on the "Load a Context" button.</li>
                        <li>....</li>
                        <li>Free</li>
                    </ul>
                </div>
                <div class="cs-second-cell" v-else>
                    {{getDescription}}
                </div>
            </div>
        </div>
        <div id="ssc-button">
            <button class="button-style" role="button" @click="goNextPage">Next</button>
            <button class="button-style" role="button" @click="goUploadContext">Upload a Context File</button>
            <button class="button-style" role="button" @click="skipSelectContext">Skip</button>
            <button class="button-style" role="button" @click="goPrePage">Back</button>
        </div>
    </div>
</template>

<script>
import {ContextService} from "../../services/context.services"
export default ({
    data(){
        return{
            selected_context: {},
            list_contexts: [],
        }
    },
    watch:{
        selected_context(val){
            this.$store.commit("data/SetSelectedContext",val)
        },
    },
    mounted(){
        let data = this.$store.getters["data/GetSelectedContext"].data
        this.selected_context = data

        this.getAllContext()
    },
    computed: {
        getSelectContextId(){
            if("ccid" in this.selected_context){
                return this.selected_context.ccid
            }else{
                return ""
            }
        },
        getSelectContextName(){
            if("name" in this.selected_context){
                return this.selected_context.name
            }else{
                return ""
            }
        },
        getSelectContextType(){
            if("context_type" in this.selected_context){
                return this.selected_context.context_type
            }else{
                return ""
            }
        },
        getListContext(){
            return this.list_contexts
        },
        getDescription(){
            return this.selected_context.description
        }
    },
    methods: {
        async getAllContext(){
            try{
                let response = await ContextService.getAllContext()
                this.list_contexts = response.data
            }catch(error){
                console.log(error)
            }
        },
        skipSelectContext(){
            let current_date = Date.now()
            let user_id = this.$store.state.user.currentUser.id
            this.$store.commit("data/SetSelectedContext",{ccid:this.hashValue("context"+current_date+user_id),name:"free_context",context_type:"FREE",content:"",description:""})
            this.$router.push({ name: "LtlCheckingOptions" });
        },
        goNextPage(){
            this.$router.push({ name: "LtlCheckingOptions" });
        },
        goPrePage(){
            this.$router.push({ name: "SmartContractSelection" });
        },
        goUploadContext(){
            this.$router.push({ name: "UploadContext" });
        }
    }
})
</script>

<style scoped>
#cs-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 30px;
    margin-bottom: 30px;
}
/* body */
#cs-body{
    width: 60%;
    margin: auto;
}
.cs-row{
    width: 100%;
    height: 140px;
    display: flex;
    justify-content: space-between;
}
.cs-first-cell{
    font-weight: bold;
    color: rgb(53, 46, 46);
    flex-basis: 20%;
}
.cs-second-cell{
    flex-basis: 80%;
}
.cs-show-context-info{
    width: 60%;
    height: 36px;
    border: 2px solid rgb(155, 154, 154);
    border-radius: 4px;
}
#cs-type-text{
    padding: 6px 14px;
    font-size: 13px;
    color: rgb(36, 34, 34);
}
.selected_context_row{
    background-color: #ece6e6;
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
    padding: 10px 14px;
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
</style>
