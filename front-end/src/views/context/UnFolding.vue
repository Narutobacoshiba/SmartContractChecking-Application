<template>
  <div id="main">
    <div id="header">
      <h2>Choose functions for unfolding
</h2>

    </div>
    <!-- nav -->
    <div class="screen">
      <nav class="nav">
        <div class="trapezoid "><a href="#">SC</a></div>

      </nav>
    </div>
    <div class="row">
      <div class="row-1">

        <div class="table-layout">
          <table class="table-1 table-bordered " border="1">
            <tr>
              <th>#</th>
              <th>Global variables</th>
              <th>Selected All</th>
            </tr>
            <tr v-for="data in datatable" :key="data.id">
              <td>{{ data.id }}</td>
              <td>{{ data.var }}</td>
              <td><input type="checkbox" /></td>
            </tr>
          </table>
        </div>
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
export default {
  data () {
    return {
      datatable: [
        { id: '1', var: 'GV1' },
        { id: '2', var: 'GV2' },
        { id: '3', var: 'GV3' },
        { id: '4', var: 'GV4' }
      ]
    }
  },
  methods:{
    routing(param){
      if(param=='unfolding'){this.$router.push({name:"LTLCheckOption"})}
      if(param=='next'){
        this.$router.push({name:"LTLCheckOption"})
      }
      if(param=='back'){
        this.$router.push({name:"ContextOfSmartContract"})
      }
    }
  }
}
</script>

<style scoped>
#header {
  text-align: center;
  margin-bottom: 3%;
  margin-top: 3%;
}

.table-layout {
  height: 20%;
  padding-bottom: 2%;
  padding-top: 2%;
  position: relative;
  left: 17%;
}
/* .row-1 {
  position: relative;
  left: 12%;
  padding-bottom: 2%;
  width: 80%;
  height: 20%;
  border: 3px solid black;
  margin-top: 5%;
}
.row-2 {
  margin-top: 5%;
  margin-bottom: 5%;
} */
.table-1 {
  width: 78%;
  border: 2px solid black;
}
.row {
  border: 3px solid black;
  width: 80%;
  text-align: center;
  margin-left: 10%;
}
.component-1 {
  position: relative;
  bottom: 15px;
  left: 2.1%;
  z-index: 1;
  height: 30px;
  width: 15%;
  background: white;
}
a {
  text-decoration: none;
}
li {
  list-style-type: none;
  border: 3px solid black;
  border-top-left-radius: 3px;
  font-size: 70%;
  text-align: center;
  background-color: grey;
  border: outset;
}
li a{
  color: black;
}
ul {
  margin-top: 2%;
  position: relative;
  left: 10%;
  width: 8%;
  float: left;
  top: 4%;
}

.table-2 {
  width: 85%;
  position: relative;
  left: 10%;
  bottom: 12%;
  border: 2px solid black;
}
.divtable {
  padding-top: 1%;
  padding-bottom: 1%;
  border: 3px solid;
  width: 75%;
  float: right;
  position: relative;
  right: 7%;
}
.trapezoid {
  border-bottom: 30px solid grey;
  border-right: 25px solid transparent;
  height: 0;
  width: 50px;
  text-align: center;
}
.trapezoid a {
  color: black;
}
.screen {
  margin-left: 13%;
}

#sc-save{
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
#sc-cancel{
   cursor: pointer;
   width: 15%;
    height: 2%;
    background-color: white;
    text-align: center;
    color: black;
    font-size: 13px;
    line-height: 22px;
    font-weight: 600;
    padding: 4px 3px;
    border: 1px solid;
    border-radius: 4px;
    cursor: pointer;
}

#sc-unfold{
   cursor: pointer;
   width: 15%;
    height: 2%;
    background-color: white;
    text-align: center;
    color: black;
    font-size: 13px;
    line-height: 22px;
    font-weight: 600;
    padding: 4px 3px;
    border: 1px solid;
    border-radius: 4px;
    cursor: pointer;
}

#sc-save:hover {
    background-color: #1079cf;
}
#action{
  margin : 0 auto;
  margin-top: 4%;
   display: flex;
  justify-content: space-between;
  width: 60%;
}
</style>