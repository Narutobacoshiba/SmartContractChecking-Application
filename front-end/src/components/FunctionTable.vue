<template>
 <div id ="main">
   <a>Return to home</a>
   <div id ="header">
     <h2>Choose a function for the {Function 1} </h2>
   </div>
   <div id = "screen">
      <div class="trapezoid "><p>SC</p></div>
   </div>
   <div id = "component">
          <div class="table table-striped table-hover">
          <table class="table" border="1">
            <tr>
              <th>#</th>
              <th>Funtions</th>
              <th>Select</th>
            </tr>
            <tr v-for="data in datatable" :key="data.id">
              <td>{{ data.id }}</td>
              <td>{{ data.var }}</td>
              <td><input type="checkbox" /></td>
            </tr>
          </table>
        </div>
      </div>
      <div id="action">
        <div id="sc-save" @click="save">Save</div>
        <div id="sc-cancel" @click="cancel">Cancel</div>
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
}
</script>

<style>
#header {
  text-align: center;
  margin-top: 8%;
  margin-bottom: 3%
}
#main {
  text-align: center;
}
#component{
  margin: 0 auto;
  border: 2px solid #332529;
  width: 80%;
  padding-top: 4%;
  padding-bottom: 3%;
}
.table{
  width:80%;
  margin: 0 auto
}
.table tr:first-child{
    background-color:#483125;
    color: white;
}
.trapezoid {
  border-bottom: 40px solid #483125;
  border-right: 20px solid transparent;
  height: 0;
  width: 50px;
  text-align: center;
  position: relative;
  left:15%;
  text-align: center;
  color: white;
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
