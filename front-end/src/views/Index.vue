<template>
    <div id="body">
        <svg width="380px" height="500px" viewBox="0 0 837 1045" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:sketch="http://www.bohemiancoding.com/sketch/ns">
            <g id="Page-1" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd" sketch:type="MSPage">
                <path d="M353,9 L626.664028,170 L626.664028,487 L353,642 L79.3359724,487 L79.3359724,170 L353,9 Z" id="Polygon-1" stroke="#007FB2" stroke-width="6" sketch:type="MSShapeGroup"></path>
                <path d="M78.5,529 L147,569.186414 L147,648.311216 L78.5,687 L10,648.311216 L10,569.186414 L78.5,529 Z" id="Polygon-2" stroke="#EF4A5B" stroke-width="6" sketch:type="MSShapeGroup"></path>
                <path d="M773,186 L827,217.538705 L827,279.636651 L773,310 L719,279.636651 L719,217.538705 L773,186 Z" id="Polygon-3" stroke="#795D9C" stroke-width="6" sketch:type="MSShapeGroup"></path>
                <path d="M639,529 L773,607.846761 L773,763.091627 L639,839 L505,763.091627 L505,607.846761 L639,529 Z" id="Polygon-4" stroke="#F2773F" stroke-width="6" sketch:type="MSShapeGroup"></path>
                <path d="M281,801 L383,861.025276 L383,979.21169 L281,1037 L179,979.21169 L179,861.025276 L281,801 Z" id="Polygon-5" stroke="#36B455" stroke-width="6" sketch:type="MSShapeGroup"></path>
            </g>
        </svg>
        <div class="message-box">
            <h1>Solidity To CPN</h1>
            <p>Check for vulnerabilities in smart contracts</p>
            <div class="buttons-con">
                <div class="action-link-wrap">
                <a @click="routing('check')" class="link-button">Check smart contracts</a>
                </div>
            </div>
            <div id="current-process" v-if="haveProcess">
                <div id="text-infor">
                  <p>Date: {{getCPDateModified()}}</p>
                  <p>Step: {{getCPStep()}}</p>
                </div>
                <div id="cp-button" @click="resumeProcess">
                  <p>Resume</p>
                </div>
            </div>
        </div>
        <div id="showConfirmation" v-if="showDialog">
            <div id="components-holder">
                <confirm @cancel="closeDialog" @confirm="cfNewProcess" :dialog="dialog" />
            </div>
        </div>
    </div>
</template>

<script>
import ConfirmationDialog from "../components/ConfirmationDialog.vue"
export default ({
  components:{'confirm': ConfirmationDialog},
  data(){
    return{
      showDialog: false,
      dialog: {title: 'Start a new process', message: 'Are you sure to start a new process?', confirmbtn: 'OK'},
      pages: [
                    { id: 1, name: "Select Smart Contracts", view: "sc-selection"},
                    { id: 2, name: "Select Context", view: "select-context"},
                    { id: 3, name: "Choose Vulnerabilities", view: "choose-vul"},
                    { id: 4, name: "Generate SC to CPN",view: "generate-sc2cpn"},
                    { id: 5, name: "Check the SCs",view: "check-sc" },
                    { id: 6, name: "Finish",view: "finish"},
                ],
    }
  },
  computed: {
    haveProcess(){
      return this.$store.state.data.used
    }
  },
  methods: {
      routing(param){
          if(param == 'check'){
              var current_date = Date.now()
              if(this.$store.state.data.used)
              {   
                this.showDialog = true;
              }
              else{
                  this.$store.commit("data/ResetState")
                  this.$store.commit('data/SetUsedState',true)
                  this.$store.commit('data/SetDateState',current_date)
                  this.$store.commit("data/SetProcessView","sc-selection")
                  this.$router.push({name:'ListOfCheckedTransactions'})
              }
          }
      },
      closeDialog(){
        this.showDialog = false;
      },
      cfNewProcess(){
        var current_date = Date.now()
        this.$store.commit("data/ResetState")
        this.$store.commit('data/SetUsedState',true)
        this.$store.commit('data/SetDateState',current_date)
        this.$store.commit("data/SetProcessView","sc-selection")
        this.$router.push({name:'ListOfCheckedTransactions'})
        this.closeDialog()
      },
      resumeProcess(){
        this.$store.commit("data/SetProcessView",this.pages[this.$store.getters["data/GetRoadPage"]-1].view)
        this.$router.push({name:'ListOfCheckedTransactions'})
      },
      getCPDateModified(){
        var date = new Date(this.$store.state.data.date_modified)
        return date.getDate()+"/"+(date.getMonth()+1)+"/"+date.getFullYear()+" "+date.getHours()+":"+date.getMinutes()
      },
      getCPStep(){
        return this.$store.state.data.views.road_page+"/6"
      }
  }
})
</script>

<style scoped>
#body {
  height: 700px;
  width: 100%;
  min-width: 420px;
  background-color: #f9f9f9;
  display: flex;
  align-items: center;
}
svg {
  flex-basis: 50%;
}
.message-box {
  flex-basis: 50%;
  color: rgb(68, 67, 67);
  font-family: Roboto;
  font-weight: 300;
}
.message-box h1 {
  font-size: 60px;
  line-height: 46px;
  margin-bottom: 40px;
}
.message-box p {
  font-size: 16px;
  line-height: 10px;
  margin-bottom: 20px;
}
.buttons-con .action-link-wrap {
  margin-top: 40px;
}
.buttons-con .action-link-wrap a {
  background: #68c950;
  padding: 8px 25px;
  border-radius: 4px;
  color: #FFF;
  font-weight: bold;
  font-size: 14px;
  transition: all 0.3s linear;
  cursor: pointer;
  text-decoration: none;
  margin-right: 10px
}
.buttons-con .action-link-wrap a:hover {
  background: #5A5C6C;
  color: #fff;
}

#Polygon-1 , #Polygon-2 , #Polygon-3 , #Polygon-4 , #Polygon-4, #Polygon-5 {
  animation: float 1s infinite ease-in-out alternate;
}
#Polygon-2 {
  animation-delay: .2s; 
}
#Polygon-3 {
  animation-delay: .4s; 
}
#Polygon-4 {
  animation-delay: .6s; 
}
#Polygon-5 {
  animation-delay: .8s; 
}

/* -- current process -- */
#current-process{
  width: 400px;
  height: 60px;
  margin-top: 40px;
  background-image: linear-gradient(to right, #f5f3f3, #d6d4d4);

  display: flex;
  align-items: center;
  justify-content: space-between;
}
#current-process #text-infor{
  padding-left: 25px;
}
#current-process #text-infor p{
  font-size: 13px;
  font-weight: bold;
  margin-bottom: 0px;
  margin-top: 5px;
  color: #918f8f;
}
#current-process #cp-button{
  height: 30px;
  width: 80px;

  border: 1px solid #918f8f;
  border-color: #918f8f;
  color: #918f8f;

  padding: 8px 12px;
  margin-right: 10px;
  cursor: pointer;
}
#current-process #cp-button:hover{
  border-color: #535353;
  color: #535353;
}
 /*---- showConfirmation */
 #showConfirmation{
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0,0,0,0.2);
    z-index: 1;
    align-items: center;
    justify-content: center;
}
#components-holder{
    width: 50%;
    margin: auto;
    margin-top: 200px;
}
@keyframes float {
	100% {
    transform: translateY(20px);
  }
}
@media only screen and (max-width: 820px){
  #body {
      flex-direction: column;
  }
  .message-box {
      margin-top: 30px;
  }
}

</style>