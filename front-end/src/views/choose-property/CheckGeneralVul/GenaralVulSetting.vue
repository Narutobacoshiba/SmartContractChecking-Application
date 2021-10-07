<template>
  <div class="container" id="add-vul">
    <div id="header">General Vulnerability Setting</div>
    <div class="row">
      <div class="col-2">Vulnerability</div>
      <div class="col-9">
        <select name="" class="form-select" v-model="selected_template">
          <option value="interger_overflow_underflow">
            Integer Overflow/Underflow
          </option>
          <option value="reetrancy">Reentrancy</option>
          <option value="self_destruction">Self-destruction</option>
          <option value="timestamp_dependence">Timestamp Dependence</option>
        </select>
      </div>
    </div>
    <div class="row">
      <div class="col-2">Formular</div>
      <div class="col-9">
        <div
          class="language-ltl"
          id="highlighting-content"
          spellcheck="false"
          contenteditable=""
          @input="updateInput"
          @keydown.enter.prevent="keyEnter"
          @keydown.tab.prevent="keyTab"
        ></div>
      </div>
    </div>
    <div class="row">
      <div class="col-2">Description</div>
      <div class="col-10">
        <textarea name="" id="" cols="30" rows="5" class="form-control">
            This is by far the most notorious vulnerability since it led to the 
infamous DAO attack. An attack of this type can take several forms 
(e.g, we can talk about a single function reentrancy attack or a 
cross-function reentrancy attack), but the main idea behind it is that 
a function can be interrupted in the middle of its execution and then
be safely called again before its initial call completes. Once the 
second call completes, the initial one resumes correct execution.
          </textarea
        >
      </div>
    </div>
    <div id="btn-group">
      <button class="btn btn-primary-outline btn-sm" @click="routing('add')">
        Add
      </button>
      <button
        class="btn btn-primary-outline btn-sm"
        type="button"
        @click="routing('back')"
      >
        Cancel
      </button>
    </div>
    <div id="selection-table" v-if="isSelectVariable">
      <div id="selection-table-b2">
        <ArgumentSelection
          v-if="getVariableType == 'arg'"
          :current_value="getSelectVariableValue"
          @updateCurrentSelectVariable="updateSelection"
        />
        <VariableSelection
          v-if="getVariableType == 'var'"
          :current_value="getSelectVariableValue"
          @updateCurrentSelectVariable="updateSelection"
        />
        <FunctionSelection
          v-if="getVariableType == 'func'"
          :current_value="getSelectVariableValue"
          @updateCurrentSelectVariable="updateSelection"
        />
      </div>
    </div>
  </div>
</template>

<script>
import { analyseLTLCode } from "../../../mixins/text-parser.js";
import ArgumentSelection from "../../../components/ArgumentTable.vue";
import VariableSelection from "../../../components/VarialbleTable.vue";
import FunctionSelection from "../../../components/FunctionTable.vue";

export default {
  data: function () {
    return {
      selectVariable: false,
      select_variable_value: "",
      select_variable_id: "",
      select_variable_type: "",
      selected_template: "",
      ltlcode:
        "const minThreshold = 0;\nconst maxThreshold = 10;\nproposition out: ('variable' < minThreshold) | ('variable' > maxThreshold);\nproperty outOfRange: ! out;",
    };
  },
  components: { ArgumentSelection, VariableSelection, FunctionSelection },
  mounted() {
    this.updateContent(1, " ");
  },
  watch: {
    selected_template: function (val) {
      if (val == "interger_overflow_underflow") {
        this.updateContent(1, this.ltlcode);
      } else {
        this.updateContent(1, "");
      }
    },
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
    routing(param) {
      /* let ltl_content = this.getNodeValue() ltl content se duoc gui ve phia backend*/
      if (param == "add") {
        this.$router.push({ name: "Initial" });
      }
      if (param == "back") {
        this.$router.push({ name: "CSPSettingType" });
      }
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
};
</script>

<style scoped>
#container {
  height: 100%;
  width: 100%;
}
#con-setting {
  width: 70%;
}
#header {
  margin-top: 1%;
  text-align: center;
  font-size: 35px;
  font-weight: bold;
}
.row {
  margin-top: 20px;
}
.col-2 {
  font-size: 20px;
}
textarea {
  height: auto;
}
#btn-group {
  /* width: 100%; */
  padding-bottom: 5%;
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: 25px;
  margin-bottom: 15px;
}
button {
  margin: auto;
  cursor: pointer;
  width: 15%;
  height: 2%;
  border: 1px solid #2196f3;
  text-align: center;
  color: #2196f3;
  font-size: 13px;
  line-height: 22px;
  font-weight: 600;
  padding: 4px 3px;
  border-radius: 4px;
  cursor: pointer;
}

#highlighting-content {
  margin: 10px;
  padding: 10px;
  border: 0;
  width: calc(100% - 32px);
  height: 150px;
  background-color: #f6f6f6;

  font-size: 15pt;
  font-family: normal normal 1em/1.2em monospace;
  line-height: 20pt;

  overflow: auto;
  white-space: pre;
}

#selection-table {
  position: absolute;
  width: 100%;
  height: 100%;
  top: 0;
  left: 0;
  z-index: 1000;
  background: rgba(0, 0, 0, 0.5);
  transition: opacity 0.3s;
}
#selection-table-b2 {
  position: absolute;
  height: 550px;
  width: 1000px;
  border-radius: 10px;
  top: 60px;
  left: calc(50% - 500px);
  background-color: white;
}
</style>