<template>
  <div id="main">
    <div id="header">
      <h1>Select Smart Contracts</h1>
    </div>

    <div class="grey">
      <span>Common Smart Contracts</span>
    </div>

    <div class="blue">
      <div class="atable">
        <table class="table table-striped table-hover table-sm">
          <thead class="table-inside">
            <tr>
              <th style="width: 20%" scope="col">#</th>
              <th style="width: 60%" scope="col">Smart Contract Name</th>
              <th style="width: 20%" scope="col">Select</th>
            </tr>
          </thead>
          <tbody>
            <tr  v-for="(item, index) in Common(getlistSmartContract)" 
                  v-bind:key="index"
                  >
              <th scope="row" >{{index+1}}</th>
              <td>{{item.name}}</td>
              <td>
                <input type="checkbox" id="one" value="One" v-model="picked" />
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>

    <div class="grey">
      <span>Private Smart Contracts</span>
    </div>
    <div class="blue">
      <div class="atable">
        <table class="table table-striped table-hover table-sm">
          <thead class="table-inside">
            <tr>
              <th style="width: 20%" scope="col">#</th>
              <th style="width: 60%" scope="col">Smart Contract Name</th>
              <th style="width: 20%" scope="col">Select</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(item, index) in Private(getlistSmartContract)" 
                  v-bind:key="index">
              <th scope="row"> {{index+1}} </th>
              <td>{{item.name}}</td>
              <td>
                <input type="checkbox" id="one" value="One" v-model="picked" />
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
    <div id="action">
      <div id="btn" @click="routing('add')">Add</div>
      <div id="btn" v-on:click="load">Upload File</div>
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
                  return array.type === "Private"
              });
            },
    Common: function (arrays) {
                return arrays.filter(function (array) {
                  return array.type === "Common"
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
  margin-bottom: 3%;
  margin-top: 3%;
}
.table-inside {
  background-color: #d9edf7;
  color: #3a7694;
}
.blue {
  border-radius: 10px;
  width: 80%;
  text-align: center;
  margin-left: 10%;
  margin-right: 30%;
  height: 270px;
  color: black;
}
.grey {
  width: 190px;
  height: 30px;
  color: black;
}
.grey {
  margin-left: 11%;
  margin-bottom: 25px;
  background: white;
  z-index: 3;
  position: relative;
}
.blue {
  border: 1px solid #d9edf7;
  box-shadow: rgba(0, 0, 0, 0.05) 0px 6px 24px 0px,
    rgba(0, 0, 0, 0.08) 0px 0px 0px 1px;
  margin-top: -40px;
  background: none;
  z-index: 2;
  position: relative;
}

h1 {
  text-align: center;
  font-size: 35px;
  font-weight: bold;
}

.atable {
  box-shadow: rgba(0, 0, 0, 0.05) 0px 6px 24px 0px,
    rgba(0, 0, 0, 0.08) 0px 0px 0px 1px;
  margin-left: 50px;
  margin-top: 30px;
  margin-right: 50px;
  padding-bottom: 5%;
  border: 1px solid #d9edf7;
  border-radius: 10px;
}
#btn {
  cursor: pointer;
  width: 12%;
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
  width: 60%;
}
div#main {
  padding-bottom: 3%;
}

</style>