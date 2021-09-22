<template>
  <div class="" id="add-vul">
    <div class="header">
      <h1 class="title">Contract-Specifc Property Confguration</h1>
    </div>
    <div class="body">
      <div class="name-area">
        <div class="label"><h3>Name</h3></div>
        <div class="pro-input">
          <input type="text" placeholder="Property Name" />
        </div>
      </div>
      <div class="formular-area">
        <div class="label"><h3>Formular</h3></div>
        <div class="tem-drop">
          <select name="" id="tem">
            <option value="">Template 1</option>
            <option value="">Template 1</option>
            <option value="">Template 1</option>
            <option value="">Template 1</option>
          </select>
        </div>
        <div class="formular-text">
          <div class="textarea" contenteditable="true">
            { <span @click="showPopUp()">{{ func1 }}</span> } will always be
            followed by { <span @click="showPopUp()">{{ func2 }}</span> }
          </div>
        </div>
      </div>
      <div class="description">
        <div class="label"><h3>Description</h3></div>
        <div class="des-text">
          <textarea name="" id="" cols="30" rows="10"></textarea>
        </div>
      </div>
    </div>
    <div class="footer">
      <div class="button-area">
        <div class="button-add-cancell">
          <button id="button-add" type="button" @click="routing('save')">
            Save
          </button>
          <button id="button-cancel" type="button" @click="routing('cancel')">
            Cancel
          </button>
        </div>
      </div>
    </div>
    <div class="choose-func" v-show="showPop">
      <choose-function v-model="showPop" :fName="func1" @up="close" />
    </div>
  </div>
</template>

<script>
/* import ChooseFunction from "../add-segmented-sc/11-Choose-Func-Temp.vue"; */
export default {
  data: function () {
    return {
      func1: "Function 1",
      func2: "Function 2",
      showPop: false,
    };
  },
  components: {
    /* ChooseFunction */
  },
  methods: {
    updateElement() {
      this.$emit("changeView", 2);
    },
    routing(param) {
      if (param == "save") {
        1;
      }
      if (param == "cancel") {
        let temp = this.$store.getters["data/GetFourthStepViewsList"];
        this.$store.commit("data/SetFourthStepViewsList", temp.splice(-1, 1));
        this.$store.commit("data/SetFourthStepViews", "csps-choosetypes");
        this.updateElement();
      }
    },
    close(e) {
      this.showPop = e;
    },
    showPopUp() {
      this.showPop = !this.showPop;
    },
  },
};
</script>

<style scoped>
.title {
  font-size: 40px;
  font-family: sans-serif;
  font-weight: 600;
  color: #62a9e6;
}
.choose-func {
  width: 100%;
  height: 100%;
  position: fixed;
  top: 0px;
  left: 0;
  background-color: rgb(58, 58, 58);
  padding-top: 50px;
}
.textarea span {
  color: saddlebrown;
}
.textarea span:hover {
  color: brown;
  cursor: pointer;
}
.formular-text {
  position: relative;
  text-align: start;
}
.formular-text .textarea {
  position: relative;
  left: 225px;
  width: 400px;
  height: 130px;
  line-height: 25px;
  border: 1px solid;
  background-color: white;
  transition: 0.5s height ease-in-out;
  border-color: rgb(138, 138, 138);
  border-radius: 4px;
  margin-top: 10px;
}
.textarea:focus {
  height: 200px;
  outline: none;
}
.des-text textarea {
  position: relative;
  left: 225px;
  width: 400px;
  height: 135px;
  line-height: 25px;
  transition: 0.5s height ease-in-out;
  border-color: rgb(138, 138, 138);
  border-radius: 4px;
}
.des-text {
  position: relative;
  text-align: start;
}
.des-text textarea:focus {
  height: 200px;
  outline: none;
}
#tem option {
  width: 200px;
  line-height: 25px;
}
#tem {
  position: relative;
  left: 225px;
  width: 300px;
  line-height: 25px;
  padding: 10px 10px;
  border-radius: 4px;
  box-shadow: rgba(0, 0, 0, 0.12) 0px 1px 3px, rgba(0, 0, 0, 0.24) 0px 1px 2px;
}
#tem:focus-visible {
  outline: none;
}
.tem-drop {
  position: relative;
  text-align: start;
}
.pro-input {
  position: relative;
  text-align: start;
}
.pro-input input {
  width: 300px;
  line-height: 25px;
  position: relative;
  left: 225px;
  border-top: 0;
  border-left: 0;
  border-right: 0;
  transition: width 0.35s ease-in-out;
}
.pro-input input:focus {
  width: 400px;
  border-bottom-color: rgb(109, 109, 109);
  color: rgb(65, 65, 65);
  outline: none;
}

h3 {
  margin: 0;
}
.name-area,
.formular-area,
.description {
  position: relative;
  margin: 10px 0 60px 0;
}
.label {
  text-align: start;
  width: 150px;
  line-height: 40px;
  position: absolute;
  left: 0;
}
#add-vul {
  width: 100%;
  background-color: #fff;
  display: flex;
  flex-direction: column;
  align-items: center;
  position: relative;
  padding-top: 30px;
}
#add-vul .header,
.body,
.footer {
  margin-bottom: 30px;
}
/* body */
.body {
  width: 50%;
  padding: 30px;
}
/* button style */
.button-add-cancell button {
  width: 170px;
  height: 30px;
  color: #0d6efd;
  border: 1px solid;
  border-radius: 4px;
}
.button-add-cancell button:hover {
  opacity: 0.9;
  background-color: #0d6efd;
  color: white;
  cursor: pointer;
}
.button-add-cancell button:active {
  cursor: wait;
}
#button-add {
  margin-right: 20px;
}
.button-add-cancell {
  position: relative;
  left: 40px;
}
</style>