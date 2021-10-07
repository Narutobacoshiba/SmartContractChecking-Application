<template>
  <div class="container" id="add-vul">
    <div id="header">General Vulnerability Setting</div>
    <div class="row">
      <div class="col-2">Vulnerability</div>
      <div class="col-9">
        <select
          name="lteid"
          class="form-select"
          @change="changeid($event.target.value)"
        >
        <option value="#">--- Choose Vulnerability ---</option>
          <option v-for="c in ltltemplate" :key="c.lteid" :value="c.lteid">
            {{ c.name }}
          </option>
        </select>
      </div>
    </div>
    <div class="row">
      <div class="col-2">Formular</div>
      <div class="col-9">
        <LTLEditor  :code="ltlcode" />
      </div>
    </div>
    <div class="row">
      <div class="col-2">Description</div>
      <div class="col-9">
        <!-- <span v-for="c in ltltemplate" :key="c" :value="c">{{ c.description }}</span> -->
        <textarea
          name=""
          id=""
          cols="30"
          rows="5"
          class="form-control"
          v-model="description"
        >
        </textarea>
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
import LTLEditor from "../../../components/LTLEditor.vue";
import { GetAllltltemplates } from "../../../services/data";
export default {
  data: function() {
    return {
      ltlcode: "abc",
      ltltemplate: [],
      description: "",
    };
  },
  mounted() {
    this.initData();
    // this.ltlcode = this.ltltemplate[0].formula;
    // this.description =  this.ltltemplate[0].description;
  },
  components: {
    LTLEditor,
  },
  methods: {
    async initData() {
      this.ltltemplate = await GetAllltltemplates();
      this.ltlcode = await this.ltltemplate[0].formula;
      this.description = await this.ltltemplate[0].description;
    },

    changeid(value) {
      const data = this.ltltemplate.find((i) => {
        return i.lteid == value;
      });
      this.ltltemplate= data
      console.log(data);
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
