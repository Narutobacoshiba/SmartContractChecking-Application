<template>
  <div id="editor">
    <div id="symbols-group">
      <button @click="insertSymbol('%u2260')">&ne;</button>
      <button @click="insertSymbol('%B7')">&middot;</button>
      <button @click="insertSymbol('%u2227')">&and;</button>
      <button @click="insertSymbol('%u2228')">&or;</button>
      <button @click="insertSymbol('+')">+</button>
      <button @click="insertSymbol('%26')">&amp;</button>
      <button @click="insertSymbol('|')">|</button>
      <button @click="insertSymbol('%AC')">&not;</button>
      <button @click="insertSymbol('%u2295')">&oplus;</button>
      <button @click="insertSymbol('!')">!</button>
      <button @click="insertSymbol('~')">~</button>
      <button @click="insertSymbol('%u21D2')">&rArr;</button>
      <button @click="insertSymbol('%u21D4')">&hArr;</button>
      <button @click="insertSymbol('%u2194')">&harr;</button>
      <button @click="insertSymbol('%u2200')">&forall;</button>
      <button @click="insertSymbol('%u2203')">&exist;</button>
      <button @click="insertSymbol('%u2204')">&NotExists;</button>
      <button @click="insertSymbol('%u2234')">&there4;</button>
      <button @click="insertSymbol('%u2235')">&because;</button>
    </div>

    <div
      name="inputCode"
      id="textarea-input"
      cols="30"
      rows="10"
      wrap="soft"
      spellcheck="false"
      contenteditable=""
      @keyup="resetContent"
      @mouseup="mouseUp"
    >
      <span id="first">{{ this.ltlcode }}</span>
    </div>
    <div id="group-btn">
      <button id="check-btn" @click="checkError">Check</button>
      <button id="clear-btn" @click="Clear">Clear</button>
    </div>
  </div>
</template>

<script>
// import EditorSc from "../../../../components/TextEditor.vue";
import { DetectLTLFormatError } from "../mixins/text-parser";
import { extractTokensTag } from "../mixins/text-parser";

