<template>
  <div class="container">
        <h1>Initial Marking Setting</h1>
        <div class="pa">
            <div class="row">
                <div class="col-sm-3 left">Number of users</div>
                <div class="col-sm-9 right"><input type="text" class="form-control" id="basic-url"
                        aria-describedby="basic-addon3"></div>
            </div>
        </div>

        <div class="pa">
            <div class="row">
                <div class="col-sm-3 left">Users balance </div>
                <div class="col-sm-9 right"><input type="text" class="form-control" id="basic-url"
                        aria-describedby="basic-addon3"></div>
            </div>
        </div>

        <div class="pa">
            <div class="row">
                <div class="col-sm-3 left">Sender value </div>
                <div class="col-sm-9 right"><input type="text" class="form-control" id="basic-url"
                        aria-describedby="basic-addon3"></div>
            </div>
        </div>

        <div class="pa">
            <div class="row">
                <div class="col-sm-3 left">Other parameters</div>
                <div class="col-sm-9 right"><textarea class="form-control text" aria-label="With textarea"></textarea>
                </div>
            </div>
        </div>

        <div class="pabutton">
            <div class="row">
                <div class="col-sm-6 buttonsleft"><button type="button" class="btn btn-primary" @click="routing('save')">Add</button></div>
                <div class="col-sm-6 buttonsright"><button type="button" class="btn btn-primary" @click="routing('back')">Back</button></div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
  data () {
    return {
     
    }
  },
  methods: {
    routing(param) {
      if (param == "save") {
        this.$router.push({ name: "CheckSmartContract" });
      }
      if(param=='back'){
        this.$router.push({name:"CSPSettingType"})
      }
    },
  },
};
</script>
<style scoped>
 h1{
  text-align: center;
}


.left{
  text-align: right;
}

.pa{
  margin-top: 30px;
  margin-bottom: 30px;
}

.text{
  height: 200px;
}

.buttonsright{
  text-align: center;
}

.buttonsleft{
  text-align: right;
}

.pabutton{
  margin-top: 100px;
}
</style>