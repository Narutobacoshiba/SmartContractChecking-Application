<template>
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
</template>

<script>
export default {
  
  
};
</script>

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

.blues {
  width: 100%;
  color: black;
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