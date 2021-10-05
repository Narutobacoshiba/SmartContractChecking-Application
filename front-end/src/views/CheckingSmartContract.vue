<template>
   <div id ="main">
   <div id ="header">
     <h2>Checking Smart Contracts</h2>
   </div>
   <div class ="text">
       <span>DCR</span>
   </div>
   <div id="locate-1">
    <div class="text-1">
          <span>Blind Auction</span>
      </div>
   <div id = "component">
          <div class="table table-striped table-hover">
          <table class="table" border="1">
            <tr>
              <th>#</th>
              <th>LTL Property</th>
              <th>Type</th>
            </tr>
            <tr v-for="data in datatable" :key="data.id">
              <td>{{ data.id }}</td>
              <td>{{ data.var }}</td>
              <td><input type="checkbox" /></td>
            </tr>
          </table>
        </div>
      </div>
        <div class="text-1">
          <span>EitherGame</span>
      </div>
   <div id = "component">
          <div class="table table-striped table-hover">
          <table class="table" border="1">
            <tr>
              <th>#</th>
              <th>LTL Property</th>
              <th>Type</th>
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
      <div class ="text-2">
       <span>Free-content</span>
   </div>
   <div id="locate-1">
        <div class="text-1">
          <span>EitherLotto</span>
      </div>
   <div id = "component">
          <div class="table table-striped table-hover">
          <table class="table" border="1">
            <tr>
              <th>#</th>
              <th>LTL Property</th>
              <th>Type</th>
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
        <div id="sc-check" @click="check">Check</div>
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
  }
  
};
</script>
<style>
#header {
  text-align: center;
  margin-top: 4%;
  margin-bottom: 3%
}
#locate-1{
    border: 1px solid;
    width: 80%;
    margin: 0 auto;
    padding-bottom: 3%;
}
.text-1 {
  position: relative;
  left: 15%;
  top:15px;
  z-index: 1;
  height: 30px;
  width: 8%;
  background: white;
  text-align: center;
}
.text-2{
  position: relative;
  left: 15%;
  top:15px;
  z-index: 1;
  height: 30px;
  width: 6.6%;
  background: white;
  text-align: center;
}
.text{
   position: relative;
  left: 15%;
  top:15px;
  z-index: 1;
  height: 30px;
  width: 3.6%;
  background: white;
  text-align: center;
}
#component{
  margin: 0 auto;
  border: 2px solid #332529;
  width: 94%;
  padding-top: 2%;
  padding-bottom: 2%;
}
.table{
  width:94%;
  margin: 0 auto
}
.table tr:first-child{
    background-color:#2196f3;
    color: white;
}
#sc-check{
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
#sc-check:hover {
    background-color: #2196f3;
}
#action{
  margin : 0 auto;
  margin-top: 4%;
   display: flex;
  justify-content: center;
  width: 60%;
}

</style>
