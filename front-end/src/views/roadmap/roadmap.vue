<template>
  <div class="container">
    
    <h1>Roadmap</h1>
  <div id="main">
    <ul class="progressbar">
      <li v-for="page in pages" :key="page.id" :class="{ active: page.id <= road_page , choosen: page.id == current_page}">
        <a @click="routing(page)" class="dropbtn">{{ page.name }}</a>
      </li>
    </ul>
  </div></div>
</template>

<script>
export default {
  data() {
    return {
      pages: [
        { id: 1, name: "Select Smart Contracts", view: "sc-selection"},
        { id: 2, name: "Select Context", view: "select-context"},
        { id: 3, name: "Choose Vulnerabilities", view: "choose-vul"},
        { id: 4, name: "Generate SC to CPN",view: "generate-sc2cpn"},
        { id: 5, name: "Check the SCs",view: "check-sc" },
        { id: 6, name: "Finish",view: "finish"},
      ],
    };
  },
   methods: {
    routing(page){
      if(page.id <= this.road_page){
        this.$store.commit("data/SetProcessView",page.view)
        this.$router.push("/process")
      }
    }
  },
  computed: {
      current_page(){
            var view = this.$store.getters["data/GetProcessView"]
            var id = this.pages.filter(item => {
            return item.view == view;
          })[0].id
          return id
        },
      road_page(){
        return this.$store.getters["data/GetRoadPage"]
      }
  }
};
</script>

<style scoped>
h1{
  text-align: center;
  margin-top: 30px;
}
#main{
  height: 70vh;
  width: 50%;
  max-width: 500px;
  margin: auto;
  box-sizing: border-box;
}
.progressbar{
  position: relative;
  top: 50%;
  transform: translateY(-50%);
  counter-reset: step;
}
.progressbar li{
  list-style: none;
}
.progressbar::after{
  content: '';
  position: absolute;
  width: 2px;
  height: calc(100% - 60px);
  right: 90px;
  top: 0;
  background: black;
  z-index: -1;
  margin-top: 5px;
  transform: translateY(5%);
}
.progressbar ul li{
  line-height: 300px;
}
.progressbar li a{
  font-size: 1.2rem;
  line-height: 5rem;
  font-weight: 500;
  
}
.progressbar li a::before {
  content: counter(step);
  counter-increment: step;
  background-color: red;
  position: absolute;
  width: 30px;
  height: 30px;
  line-height: 1.5;
  text-align:  center;
  right: 76px;
  border: 2px solid #bebebe;
  border-radius: 4px;
  font-size: 1rem;
  transform: translateY(80%);
  background: white;
  color: #bebebe;
  text-align: center;
  font-weight: bold;
}
.progressbar li.active a:before {
  border-color: #5fb8ee;
  background-color: #5fb8ee;
  color: white;
}
.progressbar li.choosen a:before {
  border-color: #3a7694;
  background-color: #3a7694;
  color: white;
}
li a{
  text-decoration: none;
  color: black;
}
li.active a{
  color: #1967d2;
  text-decoration: underline;
}
li.active a:hover{
  cursor: pointer;
}
@media only screen and (max-width: 960px) {
  #main{
    width: 100%;
    margin: auto;
  }
  .progressbar::after{
    right: 20px;
  }
  .progressbar li a::before{
    right: 6px;
  }
  .progressbar{
    margin: auto;
  }
}
</style>