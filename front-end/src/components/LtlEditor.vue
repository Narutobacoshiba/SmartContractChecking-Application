<template>
    <div id="ltleditor-container">
        <div
            class="language-ltl"
            id="highlighting-content"
            spellcheck="false"
            contenteditable=""
            @input="updateInput"
            @keydown.enter.prevent="keyEnter"
            @keydown.tab.prevent="keyTab"
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
import { analyseLTLCode } from "../mixins/text-parser.js";
import ArgumentSelection from "./smart-contract-table/ArgumentTable.vue";
import VariableSelection from "./smart-contract-table/VariableTable.vue";
import FunctionSelection from "./smart-contract-table/FunctionTable.vue";

export default ({
    props: ["ltlcode"],
    components: { ArgumentSelection, VariableSelection, FunctionSelection },
    data(){
        return{
            selectVariable: false,
            select_variable_value: "",
            select_variable_id: "",
            select_variable_type: "",
            temp_selection: "",
        }
    },
    mounted(){
        this.updateContent(this.ltlcode.length, this.ltlcode)
    },
    watch:{
        ltlcode(new_var){
            if(this.getNodeValue() != new_var){
                this.updateContent(new_var.length, new_var)
            }
        }
    },
    computed: {
        isSelectVariable() {
        return this.selectVariable;
        },
        getSelectVariableValue() {
        return this.select_variable_value;
        },
        getVariableType() {
        return this.select_variable_type;
        },
    },
    methods: {
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
                let elemnet = document.getElementById(this.select_variable_id);
                elemnet.innerText = "'"+this.temp_selection+"'";
                this.$emit("changeContent",this.getNodeValue())
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
                userSelection[index].removeEventListener("click", function (event) {
                    self.openSelectTable(
                    event.target.id,
                    event.target.innerHTML,
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
                userSelection[index].setAttribute("id", "select_var_" + i);
                userSelection[index].addEventListener("click", function (event) {
                    self.openSelectTable(
                    event.target.id,
                    event.target.innerHTML,
                    event.target.type
                    );
                });
                })(i);
            }
        },
        updateContent(pos, value) {
            let result_element = document.getElementById("highlighting-content");
            this.removeSelectVarEventListener();
            result_element.innerHTML = analyseLTLCode(value);
            this.setCursor(pos);
            this.addSelectVarEventListener();
            this.$emit("changeContent",value)
        },
        getNodeValue() {
            let result_element = document.getElementById("highlighting-content");
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
        updateInput() {
            let value = this.getNodeValue();
            let pos = this.getCursorPos();
            this.updateContent(pos, value);
        },
        keyEnter() {
            let value = this.getNodeValue();
            let pos = this.getCursorPos();
            value = value.substring(0, pos) + "\n " + value.substring(pos, value.length);
            this.updateContent(pos + 1, value);
        },
        keyTab() {
            let value = this.getNodeValue();
            let pos = this.getCursorPos();
            value = value.substring(0, pos) + "\t" + value.substring(pos, value.length);
            this.updateContent(pos + 1, value);
        },
        getCursorPos() {
            let selection = window.getSelection();
            let range = selection.getRangeAt(0);
            range.setStartBefore(
                document.getElementById("highlighting-content").parentNode
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
}

#highlighting-content {
  border: 0;
  width: 100%;
  height: 100%;
  background-color: #f6f6f6;
  font-size: 13pt;
  font-family: normal normal 1em/1.2em monospace;
  line-height: 20pt;
  overflow: auto;
  white-space: pre;
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