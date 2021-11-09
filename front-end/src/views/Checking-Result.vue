<template>
    <div>
        <div id="cr-header">
            Checking Result
        </div>
        <div id="cr-content">
            <div id="crc-show-text">
                {{getCheckingResult}}
            </div>
            <div id="crc-button">
                <button class="button-style" role="button" @click="checkSLTL">Checking with the same LTL property and different configuration</button>
                <button class="button-style" role="button" @click="checkDLTL">Checking with different LTL property</button>
            </div>
            <div id="crc-button">
                <button class="button-style" role="button" @click="startNewSession">Start a new checking session</button>
                <button class="button-style" role="button" @click="goPrePage">Back</button>
            </div>
        </div>  
    </div>
</template>

<script>
export default ({
    data() {
        return{
            checking_result: "",
        }
    },
    mounted(){
        let checking_data = this.$store.getters["data/GetCheckingModelData"]
        this.checking_result = checking_data.data
    },
    computed:{
        getCheckingResult(){
            return this.checking_result
        }
    },
    methods: {
        checkSLTL(){
            this.$store.commit("data/ResetGenerateModelData")
            this.$store.commit("data/ResetCheckingModelData")
            this.$store.commit("data/ResetInitialMarking")
            this.$store.commit("data/SetCheckingRoadView",3)
            this.$store.commit("data/SetCurrentRoadView",3)
            this.$router.push({ name: "InitialMarkingSetting" })
        },
        checkDLTL(){
            this.$store.commit("data/ResetGenerateModelData")
            this.$store.commit("data/ResetCheckingModelData")
            this.$store.commit("data/ResetSelectedVulnerability")
            this.$store.commit("data/SetCheckingRoadView",3)
            this.$store.commit("data/SetCurrentRoadView",3)
            this.$router.push({ name: "LtlCheckingOptions" })
        },
        startNewSession(){
            this.$store.commit("data/ResetAllData")
            this.$router.push({ name: "SmartContractSelection" })
        },
        goPrePage(){
            this.$router.push({ name: "CheckCPNModel" })
        },
    }
})
</script>

<style scoped>
/* header */
#cr-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 20px;
    margin-bottom: 20px;
}

/* content */
#cr-content{
    width: 60%;
    margin:auto;
}

#crc-show-text{
    width: 90%;
    height: 400px;
    margin: auto;
    margin-bottom: 20px;
    padding-left: 10px;
    padding-top: 5px;
    padding-bottom: 5px;
    border: 1px solid black;
    border-radius: 4px;
    white-space: pre-line;
    overflow-y: auto;
}

/* Button */
#crc-button{
    width: 100%;
    height: 60px;
    margin: auto;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.button-style {
  background-color: #FFFFFF;
  border: 0;
  border-radius: .5rem;
  box-sizing: border-box;
  color: #111827;
  font-family: "Inter var",ui-sans-serif,system-ui,-apple-system,system-ui,"Segoe UI",Roboto,"Helvetica Neue",Arial,"Noto Sans",sans-serif,"Apple Color Emoji","Segoe UI Emoji","Segoe UI Symbol","Noto Color Emoji";
  font-size: .875rem;
  font-weight: 600;
  line-height: 1.25rem;
  padding: .75rem 1rem;
  text-align: center;
  text-decoration: none #D1D5DB solid;
  text-decoration-thickness: auto;
  box-shadow: 0 2px 4px 0 rgba(0, 0, 0, 0.1), 0 2px 3px 0 rgba(0, 0, 0, 0.06);
  cursor: pointer;
  user-select: none;
  -webkit-user-select: none;
  touch-action: manipulation;
}

.button-style:hover {
  background-color: rgb(249,250,251);
}

.button-style:focus {
  outline: 2px solid transparent;
  outline-offset: 2px;
}

.button-style:focus-visible {
  box-shadow: none;
}
</style>
