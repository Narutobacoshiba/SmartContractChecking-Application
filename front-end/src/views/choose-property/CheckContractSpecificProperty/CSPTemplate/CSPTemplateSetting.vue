<template>
  <div class="container" id="add-vul">
    <div id="header">Contract-Specific Property Template - Template</div>
    <div class="row">
      <div class="col-2">Name</div>
      <div class="col-10">
        <input class="form-control" type="text" value="Property 1" />
      </div>
    </div>
    <div class="row">
      <div class="col-2">Template</div>
      <div class="col-10">
        <select name="" class="form-select">
          <option value="">Template 1</option>
          <option value="">Template 1</option>
          <option value="">Template 1</option>
          <option value="">Template 1</option>
        </select>
      </div>
    </div>
    <div class="row">
      <div class="col-2">Formular</div>
      <div class="col-10">
        <formular-editor />
      </div>
    </div>
    <div class="row">
      <div class="col-2">Description</div>
      <div class="col-10">
        <textarea name="" id="" cols="30" rows="5" class="form-control">
            If {variable 1} occurs infnitely often and {variable 2} occurs 
inifnitely often, then each occurrence of {function 3} is 
followed by an occurrence of {function 4}
          </textarea
        >
      </div>
    </div>
    <div id="btn-group">
      <button class="btn btn-primary-outline btn-sm" @click="routing('add')">
        Next
      </button>
      <button
        class="btn btn-outline-secondary btn-sm"
        type="button"
        @click="routing('back')"
      >
        Back
      </button>
    </div>
  </div>
</template>

<script>
import FormularEditor from "../../../../components/FormularEditor.vue";
import { GetGloLocArgOfSmartContract } from "../../../../services/data";
export default {
  data: function () {
    return {};
  },
  mounted() {
    this.fetchData();
  },
  components: {
    FormularEditor,
  },
  computed: {
  },
  methods: {
    async fetchData() {
      const res = await GetGloLocArgOfSmartContract(3);
      console.log(res);
      console.log(this.GetSCSelectedInfor.name);
    },
    routing(param) {
      if (param == "add") {
        this.$router.push({ name: "Initial" });
      }
      if (param == "back") {
        this.$router.push({ name: "CSPSettingType" });
      }
    },
  },
};
</script>

<style scoped>
.choose-func {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.7);
  z-index: 100;
  display: flex;
  align-items: center;
  justify-content: center;
}
.col-2 {
  font-size: 20px;
}
#add-vul {
  width: 60%;
}
#header {
  margin-top: 0;
  text-align: center;
  font-size: 35px;
  font-weight: bold;
}
.row {
  margin-top: 20px;
}
#textarea {
  height: 160px;
  margin-top: 20px;
}
#textarea span {
  color: saddlebrown;
}
#textarea span:hover {
  color: brown;
  cursor: pointer;
}
#name-box {
  width: 100%;
}
select {
  width: 100%;
}
textarea {
  width: 100%;
}
#btn-group {
  width: 100%;
  display: flex;
  margin-left: 4%;
}
button:hover {
  background-color: #1079cf;
  color: white;
}
button {
  margin: auto;
  margin-top: 40px;
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
@media only screen and (max-width: 960px) {
  #add-vul {
    width: 90%;
  }
}

/* ---Formular Editor Style---- */
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
</style>