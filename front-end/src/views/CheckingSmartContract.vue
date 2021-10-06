<template>
<<<<<<< Updated upstream
  <div class="container">
        <div class="smart">
            <h1>Checking smart contract</h1>

            <div class="parent">
                <div class="greys">
                    <span>DCR</span>
                </div>
                <div class="blues">
                    <div class="sub">
                        <div class="grey">
                            <span>Blind Aution</span>
                        </div>
                        <div class="blue">
                            <div class="atable">
                                <table class="table table-striped table-hover table-sm ">
                                    <thead class="table-dark">
                                        <tr>
                                            <th style="width: 10%" scope="col">#</th>
                                            <th style="width: 45%" scope="col">LTL Property</th>
                                            <th style="width: 45%" scope="col">Type</th>
                                        </tr>
                                    </thead>
                                    <tbody>
                                        <tr>
                                            <th scope="row">1</th>
                                            <td>Mark</td>
                                            <td>Otto</td>

                                        </tr>
                                        <tr>
                                            <th scope="row">2</th>
                                            <td>Jacob</td>
                                            <td>Thornton</td>

                                        </tr>
                                        <tr>
                                            <th scope="row">3</th>
                                            <td>Larry the Bird</td>
                                            <td>Larry the Bird</td>

                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                        </div>
=======
   <div id ="main">
   <div id ="header">
     <h1>Checking Smart Contracts</h1>
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
         <div id="processing-btn">
                <button v-if="step == 'initial' || step == 'generating'" class="btn btn-outline-primary" @click="generate">Generate</button>
                <button v-else class="btn btn-outline-primary" @click="check">Check</button>
            </div>
            <div class="process-contain">        
       <div id="processing-section">
                <div id="download"><a v-if="showDownload" class="btn btn-outline-primary" href="" download="Solidity">Download</a></div>
                <div id="initial" v-if="step == 'initial'"></div>
                <div id="generating" v-show="step == 'generating'">
                    <div>The smart contract is generating...</div>
                    <div class="progress" id="progress">
                        <div id="progress-bar-gen" class="progress-bar progress-bar-striped bg-warning" role="progressbar" style="width: 0%"></div>
>>>>>>> Stashed changes
                    </div>
                    <div class="sub">
                        <div class="grey">
                            <span>EtherGame</span>
                        </div>
                        <div class="blue">
                            <div class="atable">
                                <table class="table table-striped table-hover table-sm ">
                                    <thead class="table-dark">
                                        <tr>
                                            <th style="width: 10%" scope="col">#</th>
                                            <th style="width: 45%" scope="col">LTL Property</th>
                                            <th style="width: 45%" scope="col">Type</th>
                                        </tr>
                                    </thead>
                                    <tbody>
                                        <tr>
                                            <th scope="row">1</th>
                                            <td>Mark</td>
                                            <td>Otto</td>

                                        </tr>
                                        <tr>
                                            <th scope="row">2</th>
                                            <td>Jacob</td>
                                            <td>Thornton</td>

                                        </tr>
                                        <tr>
                                            <th scope="row">3</th>
                                            <td>Larry the Bird</td>
                                            <td>Larry the Bird</td>

                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                        </div>
                    </div>
                </div>
            </div>

            <div class="parent">
                <div class="greys">
                    <span>Free-context</span>
                </div>
                <div class="blues">
                    <div class="sub">
                        <div class="grey">
                            <span>Blind Aution</span>
                        </div>
                        <div class="blue">
                            <div class="atable">
                                <table class="table table-striped table-hover table-sm ">
                                    <thead class="table-dark">
                                        <tr>
                                            <th style="width: 10%" scope="col">#</th>
                                            <th style="width: 45%" scope="col">LTL Property</th>
                                            <th style="width: 45%" scope="col">Type</th>
                                        </tr>
                                    </thead>
                                    <tbody>
                                        <tr>
                                            <th scope="row">1</th>
                                            <td>Mark</td>
                                            <td>Otto</td>

                                        </tr>
                                        <tr>
                                            <th scope="row">2</th>
                                            <td>Jacob</td>
                                            <td>Thornton</td>

                                        </tr>
                                        <tr>
                                            <th scope="row">3</th>
                                            <td>Larry the Bird</td>
                                            <td>Larry the Bird</td>

                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="Button">
            <div class="row">
                <div class="col-sm-6 left">
                    <button type="button" class="btn btn-primary">Generate</button>
                </div>
                <div class="col-sm-6 right">
                    <button type="button" class="btn btn-primary">Add new session</button>
                </div>
            </div> 
            </div>
        </div>

    </div>
</template>

<script>
export default {
  
  
};
</script>
<<<<<<< Updated upstream

<style scoped>
 .blue {
    width: 100%;
    height: 200px;
    color: black;
  }
  .grey{
    width: 100px;
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
  }
h1{
    text-align: center;
=======
<style>
.process-contain{ 
  padding-bottom: 5%;
}
#header {
  text-align: center;
  margin-top: 4%;
  margin-bottom: 3%;
  
}
#header h1{
  font-size: 35px;
  font-weight: bold;
>>>>>>> Stashed changes
}

.sub{
  margin-top: 20px;
  margin-right: 20px;
  margin-left: 20px;
  margin-bottom: 25px;
}
.atable{
    margin-left: 40px;
    margin-top: 20px;
    margin-right: 40px;
}

.Button{
    margin-top: 80px;
}

.left, .right{
  text-align: center;
}
<<<<<<< Updated upstream

.blues {
  width: 100%;
  color: black;
=======
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
    background-color:#d9edf7;
    color: #4ea8d6;
}
#processing-btn{
    margin: 40px;
    text-align: center;
}


#download{
    text-align: right;
    padding: 20px;
    height: 60px;
}
#processing-section{
    height: 300px;
    margin: auto;
    border: 1px black solid;
    border-radius: 3px;
    text-align: center;
    background-color: #f5f5f5;
    width: 80%;
    padding-bottom: 5%;
}
#generating, #checking{
    margin: auto;
    margin-top: 60px;
    padding: 0;
    width: 70%;
>>>>>>> Stashed changes
}
.greys{
  text-align: center;
  width: 100px;
  height: 30px;
  color: black;
}
.greys{
  margin-left: 20px;
  margin-bottom: 25px;
  background: white;
  z-index: 3;
  position: relative;
}
.blues{
  border: 1px solid black;
  margin-top: -40px;
  background: none;
  z-index: 2;
  position: relative;
}

.parent{
  margin-top: 20px;
}
</style>