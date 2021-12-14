<template>
    <div id="ltleditor-container">
        <div id="select-type">
            <div class="select-option" :class="{'selected-option': getSelectOption == 'text'}" @click="changeSelectOption('text')">Text</div>
            <div class="select-option" :class="{'selected-option': getSelectOption == 'raw'}" @click="changeSelectOption('raw')">Raw</div>
        </div>
        <div
            class="language-ltl"
            id="highlighting-content-text"
            spellcheck="false"
        ></div>
        <div
            class="language-ltl"
            id="highlighting-content-raw"
            spellcheck="false"
        ></div>

        <div id="selection-table" v-if="isSelectVariable">
            <div id="selection-table-b2">
                <div id="selection-table-b2-s">
                    <ArgumentSelection
                    v-if="getVariableType == 'arg'"
                    :selectValue="getSelectVariableValue"
                    @changeValue="updateSelection"
                    />
                    <VariableSelection
                    v-if="getVariableType == 'var'"
                    :selectValue="getSelectVariableValue"
                    @changeValue="updateSelection"
                    />
                    <FunctionSelection
                    v-if="getVariableType == 'func'"
                    :selectValue="getSelectVariableValue"
                    @changeValue="updateSelection"
                    />
                </div>
                <div id="ssc-button">
                    <button class="button-style" role="button" @click="updateSelectValue">Ok</button>
                    <button class="button-style" role="button" @click="cancelSelectValue">Cancel</button>
                </div>
            </div>
        </div>
    </div>
</template>


<script>
import { analyseLTLCode, analyseLTLTextCode } from "../mixins/text-parser.js";
import ArgumentSelection from "./smart-contract-table/ArgumentTable.vue";
import VariableSelection from "./smart-contract-table/VariableTable.vue";
import FunctionSelection from "./smart-contract-table/FunctionTable.vue";

