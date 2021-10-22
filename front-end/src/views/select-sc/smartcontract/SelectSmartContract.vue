<template>
  <div id="main" class="container">
    <div id="header">
      <h1>Select Smart Contracts</h1>
    </div>

    <div class="row type">
      <div class="col"></div>
      <div class="col"></div>
      <div class="col">
        <div class="input-group mb-3">
          <label class="input-group-text" for="inputGroupSelect01">Type</label>
          <select class="form-select" id="inputGroupSelect01">
            <option value="1">Common</option>
            <option value="2">Private</option>
            <option value="3">Pending</option>
            <option value="4">All</option>
          </select>
        </div>
      </div>
    </div>

    <div class="atable">
      <table class="table table-striped table-hover table-sm">
        <thead class="table-inside">
          <tr>
            <th style="width: 10%" scope="col">#</th>
            <th style="width: 40%" scope="col">Name</th>
            <th style="width: 30%" scope="col">Type</th>
            <th style="width: 20%" scope="col"></th>
          </tr>
        </thead>
        <tbody>
          <tr
            v-for="(item, index) in Common(getlistSmartContract)"
            v-bind:key="index"
          >
            <th scope="row">{{ index + 1 }}</th>
            <td>{{ item.name }}</td>
            <td>
              <input type="checkbox" id="one" value="One" v-model="picked" />
            </td>
          </tr>
          <tr>
            <th>1</th>
            <td>blindAuction</td>
            <td>Common</td>
            <td>
              <input type="checkbox" id="one" v-model="picked" name="ch" />
            </td>
          </tr>
        </tbody>
      </table>
    </div>

    <div id="action">
      <div id="btn" @click="funtionNext()">Next</div>
      <div id="btn" v-on:click="load">Upload Smart Contract</div>
      <div id="btn" @click="routing('back')">Back</div>
    </div>

    <popup v-bind:isOpen="isOpen" v-on:clickdahieu="dahieu" />
  </div>
  <!-- </div> -->
</template>

<script>
import Popup from "./Popup.vue";
import { mapActions, mapGetters } from "vuex";
export default {
  data() {
    return {
      isOpen: false,
      info: null,
      k: 1,
      h: 1,
    };
  },
  methods: {
    funtionNext() {
      var checkbox = document.getElementsByName("ch");
      if 
    },
    load() {
      this.isOpen = true;
    },
    dahieu() {
      this.isOpen = false;
    },
    routing(param) {
      if (param == "add") {
        this.$router.push({ name: "ContextOfSmartContract" });
      }
      if (param == "back") {
        this.$router.push({ name: "ListOfCheckedTransactions" });
      }
      if (param == "uploadfile") {
        this.$router.push({ name: "UpLoadSc" });
      }
    },
    ...mapActions(["setListSmartContract"]),
    Private: function (arrays) {
      return arrays.filter(function (array) {
        return array.type === "Private";
      });
    },
    Common: function (arrays) {
      return arrays.filter(function (array) {
        return array.type === "Common";
      });
    },
  },
  created() {
    this.setListSmartContract();
  },
  computed: {
    ...mapGetters(["getlistSmartContract"]),

    // return k;
  },
  components: {
    Popup,
  },
};
</script>

<style scoped>
.main {
  font-family: Arial, Helvetica, sans-serif;
}
#header {
  text-align: center;
  margin-bottom: 7%;
  margin-top: 2%;
}
.table-inside {
  background-color: #d9edf7;
  color: #3a7694;
}

h1 {
  text-align: center;
  font-size: 35px;
  font-weight: bold;
}

.atable {
  box-shadow: rgba(0, 0, 0, 0.05) 0px 6px 24px 0px,
    rgba(0, 0, 0, 0.08) 0px 0px 0px 1px;
  margin-top: 40px;
  padding-bottom: 5%;
  border: 1px solid #d9edf7;
  border-radius: 10px;
}
#btn {
  cursor: pointer;
  width: 18%;
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
#btn:hover {
  background-color: #1079cf;
  color: white;
}

#action {
  margin: 0 auto;
  margin-top: 4%;
  display: flex;
  justify-content: space-between;
  width: 70%;
}

div#main {
  padding-bottom: 3%;
}

.type {
  margin-top: 50px;
}
</style>