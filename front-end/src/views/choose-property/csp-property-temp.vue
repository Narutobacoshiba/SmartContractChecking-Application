<template>
    <div id="csps-nontemp-container">
        <div id="cspsn-header">
            <p>Contract-Specifc Property Setting - Non Template</p>
        </div>
        <div id="cspsn-body">
            <div class="cspsn-row" id="cspsn-row-name">
                <div class="cspsn-first-cell">
                    <p>Name</p>
                </div>
                <div class="cspsn-second-cell">
                    <input id="cspsn-set-property-name" type="text" placeholder="property name" v-model="selected_vul.params.name" />
                </div>
            </div>
            <div class="cspsn-row" id="cspsn-row-name">
                <div class="cspsn-first-cell">
                    <p>Template</p>
                </div>
                <div class="cspsn-second-cell">
                    <div id="select-box-base">
                        <div id="select-box">
                            <input type="checkbox" id="options-view-button">
                            <div id="select-button">
                                <div id="selected-value">
                                    <span>{{getTempPlateName}}</span>
                                </div>
                                <div id="chevrons">
                                    <span class="material-icons">expand_less</span>
                                    <span class="material-icons">expand_more</span>
                                </div>
                            </div>
                            <div id="options">
                                <span v-for="c in getListTemplate" :key="c.id" class="label" @click="changeTemplate(c.id)" :class="{selected_template_row: c.id == selected_template}">{{c.name}}</span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            
            <div class="cspsn-row" id="cspsn-row-formula">
                <div class="cspsn-first-cell">
                    <p>Formula</p>
                </div>
                <div class="cspsn-second-cell">
                    <div id="cspsn-ltl-editor">
                        <LtlEditor :ltlcode="getLTLContent" @changeContent="getContent"/>
                    </div>
                </div>
            </div>

            <div class="cspsn-row" id="cspsn-row-description">
                <div class="cspsn-first-cell">
                    <p>Description</p>
                </div>
                <div class="cspsn-second-cell">
                    <textarea disabled id="cspsn-description-text-input" spellcheck="false" v-model="getLTLDescription" />
                </div>
            </div>
            <div id="ssc-button">
                <button class="button-style" role="button" @click="goNextPage">Next</button>
                <button class="button-style" role="button" @click="goPrePage">Back</button>
            </div>
        </div>
    </div>
</template>


<script>
import LtlEditor from "../../components/LtlEditor.vue";
import {LTLTemplate} from "../../services/ltlproperty.services"

export default ({
    components: { LtlEditor},
    data(){
        return{
            selected_vul: {},
            selected_template: null,
            list_template: [],
            formula: "* Please select the template to edit. *",
        }
    },
    beforeMount(){
        this.selected_vul = this.$store.getters["data/GetSelectedVulnerability"]

        if(!("name" in this.selected_vul.params)){
            this.selected_vul.params.name = ""
        }

        if(!("id" in this.selected_vul.params)){
            this.selected_vul.params.id = null
        }else{
            this.selected_template = this.selected_vul.params.id
        }

        if(!("description" in this.selected_vul.params)){
            this.selected_vul.params.description = ""
        }
        
        if(!("formula" in this.selected_vul.params)){
            this.selected_vul.params.formula = "* Please select the template to edit. *"
        }else{
            this.formula = this.selected_vul.params.formula
        }
    },
    mounted(){
        this.getLTLTemplate()
    },
    watch: {
        formula(val){
            this.selected_vul.params.formula = val
        },
        selected_vul: {
            handler(val){
                this.$store.commit("data/SetSelectedVulnerability", val);
            },
            deep: true
        }
    },
    computed:{
        getListTemplate(){
            return this.list_template
        },
        getTempPlateName(){
            for(let i=0; i<this.list_template.length; i++){
                if(this.list_template[i].id == this.selected_template){
                    return this.list_template[i].name
                }
            }
            return ""
        },
        getLTLContent(){
            return this.formula
        },
        getLTLDescription(){
            for(let i=0; i<this.list_template.length; i++){
                if(this.list_template[i].id == this.selected_template){
                    return this.list_template[i].description
                }
            }
            return ""
        }
    },
    methods: {
        async getLTLTemplate(){
            try{
                let response = await LTLTemplate.getLTLTemplate()
                this.list_template = response.data
      
            }catch(error){
                console.log(error)
            }
        },
        changeTemplate(id){
            if(this.selected_template != id){
                this.selected_template = id
                for(let i=0; i<this.list_template.length; i++){
                    if(this.list_template[i].id == this.selected_template){
                        this.formula = this.list_template[i].formula
                        this.selected_vul.params.description = this.list_template[i].description
                        this.selected_vul.params.id = this.list_template[i].id
                        break
                    }
                }
            }
        },
        getContent(e){
            this.formula = e
        },
        goNextPage(){
            this.$router.push({ name: "InitialMarkingSetting"})
        },
        goPrePage(){
            this.$router.push({ name: "CSPSettingChooseType"});
        }
    }
})
</script>

<style scoped>
#cspsn-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 30px;
    margin-bottom: 30px;
}
/* body */
#cspsn-body{
    width: 60%;
    margin: auto;
}
.cspsn-row{
    width: 100%;
    display: flex;
    justify-content: space-between;
}
.cspsn-first-cell{
    font-weight: bold;
    color: rgb(53, 46, 46);
    flex-basis: 20%;
}
.cspsn-second-cell{
    flex-basis: 80%;
}

#cspsn-row-name{
    height: 80px;
}
#cspsn-row-formula{
    height: 280px;
}
#cspsn-row-description{
    height: 80px;
}

#cspsn-set-property-name{
    width: 80%;
    font-size: 14px;
    color: rgb(36, 34, 34);
    height: 36px;
    border: 2px solid rgb(155, 154, 154);
    border-radius: 4px;
}

#cspsn-ltl-editor{
    width: 100%;
    height: 240px;
}

textarea{
    resize: none;
}

#cspsn-description-text-input{
    width: 100%;
    height: 80px;
    font-size: 14px;
    color: rgb(36, 34, 34);
}


/* select box */
#select-box-base{
    width: 80%;
    height: 36px;
    border: 2px solid rgb(155, 154, 154);
    border-radius: 4px;
}
#select-box
{
    width: 100%;
    top: 0;
    position: relative;
    right: 0;
    left: 0;
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

.selected_template_row{
    background-color: #ece6e6;
}
/* Button */
#ssc-button{
    width: 100%;
    height: 80px;
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