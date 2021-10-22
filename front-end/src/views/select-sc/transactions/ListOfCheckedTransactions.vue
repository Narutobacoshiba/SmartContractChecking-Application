<template>
  <div id="main">
    <div id="header">
    <h1>List of Checked Transactions</h1>
    </div>

    <div class="grey">
      <span>Checked information</span>
    </div>

    <div class="blue">
      <div class="atable">
        <table class="table table-striped table-hover table-sm">
          <thead class="table-inside">
            <tr>
              <th style="width: 10%" scope="col">#</th>
              <th style="width: 40%" scope="col">Batch Name</th>
              <th style="width: 25%" scope="col">Checked Date</th>
              <th style="width: 25%" scope="col">Description</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(item, index) in getListTransaction" v-bind:key="index">
              <th scope="row">{{ index + 1 }}</th>
              <td>
                <div v-on:click="set(item.bid)" v-bind:id="item.bid"><router-link
                  :to="{path:'checkreentrancydetail', query: { id: item.bid }}"
                  tag="a"
                  class="lk"
                  >{{ item.name }}</router-link
                ></div>
              </td>
              <td>{{ item.checkeddate }}</td>
              <td>{{ item.description }}</td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
    <div id="action">
      <div id="btn-addsc" @click="routing('addsc')">Add Smart Contracts</div>
      <div id="btn-backnext" @click="routing('back')">Back</div>
      <div id="btn-backnext" @click="routing('next')">Next</div>
    </div>
  </div>
</template>

<script>
import { mapActions, mapGetters } from "vuex";
export default {
  data() {
    return {
      info: [],
      id: null,
    };
  },
  methods: {
    
    routing(param) {
      if (param == "next") {
        this.$router.push({ name: "CheckRentrancy" });
      }
      if (param == "addsc") {
        this.$router.push({ name: "SelectSmartContract" });
      }
      if (param == "back") {
        this.$router.push({ name: "Index" });
      }
    },
    ...mapActions(["getListTran","setid"]),
    set(data){
      console.log(data);
       this.setid(data);
     }
  },

  computed: {
    ...mapGetters(["getListTransaction","getid"]),
  },

  created() {
    this.getListTran();
    
  },
};
</script>

<style scoped>
.main {
  font-family: Arial, Helvetica, sans-serif;
}
#header {
  text-align: center;
  margin-bottom: 2%;
  margin-top: 2%;
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
  height: 470px;
  color: black;
}
.grey {
  width: 150px;
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
  margin-top: 50px;
  margin-right: 50px;
  padding-bottom: 15%;
  border: 1px solid #d9edf7;
  border-radius: 10px;
}
#btn-addsc {
  cursor: pointer;
  width: 25%;
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
#btn-addsc:hover {
  background-color: #1079cf;
  color: white;
}
#btn-backnext {
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
#btn-backnext:hover {
  background-color: #1079cf;
  color: white;
}
#action {
  margin: 0 auto;
  margin-top: 4%;
  display: flex;
  justify-content: space-between;
  width: 60%;
  padding-bottom: 5%;
}
.Button {
  margin-top: 80px;
}

a {
  text-decoration: none;
  color: black;
}

a:hover {
  color: red;
  text-decoration: underline red wavy;
}
div#main {
  padding-bottom: 10%;
}
</style>