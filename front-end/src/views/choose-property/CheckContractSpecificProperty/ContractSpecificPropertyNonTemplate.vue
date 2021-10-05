<template>
  <div>
    <div id="con-setting" class="container">
      <div id="header">Contract-Specifc Property Setting Non-Template</div>
      <div class="row">
        <div class="col-2">Name</div>
        <div class="col-9">
          <input type="text" class="form-control">
        </div>
      </div>
      <div class="row">
        <div class="col-2">Formular</div>
        <div class="col-9">
          <LTLEditor @update="getLTLCode" :code="ltlcode" />
        </div>
      </div>
      <div class="row">
      <div class="col-2">Description</div>
      <div class="col-9">
        <textarea name="" id="" cols="30" rows="5" class="form-control">
            If {variable 1} occurs infnitely often and {variable 2} occurs 
inifnitely often, then each occurrence of {function 3} is 
followed by an occurrence of {function 4}
          </textarea
        >
      </div>
    </div>
      <div class="row">
        <div class="col-2"></div>
        <div id="btn-group" class="col-9">
          <button class="btn btn-primary btn-sm" @click="routing('save')">
            Add
          </button>
          <button
            class="btn btn-outline-secondary btn-sm"
            @click="routing('back')"
          >
            Back
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import LTLEditor from "../../../components/LTLEditor.vue";
export default {
  components: {
    LTLEditor,
  },
  methods: {
    getLTLCode(code) {
      this.ltlcode = code;
    },
    routing(param) {
      if (param == "save") {
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
#con-setting {
  width: 70%;
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
.col-2 {
  font-size: 20px;
}
textarea {
  height: auto;
}
#btn-group {
  /* width: 100%; */
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: 25px;
  margin-bottom: 15px;
}
button {
  margin: auto;
}
</style>