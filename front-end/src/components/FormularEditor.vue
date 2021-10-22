<template>
  <div
          class="language-ltl"
          id="highlighting-content"
          spellcheck="false"
          contenteditable=""
          @input="updateInput"
          @keydown.enter.prevent="keyEnter"
          @keydown.tab.prevent="keyTab"
        ></div>
</template>

<script>
import { analyseLTLCode } from "../mixins/text-parser.js"
export default {
data: function () {
    return {
      selectVariable: false,
      select_variable_value: "",
      select_variable_id: "",
      select_variable_type: "",
      selected_template: "",
      ltlcode:"(GF{ local variable 1 } ^ GF{ global variable 2 }) => G({ local variable 2 }=> F{ smart contract })",
      ltltemplate: [],
      description: "",
    };
  },
  mounted() {
    this.updateContent(1, this.ltlcode);
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
    changeid(value) {
      const data = this.ltltemplate.find((i) => {
        return i.lteid == value;
      });
      this.ltlcode= data.formula;
      this.description = data.description;
    },
    updateSelection(new_value) {
      if (new_value != "") {
        let elemnet = document.getElementById(this.select_variable_id);
        elemnet.innerText = new_value;
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
      if (value.length == 0 && pos == 0) {
        value = " ";
        pos = 1;
      }
      this.updateContent(pos, value);
    },
    keyEnter() {
      let value = this.getNodeValue();
      let pos = this.getCursorPos();
      value =
        value.substring(0, pos) + "\n " + value.substring(pos, value.length);
      this.updateContent(pos + 1, value);
    },
    keyTab() {
      let value = this.getNodeValue();
      let pos = this.getCursorPos();
      value =
        value.substring(0, pos) + "\t" + value.substring(pos, value.length);
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
  },
}
</script>

<style scoped>
/* ---Formular Editor Style---- */
#highlighting-content {
  margin: 10px;
  padding: 10px;
  border: 0;
  width: calc(101% - 32px);
  height: 150px;
  background-color: #f6f6f6;
  font-size: 15pt;
  font-family: normal normal 1em/1.2em monospace;
  line-height: 20pt;
  overflow: auto;
  white-space: pre;
}
</style>