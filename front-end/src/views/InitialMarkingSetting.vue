<template>
  <div class="container">
    <h1>Initial Marking Setting</h1>

    <div class="row">
      <div class="col-2 left">Number of users</div>
      <div class="col-9 right">
        <input
          type="text"
          class="form-control"
          id="basic-url"
          aria-describedby="basic-addon3"
        />
      </div>
    </div>

    <div class="row">
      <div class="col-2">Users balance</div>
      <div class="col-9">
        <input
          type="text"
          class="form-control"
          id="basic-url"
          aria-describedby="basic-addon3"
        />
      </div>
    </div>

    <div class="row">
      <div class="col-2">Sender value</div>
      <div class="col-9">
        <input
          type="text"
          class="form-control"
          id="basic-url"
          aria-describedby="basic-addon3"
        />
      </div>
    </div>

    <div class="row">
      <div class="col-2">Other parameters</div>
      <div class="col-9">
        <textarea class="form-control" aria-label="With textarea"></textarea>
      </div>
    </div>

    <div id="btn-group">
      <button class="btn btn-outline-primary btn-sm" @click="routing('save')">
        Save
      </button>
      <button
        class="btn btn btn-outline-primary btn-sm"
        type="button"
        @click="routing('back')"
      >
        Back
      </button>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {};
  },
  methods: {
    routing(param) {
      if (param == "save") {
        this.$router.push({ name: "CheckSmartContract" });
      }
      if (param == "back") {
        this.$router.push({ name: "CSPSettingType" });
      }
    },
  },
};
</script>
<style scoped>
h1 {
  padding-top: 50px;
  padding-bottom: 50px;
  text-align: center;
}
.container {
  width: 60%;
}
.left {
  font-size: 20px;
}

.col-2 {
  font-size: 20px;
}
.row {
  margin-top: 30px;
  margin-bottom: 30px;
}

.text {
  height: 200px;
}

#btn-group {
  width: 100%;
  display: flex;
  margin-left: 4%;
}
button {
  margin: auto;
  margin-top: 40px;
  cursor: pointer;
  width: 15%;
  height: 2%;
  border: 1px solid #2196f3;
  color: #2196f3;
  font-size: 13px;
  line-height: 22px;
  font-weight: 600;
  border-radius: 4px;
  cursor: pointer;
}
</style>