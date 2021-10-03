<template>
  <div class="container" id="add-vul">
    <div id="header">Contract-Specific Property Template - Setting</div>
    <div class="row">
      <div class="col-2">Name</div>
      <div class="col-9">
        <input class="form-control" type="text" value="Property 1" />
      </div>
    </div>
    <div class="row">
      <div class="col-2">Template</div>
      <div class="col-9">
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
      <div class="col-9">
        <textarea name="" id="" cols="30" rows="5" class="form-control">
            (GF{ variable 1 } ^ GF{ variable 2 }) => G({ function 3 }=> F{ function 4 })

          </textarea
        >
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
    <div id="btn-group">
      <button class="btn btn-primary btn-sm" @click="routing('add')">
        Add
      </button>
      <button
        class="btn btn-outline-secondary btn-sm"
        type="button"
        @click="routing('back')"
      >
        Cancel
      </button>
    </div>
  </div>
</template>

<script>
export default {
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
  width: 50%;
}
textarea {
  width: 100%;
}
#btn-group {
  width: 100%;
  display: flex;
  align-items: center;
}
button {
  margin: auto;
  margin-top: 40px;
}
@media only screen and (max-width: 960px) {
  #add-vul {
    width: 90%;
  }
}
</style>