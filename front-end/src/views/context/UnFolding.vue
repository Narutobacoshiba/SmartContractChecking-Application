
<template>
  <div id="main">
    <!-- nav -->

    <div id="header">
      <h1>Choose functions for unfolding</h1>
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
              <th style="width: 40%" scope="col">Global variables</th>
              <th style="width: 25%" scope="col">Selected All</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="data in datatable" :key="data.id">
              <td>{{ data.id }}</td>
              <td>{{ data.var }}</td>
              <td><input type="checkbox" /></td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
    <div id="action">
      <div id="sc-unfold" @click="routing('unfolding')">Unfold</div>
      <div id="sc-save" @click="routing('next')">Next</div>
      <div id="sc-cancel" @click="routing('back')">Back</div>
    </div>
  </div>
</template>

<script>
import Axios from "axios";
export default {
  data() {
    return {
      datatable: [
        { id: "1", var: "GV1" },
        { id: "2", var: "GV2" },
        { id: "3", var: "GV3" },
        { id: "4", var: "GV4" },
      ],
    };
  },
  methods: {
    routing(param) {
      if (param == "unfolding") {
        const dcr2cpn = Axios.get("http://127.0.0.1:8000/calltool/unfolding/")
        console.log(dcr2cpn)  
        this.$router.push({ name: "LTLCheckOption" });
      }
      if (param == "next") {
        this.$router.push({ name: "LTLCheckOption" });
      }
      if (param == "back") {
        this.$router.push({ name: "ContextOfSmartContract" });
      }
    },
  },
};
</script>

<style scoped>
.main{
  font-family: Arial, Helvetica, sans-serif;
}
.trapezoid {
  border-bottom: 30px solid grey;
  border-right: 25px solid transparent;
  height: 0;
  width: 50px;
  text-align: center;
  margin-bottom: 11px;
}
.trapezoid a {
  color: black;
}
#header {
  text-align: center;
  margin-bottom: 3%;
  margin-top: 3%;
}
.table-inside{
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
  box-shadow: rgba(0, 0, 0, 0.05) 0px 6px 24px 0px, rgba(0, 0, 0, 0.08) 0px 0px 0px 1px;
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
  box-shadow: rgba(0, 0, 0, 0.05) 0px 6px 24px 0px, rgba(0, 0, 0, 0.08) 0px 0px 0px 1px;
  margin-left: 50px;
  margin-top: 50px;
  margin-right: 50px;
  padding-bottom: 15%;;
  border: 1px solid #d9edf7;
  border-radius: 10px;
}
#sc-save {
  cursor: pointer;
  width: 15%;
  height: 2%;
  background-color: #2196f3;
  text-align: center;
  color: white;
  font-size: 13px;
  line-height: 22px;
  font-weight: 600;
  padding: 4px 3px;
  border-radius: 4px;
  cursor: pointer;
  border-width: 0px;
}
#sc-cancel {
  cursor: pointer;
  width: 15%;
  height: 2%;
  background-color: #2196f3;
  text-align: center;
  color: white;
  font-size: 13px;
  line-height: 22px;
  font-weight: 600;
  padding: 4px 3px;
  border-radius: 4px;
  cursor: pointer;
  border-width: 0px;
}
#sc-unfold {
 cursor: pointer;
  width: 15%;
  height: 2%;
  background-color: #2196f3;
  text-align: center;
  color: white;
  font-size: 13px;
  line-height: 22px;
  font-weight: 600;
  padding: 4px 3px;
  border-radius: 4px;
  cursor: pointer;
  border-width: 0px;
}
#sc-save:hover {
  background-color: #1079cf;
}
#action {
  margin: 0 auto;
  margin-top: 4%;
  display: flex;
  justify-content: space-between;
  width: 60%;
}
div#main {
    padding-bottom: 50px;
}
</style>