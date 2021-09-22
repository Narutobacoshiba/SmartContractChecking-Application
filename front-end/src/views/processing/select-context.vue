<template>
      <div class="container" id="section">
        <div id="header">Context of the Smart Contract</div>

        <div class="row" id="select">
          <div class="col-3">
            <p>Context of the SCs</p>
          </div>
          <div class="col-6">
            <select class="form-select input-sm" aria-label="Default select example" v-model="contextSC" @change="setContext()">
              <option v-for="c in contexts" :key="c" :value="c">{{c.context}}</option>
            </select>
          </div>
          <div class="col-3">
            <button type="button" id="load-btn" class="btn btn-outline-primary btn-md" @click="loadContext()">
              Load a Context
            </button>
          </div>
        </div>

        <div class="row" id="description">
          <div class="col-3">
            <p>Description</p>
          </div>
          <div class="col-9">
            <span>There are several options:</span>
            <ul>
              <li v-for="c in contexts" :key="c">{{c.des}}</li>
            </ul>
          </div>
        </div>

        <div id="btns">
          <button id="btn1" type="button" class="btn btn-outline-primary btn-sm" @click="routing('back')">Back</button>
          <button id="btn2" type="button" class="btn btn-primary btn-sm" @click="routing('next')">Next</button>
        </div>
        <div id="showComponents" v-if="getShowComponents">
            <div id="components-holder">
              <UpLoadItems @closeComponents="cComponents"/>
            </div>
        </div>
      </div>
</template>
<script>
import UpLoadItems from "./sc-selection/upload-data.vue"
import {GetContext} from "../../services/data";
export default {
  components:{UpLoadItems},
    data(){
        return{
            contexts: [],
            selectedContext: [],
            contextSC: [],
            showComponents: false,
        }
    },
  mounted: function(){
    this.contexts = GetContext();
  },
  methods: {
    cComponents(){
            this.showComponents = false
        },
    routing(param){
            if(param == "back"){
                this.$store.commit("data/SetProcessView","sc-selection")
            }
            if(param == "next"){
                this.$store.commit("data/SetProcessView","choose-vul")
            }
        },
    loadContext(){
            this.showComponents = true
        },
    setContext(){
            var arr = [];
            arr.push(this.contextSC);
            this.$store.commit("data/SetSelectedContext", arr);
          
    }
  },
  computed:{
    getShowComponents(){
            return this.showComponents
        },
  }
};
</script>
<style scoped>
#section{
  width: 70%;
  margin: auto;
}
#header{
  text-align: center;
  font-size: 35px;
  font-weight: bold;
  margin-top: 20px;
}
#select {
  margin-top: 60px;
  text-align: center;
}
#select p {
  text-align: left;
  font-size: 18px;
}
#load-btn{
  float: left;
}
#description {
  margin-top: 100px;
}
#description p {
  text-align: left;
  font-size: 18px;
}
#btns {
  text-align: center;
  margin-top: 50px;
  margin-bottom: 50px;
}
#btns button {
  margin-left: 40px;
  margin-right: 40px;
}

/* ---- showComponents ---- */
#showComponents{
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0,0,0,0.7);
    z-index: 100;
    display: flex;
    align-items: center;
    justify-content: center;
}

@media screen and (max-width: 800px) {
    #section{
      width: 100%;
    }
}
</style>