export default {
    props:["code"],
  data() {
    return {
      ltlcode: this.code,
      pos: 0,
    };
  },
  mounted() {
    if (this.list_property.length > 0)
      this.selected_property = this.list_property[0];
  },
  methods: {
    updateCode(){
        this.$emit("update", this.ltlcode)
    },
    Clear() {
      var el = document.getElementById("textarea-input");
      this.ltlcode = "";
      el.innerHTML = '<span id="first">' + this.ltlcode + "</span>";
      console.log(document.getElementById("textarea-input").innerHTML);
    },
    mouseUp() {
      let selection = window.getSelection();
      let range = selection.getRangeAt(0);
      document.getElementById("textarea-input").innerHTML;
      if (range.toString().split("").length == 0) {
        range.setStartBefore(
          document.getElementById("textarea-input").childNodes[0]
        );
        this.pos = range.toString().split("").length;
        range.collapse(false);
      }
    },
    insertSymbol(symbol) {
      let selection = window.getSelection();
      if (selection.rangeCount == 0) return;
      let range = selection.getRangeAt(0);
      range.insertNode(document.createTextNode(unescape(symbol)));
      range.collapse(false);
      this.resetContent();
      // document.getElementById("textarea-input").focus()
    },
    getCursorPos() {
      let selection = window.getSelection();
      let range = selection.getRangeAt(0);
      range.setStartBefore(
        document.getElementById("textarea-input").childNodes[0]
      );
      this.pos = range.toString().split("").length;
      range.collapse(false);
    },
    setCursor() {
      this.pos += 1;
      let selection = window.getSelection();
      for (let position = 1; position < this.pos; position++) {
        selection.modify("move", "right", "character");
      }
    },
    getInnerHtml() {
      this.getCursorPos();
      this.ltlcode = document.getElementById("textarea-input").textContent;
      this.updateCode()
      var codearr = extractTokensTag(this.ltlcode);
      var ltl = this.ltlcode;
      ltl = ltl.split("");
      var span_opr = '<span style="color: blueviolet" class="sp">';
      var span_opl = '<span style="color: red" class="sp">';
      var span_opt = '<span style="color: blue" class="sp">';
      codearr.forEach((el) => {
        var el2 = el[2];
        if (el2 >= ltl.length) el2 = ltl.length - 1;
        var span_type = "";
        if (el[0] == "opr") span_type = span_opr;
        else if (el[0] == "opl") span_type = span_opl;
        else if (el[0] == "opt") span_type = span_opt;

        if (el[2] - el[1] == 1) {
          ltl[el[1]] = span_type + ltl[el[1]] + "</span>";
        } else {
          ltl[el[1]] = span_type + ltl[el[1]];
          ltl[el2] = ltl[el2] + "</span>";
        }
      });
      return ltl;
    },
    resetContent() {
      var ltl_arr = this.getInnerHtml();
      document.getElementById("textarea-input").innerHTML = ltl_arr.join("");
      this.setCursor();
    },
    checkError() {
      var ltl = this.getInnerHtml();
      var error = DetectLTLFormatError(this.ltlcode);
      var detail = error.detail;
      // add styling to error
      if (detail == "invalid naming") {
        error.addr.forEach((el) => {
          var name = el[0];
          if (el[2] - el[1] == 1) {
            ltl[el[1]] =
              this.getTagWName(detail, name) + ltl[el[1]] + "</span>";
          } else {
            ltl[el[1]] = this.getTagWName(detail, name) + ltl[el[1]];
            ltl[el[2]] = ltl[el[2]] + "</span>";
          }
        });
      } else if (detail != "") {
        error.addr.forEach((el) => {
          if (el[1] - el[0] == 1) {
            ltl[el[0]] = this.getTag(detail) + ltl[el[0]] + "</span>";
          } else {
            ltl[el[0]] = this.getTag(detail) + ltl[el[0]];
            ltl[el[1]] = ltl[error.addr[0][1]] + "</span>";
          }
        });
        console.error(error.detail);
      }
      document.getElementById("textarea-input").innerHTML = ltl.join("");
      this.setCursor();
    },
    getTagWName(detail, sub) {
      var tag =
        '<span style="background-color: #f8ffa8">' +
        '<span class = "ttip" style = "display: none">' +
        detail +
        '<a href = "">' +
        sub +
        "</a>" +
        "</span>";
      console.log(tag + "</span>");
      var tag_title =
        '<span style="background-color: #f8ffa8" title="' +
        detail +
        ": " +
        sub +
        '">';
      return tag_title;
    },
    disp() {
      document.querySelector("span > .ttip").display = "inline-block";
    },
    getTag(detail) {
      var tag =
        '<span style="background-color: #f8ffa8" title="' + detail + '">';
      return tag;
    },
    routing(param) {
      if (param == "save") {
        this.checkError();
        console.log(DetectLTLFormatError(this.ltlcode));
        //this.$store.commit("data/SetProcessView","generate-sc2cpn")
      } else if (param == "back") {
        this.$store.commit("data/SetFourthStepViews", "csps-choosetypes");
        this.$emit("changeView", 2);
      } else if (param == "create") {
        this.$router.push({
          name: "CreateCsp",
          params: { parent_path: "/process" },
        });
      }
    },
  },
};
</script>

<style scoped>
/* Editor */
#editor {
  width: 100%;
  background-color: rgb(241, 240, 240);
  height: auto;
}
#symbols-group {
  display: inline;
  margin-left: 0;
}
#symbols-group button {
  border: 1px solid lightgray;
  font-size: 20px;
  width: 30px;
  padding: auto;
  border-radius: 2px;
  background-color: #fff;
}
#group-btn {
  margin: 10px;
  padding-bottom: 10px;
  display: flex;
  justify-content: space-around;
}
#symbols-group button:hover {
  background-color: rgb(241, 240, 240);
}
#clear-btn,
#check-btn {
  background-color: lightblue;
  border: none;
  border-radius: 3px;
  width: 70px;
  border-radius: 3px;
}
#check-btn {
  color: white;
  background-color: blue;
}
#textarea-input {
  resize: none;
  width: 100%;
  height: 300px;
  border-width: 1px;
  border-style: dashed;
  background-color: white;
  padding: 10px;
  font-size: 18px;
  user-select: text;
  cursor: text;
  -moz-user-select: none;
}
#textarea-input:focus {
  background-color: white;
  color: black;
}
.save-check {
  position: absolute;
  top: 0px;
  right: 1%;
  width: 10px;
  height: 10px;
  background-color: yellowgreen;
  border-radius: 50%;
}
span .ttip {
  display: none;
}
span:hover .ttip {
  display: inline-block;
  background-color: black;
  opacity: 0.8;
  color: white;
  padding: 5px;
  border-radius: 3px;
  margin: 0;
  position: absolute;
}
</style>