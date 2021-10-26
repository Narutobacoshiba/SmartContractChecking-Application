<template>
  <div class="container">
    <div id="header">Checking Result</div>
    <div class="main">
      <div class="content">
        <p v-for="(item, index) in getListCheck" v-bind:key="index">
            {{item[0]}}
        </p>
      </div>
    </div>

    <div class="button">
      <div class="container">
        <div class="row up">
          <div class="col-5">
            <button type="button" class="btn btn-outline-primary" @click="routing('start')">
              Start a new checking session
            </button>
          </div>
          <div class="col-5 right">
            <button type="button" class="btn btn-outline-primary" @click="routing('back')">Back</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { mapActions, mapGetters } from "vuex";
export default {
  methods:{
    routing(param){
      if(param=='back'){
        this.$router.push({name:"ListOfCheckedTransactions"})
      }
      if(param=='start'){
        this.$router.push({ name: "SelectSmartContract" });
      }
    },
    ...mapActions(["setlistcheck"]),
  },
  computed: {
    ...mapGetters(["getListCheck"]),
  },
  created() {
    this.setlistcheck(this.$route.query.id);
  },
};
</script>

<style>
#header {
  text-align: center;
  font-weight: bolder;
  font-size: 30px;
  margin-bottom: 70px;
}
.main {
  display: flex;
  justify-content: center;
}
.content {
  width: 800px;
  border: 1px solid black;
  width: 60%;
  height: 300px;
  font-weight: bolder;
  margin-bottom: 100px;
}
.right {
  text-align: right;
}
.up {
  margin-bottom: 20px;
}
</style>