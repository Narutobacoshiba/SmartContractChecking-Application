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
            <div class="cspsn-row" id="cspsn-row-formula">
                <div class="cspsn-first-cell">
                    <p>Formula</p>
                </div>
                <div class="cspsn-second-cell over-flow-cell">
                    <div id="cspsn-ltl-editor">
                        <LtlEditor :ltlcode="selected_vul.params.formula" @changeContent="getContent"/>
                    </div>
                </div>
            </div>
            <div class="cspsn-row" id="cspsn-row-description">
                <div class="cspsn-first-cell">
                    <p>Description</p>
                </div>
                <div class="cspsn-second-cell">
                    <textarea id="cspsn-description-text-input" spellcheck="false" v-model="selected_vul.params.description" />
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

export default ({
    components: { LtlEditor},
    data(){
        return{
            selected_vul: {},
        }
    },
    beforeMount(){
        this.selected_vul = this.$store.getters["data/GetSelectedVulnerability"]

        if(!("name" in this.selected_vul.params)){
            this.selected_vul.params.name = ""
        }
        if(!("description" in this.selected_vul.params)){
            this.selected_vul.params.description = ""
        }
        if(!("formula" in this.selected_vul.params)){
            this.selected_vul.params.formula = "* create new property here. *"
        }
    },
    watch: {
        selected_vul: {
            handler(val){
                this.$store.commit("data/SetSelectedVulnerability", val);
            },
            deep: true
        }
    },
    methods: {
        getContent(e){
            this.selected_vul.params.formula = e
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
.over-flow-cell{
    overflow: auto;
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
    height: 30px;
    font-size: 14px;
    color: rgb(36, 34, 34);
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