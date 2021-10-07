<template>
  <div class="container" id="add-vul">
    <div id="header">General Vulnerability Setting</div>
    <div class="row">
      <div class="col-2">Vulnerability</div>
      <div class="col-10">
        <select name="" class="form-select">
          <option value="">Integer Overflow/Underflow</option>
          <option value="">Reentracy</option>
          <option value="">Self-destruction</option>
          <option value="">Timestamp Dependence</option>
        </select>
      </div>
    </div>
    <div class="row">
      <div class="col-2">Formular</div>
      <div class="col-10">
        <LTLEditor @update="getLTLCode" :code="ltlcode" />
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
  </div>
</template>

<script>
import LTLEditor from "../../../components/LTLEditor.vue";
export default {
  data:function(){
    return{
      ltlcode:"containsSending({ function1 }) => (sendingTo({ function 2 }) =>O((¬sendingTo({ function 2 })) U end({ function 3 })))"
    }
  },
  components: {
    LTLEditor,
  },
  methods: {
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
</style>