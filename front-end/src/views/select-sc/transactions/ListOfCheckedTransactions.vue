<template>
  <div class="container">
    <div class="smart">
      <h1>List of Checked Transctions</h1>
      <div class="grey">
        <span>Checked information</span>
      </div>
      <div class="blue">
        <div class="atable">
          <table class="table table-striped table-hover table-sm">
            <thead class="header">
              <tr>
                <th style="width: 10%" scope="col">#</th>
                <th style="width: 40%" scope="col">Batch Name</th>
                <th style="width: 25%" scope="col">Checked Date</th>
                <th style="width: 25%" scope="col">Description</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="(item, index) in getListTransaction" v-bind:key="index" >
                <th scope="row">{{ index +1}}</th>
                <td>
                  <router-link :to="'checkreentrancydetail'" tag="a" class="lk"
                    >{{ item.name}}</router-link
                  >
                </td>
                <td>{{item.checkeddate}}</td>
                <td>{{item.description}}</td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>
    <div class="Button">
      <div class="row">
        <div class="col-sm-8">
          <button
            type="button"
            class="btn btn-primary"
            @click="routing('addsc')"
          >
            Add Smart Contracts
          </button>
        </div>
        <div class="col-sm-2">
          <button
            type="button"
            class="btn btn-primary"
            @click="routing('back')"
          >
            Back
          </button>
        </div>
        <div class="col-sm-2">
          <button
            type="button"
            class="btn btn-primary"
            @click="routing('next')"
          >
            Next
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { mapActions, mapGetters } from 'vuex';
//import axios from "axios";
export default {
  data() {
    return {
      info: [],
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
    ...mapActions(['getListTran']),
  },

  computed :{
    ...mapGetters(['getListTransaction'])
  },

  created() {
    this.getListTran();
  },
};
</script>

<style scoped>
.blue {
  width: 100%;
  height: 450px;
  color: black;
}
.grey {
  width: 150px;
  height: 30px;
  color: black;
}
.grey {
  margin-left: 20px;
  margin-bottom: 25px;
  background: white;
  z-index: 3;
  position: relative;
}
.blue {
  border: 1px solid black;
  margin-top: -40px;
  background: none;
  z-index: 2;
  position: relative;
  border-radius: 10px;
}
h1 {
  text-align: center;
}

.atable {
  margin-left: 25px;
  margin-top: 20px;
  margin-right: 25px;
}

.Button {
  margin-top: 80px;
}

.header {
  background-color: rgb(144, 208, 243);
}

a {
  text-decoration: none;
  color: black;
}

a:hover {
  color: red;
  text-decoration: underline red wavy;
}
</style>