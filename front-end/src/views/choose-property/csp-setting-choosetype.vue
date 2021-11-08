<template>
    <div>
        <div id="lco-header">
            <p>Contract-Specifc Property Setting - Choose Types</p>
        </div>
        <div id="lco-content">
            <div id="lcoc-description">
                <p>Please choose your type of Contract-Specifc Property:</p>
                <ul>
                    <li>Template: You will design the property by using our template.</li>
                    <li>Non-template: You will design the property by your own.</li>
                </ul>
            </div>
            <div id="ssc-button">
                <button class="button-style" role="button" @click="goTemp" :class="{'selected-button': getSelectedVulSubType == 'temp'}">Template</button>
                <button class="button-style" role="button" @click="goNonTemp" :class="{'selected-button': getSelectedVulSubType == 'nontemp'}">Non-template</button>
                <button class="button-style" role="button" @click="goPrePage">Back</button>
            </div>
        </div>
    </div>
</template>

<script>
export default({
    data() {
        return {
            selected_vul: {}
        }
    },
    mounted(){
        this.selected_vul = this.$store.getters["data/GetSelectedVulnerability"]
    },
    computed:{
        getSelectedVulSubType(){
            return this.selected_vul.subtype
        }
    },
    methods: {
        goTemp(){
            if(this.selected_vul.subtype != 'temp'){
                this.selected_vul.subtype = 'temp'
                this.selected_vul.params = {}
                this.$store.commit("data/SetSelectedVulnerability",this.selected_vul)
            }
            this.$router.push({ name: "CSPPropertyTemp"});
        },
        goNonTemp(){
            if(this.selected_vul.subtype != 'nontemp'){
                this.selected_vul.subtype = 'nontemp'
                this.selected_vul.params = {}
                this.$store.commit("data/SetSelectedVulnerability",this.selected_vul)
            }
            this.$router.push({ name: "CSPSettingNonTemp"});
        },
        goPrePage(){
            this.$router.push({ name: "LtlCheckingOptions"});
        }
    }
})
</script>

<style scoped>
/* header */
#lco-header{
    text-align: center;
    font-size: 30px;
    font-weight: bold;
    margin-top: 40px;
    margin-bottom: 80px;
}
/* content */
#lco-content{
    width: 50%;
    margin: auto;
}
/* Button */
#ssc-button{
    width: 100%;
    height: 80px;
    margin: auto;
    margin-top: 40px;
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

.selected-button{
    background-color: #aed7f8;
}
</style>
