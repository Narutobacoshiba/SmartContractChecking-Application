<template>
  <div id="editor">
    <div class="body">
      <div class="title">
      </div>
      <div class="btn">
        <button class="clear" @click="clear()">Clear</button>
      </div>
      <div class="box-code">
        <section class="input-box">
          <div
            name="inputCode"
            id="textarea-input"
            cols="30"
            rows="10"
            wrap="soft"
            contenteditable=""
            @keyup="getCode"
          >
          <span v-for="ltl in codearr" :key="ltl" :class="{opr: ltl[0]=='opr'}">{{getSubString(ltl[1], ltl[2])}}</span>
          </div>
        </section>
      </div>
    </div>
  </div>
</template>

<script>

export default {
  props: ["ltlcode", "codearr"],
  name: "editor",
  data() {
    return {
      code: "",
    };
  },
  methods: {
    getSubString(from, to){
      return this.ltlcode.substring(from, to)
    },
    clear() {
       this.code = "";
       this.isSaved = false;
    },
    getCode(){
      var el = document.getElementById("textarea-input");
      var ltl = ""
      if(el.children.length > 0){
        el.children.forEach(el => {ltl = ltl.concat(el.innerHTML)})
      }else ltl = el.innerHTML
      this.code = ltl
      this.$emit('update', this.code)
      console.log(this.codearr)
      console.log(this.ltlcode)
    }
  },
};
</script>

<style scoped>
#editor {
  width: 700px;
  background-color: rgb(241, 240, 240);
  height: auto;
  padding-left: 10px;
}
.btn {
  position: absolute;
  right: 30px;
  top: 85px;
  box-shadow: rgb(0 0 0 / 2%) 0px 1px 3px 0px,
    rgb(27 31 35 / 15%) 0px 0px 0px 1px;
  border-radius: 5px;
  overflow: hidden;
}
.btn button {
  width: 80px;
  height: 25px;
  border-style: none;
  border-radius: 0;
}
.btn button:hover {
  background-color: white;
  cursor: pointer;
}
#textarea-input {
  resize: none;
  width: 90%;
  height: 100%;
  border-width: 1px;
  border-style: dashed;
}
#textarea-input:focus {
  background-color: beige;
  color: blueviolet;
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
.input-box {
  height: 100%;
  position: relative;
}
.box-code {
  margin-top: 20px;
  width: 95%;
  height: 350px;
  border: 1px solid darkgray;
  border-radius: 5px;
  padding: 10px 0;
  border-left-style: none;
  border-right-style: none;
}
.title p {
  text-align: start;
  font-size: 25px;
  color: #2c3e50;
}
.title {
  width: 100%;
  height: 80px;
  overflow: hidden;
}
.title span {
  color: darkblue;
  font-family: revert;
  font-weight: 100;
}
.body {
  position: relative;
  width: 100%;
  height: auto;
  font-family: Arial, Helvetica, sans-serif;
  margin-bottom: 50px;
  background-color: rgb(241, 240, 240);
  display: flex;
  flex-direction: column;
  align-items: center;
  padding-bottom: 50px;
  padding-top: 20px;
  padding-left: 15px;
  box-shadow: rgb(0 0 0 / 12%) 0px 1px 3px, rgb(0 0 0 / 12%) 0px 1px 2px;
}
.opr{
  color: red;
  background-color: white;
}
@media only screen and (max-width: 1100px) {
  .title p {
    font-size: 20px;
    white-space: nowrap;
    transition: 0.2s;
  }
  .btn button {
    width: 55px;
  }
  .title b {
    display: none;
  }
}
</style>