export default ({
    props: ["ltlcode","ltlcodetext"],
    components: { ArgumentSelection, VariableSelection, FunctionSelection },
    data(){
        return{
            select_option: "text",
            selectVariable: false,
            select_variable_value: "",
            select_variable_id: "",
            select_variable_type: "",
            temp_selection: "",
        }
    },
    mounted(){
        this.updateContent(this.ltlcode.length, this.ltlcode, 'highlighting-content-raw')
        this.updateContent(this.ltlcodetext.length, this.ltlcodetext, 'highlighting-content-text')
        this.changeSelectOption(this.select_option)
    },
    watch:{
        ltlcode(new_var){
            if(this.getNodeValue('highlighting-content-raw') != new_var){
                this.updateContent(new_var.length, new_var, 'highlighting-content-raw')
            }
        },
        ltlcodetext(new_var){
            if(this.getNodeValue('highlighting-content-text') != new_var){
                this.updateContent(new_var.length, new_var, 'highlighting-content-text')
            }
        }
    },
    computed: {
        isSelectVariable() {
        return this.selectVariable
        },
        getSelectVariableValue() {
        return this.select_variable_value
        },
        getVariableType() {
        return this.select_variable_type
        },
        getSelectOption(){
            return this.select_option
        }
    },
    methods: {
        changeSelectOption(op){
            this.select_option = op
            if(op == "text"){
                document.getElementById("highlighting-content-text").style.display = "block"
                document.getElementById("highlighting-content-raw").style.display = "none"
            }else if(op == "raw"){
                document.getElementById("highlighting-content-text").style.display = "none"
                document.getElementById("highlighting-content-raw").style.display = "block"
            }
        },
        cancelEvent(){
            this.$router.push({ name: "ContextSelection"});
        },
        updateSelection(new_value){
            this.temp_selection = new_value
        },
        cancelSelectValue(){
            this.selectVariable = false;
        },
        updateSelectValue() {
            if (this.temp_selection != "") {
                let elements = document.getElementsByClassName(this.select_variable_id)
                for(let i=0; i<elements.length; i++){
                    let type = elements[i].type
                    if(type == ""){
                        type = "var"
                    }
                    if(type == this.select_variable_type){
                        elements[i].innerText = "'"+this.temp_selection+"'"
                    }
                }
                this.$emit("changeContent",this.getNodeValue("highlighting-content-raw"),this.getNodeValue("highlighting-content-text"))
            }
            this.select_variable_id = "";
            this.select_variable_value = "";
            this.select_variable_type = "";
            this.selectVariable = false;
        },
        openSelectTable(id, value, type) {
            this.select_variable_value = value.substring(1, value.length - 1);
            this.select_variable_id = id;
            if (type != "") {
                this.select_variable_type = type;
            } else {
                this.select_variable_type = "var";
            }
            this.selectVariable = true;
        },
        removeSelectVarEventListener() {
            var userSelection = document.getElementsByClassName("select-variable");
            var self = this;
            for (var i = 0; i < userSelection.length; i++) {
                (function (index) {
                userSelection[index].addEventListener("click", function (event) {
                    let val = event.target.innerHTML
                    let classList = event.target.classList
                    self.openSelectTable(
                    classList[classList.length - 1],
                    val,
                    event.target.type
                    );
                });
                })(i);
            }
        },
        addSelectVarEventListener() {
            var userSelection = document.getElementsByClassName("select-variable");
            var self = this;
            for (var i = 0; i < userSelection.length; i++) {
                (function (index) {
                userSelection[index].addEventListener("click", function (event) {
                    let val = event.target.innerHTML
                    let classList = event.target.classList
                    self.openSelectTable(
                    classList[classList.length - 1],
                    val,
                    event.target.type
                    );
                });
                })(i);
            }
        },
        updateContent(pos, value, class_option) {
            let result_element = document.getElementById(class_option)
            this.removeSelectVarEventListener();
            if(class_option == "highlighting-content-raw"){
                result_element.innerHTML = analyseLTLCode(value,false)
            }else if( class_option == "highlighting-content-text"){
                result_element.innerHTML = analyseLTLTextCode(value,false)
            }
            
            this.setCursor(pos);
            this.addSelectVarEventListener();
        },
        getNodeValue(class_option) {
            let result_element = document.getElementById(class_option)
            let childs = result_element.childNodes;
            let all_text = [];
            for (let i = 0; i < childs.length; ++i) {
                if (childs[i]) {
                    if (childs[i].nodeType != 3) {
                        let value = childs[i].innerHTML;
                        all_text.push(value);
                    } else {
                        all_text.push(childs[i].data);
                    }
                }
            }
            return all_text
                .join("")
                .replace(/&amp;/g, "&")
                .replace(/&lt;/g, "<")
                .replace(/&gt;/g, ">");
        },
        getCursorPos(class_option) {
            let selection = window.getSelection();
            let range = selection.getRangeAt(0);
            range.setStartBefore(
                document.getElementById(class_option).parentNode
            );
            let pos = range.toString().split("").length;
            range.collapse(false);
            return pos;
        },
        setCursor(pos) {
            pos += 1;
            let selection = window.getSelection();
            for (let position = 1; position < pos; position++) {
                selection.modify("move", "right", "character");
            }
        },
    }
})
</script>

<style scoped>
#ltleditor-container {
  height: 100%;
  width: 100%;
  background-color: #f6f6f6;
}

#select-type{
    display: flex;
}
.select-option{
    width: 10%;
    height: 26px;
    border: 1px solid #d8dfec;
    border-radius: 2px;
    margin: 5px 10px 15px 10px;
    text-align: center;
    color: #3e7fd8;
    background-color: #fafafa;
    cursor: pointer;
}
.selected-option{
    background-color: #e4ecfa;
}
.language-ltl {
  border: 0;
  width: calc(100% - 10px);
  margin-left: 10px;
  height: calc(100% - 46px);
  font-size: 13pt;
  font-family: normal normal 1em/1.2em monospace;
  line-height: 20pt;
  overflow: auto;
  white-space: pre;
  display: none;
}

#selection-table {
  position: fixed;
  width: 100%;
  height: 100%;
  top: 0;
  left: 0;
  z-index: 100;
  background: rgba(0, 0, 0, 0.5);
  transition: opacity 0.3s;
}
#selection-table-b2 {
  position: absolute;
  height: 550px;
  width: 900px;
  border-radius: 10px;
  top: 130px;
  left: calc(50% - 450px);
  background-color: white;
}

#selection-table-b2-s{
    width: 90%;
    margin: auto;
    height: 460px;
    margin-top: 10px;
}

/* button */
#ssc-button{
    width: 90%;
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