<template>
  <div>
      <h1>Choose Element Of The Smart Contract</h1>
      <button @click="routing('next')">Next</button>
      <button @click="routing('back')">Back</button>
  </div>
</template>
<script>
export default {
    methods:{
        routing(param){
            if(param=='next'){
                this.$router.push({name:"VulSummary"})
            }
            if(param=='back'){
                this.$router.push({name:"LTLCheckOption"})
            }
        }
    }
}
</script>

<style>

</style>